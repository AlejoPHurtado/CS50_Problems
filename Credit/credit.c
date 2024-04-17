#include <cs50.h>
#include <stdio.h>

int credit_lenth(long l_number);
string credit_type(int t_lenth, long t_number);
string master_visa(long m_number);
int number_valid(long v_number, int v_lenth);

int main(void)
{
    long number = get_long("Credit card number: ");
    // Calculates the lenth of the credit card number.
    int lenth = credit_lenth(number);
    // Checks that the number is valid for a credit card.
    if (number_valid(number, lenth))
    {
        // Checks the franchise of the credit card
        printf("%s\n", credit_type(lenth, number));
    }
    else
    {
        printf("INVALID\n");
    }
}

int credit_lenth(long l_number)
{
    int count = 0;
    do
    {
        l_number = l_number / 10;
        ++count;
    }
    while (l_number != 0);
    return (count);
}

string credit_type(int t_lenth, long t_number)
{
    string type = "INVALID";
    while (t_number > 60)
    {
        t_number /= 10;
    }
    if (t_lenth == 16)
    {
        if ((t_number > 50) && (t_number < 56))
        {
            type = "MASTERCARD";
        }
        else if ((t_number >= 40) && (t_number < 50))
        {
            type = "VISA";
        }
    }
    else if ((t_lenth == 15) && (t_number == 34 || t_number == 37))
    {
        type = "AMEX";
    }
    else if ((t_lenth == 13) && ((t_number >= 40) && (t_number < 50)))
    {
        type = "VISA";
    }
    return (type);
}

int number_valid(long v_number, int v_lenth)
{
    int x = 0;
    int sum1 = 0;
    int sum2 = 0;

    for (int i = 0; i < v_lenth; i++, x = 0)
    {
        x = v_number % 10;
        v_number /= 10;
        if (i % 2)
        {
            x = x * 2;
            if (x > 9)
            {
                while (x)
                {
                    sum1 += x % 10;
                    x /= 10;
                }
            }
            else
            {
                sum1 += x;
            }
        }
        else
        {
            sum2 += x;
        }
    }
    int result = sum1 + sum2;
    int B = result % 10;
    if (B == 0)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}
