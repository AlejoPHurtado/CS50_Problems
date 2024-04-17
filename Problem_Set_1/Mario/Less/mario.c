#include <cs50.h>
#include <stdio.h>

int main()
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    // The height has to be between 1 and 8
    while ((h < 1) || (h > 8));

    for (int i = 0; i < h; i++)
    {
        for (int j = 1; j < h - i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}
