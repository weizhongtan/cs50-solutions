#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // store original hash
    string original_hash = argv[1];
    // reject incorrect usage
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    // save the first two characters as the salt
    char salt[3];
    strncpy(salt, original_hash, 2);
    // remember to null terminate the string
    salt[2] = '\0';
    
    // save the further 13 characters as the hash
    // char hash[14];
    // for (int i = 0; i < 13; i++)
    // {
    //     hash[i] = argv[1][i+2];
    // }
    // hash[13] = '\0';
    
    // TESTING: bcnk: 50/kOLeoxy63c
    
    // initialize test_key
    char key[5] = "baa\0\0";
    
    printf("%s\n", crypt(key, salt));
}