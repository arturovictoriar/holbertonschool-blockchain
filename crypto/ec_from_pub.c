#include "hblk_crypto.h"

/**
 * ec_from_pub - creates an EC_KEY structure given a public key
 * @pub: contains the public key to be converted
 * Return: EC_KEY structure
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key = NULL;
	const EC_GROUP *group = NULL;
	EC_POINT *point = NULL;

	/*Create a key from the curve name*/
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	/*Get the group of the key*/
	group = EC_KEY_get0_group(key);
	/*Create a point*/
	point = EC_POINT_new(group);
	if (point == NULL)
	{
		EC_KEY_free(key);
		return (NULL);
	}

	/*creates an EC_KEY structure given a public key*/
	if (!EC_POINT_oct2point(group, point, pub, EC_PUB_LEN, NULL) ||
			!EC_KEY_set_public_key(key, (const EC_POINT *) point))
	{
		EC_KEY_free(key);
		EC_POINT_free(point);
		return (NULL);
	}


	EC_POINT_free(point);
	return (key);
}
