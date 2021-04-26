#include "blockchain.h"

#define CLEAN_UP (free(chain), close(fd))
#define CLEAN_UP_BLOCKS (free(block), llist_destroy(list, 1, NULL))
#define CHECK_ENDIAN(x) (endianness ? SWAPENDIAN(x) : (void)0)
/**
 * blockchain_deserialize - deserializes blockchain from file
 * @path: path to serialized blockchain file
 * Return: pointer to deserialized blockchain or null
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	int fd;
	blockchain_t *chain = NULL;
	uint8_t endianness;
	char buf[4096] = {0};
	uint32_t size;

	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, buf, strlen(HBLK_MAGIC)) != strlen(HBLK_MAGIC) ||
		strcmp(buf, HBLK_MAGIC))
		return (CLEAN_UP, NULL);
	buf[strlen(HBLK_VERSION)] = 0;
	if (read(fd, buf, strlen(HBLK_VERSION)) != strlen(HBLK_VERSION) ||
		strcmp(buf, HBLK_VERSION))
		return (CLEAN_UP, NULL);
	chain = calloc(1, sizeof(*chain));
	if (!chain)
		return (CLEAN_UP, NULL);
	if (read(fd, &endianness, 1) != 1)
		return (CLEAN_UP, NULL);
	endianness = endianness != _get_endianness();
	if (read(fd, &size, 4) != 4)
		return (CLEAN_UP, NULL);
	CHECK_ENDIAN(size);
	chain->chain = deserialize_blocks(fd, size, endianness);
	if (!chain)
		return (CLEAN_UP, NULL);
	return (close(fd), chain);
}

/**
 * deserialize_blocks - deserializes all the blocks in the file
 * @fd: open fd to save file
 * @size: number of blocks in the file
 * @endianness: if endianess needs switching
 * Return: pointer to list of blocks or NULL
 */
llist_t *deserialize_blocks(int fd, uint32_t size, uint8_t endianness)
{
	block_t *block;
	llist_t *list = llist_create(MT_SUPPORT_TRUE);
	uint32_t i = 0;

	if (!list)
		return (NULL);
	for (i = 0; i < size; i++)
	{
		block = calloc(1, sizeof(*block));
		if (!block)
			return (CLEAN_UP_BLOCKS, NULL);
		if (read(fd, &(block->info), sizeof(block->info)) != sizeof(block->info))
			return (CLEAN_UP_BLOCKS, NULL);
		CHECK_ENDIAN(block->info.index);
		CHECK_ENDIAN(block->info.difficulty);
		CHECK_ENDIAN(block->info.timestamp);
		CHECK_ENDIAN(block->info.nonce);
		if (read(fd, &(block->data.len), 4) != 4)
			return (CLEAN_UP_BLOCKS, NULL);
		CHECK_ENDIAN(block->data.len);
		if (read(fd, block->data.buffer, block->data.len) != block->data.len)
			return (CLEAN_UP_BLOCKS, NULL);
		if (read(fd, block->hash, SHA256_DIGEST_LENGTH) !=
			SHA256_DIGEST_LENGTH)
			return (CLEAN_UP_BLOCKS, NULL);
		if (llist_add_node(list, block, ADD_NODE_REAR))
			return (CLEAN_UP_BLOCKS, NULL);
	}
	return (list);
}
