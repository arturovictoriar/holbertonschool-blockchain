#include "blockchain.h"

#define GENESIS_TIMESTAMP 1537578000
#define GENESIS_DATA "Holberton School"
#define GENESIS_DATA_LEN 16
#define GENESIS_HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"

/**
 * blockchain_create - creates a genesis blockchain
 * Return: pointer to new blockchain or NULL on error
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *chain = calloc(1, sizeof(*chain));
	block_t *block = calloc(1, sizeof(*block));
	llist_t *list = llist_create(MT_SUPPORT_TRUE);
	llist_t *unspent = llist_create(MT_SUPPORT_TRUE);

	if (!chain || !block || !list || !unspent)
	{
		free(chain), free(block), llist_destroy(list, 1, NULL);
		llist_destroy(unspent, 1, NULL);
		return (NULL);
	}

	block->info.timestamp = GENESIS_TIMESTAMP;
	memcpy(&(block->data.buffer), GENESIS_DATA, GENESIS_DATA_LEN);
	block->data.len = GENESIS_DATA_LEN;
	memcpy(&(block->hash), GENESIS_HASH, SHA256_DIGEST_LENGTH);

	if (llist_add_node(list, block, ADD_NODE_FRONT))
	{
		free(chain), free(block), llist_destroy(list, 1, NULL);
		return (NULL);
	}
	chain->chain = list;
	chain->unspent = unspent;
	return (chain);
}
