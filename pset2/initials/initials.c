#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // get name as input and store in s
    string s = get_string();
    
    char last_ch = ' ';
    // iterate over input string s
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        char curr_ch = s[i];
        if (curr_ch != ' ' && (i == 0 || last_ch == ' '))
        {
            printf("%c", toupper(curr_ch));
        }
        // set the last character for the next iteration
        last_ch = curr_ch;
    }
    printf("\n");
}