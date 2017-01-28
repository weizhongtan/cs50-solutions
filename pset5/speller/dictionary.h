/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// trie node definitions
typedef struct node
{
    bool is_word;
    
    // an array of 27 pointers to nodes, one for each alphabetic character and the apostrophe '\''
    struct node *children[27];
}
node;

// this root will be accessible to all functions in dictionary.c
node *root;

int dictionary_size;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

void free_trie(node *current_node);

#endif // DICTIONARY_H
