#include "hblk_crypto.h"

/**
 * ec_to_pub - extracts the public key from an EC_KEY opaque structure
 * @key: pointer to the EC_KEY structure
 * @pub: address at which to store the extracted public key
 * Return: public key from an EC_KEY opaque structure, NULL otherwise
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	BN_CTX *ctx = NULL;
	const EC_GROUP *group = NULL;
	const EC_POINT *point = NULL;

	if (key == NULL)
		return (NULL);
	/*Initialize a temporaly Big Number*/
	ctx = BN_CTX_new();
	/*Get the curve of the key*/
	group = EC_KEY_get0_group(key);
	/*Get the point of the key curve*/
	point = EC_KEY_get0_public_key(key);
	/*Set the public key in the pub variable (extract the public key in octact)*/
	EC_POINT_point2oct(group, point,
			(point_conversion_form_t) POINT_CONVERSION_UNCOMPRESSED,
			(unsigned char *) pub, EC_PUB_LEN, ctx);
	/*Deallocate the big number*/
	BN_CTX_free(ctx);

	return (pub);
}
