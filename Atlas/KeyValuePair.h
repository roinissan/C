//
// Created by Roi on 01/12/2018.
//
#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_
#include "Defs.h"

typedef struct GenKeyValue *GenKeyValueP;


GenKeyValueP createKeyValuePair (Element key ,Element value,
                                 copyFunction value_copy_func, copyFunction key_copy_func,
                                 freeFunction key_free_func,freeFunction value_free_func,
                                 printFunction value_print_func,printFunction key_print_func,
                                 equalFunction key_equal_func);

status destroyKeyValuePair (Element key_value_pair);
status displayValue (GenKeyValueP key_value_pair);
status displayKey (GenKeyValueP key_value_pair);
Element getValue(GenKeyValueP key_value_pair);
Element getKey(GenKeyValueP key_value_pair);
bool isEqualKey(Element key_value_pair_1, Element key_value_pair_2);


Element copyPairFunction(Element key_value_pair);
status printPairFunction(Element key_value_pair);





#endif /* KEYVALUEPAIR_H_ */
