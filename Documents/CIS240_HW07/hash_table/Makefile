
CC=clang

hash_table.o : hash_table.c hash_table.h
	$(CC) -c hash_table.c

test_hash_table : test_hash_table.c hash_table.o hash_table.h
	$(CC) -o test_hash_table test_hash_table.c hash_table.o
