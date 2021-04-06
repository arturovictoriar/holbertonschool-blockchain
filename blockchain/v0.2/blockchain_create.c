#include "blockchain.h"

#define GENESIS_INDEX 0
#define GENESIS_DIFFICULTY 0
#define GENESIS_TIMESTAMP 1537578000
#define GENESIS_NONCE 0
#define GENESIS_PREV_HASH 0
#define GENESIS_LEN 16
#define GENESIS_BUFFER "Holberton School"
#define GENESIS_HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"

/**
* free_block_chain - free memory allocate from blockchain_create function
* @new_block: block which store data
* @new_block_chain: block chain structure
* @chain: linked list of block
* Return: Nothing
*/
void free_block_chain(block_t *new_block, blockchain_t *new_block_chain,
		llist_t *chain)
{
	free(new_block_chain);
	llist_destroy(chain, 1, NULL);
	free(new_block);
}

/**
* blockchain_create - create a block chain structure
* Return: a new blockchain structure
*/
blockchain_t *blockchain_create(void)
{
	block_t *new_block = NULL;
	blockchain_t *new_block_chain = NULL;
	llist_t *chain = NULL;
	int i = 0;

	/*Allocate memory for create a block chain*/
	new_block_chain = calloc(1, sizeof(blockchain_t));
	chain = llist_create(MT_SUPPORT_TRUE);
	new_block = calloc(1, sizeof(block_t));
	if (new_block_chain == NULL || chain == NULL || new_block == NULL)
	{
		free_block_chain(new_block, new_block_chain, chain);
		return (NULL);
	}
	/*Initialize the new block*/
	(new_block->info).index = GENESIS_INDEX;
	(new_block->info).difficulty = GENESIS_DIFFICULTY;
	(new_block->info).timestamp = GENESIS_TIMESTAMP;
	(new_block->info).nonce = GENESIS_NONCE;

	for (i = 0; i < 32; i++)
		((new_block->info).prev_hash)[i] = GENESIS_PREV_HASH;

	new_block->data.len = GENESIS_LEN;
	memcpy(new_block->data.buffer, GENESIS_BUFFER, GENESIS_LEN);
	memcpy(new_block->hash, GENESIS_HASH, SHA256_DIGEST_LENGTH);
	/*Add the new block into the chain of blocks*/
	if (llist_add_node(chain, new_block, ADD_NODE_FRONT) != 0)
	{
		free_block_chain(new_block, new_block_chain, chain);
		return (NULL);
	}
	new_block_chain->chain = chain;

	return (new_block_chain);
}
