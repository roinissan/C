#ifndef COUNTRIES_H_
#define COUNTRIES_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "HashTable.h"


typedef struct City* pCity;
typedef struct Country* pCountry;
typedef struct Territory* pTerritory;



pCountry addCountry(char* name,int x1,int y1,int x2,int y2);
status addCity(pCountry country,pCity city);
status deleteCity(pCountry country,char* cityName);
bool checkIfInTerr(pCountry country,int x,int y);
status deleteCountry(pCountry country);
pCountry copyCountry(pCountry country);
status printCountry(pCountry country);
int isCityExist(char* city_name,pCountry country);
char* getCountryName(pCountry country);


Element copyCountryElement(Element country);
status deleteCountryElement(Element country);
status printCountryElement(Element country);


Element copyName(Element key);
status freeName(Element key);
status printName(Element key);
bool equalNames(Element key1,Element key2);

int parse_file(FILE *country_file, Element pHashTable);
pCountry add_parsed_country(char* country_line);
int add_parsed_city(char* country_line,pCountry country_pointer);

pCity citySetter(pCity new_city, char* name, char* food,int popolution);
char* strsep(char** stringp, const char* delim);
int hash_code_function(Element key);

#endif /* COUNTRIES_H_ */
