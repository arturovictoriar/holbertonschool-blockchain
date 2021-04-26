#include "transaction.h"

/**
 * coinbase_create - create coinbase transaction
 * @receiver: contains the public key of the miner,
 * who will receive the coinbase coins
 * @block_index: is the index of the Block the coinbase
 * transaction will belong to
 * Return: pointer to the created transaction upon success,
 * or NULL upon failure
 */
transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index)
{
	transaction_t *tx = NULL;
	tx_out_t *txo = NULL;
	tx_in_t *txi = NULL;
	llist_t *inputs = NULL, *outputs = NULL;
	uint8_t pub[EC_PUB_LEN] = {0};

	if (receiver == NULL || ec_to_pub(receiver, pub) == NULL)
	{
		return (NULL);
	}
	tx = calloc(1, sizeof(*tx));
	txi = calloc(1, sizeof(*txi));
	txo = tx_out_create(COINBASE_AMOUNT, pub);
	inputs = llist_create(MT_SUPPORT_FALSE);
	outputs = llist_create(MT_SUPPORT_FALSE);
	if (!tx || !txi || !txo || !inputs || !outputs ||
		llist_add_node(inputs, txi, ADD_NODE_REAR) ||
		llist_add_node(outputs, txo, ADD_NODE_REAR))
	{
		return (free(tx), free(txi), free(txo), llist_destroy(inputs, 0, NULL),
			llist_destroy(outputs, 0, NULL), NULL);
	}
	memcpy(txi->tx_out_hash, &block_index, 4);
	tx->inputs = inputs;
	tx->outputs = outputs;
	if (!transaction_hash(tx, tx->id))
	{
		return (free(tx), free(txi), free(txo), llist_destroy(inputs, 0, NULL),
			llist_destroy(outputs, 0, NULL), NULL);
	}
	return (tx);
}
