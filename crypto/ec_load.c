#include "hblk_crypto.h"

/**
 * ec_load - loads an EC key pair from the disk.
 * @folder: path to the folder in which to save the keys
 * Return: return a pointer to the created EC key pair
 * upon success, or NULL upon failure
 */
EC_KEY *ec_load(char const *folder)
{
	FILE *fp;
	char path[256] = {0};
	EC_KEY *key = NULL;

	if (!folder)
		return (0);

	/*Create the complete path to read the public key*/
	sprintf(path, "%s/" PUB_FILENAME, folder);
	/*Open a file descriptor to read the public key*/
	fp = fopen(path, "r");
	if (!fp)
	{
		EC_KEY_free(key);
		return (0);
	}
	/*Read the public key in the given file and store it in key*/
	if (!PEM_read_EC_PUBKEY(fp, &key, NULL, NULL))
	{
		EC_KEY_free(key);
		fclose(fp);
		return (0);
	}
	fclose(fp);
	/*Create the complete path to read the private key*/
	sprintf(path, "%s/" PRI_FILENAME, folder);
	/*Open a file descriptor to read the private key*/
	fp = fopen(path, "r");
	if (!fp)
		return (0);
	/*read the private key in the given file and store it in key*/
	if (!PEM_read_ECPrivateKey(fp, &key, NULL, NULL))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);
	return (key);
}
