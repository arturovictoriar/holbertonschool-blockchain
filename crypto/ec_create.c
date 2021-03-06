#include "hblk_crypto.h"

/**
* ec_create - create a new EC key pair
* Return: a struct representation of a new EC key pair, NULL otherwise
*/
EC_KEY *ec_create(void)
{
	EC_KEY *my_ecc_pair  = NULL;

	/*Set the curve to use when generate the EC key pair*/
	my_ecc_pair = EC_KEY_new_by_curve_name(EC_CURVE);

	/*Generate the EC key pair*/
	if (!(EC_KEY_generate_key(my_ecc_pair)))
		return (NULL);
	return (my_ecc_pair);
}
