#include "transaction.h"

/**
 * match_unspent - finds unspent to match txi
 * @node: utxo
 * @arg: txi struct
 * Return: 0 if continue else 1
 */
int match_unspent(llist_node_t node, void *arg)
{
	unspent_tx_out_t *utxo = node;
	tx_in_t *txi = arg;

	if (memcmp(txi->tx_out_hash, utxo->out.hash, SHA256_DIGEST_LENGTH) == 0)
	{
		return (1);
	}
	return (0);
}

/**
 * check_inputs - validates each input
 * @node: txi
 * @idx: index of node
 * @arg: visitor
 * Return: 0 if continue else 1
 */
int check_inputs(llist_node_t node, unsigned int idx, void *arg)
{
	tx_in_t *txi = node;
	validation_vistor_t *visitor = arg;
	unspent_tx_out_t *utxo =
		llist_find_node(visitor->all_unspent, match_unspent, txi);
	EC_KEY *key = NULL;

	(void) idx;

	if (utxo == NULL)
	{
		dprintf(2, "check_inputs: utxo NULL\n");
		visitor->valid = 0;
		return (1);
	}
	key = ec_from_pub(utxo->out.pub);
	if (key == NULL ||
			ec_verify(key, visitor->tx->id, SHA256_DIGEST_LENGTH, &txi->sig) == 0)
	{
		dprintf(2, "check_inputs: key error\n");
		visitor->valid = 0;
		return (EC_KEY_free(key), 1);
	}
	EC_KEY_free(key);
	visitor->in_amount += utxo->out.amount;
	return (0);
}

/**
 * check_outputs - validates each input
 * @node: tx_out_t *
 * @idx: index of node
 * @arg: visitor
 * Return: 0 if continue else 1
 */
int check_outputs(llist_node_t node, unsigned int idx, void *arg)
{
	tx_out_t *txo = node;
	validation_vistor_t *visitor = arg;

	(void) idx;

	visitor->out_amount += txo->amount;
	return (0);
}

/**
 * transaction_is_valid - checks whether a transaction is valid
 * @transaction: points to the transaction to verify
 * @all_unspent: is the list of all unspent transaction outputs to date
 * Return: 1 if valid else 0
 */
int transaction_is_valid(
		transaction_t const *transaction,
		llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	validation_vistor_t visitor = {0};

	if (transaction == NULL || all_unspent == NULL)
	{
		return (0);
	}
	visitor.tx = transaction;
	visitor.all_unspent = all_unspent;
	visitor.valid = 1;
	if (transaction_hash(transaction, hash_buf) == NULL)
	{
		return (0);
	}
	if (memcmp(transaction->id, hash_buf, SHA256_DIGEST_LENGTH))
	{
		return (0);
	}
	if (llist_for_each(transaction->inputs, check_inputs, &visitor) ||
			!visitor.valid)
	{
		return (0);
	}
	if (llist_for_each(transaction->outputs, check_outputs, &visitor) ||
			visitor.in_amount != visitor.out_amount || visitor.in_amount == 0)
	{
		return (0);
	}
	return (1);
}
