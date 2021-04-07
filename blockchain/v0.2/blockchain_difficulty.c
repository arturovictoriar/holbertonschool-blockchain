#include "blockchain.h"

/**
 * blockchain_difficulty - compute the difficulty to assign to a
 * potential next Block in the Blockchain.
 * @blockchain: points to the Blockchain to analyze
 * Return: the difficulty to be assigned to a potential next Block in
 * the Blockchain
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *last_block, *last_adjusted_block;
	uint64_t expected_time, actual_time;

	if (!blockchain)
		return (0);
	/*Get the last block in the chain*/
	last_block = llist_get_tail(blockchain->chain);
	if (!last_block)
		return (0);
	/*
	 *If the last block is genesis or multiple or difficulty ad in return
	 *its difficulty
	 */
	if (last_block->info.index == 0 ||
			last_block->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL)
		return (last_block->info.difficulty);
	/*Retrieve the last Block for which an adjustment was made*/
	last_adjusted_block = llist_get_node_at(blockchain->chain,
			last_block->info.index + 1 - DIFFICULTY_ADJUSTMENT_INTERVAL);
	/*
	 *Compute the expected elapsed time between the two Blocks and the actual
	 *elapsed time
	 */
	expected_time = DIFFICULTY_ADJUSTMENT_INTERVAL * BLOCK_GENERATION_INTERVAL;
	actual_time = last_block->info.timestamp -
		last_adjusted_block->info.timestamp;
	/*
	 *The difficulty must be incremented if the elapsed time is lower than half
	 *the expected elapsed time
	 *The difficulty must be decremented if the elapsed time is greater than twice
	 *the expected elapsed time
	 *The difficulty should not change otherwise
	 */
	if ((actual_time * 2) < expected_time)
		return (last_block->info.difficulty + 1);
	else if (actual_time > (2 * expected_time))
		return (last_block->info.difficulty > 0 ?
				last_block->info.difficulty - 1 : 0);
	return (last_block->info.difficulty);
}
