//
// Created by Roi on 01/12/2018.
//

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "Defs.h"




typedef struct hashTable_s *hashTable;

hashTable createHashTable(copyFunction copyKey, freeFunction freeKey, printFunction printKey,
                          copyFunction copyValue, freeFunction freeValue, printFunction printValue,
                          equalFunction equalKey,transformIntoNumberFunction transformKeyIntoNumber, int hashNumber);
status destroyHashTable(hashTable hash_table);
status addToHashTable(hashTable hash_table, Element key,Element value);
Element lookupInHashTable(hashTable hash_table, Element key);
status removeFromHashTable(hashTable hash_table, Element key);
status displayHashElements(hashTable hash_table);



#endif /* HASH_TABLE_H */
