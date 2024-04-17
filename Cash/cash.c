#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int owed = 0;
    int change;
    // Ask the user for the change owed, has to be more than 0.
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);

    while (change > 0)
    {
        // Calculates how many coins you need to give the change owed back.
        if (change >= 25)
        {
            owed = owed + 1;
            change = change - 25;
        }
        else if (change >= 10)
        {
            owed = owed + 1;
            change = change - 10;
        }
        else if (change >= 5)
        {
            owed = owed + 1;
            change = change - 5;
        }
        else
        {
            owed = owed + 1;
            change = change - 1;
        }
    }
    printf("%i\n", owed);

    return 0;
}
