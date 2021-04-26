#include "transaction.h"

/**
 * tx_in_sign - signs a transaction input, given the transaction id it is from
 * @in: points to the transaction input structure to sign
 * @tx_id: contains the ID (hash) of the transaction the transaction
 * input to sign is stored in
 * @sender: contains the private key of the receiver of the coins contained
 * in the transaction output referenced by the transaction input
 * @all_unspent: is the list of all unspent transaction outputs to date
 * Return: a pointer to the resulting signature structure upon success,
 * or NULL upon failure
 */
sig_t *tx_in_sign(
		tx_in_t *in,
		uint8_t const tx_id[SHA256_DIGEST_LENGTH],
		EC_KEY const *sender,
		llist_t *all_unspent)
{
	uint8_t pub[EC_PUB_LEN] = {0};
	ssize_t i = 0;
	unspent_tx_out_t *UTXO_output = NULL;

	for (i = 0; i < llist_size(all_unspent); i++)
	{
		UTXO_output = llist_get_node_at(all_unspent, i);

		if (!memcmp(in->tx_out_hash, UTXO_output->out.hash, SHA256_DIGEST_LENGTH))
		{
			break;
		}
		UTXO_output = NULL;
	}

	if (UTXO_output == NULL ||
			ec_to_pub(sender, pub) == NULL ||
			memcmp(pub, UTXO_output->out.pub, EC_PUB_LEN))
	{
		return (NULL);
	}
	if (ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &in->sig) == NULL)
	{
		return (NULL);
	}

	return (&in->sig);
}
