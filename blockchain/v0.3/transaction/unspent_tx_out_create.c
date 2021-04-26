#include "transaction.h"

/**
 * unspent_tx_out_create - allocates and initializes an unspent
 * transaction output structure
 * @block_hash: contains the hash of the Block where
 * the referenced transaction output is located
 * @tx_id: contains the hash of a transaction in the Block block_hash,
 * where the referenced transaction output is located
 * @out: points to the referenced transaction output
 * Return:n a pointer to the created unspent transaction output upon success,
 * or NULL upon failure
 */
unspent_tx_out_t *unspent_tx_out_create(
		uint8_t block_hash[SHA256_DIGEST_LENGTH],
		uint8_t tx_id[SHA256_DIGEST_LENGTH],
		tx_out_t const *out)
{
	unspent_tx_out_t *new_UTXO_output = NULL;

	new_UTXO_output = calloc(1, sizeof(unspent_tx_out_t));
	if (new_UTXO_output == NULL)
	{
		return (NULL);
	}

	memcpy(new_UTXO_output->block_hash, block_hash,
			sizeof(new_UTXO_output->block_hash));
	memcpy(new_UTXO_output->tx_id, tx_id, sizeof(new_UTXO_output->tx_id));
	memcpy(&new_UTXO_output->out, out, sizeof(new_UTXO_output->out));

	return (new_UTXO_output);
}
