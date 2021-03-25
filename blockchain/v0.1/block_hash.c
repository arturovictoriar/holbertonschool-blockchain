#include "blockchain.h"

/**
 * block_hash - computes the hash of a Block
 * @block: points to the Block to be hashed
 * @hash_buf: memory to store the hash
 * Return: hash of a given Block
 */
uint8_t *block_hash(block_t const *block,
		uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t len = 0;

	len = sizeof(block->info) + block->data.len;

	sha256((int8_t const *) &(block->info), len, hash_buf);
	return (hash_buf);
}
