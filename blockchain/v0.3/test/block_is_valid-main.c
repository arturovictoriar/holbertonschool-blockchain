#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "blockchain.h"

void _blockchain_print_brief(blockchain_t const *blockchain);
void _print_hex_buffer(uint8_t const *buf, size_t len);

static block_t *_add_block(blockchain_t *blockchain, block_t const *prev,
	char const *data, EC_KEY *miner)
{
	block_t *block;
	transaction_t *coinbase;

    printf("Addblock 1\n");
	block = block_create(prev, (int8_t *)data, (uint32_t)strlen(data));
	block->info.difficulty = 20;

	printf("Addblock 2\n");
    coinbase = coinbase_create(miner, block->info.index);
	llist_add_node(block->transactions, coinbase, ADD_NODE_FRONT);

	printf("Addblock 3\n");
    block_mine(block);
    printf("Addblock 4\n");
    block_is_valid(block, prev, blockchain->unspent);
    printf("Addblock 5\n");

	if (block_is_valid(block, prev, blockchain->unspent) == 0)
	{
        printf("Addblock 4\n");
		printf("Block mined: [%u] ", block->info.difficulty);
		_print_hex_buffer(block->hash, SHA256_DIGEST_LENGTH);
		printf("\n");
		llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
	}
	else
	{
		fprintf(stderr, "Invalid Block with index: %u\n",
			block->info.index);
	}

	return (block);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
		blockchain_t *blockchain;
	block_t *block;
	EC_KEY *miner;

    setbuf(stdout, NULL);
    printf("1\n");
	miner = ec_create();
    printf("2 [%p]\n", (void *)miner);
	blockchain = blockchain_create();

    printf("3 [%p]\n", (void *)blockchain);
	block = llist_get_head(blockchain->chain);
    printf("4 [%p]\n", (void *)block);
	block = _add_block(blockchain, block, "Holberton", miner);
    printf("5\n");
	block = _add_block(blockchain, block, "School", miner);

    printf("6\n");
	blockchain_destroy(blockchain);
    printf("7\n");
	EC_KEY_free(miner);
    printf("8\n");
	return (EXIT_SUCCESS);
}
