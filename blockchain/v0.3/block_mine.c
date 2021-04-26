#include "blockchain.h"

/**
 * block_mine - mines a block with requisite difficulty
 * @block: pointer to block to mine
 */
void block_mine(block_t *block)
{
	uint64_t nonce = 0;

	do {
		block->info.nonce = nonce;
		block_hash(block, block->hash);
		nonce++;
	} while (!hash_matches_difficulty(block->hash, block->info.difficulty));
}
