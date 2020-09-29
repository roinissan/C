#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Defs.h"
#include "LinkedList.h"
#include "Countries.h"
#include "KeyValuePair.h"
#include "HashTable.h"


int main(int argc, char *argv[]) {
    // getting the arguments from the user and opening the file
    char *temp = NULL, *temp2 = NULL;
    int parse_file_result;
    if (argc != 4)
        return -1;
    FILE *file = NULL;
    int hashNumber = strtol(argv[1], &temp2, 10);
    int numberOfCountries = strtol(argv[2], &temp, 10);
    file = fopen(argv[3], "r");
    if (!file)
        return -1;
    pCountry temp_Country;
    //creating hash table that the Countries will be saved in
    hashTable pHashTable = createHashTable(copyName,freeName,printName,copyCountryElement,deleteCountryElement,printCountryElement,equalNames,hash_code_function,hashNumber);
    if (!pHashTable) {
        printf("no memory available");
        return -1;
    }

    // parsing the file - adding the countries and cities to the hash table
    parse_file_result = parse_file(file, pHashTable);
    fclose(file);
    if (parse_file_result == -1) {
        destroyHashTable(pHashTable);
        printf("no memory available");
        return -1;
    }

    // main variable for the user inputs
    int user_choice = 1;
    char user_input1[40];
    char user_input2[40];
    // additional variables for use during the program
    pCity new_city = NULL;
    char *temp_str = NULL, *object_string = NULL, *string_pointer = NULL,*temp_country_name = NULL;
    int pop = 0, x1_coordinate = 0, y1_coordinate = 0, x2_coordinate = 0, y2_coordinate = 0, object_counter = 0;
    while (user_choice != 8) {
        printf("please choose one of the following numbers:\n");
        printf("1 : print Countries\n");
        printf("2 : add country\n");
        printf("3 : add city to country\n");
        printf("4 : delete city from country\n");
        printf("5 : print country by name\n");
        printf("6 : delete country\n");
        printf("7 : is country in area\n");
        printf("8 : exit\n");
        if (!scanf("%d", &user_choice))
            break;
        if (user_choice < 1 || user_choice > 8)
            printf("please choose a valid number\n");
        switch (user_choice) {

            case 1:
                if (pHashTable)
                    displayHashElements(pHashTable);
                break;

            case 2:
                printf("please enter a new country name\n");
                if (!scanf("%s", user_input1))
                    break;
                temp_country_name = copyName(user_input1);
                if (lookupInHashTable(pHashTable, temp_country_name) != NULL) {
                    printf("country with this name already exist\n");
                    break;
                }
                printf("please enter two x and y coordinates :x1,y1,x2,y2\n");
                if (!scanf("%s", user_input2))
                    break;
                string_pointer = user_input2;
                object_counter = 0;
                while ((object_string = strsep(&string_pointer, ","))
                       && object_counter < 4) {
                    if (object_counter == 0)
                        x1_coordinate = strtol(object_string, &temp_str, 10);
                    if (object_counter == 1)
                        y1_coordinate = strtol(object_string, &temp_str, 10);
                    if (object_counter == 2)
                        x2_coordinate = strtol(object_string, &temp_str, 10);
                    if (object_counter == 3)
                        y2_coordinate = strtol(object_string, &temp_str, 10);
                    object_counter++;
                }
                temp_Country = addCountry(user_input1, x1_coordinate, y1_coordinate,x2_coordinate, y2_coordinate);
                temp_str = copyName(getCountryName(temp_Country));
                if (temp_Country == NULL) {
                    printf("no memory available\n");
                    user_choice = 8;
                    break;
                }
                if (addToHashTable(pHashTable, temp_str, temp_Country) == failure){
                    printf("no memory available\n");
                    user_choice = 8;
                }
                break;

            case 3:
                printf("please enter a country name\n");
                if (!scanf("%s", user_input1))
                    break;
                temp_country_name = copyName(user_input1);
                if (lookupInHashTable(pHashTable, temp_country_name) == NULL) {
                    printf("country not exist\n");
                    break;
                }
                temp_country_name = copyName(user_input1);
                temp_Country = (pCountry) lookupInHashTable(pHashTable,temp_country_name);
                printf("please enter a city name\n");
                if (!scanf("%s", user_input2))
                    break;
                if (isCityExist(user_input2, temp_Country) != (-1)) {
                    printf("this city already exist in this country\n");
                    break;
                }
                printf("please enter the city favorite food\n");
                if (!scanf("%s", user_input1))
                    break;
                printf("please enter number of residents in city\n");
                if (!scanf("%d", &pop))
                    break;
                new_city = citySetter(new_city, user_input2, user_input1, pop);
                if (addCity(temp_Country, new_city) == failure) {
                    printf("no memory available\n");
                    user_choice = 8;
                    break;
                }
                break;

            case 4:
                printf("please enter a country name\n");
                if (!scanf("%s", user_input1))
                    break;
                temp_country_name = copyName(user_input1);
                if (lookupInHashTable(pHashTable, temp_country_name) == NULL) {
                    printf("country name not exist.\n");
                    break;
                }
                temp_country_name = copyName(user_input1);
                temp_Country = (pCountry) lookupInHashTable(pHashTable,temp_country_name);
                printf("please enter a city name\n");
                if (!scanf("%s", user_input2))
                    break;
                if (deleteCity(temp_Country, user_input2) == failure) {
                    printf("the city not exist in this country\n");
                    break;
                }
                break;

            case 5:
                printf("please enter a country name\n");
                if (!scanf("%s", user_input1))
                    break;
                temp_country_name = copyName(user_input1);
                if (lookupInHashTable(pHashTable, temp_country_name) == NULL) {
                    printf("country name not exist\n");
                    break;
                }
                temp_country_name = copyName(user_input1);
                printCountry((pCountry) lookupInHashTable(pHashTable,temp_country_name));
                break;

            case 6:
                printf("please enter a country name\n");
                if (!scanf("%s", user_input1))
                    break;
                temp_country_name = copyName(user_input1);
                if (removeFromHashTable(pHashTable,temp_country_name) == failure) {
                    printf("can't delete the country\n");
                    break;
                }
                printf("country deleted\n");
                break;

            case 7:
                printf("please enter a country name\n");
                if (!scanf("%s", user_input1))
                    break;
                temp_country_name = copyName(user_input1);
                if (lookupInHashTable(pHashTable, temp_country_name) == NULL) {
                    printf("country name not exist\n");
                    break;
                }
                printf("please enter x and y coordinations:x,y\n");
                if (!scanf("%s", user_input2))
                    break;
                string_pointer = user_input2;
                object_counter = 0;
                x1_coordinate = 0;
                y1_coordinate = 0;
                while ((object_string = strsep(&string_pointer, ","))&& object_counter < 2) {
                    if (object_counter == 0)
                        x1_coordinate = strtol(object_string, &temp_str, 10);
                    else
                        y1_coordinate = strtol(object_string, &temp_str, 10);
                    object_counter++;
                }
                temp_country_name = copyName(user_input1);
                if (checkIfInTerr((pCountry)lookupInHashTable(pHashTable,temp_country_name), x1_coordinate,y1_coordinate) == true) {
                    printf("the coordinate in the country\n");
                    break;
                }
                printf("the coordinate not in the country\n");
                break;
        }
        if(user_choice == 8){
            destroyHashTable(pHashTable);
            printf("all the memory cleaned and the program is safely closed\n");
            return 1;
        }
    }

}

