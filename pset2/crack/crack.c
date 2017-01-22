#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// test passwords
// andi:50.jPgLzVirkc
// jason:50YHuxoCN9Jkc
// malan:50QvlJWn2qJGE
// mzlatkova:50CPlMDLT06yY
// patrick:50WUNAFdX/yjA
// rbowden:50fkUxYHbnXGw
// summer:50C6B0oz0HWzo
// stelios:50nq4RV/NVU0I
// wmartin:50vtwu4ujL.Dk
// zamyla:50i2t3sOSAZtk

int main(int argc, string argv[])
{
    // reject incorrect usage
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    // store original hash
    string original_hash = argv[1];
    
    // save the first two characters as the salt
    char salt[3];
    strncpy(salt, original_hash, 2);
    
    // remember to null terminate the string
    salt[2] = '\0';
    
    // initialize test_key
    char key[5];
    key[4] = '\0';

    // this part can be heavily improved...
    //  eg due to a '\0' being added to each full cycle, there are some duplicate checks ie "aa\0a\0" is the same as "aa\0\0\0"
    // iterate through all possible keys, print password if found
    for (int i = 0; i < 52; i++)
    {
        // set first character of key to respective letter
        key[0] = (i < 26 ) ? 'A' + i : 'a' + i - 26;
        
        for (int j = 0; j < 53; j++)
        {
            key[1] = (j == 52) ? '\0' : ((j < 26 ) ? 'A' + j : 'a' + j - 26);
            
            for (int k = 0; k < 53; k++)
            {
                key[2] = (k == 52) ? '\0' : ((k < 26 ) ? 'A' + k : 'a' + k - 26);
                
                for (int l = 0; l < 53; l++)
                {
                    key[3] = (l == 52) ? '\0' : ((l < 26 ) ? 'A' + l : 'a' + l - 26);
                    
                    // use crypt on each generated key and the salt given originally
                    string test_hash = crypt(key, salt);
                    
                    // check if the produced hash is the same as the one given originally
                    if (strcmp(test_hash, original_hash) == 0)
                    {
                        // print password and exit if it is
                        printf("%s\n", key);
                        return 0;
                    }
                }
            }
        }
    }
}