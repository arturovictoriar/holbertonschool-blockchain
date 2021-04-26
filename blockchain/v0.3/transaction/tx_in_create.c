#include "transaction.h"

/**
 * tx_in_create - allocates and initializes a transaction input structure
 * @unspent: points to the unspent transaction output to be
 * converted to a transaction input
 * Return: a pointer to the created transaction input upon success,
 * or NULL upon failure
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *new_tx_input = NULL;

	if (unspent == NULL)
	{
		return (NULL);
	}
	new_tx_input =  calloc(1, sizeof(tx_in_t));

	if (!new_tx_input)
	{
		return (NULL);
	}
	memcpy(new_tx_input->block_hash, unspent->block_hash,
			sizeof(new_tx_input->block_hash));
	memcpy(new_tx_input->tx_id, unspent->tx_id,
			sizeof(new_tx_input->tx_id));
	memcpy(new_tx_input->tx_out_hash, unspent->out.hash,
			sizeof(new_tx_input->tx_out_hash));

	return (new_tx_input);
}
