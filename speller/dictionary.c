// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include  <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 60000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_val = hash(word);
    //goto linked list
    node *p = table[hash_val];
    while (p != NULL){
        if (strcasecmp(p->word,word) == 0){
            return true;
        }
        p = p->next;
    }
    //for each item in each linked list
        //strcasecmp(word,item)

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 hash function.c
    char word_lower[46];
    for (int i = 0 ; i < 45 ; i++){
        word_lower[i] = tolower(word[i]);
    }
    word = word_lower;
    unsigned int hash = 5381;
    int c;
    while((c = *word++)){
        hash = ((hash << 5) + hash) +c ;
    }
    return hash%N;
}

// Loads dictionary into memory, returning true if successful, else false
int dict_size = 0 ;
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    //fscanf function
    char word_buffer[46];
    while (fscanf(file, "%s", word_buffer) != EOF){
        node *n = malloc(sizeof(node));
        strcpy(n->word,word_buffer);
        n->next = NULL;
        int hash_val = hash(word_buffer);
        if (table[hash_val] == NULL){
            //create first node
            table[hash_val] = n;
        } else {
            //insert node
            n->next = table[hash_val];
            table[hash_val] = n;
        }
        dict_size++;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (dict_size > 0){
        return dict_size;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0 ; i < N ; i++){
        node *p = table[i];
        while (p != NULL){
            node *old = p;
            p = p->next;
            //free up node
            free(old);
        }
    }
    return true;
}
