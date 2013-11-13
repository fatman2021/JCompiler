/*
 * test_hash_table.c : read in a file containing id numbers and names and add them to the hash table
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"

#define NUMBER_OF_HASH_BUCKETS  23
#define MAX_LINE_LENGTH         256

int count;

void count_s (int *id, char *name)
{
  if (name[0] == 's' || name[0] == 'S') ++count;
}

int hash_function (int *id_no)
{
  return ( (*id_no) % NUMBER_OF_HASH_BUCKETS );
}

int eq (int *id1, int *id2)
{
  return ( (*id1 == *id2) ? 1 : 0 );
}

void print_function (int *id, char *name)
{
  printf ("   %06d  :  %s\n", *id, name);
}

void add_entry (hash_table_ptr hash_table, int id_no, char *name)
{
  int *id_ptr;
  char *name_ptr;

  id_ptr = malloc (sizeof(int));
  name_ptr = malloc (strlen(name) + 1);

  if (id_ptr == NULL || name_ptr == NULL) {
    printf ("Malloc failed\n");
    exit (1);
  }

  *id_ptr = id_no;
  strcpy(name_ptr, name);
  
  add (hash_table, id_ptr, name_ptr);
}

int main ()
{
  FILE *theFile;
  int id_no;
  char input[MAX_LINE_LENGTH];
  char name[MAX_LINE_LENGTH];
  hash_table_ptr hash_table;
  char *name_ptr;


  // Initialize the hash table
  hash_table = init_hash_table (hash_function, eq, NUMBER_OF_HASH_BUCKETS);

  if (hash_table == NULL) {
    printf ("Error initializing hash table\n");
    exit (1);
  }

  // Read the data from the file
  theFile = fopen ("names.txt", "r");

  if (!theFile) {
    printf ("names.txt not found\n");
    exit (1);
  }

  // read a line from the file
  while (fgets (input, MAX_LINE_LENGTH, theFile)) {  
    if (sscanf(input, "%d %s", &id_no, name) == 2) {
      add_entry (hash_table, id_no, name);
    }
  }

  count = 0;
  map (hash_table, count_s);

  printf ("Count = %d\n\n", count);


  // Main loop
  while (1) {
    printf ("Enter command : lookup id, add id name, print, quit : \n");

    fgets (input, MAX_LINE_LENGTH, stdin);
    
    if (sscanf (input, "lookup %d", &id_no) == 1) {
      name_ptr = lookup (hash_table, &id_no);
      if (name_ptr)
	print_function (&id_no, name_ptr);
    }

    if (sscanf (input, "add %d %s", &id_no, name) == 2) {
      add_entry (hash_table, id_no, name);
    }

    if (input[0] == 'p') {
      map (hash_table, print_function);
    }

    if (input[0] == 'q') {
      exit(0);
    }

  }

  return 0;
}
