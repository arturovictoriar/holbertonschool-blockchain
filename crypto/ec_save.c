#include "hblk_crypto.h"

/**
* ec_save - save an existing EC key pair on the disk.
* @key: key points to the EC key pair to be saved on disk
* @folder: path to the folder in which to save the keys
* Return: return 1 or 0 upon success or failure
*/
int ec_save(EC_KEY *key, char const *folder)
{
	FILE *fp;
	char path[256] = {0};

	if (key == NULL || folder == NULL)
		return (0);

	/*Create a folder if not exist*/
	mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	/*Create the complete path to store the private key*/
	sprintf(path, "%s/" PRI_FILENAME, folder);
	/*Open a file descriptor to store the private key*/
	fp = fopen(path, "w");
	if (!fp)
		return (0);
	/*write the private key in the given file*/
	if (!PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);
	/*Create the complete path to store the public key*/
	sprintf(path, "%s/" PUB_FILENAME, folder);
	/*Open a file descriptor to store the public key*/
	fp = fopen(path, "w");
	if (!fp)
		return (0);
	/*write the public key in the given file*/
	if (!PEM_write_EC_PUBKEY(fp, key))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);

	return (1);
}
