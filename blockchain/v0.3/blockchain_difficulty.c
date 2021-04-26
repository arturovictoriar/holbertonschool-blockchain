#include "blockchain.h"

/**
 * blockchain_difficulty - adjust difficulty for next block of blockchain
 * @blockchain: pointer to working blockchain
 * Return: adjusted difficulty
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *last_block, *adjusted_block;
	uint64_t expected_time, actual_time;

	if (!blockchain)
		return (0);
	last_block = llist_get_tail(blockchain->chain);
	if (!last_block)
		return (0);
	if (last_block->info.index == 0 ||
		last_block->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL)
		return (last_block->info.difficulty);
	adjusted_block = llist_get_node_at(blockchain->chain,
		last_block->info.index + 1 - DIFFICULTY_ADJUSTMENT_INTERVAL);
	expected_time = DIFFICULTY_ADJUSTMENT_INTERVAL * BLOCK_GENERATION_INTERVAL;
	actual_time = last_block->info.timestamp - adjusted_block->info.timestamp;
	if (actual_time * 2 < expected_time)
		return (last_block->info.difficulty + 1);
	else if (actual_time > 2 * expected_time)
		return (last_block->info.difficulty > 0 ?
			last_block->info.difficulty - 1 : 0);
	return (last_block->info.difficulty);
}
