#include "blockchain.h"

/**
 * blockchain_destroy - deallocte a complete blockchain
 * @blockchain: reprensentative structure of a blockchain
 * Return: Nothing
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	block_t *node = NULL;

	for (node = llist_pop(blockchain->chain); node != NULL;
			node = llist_pop(blockchain->chain))
		block_destroy(node);
	llist_destroy(blockchain->chain, 0, NULL);
	free(blockchain);
}
