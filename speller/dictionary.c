// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define NUM_CONTAINERS 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[NUM_CONTAINERS];

// creates a variable intialized to 0 that will keep track of the number of words in dictionary
int wordCount = 0;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < NUM_CONTAINERS; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    // takes the dictionary file, looks for a string, and puts that string into a variable called word
    // will execute this loop until the end of the dictionary file is reached
    while (fscanf(file, "%s", word) != EOF)
    {
        // for every word that we scan we need to allocate some space in memory for it
        node *createdNode = malloc(sizeof(node));
        
        // whenever we create a node we need to check to see if malloc succeeded. 
        // if we run out of memory, malloc will return NULL and we need to check for that and return false
        if (createdNode == NULL)
        {
            unload();
            return false;
        }
        
        // strcpy inserts the "word" char into the word varaible by accesing it through arrow notation and setting the node value
        strcpy(createdNode->word, word);
        
        // sends "word" to the hash function to hash to a number between o and 25 inclusive
        int hash_value = hash(word);
        
        // if there are no nodes currently in the hash table we need to create one
        if (hashtable[hash_value] == NULL)
        {
            // set the Node (hash_value) to the current createdNode
            hashtable[hash_value] = createdNode;
            createdNode->next = NULL;
        }
        createdNode->next = hashtable[hash_value];
        hashtable[hash_value] = createdNode;
        
        wordCount++;
        printf("%i", wordCount);
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
