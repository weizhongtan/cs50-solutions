#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Number: ");
    long long cc_number = get_long_long();
    long long cc_temp = cc_number;
    long long sum = 0;
    
    while (cc_temp > 0)
    {
        int odd = (cc_temp % 100) / 10;
        odd = odd * 2;
        if (odd > 9) {
            int rem = odd % 10;
            odd = rem + 1;
        }
        sum += odd;
        
        int even = cc_temp % 10;
        sum += even;
        
        cc_temp /= 100;
    }

    cc_temp = cc_number;
    int length = 0;
    int first_two;
    while (cc_temp > 0)
    {
        if (cc_temp < 100 && cc_temp > 9)
        {
            first_two = cc_temp;
        }
        cc_temp /= 10;
        length++;
    }
    
    if (sum % 10 == 0)
    {
        switch (first_two)
        {
            case 34:
            case 37:
                if (length == 15)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                if (length == 16)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            default:
                if (first_two / 10 == 4 && (length == 13 || length == 16))
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }
    
    return 0;
}