// function to parse the country file using 2 other functions: "add_parsed_city","add_parsed_country"
int parse_file(FILE *country_file, Element pHashTable){
    pCountry new_country = NULL,country_handler = NULL;
    hashTable newHashTable = (hashTable)pHashTable;
    char *line = NULL, *new_line = NULL, *new_country_name=NULL,*country_name=NULL;
    char temp[40];
    ssize_t read;
    size_t len = 0;
    while ((read = getline(&line, &len, country_file)) != -1) {
        line[strlen(line) - 1] = '\0';
        new_line = line;

        if (!strchr(new_line,'\t')){
            new_country = add_parsed_country(new_line);
            if(new_country == NULL)
                return -1;
            new_country_name = copyName(getCountryName(new_country));
            if(new_country_name == NULL){
                deleteCountry(new_country);
                return -1;
            }
            strcpy(temp,new_country_name);
            if(addToHashTable(newHashTable,new_country_name,new_country)==failure){
                deleteCountry(new_country);
                free(new_country_name);
                return -1;
            }
        }
        else{
            country_name = copyName(temp);
            country_name[strlen(country_name)] = '\0';
			country_handler = (pCountry)lookupInHashTable(newHashTable,country_name);
            new_line = new_line + 1;
            if(add_parsed_city(new_line,country_handler) == -1)
                return -1;
        }
    }
    free(line);
    return 1;
}

// gets the country line and after parsing creates new country using "addCountry"
pCountry add_parsed_country(char* country_line) {
    int object_counter = 0, coordinate_x1 = -1, coordinate_x2 = -1,coordinate_y1 = -1, coordinate_y2 = -1;
    char *object_string = NULL, *country_name = NULL, *temp = NULL;
    while ((object_string = strsep(&country_line, ","))) {
        if (object_counter == 0) {
            country_name = object_string;
        } else if (object_counter == 1) {
            coordinate_x1 = strtol(object_string, &temp, 10);
        } else if (object_counter == 2) {
            coordinate_y1 = strtol(object_string, &temp, 10);
        } else if (object_counter == 3) {
            coordinate_x2 = strtol(object_string, &temp, 10);
        } else if (object_counter == 4) {
            coordinate_y2 = strtol(object_string, &temp, 10);
        }
        ++object_counter;
    }
    return addCountry(country_name, coordinate_x1, coordinate_x2, coordinate_y1,coordinate_y2);
}

// gets the city line and after parsing creates new city using "addCity"
int add_parsed_city(char* country_line, pCountry country_pointer) {
    status check;
    pCity new_city = NULL;
    char *name = NULL, *food = NULL;
    int object_counter = 0, popolution = 0;
    char *object_string, *temp;
    while ((object_string = strsep(&country_line, ","))) {
        if (object_counter == 0) {
            name = object_string;
        } else if (object_counter == 1) {
            food = object_string;
        } else if (object_counter == 2) {
            popolution = strtol(object_string, &temp, 10);
        }
        ++object_counter;
    }
    new_city = citySetter(new_city, name, food, popolution);
    check = addCity(country_pointer, new_city);
    if (check == failure)
        return -1;
    return 1;
}



char* strsep(char** stringp, const char* delim)
{
    char* start = *stringp;
    char* p;

    p = (start != NULL) ? strpbrk(start, delim) : NULL;

    if (p == NULL)
    {
        *stringp = NULL;
    }
    else
    {
        *p = '\0';
        *stringp = p + 1;
    }

    return start;
}
// hash-code function to send the hash table
int hash_code_function(Element key){

    char* temp = (char*)key;
    int sum = 0 ;
    for(int character = 0; character < strlen(key);character++){
        sum=sum+temp[character];
    }
    return sum;
}