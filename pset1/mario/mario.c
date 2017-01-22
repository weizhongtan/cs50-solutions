#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h = -1;
    while (h < 0 || h > 23)
    {
        printf("Height: ");
        h = get_int();
    }
    for (int i=0; i < h; i++)
    {
        for (int j=0; j < h-i-1; j++)
        {
            printf(" ");
        }
        for (int j=0; j < i+1; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j=0; j < i+1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
