#include "hblk_crypto.h"

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key = NULL;
	BN_CTX *ctx = NULL;
	const EC_GROUP *group = NULL;
	EC_POINT *point = NULL;

	key = EC_KEY_new_by_curve_name(EC_CURVE);
	/*Initialize a temporaly Big Number*/
	ctx = BN_CTX_new();
	/*Get the curve of the key*/
	group = EC_KEY_get0_group(key);
	point = EC_POINT_new(group);

	EC_POINT_oct2point(group, point, (const unsigned char *) pub, EC_PUB_LEN, ctx);
	EC_KEY_set_public_key(key, (const EC_POINT *) point);

	return (key);
}
