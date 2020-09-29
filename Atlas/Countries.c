#include "Countries.h"


//Structures
struct City{
    char* name;
    char* food;
    int population;

};

struct Country{
    char *name;
    int numCities;
    pCity cities;
    pTerritory countryTerr;

};

struct Territory{
    int x1;
    int x2;
    int y1;
    int y2;
};

//Main functions

//function to delete a city from a country - updates the array of cities accordingly
status deleteCity(pCountry country,char* cityName){
    status is_in = failure;
    int city_in_cities = isCityExist(cityName,country);
    if(city_in_cities == -1)
        return is_in;
    is_in = success;

    pCity new_cities = (pCity) calloc(country->numCities-1,sizeof(struct City));
    if (new_cities != NULL){
        for ( int i = 0 ; i < country->numCities ; ++i){
            if(i != city_in_cities){
                if(i < city_in_cities){
                    new_cities[i].population = country->cities[i].population;
                    new_cities[i].name = (char*)malloc(sizeof(char)*(strlen(country->cities[i].name)+1));
                    if(!new_cities[i].name)
                        return failure;
                    strcpy(new_cities[i].name,country->cities[i].name);
                    new_cities[i].food = (char*)malloc(sizeof(char)*(strlen(country->cities[i].food)+1));
                    if(!new_cities[i].name || !new_cities[i].food){
                        free(new_cities[i].name);
                        free(new_cities[i].food);
                        return failure;
                    }
                    strcpy(new_cities[i].food,country->cities[i].food);
                }
                else{
                    new_cities[i-1].population = country->cities[i].population;
                    new_cities[i-1].name = (char*)malloc(sizeof(char)*(strlen(country->cities[i].name)+1));
                    if(!new_cities[i-1].name)
                        return failure;
                    strcpy(new_cities[i-1].name,country->cities[i].name);
                    new_cities[i-1].food = (char*)malloc(sizeof(char)*(strlen(country->cities[i].food)+1));
                    if(!new_cities[i-1].name)
                        return failure;
                    strcpy(new_cities[i-1].food,country->cities[i].food);
                }
            }

        }
        for ( int i = 0 ; i < country->numCities ; ++i){
            free(country->cities[i].food);
            free(country->cities[i].name);
        }
        free(country->cities);
        country->cities = new_cities;
        country->numCities = country->numCities -1;
    }
    return is_in;
}

//function to delete country
status deleteCountry(pCountry country){
    if(country != NULL){
        int num_of_cities = country->numCities;
        for(int i = 0 ; i<num_of_cities; i++){
            if (country->cities){
                free(country->cities[i].food);
                free(country->cities[i].name);

            }
        }
        if(country->cities)
            free(country->cities);
        if(country->name)
            free(country->name);
        if(country->countryTerr)
            free(country->countryTerr);
        free(country);
    }
    return success;
}

//creates new country - with name and territory
pCountry addCountry(char* name,int x1,int y1,int x2,int y2){
    if(name==NULL)
        return NULL;
    pCountry newCountry = NULL;
    newCountry = (pCountry)malloc(sizeof(struct Country));
    if(!newCountry)
        return NULL;
	newCountry->cities = NULL;
    newCountry->name = (char*)malloc((strlen(name)+1)*sizeof(char));
    newCountry->countryTerr = (pTerritory)malloc(sizeof(struct Territory));
    if(!newCountry->name || ! newCountry->countryTerr){
        free(newCountry->name);
        free(newCountry->countryTerr);
        free(newCountry);
        return NULL;
    }
    strcpy(newCountry->name,name);
	newCountry->name[strlen(name)] = '\0';
    newCountry->numCities = 0;
    newCountry->countryTerr->x1=x1;
    newCountry->countryTerr->y1=y1;
    newCountry->countryTerr->x2=x2;
    newCountry->countryTerr->y2=y2;

    return newCountry;
}

//adds new city to a country - get the country pointer using the "city setter function"
status addCity(pCountry country,pCity city){
    if (country==NULL || city==NULL)
        return failure;

    country->cities =(pCity)realloc(country->cities,(country->numCities+1)*sizeof(struct City));

    if(!country->cities)
        return failure;

    country->cities[country->numCities] = *city;
    country->cities[country->numCities].population = city->population;
    free(city);
    country->numCities++;
    return success;
}

// checks if the given coordinates are in counter territory
bool checkIfInTerr(pCountry country,int x,int y){
    if(!country)
        return false;
    if(!country->countryTerr)
        return false;
    if((x >= country->countryTerr->x1 && x <= country->countryTerr->x2))
        if (y <= country->countryTerr->y1 && y >= country->countryTerr->y2)
            return true;
    return false;


}

