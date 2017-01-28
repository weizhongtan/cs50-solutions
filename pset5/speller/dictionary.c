/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // initialize current node to the root of the trie
    node *current_node = root;
    
    // iterate through each letter of the word until you reach the end of the word
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // get index from 0 - 27
        char letter = tolower(word[i]);
        int index = (letter == '\'') ? 26 : letter - 'a';
        
        // if the i'th index of the node's children is NULL, then the word is not in the dictionary
        if (current_node->children[index] == NULL)
        {
            return false;
        }
        
        // traverse down into node
        current_node = current_node->children[index];
    }
    
    // we're at the last node now, check if is_word of this node is true
    if (current_node->is_word)
    {
        // found word in dictionary
        return true;
    }
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // initiliaze dictionary size
    dictionary_size = 0;
    
    // initialize root node
    root = (node*) malloc(sizeof(node));
    if (root == NULL)
    {
        fprintf(stderr, "Not enough memory.\n");
        return false;
    }
    
    // open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open dictionary.\n");
        return false;
    }
    
    // define word array
    char word[LENGTH];
    
    // iterate through every word in the dictionary file
    while (fscanf(file, "%s", word) != EOF)
    {
        // get word length
        int len = strlen(word);
        
        // initialize current node to the root of the trie
        node *current_node = root;
        
        // iterate through each letter of the word until you reach the end (\0)
        for (int i = 0; word[i] != '\0'; i++)
        {
            // get index from 0 - 27
            int index = (word[i] == '\'') ? 26 : word[i] - 'a';
            
            // if this letter has not been used at this node before
            if (current_node->children[index] == NULL)
            {
                // create new node in memory and point children[i] to it
                current_node->children[index] = (node*) malloc(sizeof(node));
            }
            
            // traverse down into node
            current_node = current_node->children[index];
            if (current_node == NULL)
            {
                fprintf(stderr, "Not enough memory.\n");
                return false;
            }
            
            // if at end of word, set is_word to true
            if (i == len - 1)
            {
                current_node->is_word = true;
            }
        }
        
        // increment dictionary size counter
        dictionary_size++;
    }
    
    // close the dictionary file, end if successful
    if (fclose(file) == 0)
    {
        return true;
    }
    
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // by this time, dictionary size will either be 0 if the load was unsuccessful, or some positive integer
    return dictionary_size;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // initialize current node to the root of the trie
    free_trie(root);
    
    return true;
}

void free_trie(node *current_node)
{
    // recursively go through every node and free the memory
    // iterate through each pointer this node contains
    for (int i = 0; i < 27; i++)
    {
        // if the pointer is not a null pointer, go into it and execute this function on it
        if (current_node->children[i] != NULL)
        {
            free_trie(current_node->children[i]);
        }
    }
    
    // by the time the function gets here all of the current node's pointers are null. therefore we can now free this node and leave this iteration
    free(current_node);
}
