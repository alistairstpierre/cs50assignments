#include <stdio.h>
#include <cs50.h>
#include <math.h>

void check_credit();
unsigned long long int ipow(unsigned long long int base, int exp);
int get_number_length(long number);
string check_company();

int main(void)
{
    check_credit();
    return 0;
}

// Wait for user input and check if the input number is a valid credit card.
void check_credit()
{
    // Variables to store the first and second digits to check the company who owns the credit card
    int first_digit = 0;
    int second_digit = 0;

    // Wait for user to input credit card numbers
    printf("Number: ");
    long number = get_long_long();
    char buffer[25];
    int length = sprintf(buffer, "%ld", number);
    long first_pass = 0;
    long second_pass = 0;

    // Iterate through each individual credit card value.
    for(int i = 0; i < length; i++){
        long temp = (number/(ipow(10,i)))%10;
        if(i == length - 2)
        {
            second_digit = (int)temp;
        }
        if(i == length - 1)
        {
            first_digit = (int)temp;
        }
        // If value is even
        if(i % 2 == 0)
        {
            first_pass += temp;
        }
        // If value is odd
        else
        {
            if(temp * 2 < 10)
            {
                second_pass += temp * 2;
            }
            else
            {
                second_pass += (temp*2)%10;
                second_pass += ((temp*2)/10)%10;
            }
        }
    }
    // Add together both passes
    long checksum = first_pass + second_pass;
    // Check if the credit card is valid
    if(checksum % 10 == 0)
    {
        printf("%s\n", check_company(first_digit, second_digit, length));
    }
    else
    {
        printf("INVALID\n");
    }
}



// Check if the number is associated with a specific company.
string check_company(int first_digit, int second_digit, int length)
{
    string invalid = "INVALID";
    switch(first_digit){
        case 3:
            if(length == 15)
            {
                if(second_digit == 4 || second_digit == 7)
                {
                    return "AMEX";
                }
            }
        break;
        case 5:
            if(length == 16)
            {
                if(second_digit > 0 && second_digit < 6)
                {
                    return "MASTERCARD";
                }
            }
        break;
        case 4:
            if(length > 12 && length < 17)
            {
                return "VISA";
            }
        break;
    }
    return invalid;
}

// Return the result of a long long int exponenet calculation
unsigned long long int ipow(unsigned long long int base, int exp)
{
    unsigned long long int result = 1ULL;
    while (exp)
    {
        if (exp & 1)
            result *= (unsigned long long int)base;
        exp >>= 1;
        base *= base;
    }

    return result;
}