// creates new city and returns pointer of the country
pCity citySetter(pCity new_city, char* name, char* food,int popolution){

    new_city = (pCity)malloc(sizeof(*new_city));
    new_city->name = (char*)malloc((strlen(name)+1)*sizeof(char));
    new_city->food = (char*)malloc((strlen(food)+1)*sizeof(char));
    if (new_city->name && new_city->food){
        strcpy(new_city->name,name);
		new_city->name[strlen(name)] = '\0';
		strcpy(new_city->food,food);
		new_city->food[strlen(food)] = '\0';
		new_city->population = popolution;
		return new_city;
    }
    free(new_city->name);
    free(new_city->food);
    return NULL;
}

//hard copy of existing country - returns pointer to the new copied country
pCountry copyCountry(pCountry country){
	if(!country)
		return NULL;
	pCountry copied_country = (pCountry)malloc(sizeof(struct Country));
	copied_country->cities = (pCity)malloc(country->numCities*sizeof(struct City));
	copied_country->name = (char*)malloc((sizeof(char))*(strlen(country->name)+1));
	copied_country->countryTerr = (pTerritory)malloc(sizeof(struct Territory));

	if(!copied_country  || !copied_country->cities ||!copied_country->name || !copied_country->countryTerr){
		free(copied_country->cities);
		free(copied_country->name);
		free(copied_country->countryTerr);
		free(copied_country);
		return NULL;
	}

	strcpy(copied_country->name,country->name);
	copied_country->numCities = country->numCities;
	copied_country->countryTerr->x1 = country->countryTerr->x1;
	copied_country->countryTerr->x2 = country->countryTerr->x2;
	copied_country->countryTerr->y1 = country->countryTerr->y1;
	copied_country->countryTerr->y2 = country->countryTerr->y2;

	for(int city_id = 0; city_id < copied_country->numCities ; ++city_id){
		copied_country->cities[city_id].name = (char*)malloc((sizeof(char))*(strlen(country->cities[city_id].name)+1));
		copied_country->cities[city_id].food = (char*)malloc((sizeof(char))*(strlen(country->cities[city_id].food)+1));
		if(!copied_country->cities[city_id].name || !copied_country->cities[city_id].food){
			for(int free_city_id = city_id; free_city_id > -1 ; --free_city_id){
				free(copied_country->cities[city_id].name);
				free(copied_country->cities[city_id].food);
			}
			free(copied_country->cities);
			free(copied_country->name);
			free(copied_country->countryTerr);
			free(copied_country);
			return NULL;
		}
		strcpy(copied_country->cities[city_id].name,country->cities[city_id].name);
		strcpy(copied_country->cities[city_id].food,country->cities[city_id].food);
		copied_country->cities[city_id].population = country->cities[city_id].population;
	}
	return copied_country;
}


// prints the country data according to the specifications
status printCountry(pCountry country){
    if(country==NULL)
        return failure;
    printf("Country %s coordinates: <%d,%d> , <%d,%d>\n",country->name,country->countryTerr->x1,country->countryTerr->y1,country->countryTerr->x2,country->countryTerr->y2);
    int i;
    for(i = 0;i<country->numCities;i++){
        printf("\t%s includes %d residents and their favorite food is %s\n",country->cities[i].name,country->cities[i].population,country->cities[i].food);
    }
    return success;
}

//Additional functions

//checks if the city is in the given country
int isCityExist(char* city_name,pCountry country){
    if(!country)
        return -1;
    if (!country->cities)
        return -1;
    for (int city_in_cities = 0 ; city_in_cities < country->numCities ; ++city_in_cities)
        if (strcmp(country->cities[city_in_cities].name , city_name) == 0)
            return city_in_cities;
    return -1;
}

char* getCountryName(pCountry country){
    return country->name;
}

// copy key function to send the hashtable
Element copyName(Element key){
    char* new_key= (char*)key;
    char* ret = (char*)malloc((strlen(new_key)+1)*sizeof(char*));
    strcpy(ret,new_key);
    ret[strlen(new_key)] = '\0';
    return ret;
}

// copy value function to send the hashtable - using copyCountry
Element copyCountryElement(Element country){
	pCountry country_casted = (pCountry)country;
	return copyCountry(country_casted);
}

// free key function to send the hashtable
status freeName(Element key){
	char* new_key = (char*)key;
    free(new_key);
    return success;
}

// free value function to send the hashtable - using deleteCountry
status deleteCountryElement(Element country){
	pCountry country_casted = (pCountry)country;
	return deleteCountry(country_casted);

}

// print key function to send the hashtable
status printName(Element key){
    printf("");
    return success;
}

// print value function to send the hashtable - using printCountry
status printCountryElement(Element country){
	pCountry country_casted = (pCountry)country;
	return printCountry(country_casted);
}

// equal keys function to send the hashtable
bool equalNames(Element key1,Element key2){
    char *new_key1 = (char*)key1;
    char *new_key2  = (char*)key2;
    int is_equal = strcmp(new_key1,new_key2);
    if(is_equal == 0)
        return true;
    return false;
}



























