#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // reject incorrect number of command line args
        printf("Incorrect number of command line arguments\n");
        return 1;
    }
    
    // reduce key to a value between 0 and 25
    int k = atoi(argv[1]) % 26;
    
    // ask for plaintext
    printf("plaintext: ");
    string plain = get_string();
    
    // print ciphertext
    printf("ciphertext: ");
    
    // iterate over characters in the plaintext string
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        char old_ch = plain[i];
        char new_ch;
        char lower_bound = 'x';
        char upper_bound;
        int new_int;
        
        // set upper/lower bounds if the character is a-z or A-Z, else, leave lower bound set to 'x'
        if (old_ch >= 'a' && old_ch <= 'z')
        {
            lower_bound = 'a';
            upper_bound = 'z';
        }
        else if (old_ch >= 'A' && old_ch <= 'Z')
        {
            lower_bound = 'A';
            upper_bound = 'Z';
        }
        
        // for a-z or A-Z, apply cipher
        if (lower_bound != 'x')
        {
            // to prevent possible overflow of the char, cast into an int
            new_int = (int) old_ch + k;
            
            // if applying the cipher produces a character outside of the upper bound, overflow it from the lower bound
            if (new_int > upper_bound)
            {
                new_ch = lower_bound + (new_int - upper_bound) - 1;
            }
            else
            {
                new_ch = (char) new_int;
            }
        }
        else
        {
            new_ch = old_ch;
        }
        
        // print cipher character, or raw plain character if no a-z or A-Z
        printf("%c", new_ch);
    }
    
    printf("\n");

    return 0;
}