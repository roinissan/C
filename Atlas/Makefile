Globe: Main.o Countries.o HashTable.o KeyValuePair.o LinkedList.o
	gcc Main.o Countries.o HashTable.o KeyValuePair.o LinkedList.o -o Globe

Main.o: Main.c
	gcc -c Main.c

Countries.o: Countries.c Countries.h Defs.h LinkedList.h Countries.h KeyValuePair.h HashTable.h
	gcc -c Countries.c

HashTable.o: HashTable.c HashTable.h LinkedList.h KeyValuePair.h
	gcc -c HashTable.c

KeyValuePair.o: KeyValuePair.c KeyValuePair.h
	gcc -c KeyValuePair.c

LinkedList.o: LinkedList.c LinkedList.h KeyValuePair.h
	gcc -c LinkedList.c

Clean:
	rm -rf *o Globe
