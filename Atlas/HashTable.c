//
// Created by Roi on 01/12/2018.
//

#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

struct hashTable_s{

    copyFunction copyKey;
    copyFunction copyValue;

    freeFunction freeKey;
    freeFunction freeValue;

    printFunction printKey;
    printFunction printValue;

    equalFunction equalKey;
    equalFunction equalValue;

    transformIntoNumberFunction transformKeyIntoNumber;

    int hashNumber;

    pLinkedList* linkedListArr;

};

// function to create generel Hash table - acting as constructor
hashTable createHashTable(copyFunction copyKey, freeFunction freeKey, printFunction printKey,
                          copyFunction copyValue, freeFunction freeValue, printFunction printValue,
                          equalFunction equalKey,
                          transformIntoNumberFunction transformKeyIntoNumber, int hashNumber){

    hashTable new_hash_table = (hashTable)malloc(sizeof(struct hashTable_s));
    if(!new_hash_table)
        return NULL;
    new_hash_table->linkedListArr = (pLinkedList*)calloc(hashNumber,sizeof(pLinkedList));
    if(!new_hash_table->linkedListArr){
        free(new_hash_table);
        return NULL;
    }
    new_hash_table->copyValue = (Element)copyValue;
    new_hash_table->copyKey = (Element)copyKey;

    new_hash_table->freeValue = (Element)freeValue;
    new_hash_table->freeKey = (Element)freeKey;

    new_hash_table->printValue = (Element)printValue;
    new_hash_table->printKey = (Element)printKey;

    new_hash_table->equalKey = (Element)equalKey;

    new_hash_table->transformKeyIntoNumber = (Element)transformKeyIntoNumber;

    new_hash_table->hashNumber = hashNumber;

    return new_hash_table;
}

// function to free hash table using the free functions of the struct (sended to linked list)
status destroyHashTable(hashTable hash_table){
    if(!hash_table )
        return failure;
    for(int linked_list_id = 0; linked_list_id < hash_table->hashNumber; ++linked_list_id){
        destroyList(hash_table->linkedListArr[linked_list_id]);
    }
    free(hash_table->linkedListArr);
    free(hash_table);
    return success;
}


// function to add new element to the hash table - using the key-value pair and linked list
status addToHashTable(hashTable hash_table, Element key,Element value){
    if (hash_table == NULL || key == NULL || value == NULL)
        return failure;
    GenKeyValueP new_key_value_pair = createKeyValuePair(key,value,
                                                         hash_table->copyValue,hash_table->copyKey,
                                                         hash_table->freeValue,hash_table->freeKey,
                                                         hash_table->printValue,hash_table->printKey,
                                                         hash_table->equalKey);
    if(!new_key_value_pair)
        return failure;
    int hashed_key = hash_table->transformKeyIntoNumber(getKey(new_key_value_pair));
    hashed_key = hashed_key % hash_table->hashNumber;
    if(hash_table->linkedListArr[hashed_key] == NULL){
        hash_table->linkedListArr[hashed_key] = createLinkedList(copyPairFunction,isEqualKey,printPairFunction,destroyKeyValuePair);
        return (appendNode(hash_table->linkedListArr[hashed_key],new_key_value_pair));
    }
    else
        return (appendNode(hash_table->linkedListArr[hashed_key],new_key_value_pair));

}

// function to search for an element in the table - given a key
// create key value pair and then using the linked list search
Element lookupInHashTable(hashTable hash_table, Element key){
    if(!hash_table || !key)
        return NULL;

    GenKeyValueP temporary_key_value_pair = createKeyValuePair(key,NULL,  hash_table->copyValue,  hash_table->copyKey,
                                                     hash_table->freeValue, hash_table->freeKey,
                                                     hash_table->printValue, hash_table->printKey,
                                                     hash_table->equalKey);
    int hashed_key = hash_table->transformKeyIntoNumber(getKey(temporary_key_value_pair));
    hashed_key = hashed_key % hash_table->hashNumber;
    GenKeyValueP key_value_pair = (GenKeyValueP)searchInList(hash_table->linkedListArr[hashed_key],temporary_key_value_pair);
    destroyKeyValuePair(temporary_key_value_pair);
    if(!key_value_pair)
        return NULL;
    return getValue(key_value_pair);
}


// function to free node from the hash - using the linked list free function
status removeFromHashTable(hashTable hash_table, Element key){
    if(!hash_table || !key)
        return failure;
    GenKeyValueP temporary_key_value_pair = createKeyValuePair(key,NULL,  hash_table->copyValue,  hash_table->copyKey,
                                                               hash_table->freeValue, hash_table->freeKey,
                                                               hash_table->printValue, hash_table->printKey,
                                                               hash_table->equalKey);
    int hashed_key = hash_table->transformKeyIntoNumber(getKey(temporary_key_value_pair));
    hashed_key = hashed_key % hash_table->hashNumber;
    status is_success = deleteNode(hash_table->linkedListArr[hashed_key],temporary_key_value_pair);
    destroyKeyValuePair(temporary_key_value_pair);
    return(is_success);
}

// function to print the all the hash element using the print functions and linked list
status displayHashElements(hashTable hash_table){
    if(!hash_table)
        return failure;

    for(int linked_list_id = 0; linked_list_id < hash_table->hashNumber; ++linked_list_id)
        displayList(hash_table->linkedListArr[linked_list_id]);
    return success;
}


