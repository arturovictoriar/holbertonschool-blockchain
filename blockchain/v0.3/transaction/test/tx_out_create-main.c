#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "hblk_crypto.h"
#include "transaction.h"

void _print_hex_buffer(uint8_t const *buf, size_t len);

/**
 * _tx_out_print - Print a transaction output
 *
 * @out: Pointer to the transaction output to print
 */
static void _tx_out_print(tx_out_t const *out)
{
	if (!out)
		return;

	printf("Transaction output: {\n");

	printf("\tamount: %u,\n", out->amount);
	printf("\tpub: ");
	_print_hex_buffer(out->pub, sizeof(out->pub));
	printf(",\n");
	printf("\thash: ");
	_print_hex_buffer(out->hash, sizeof(out->hash));
	printf("\n");

	printf("}\n");
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	
	tx_out_t *out;
	const uint8_t *str = (unsigned char *)"\x04\x28\x35\x90\x8c\x04\xf2\xb9\xa7\x51\x53\xda\x5e\x4a\x46\x60\x22\x2a\x59\x70\xcf\xdd\xa9\x2a\x1a\xbb\x38\xc1\x40\xa2\xd6\x5f\x7e\xf6\xe5\x56\x63\x28\x4f\x8a\x5b\xbc\x7b\x6e\xb8\xe7\x8f\x0b\x98\xcd\x2b\x27\x90\xdf\x2b\x63\xc6\x55\x1f\x7c\xb6\xa9\xfa\x9a\xeb";
	

	
	out = tx_out_create(972, str);
	_tx_out_print(out);

	free(out);
	

	return (EXIT_SUCCESS);
}
