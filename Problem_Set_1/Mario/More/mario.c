#include <cs50.h>
#include <stdio.h>

void left_side(int i, int h);
void right_side(int i);

int main()
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    // Height has to be between 1 and 8
    while ((h < 1) || (h > 8));

    for (int i = 0; i < h; i++)
    {
        left_side(i, h);
        // Prints double space between left side and right side.
        printf("  ");
        right_side(i);
        printf("\n");
    }

    return 0;
}
// Prints left side of the pyramid
void left_side(int i, int h)
{
    for (int j = 1; j < h - i; j++)
    {
        printf(" ");
    }
    for (int k = 0; k <= i; k++)
    {
        printf("#");
    }
}
// Prints right side of the pyramid
void right_side(int i)
{
    for (int k = 0; k <= i; k++)
    {
        printf("#");
    }
}
