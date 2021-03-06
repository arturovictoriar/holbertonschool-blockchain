#include "hblk_crypto.h"

/**
 * sha256 - hash a string using sha256
 * @s: string to be hash
 * @len: len of the string
 * @digest: memory to store the hash digest
 * Return: the hash digest, otherwise NULL
 */
uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH])
{
	/*SHA_CTX structure*/
	SHA256_CTX context;

	/*Initialize a SHA_CTX structure.*/
	if (!SHA256_Init(&context))
		return (NULL);

	/*
	 *Can be called repeatedly with chunks of the message
	 *to be hashed (len bytes at data)
	 */
	if (!SHA256_Update(&context, (unsigned char *) s, len))
		return (NULL);

	/*
	 *Place the message digest in digest,
	 *which must have space for SHA_DIGEST_LENGTH == 20 bytes of output,
	 *and erases the SHA_CTX structure.
	 */
	if (!SHA256_Final(digest, &context))
		return (NULL);

	return (digest);
}
