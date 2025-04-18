#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"
#define POSNULA -1


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long pos = hash(key, map->capacity);
    Pair *dato = createPair(key, value);
    for(long j = 0; j < map->capacity; pos++){
        long nuevaPos =(pos + j) % map->capacity;
        if(map->buckets[nuevaPos] == NULL || map->buckets[nuevaPos]->key == NULL){
            map->buckets[nuevaPos] = dato;
            map->current = nuevaPos;
            map->size++;
            return;
        }            
    }
}


void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *map = (HashMap*)malloc(sizeof(HashMap));
    map->buckets = (Pair**)calloc(capacity, sizeof(Pair*));
    map->capacity = capacity;
    map->size = 0;
    map->current = POSNULA;

    return map;
}

void eraseMap(HashMap * map,  char * key) {    
    long pos = hash(key, map->capacity);
    for(long j = 0; j < map->capacity; pos++){
        long nuevaPos = (pos + j) % map->capacity;
        if(map->buckets[nuevaPos] == NULL)return;
        if(strcmp(map->buckets[nuevaPos]->key, key) == 0 ){
            map->buckets[nuevaPos]->key = NULL;
            map->size--;
            return;
        }
    }            
}



Pair * searchMap(HashMap * map,  char * key) {   
    long pos = hash(key, map->capacity);
    for(long j = 0 ; j < map->capacity ; j++){
        long nuevaPos =(pos + j) % map->capacity;
        if(map->buckets[nuevaPos] == NULL)return NULL;
        if(map->buckets[nuevaPos]->key != NULL && strcmp(map->buckets[nuevaPos]->key, key) == 0){
            map->current = nuevaPos;
            return map->buckets[nuevaPos];
        }
    }
    return NULL;
}


Pair * firstMap(HashMap * map){
    for(long j = 0 ; j < map->capacity ; j++){
        if(map->buckets[j]->key != NULL){
            map->current = j;
            return map->buckets[j];
        }
    }
    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
