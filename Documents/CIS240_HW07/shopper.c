#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_LINE_LENGTH 200

/*
 * update: Updates the list of items to include the new item.
 * If the item is already in the list, update its value.
 * Otherwise, create a new element and add it to the list.
 * If the count of an element reaches 0, delete that element
 * from the list.
 * Returns: The new first_elt of the list (which could be the 
   old first element as well).
 */

 // WILL PROBABLY HAVE TONS OF POINTER ISSUES HERE
list_elt *update (list_elt *first_elt, char *name, int count) {
	list_elt *elt = lookup(first_elt, name); // don't know if pointers will work in this case(?)
	
	// If element is already in the list, update value
	if (elt != NULL) {
		elt->number = elt->number + count;
		// Delete from list if count reaches 0
		if (elt->number <= 0) {
			return delete(first_elt, elt);
		}
	}
	else {
		// Only add element if count is greater than zero
		if (count > 0){
			return addNew(first_elt, name, count);
		}
	}
	return first_elt;
}

// Prints elements in list in order
void print_list (list_elt *first_elt)
{
  list_elt *elt = first_elt;

  while (elt) {
    printf ("%s\t%d\n", elt->name, elt->number);
    elt = elt->next;
  }
}


/* Reads the file stream and creates an order according to 
 * its input. All names of items will be in all caps. No item
 * should have a zero or negative count associated with it.
 * Returns: pointer to first element of order list. If file is
 * null or empty, will return null. Will throw error if file
 * is formatted incorrectly.
 */
list_elt *makeOrder(FILE *stream) {

	char *name;
	int count;
	list_elt *first_elt;

	// MIGHT WANT TO THROW SOME SORT OF ERROR
	if(stream==NULL) {
		return NULL;
	}

	// Initialize first element to NULL
	first_elt = NULL;

	while(feof(stream) != 1) {
		fscanf(stream, "%s %d", name, count);
		allCaps(name);
		first_elt = update(first_elt, name, count);
	}
	return first_elt;

}

// Function to convert string to all caps
 void allCaps(char *str) {
	char *i = str;
	char c = *i;
	while(c != NULL) {
		c = c.toupper();
		i++;
		c = *i;
	}
}


int main() {

	char *fileName;
	FILE *theFile;

	scanf("shopper %s", fileName);
	theFile = fopen(*fileName, "r");
	print_list(makeOrder(theFile));
	fclose(theFile);

	return 0;

}