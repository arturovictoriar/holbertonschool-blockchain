#include "transaction.h"

/**
 * transaction_destroy - deallocates a transaction structure
 * @transaction: points to the transaction to delete
 * Return: Nothing
 */
void transaction_destroy(transaction_t *transaction)
{
	if (!transaction)
	{
		return;
	}

	llist_destroy(transaction->inputs, 1, free);
	llist_destroy(transaction->outputs, 1, free);

	free(transaction);
}
