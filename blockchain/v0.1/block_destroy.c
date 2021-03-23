#include "blockchain.h"

/**
* block_destroy - deallocate the memory of a block
* @block: representative structure of a block
* Return: Nothing
*/
void block_destroy(block_t *block)
{
	free(block);
}
