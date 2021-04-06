#include "blockchain.h"

/**
 * hash_matches_difficulty - check whether a given hash matches
 * a given difficulty
 * @hash: the hash to check
 * @difficulty: is the minimum difficulty the hash should match
 * Return: return 1 if the difficulty is respected, or 0 otherwise
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
		uint32_t difficulty)
{
	int i = 0, bit = 0, one_found = 0, copy_difficulty = 0;

	copy_difficulty = difficulty;
	/*Iterate every byte*/
	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		/*Check every bit from left to right*/
		for (bit = 7; bit >= 0; bit--)
		{
			/*If we foudn something different to zero stop of iterate*/
			if (hash[i] & 1 << bit)
			{
				one_found = 1;
				break;
			}
			copy_difficulty--;
		}
		if (one_found == 1)
		{
			break;
		}
	}
	/*If the zeros from left to right is greater than difficulty return 1else0*/
	if (copy_difficulty <= 0)
	{
		return (1);
	}
	return (0);
}

/**
 * block_is_valid - verifies that a Block is valid
 * @block: points to the Block to check
 * @prev_block: points to the previous Block in the Blockchain
 * Return: 0 on sucess, 1 otherwise
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t hash_buffer[SHA256_DIGEST_LENGTH] = {0};
	block_t GENESIS = GENESIS_BLOCK;

	/*
	 *block should not be NULL and prev_block should be
	 *NULL ONLY if block‘s index is 0
	 */
	if (!block || (!prev_block && block->info.index != 0))
		return (1);
	/*
	 *If the Block index is 0, the Block should
	 *match the Genesis Block described in the first task
	 */
	if (block->info.index == 0)
		return (memcmp(block, &GENESIS, sizeof(GENESIS)));
	/*The Blocks index must be the previous Blocks index, plus 1*/
	if (block->info.index != prev_block->info.index + 1)
		return (1);
	/*The computed hash of the previous block must match the one it stores*/
	if (!block_hash(prev_block, hash_buffer) ||
			memcmp(hash_buffer, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	/*
	 *The computed hash of the previous block must match the reference one
	 *stored in block
	 */
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);
	/*The computed hash of the Block must match the one it stores*/
	if (!block_hash(block, hash_buffer) ||
			memcmp(hash_buffer, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	/*The Block data length must not exceed BLOCKCHAIN_DATA_MAX*/
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);
	/*The hash matches a given difficulty*/
	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (1);
	return (0);
}
