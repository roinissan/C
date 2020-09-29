//
// Created by Roi on 01/12/2018.
//

#include "KeyValuePair.h"

struct GenKeyValue{
    Element key;
    Element value;

    copyFunction value_copy_func;
    copyFunction key_copy_func;

    freeFunction value_free_func;
    freeFunction key_free_func;

    printFunction value_print_func;
    printFunction key_print_func;

    equalFunction key_equal_func;

};

// function to create generel key-value pair - acting as constructor
GenKeyValueP createKeyValuePair (Element key ,Element value,
                                 copyFunction value_copy_func, copyFunction key_copy_func,
                                 freeFunction value_free_func,freeFunction key_free_func,
                                 printFunction value_print_func,printFunction key_print_func,
                                 equalFunction key_equal_func){

    GenKeyValueP new_pair = (GenKeyValueP)malloc(sizeof(struct GenKeyValue));
    if(!new_pair)
        return NULL;
    new_pair->value_copy_func = (Element)value_copy_func;
    new_pair->key_copy_func = (Element)key_copy_func;

    new_pair->value_free_func = (Element)value_free_func;
    new_pair->key_free_func = (Element)key_free_func;

    new_pair->value_print_func = (Element)value_print_func;
    new_pair->key_print_func = (Element)key_print_func;

    new_pair->key_equal_func = (Element)key_equal_func;

    if(value){
        new_pair->value =value_copy_func(value);
        value_free_func(value);
        }
    else
        new_pair->value = NULL;

    new_pair->key = key_copy_func(key);
	key_free_func(key);
    if(!(new_pair->key)) {
        free(new_pair);
        free(new_pair->value);
        return NULL;
    }


    return new_pair;
};


// function to free key-value pair using the free functions of the struct
status destroyKeyValuePair (Element key_value_pair){
    if(!key_value_pair)
        return success;
    GenKeyValueP key_value_pair_casted = (GenKeyValueP)key_value_pair;
    status key_free,value_free;
    key_free = key_value_pair_casted->key_free_func(key_value_pair_casted->key);
    value_free = key_value_pair_casted->value_free_func(key_value_pair_casted->value);
    free(key_value_pair);
    if(key_free == failure || value_free == failure)
        return failure;
    return success;
};

// function to print the value of the pair - using the "value_print_func" function of the struct
status displayValue (GenKeyValueP key_value_pair){
    if(!key_value_pair)
        return failure;
    GenKeyValueP key_value_pair_casted = (GenKeyValueP)key_value_pair;
    return (key_value_pair_casted->value_print_func(key_value_pair_casted->value));
}

// function to print the key of the pair - using the "key_print_func" function of the struct
status displayKey (GenKeyValueP key_value_pair){
    if(!key_value_pair)
        return failure;
    GenKeyValueP key_value_pair_casted = (GenKeyValueP)key_value_pair;
    return(key_value_pair_casted->key_print_func(key_value_pair_casted->key));
}

// function which returns the value of the pair
Element getValue (GenKeyValueP key_value_pair){
    if(!key_value_pair)
        return NULL;
    return key_value_pair->value;
}

// function which returns the key of the pair
Element getKey(GenKeyValueP key_value_pair){
    if(!key_value_pair)
        return NULL;
    return(key_value_pair->key);
}

// function which check if to given key are equal using the "key_equal_func" function of the struct
bool isEqualKey(Element key_value_pair_1, Element key_value_pair_2){
    if(!key_value_pair_1 || !key_value_pair_2)
        return false;
    GenKeyValueP key_value_pair_casted_1 = (GenKeyValueP)key_value_pair_1;
    GenKeyValueP key_value_pair_casted_2 = (GenKeyValueP)key_value_pair_2;
    return key_value_pair_casted_1->key_equal_func(key_value_pair_casted_1->key,key_value_pair_casted_2->key);
}


// function to copy the key-value pair using the copy functions of the struct
Element copyPairFunction(Element key_value_pair){
    if(!key_value_pair)
        return NULL;
    GenKeyValueP key_value_pair_casted = (GenKeyValueP)key_value_pair;
    GenKeyValueP new_pair = (GenKeyValueP) malloc(sizeof(struct GenKeyValue));
    if(!new_pair)
        return NULL;

    new_pair->value_print_func = key_value_pair_casted->value_print_func;
    new_pair->value_free_func = key_value_pair_casted->value_free_func;
    new_pair->value_copy_func = key_value_pair_casted->value_copy_func;

    new_pair->key_copy_func = key_value_pair_casted->key_copy_func;
    new_pair->key_free_func = key_value_pair_casted->key_free_func;
    new_pair->key_print_func = key_value_pair_casted->key_print_func;
    new_pair->key_equal_func = key_value_pair_casted->key_equal_func;

    new_pair->key = key_value_pair_casted->key_copy_func(key_value_pair_casted->key);
    new_pair->value = key_value_pair_casted->value_copy_func(key_value_pair_casted->value);

    return new_pair;
}


// function to print the key-value pair using the print functions of the struct
status printPairFunction(Element key_value_pair){
    if(!key_value_pair)
        return failure;
    GenKeyValueP key_value_pair_casted = (GenKeyValueP)key_value_pair;
    status value_result,key_result;
    key_result = displayKey(key_value_pair_casted);
    value_result = displayValue(key_value_pair_casted);
    if(value_result == failure || key_result == failure)
        return failure;
    return success;
}








