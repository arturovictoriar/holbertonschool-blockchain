#include "transaction.h"

/**
 * is_empty - checks if buffer memory is all 0
 * @buf: the buffer to check
 * @size: size of buffer
 * Return: 1 if empty else 0
 */
int is_empty(uint8_t *buf, size_t size)
{
	return (buf[0] == 0 && memcmp(buf, buf + 1, size - 1) == 0);
}

/**
 * coinbase_is_valid - validates coinbase tx
 * @coinbase: the tx to validate
 * @block_index: index of block containing tx
 * Return: 1 if valid else 0
 */
int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	uint8_t hash[SHA256_DIGEST_LENGTH];
	tx_in_t *txi;
	tx_out_t *txo;

	if (coinbase == NULL)
	{
		return (0);
	}
	if (transaction_hash(coinbase, hash) == NULL ||
		memcmp(coinbase->id, hash, SHA256_DIGEST_LENGTH))
	{
		return (0);
	}
	if (llist_size(coinbase->inputs) != 1 ||
		llist_size(coinbase->outputs) != 1)
	{
		return (0);
	}
	txi = llist_get_node_at(coinbase->inputs, 0);
	txo = llist_get_node_at(coinbase->outputs, 0);
	if (memcmp(txi->tx_out_hash, &block_index, 4))
	{
		return (0);
	}
	if (is_empty(txi->block_hash, sizeof(txi->block_hash)) == 0 ||
		is_empty(txi->tx_id, sizeof(txi->tx_id)) == 0 ||
		is_empty((uint8_t *)&txi->sig, sizeof(txi->sig)) == 0)
	{
		return (0);
	}
	if (txo->amount != COINBASE_AMOUNT)
	{
		return (0);
	}
	return (1);
}
