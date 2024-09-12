#import <cs50.h>
#import <ctype.h>
#import <stdio.h>
#import <stdlib.h>
#import <string.h>

bool number(string number);
char *fcipher(string plain, int ckey);

int main(int argc, char *argv[])
{
    // checks if the command has two arguments
    if (argc == 2)
    {
        if (number(argv[1]))
        {
            int key = atoi(argv[1]);
            if (key > 0)
            {
                // deals with numbers higher than 26
                while (key > 26)
                {
                    key = key - 26;
                }
                string plaintext = get_string("Plaintext:  ");
                string ciphertext = fcipher(plaintext, key);
                printf("Ciphertext: %s\n", ciphertext);
            }
            return 0;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
// checks that argv[1] is a number
bool number(string number)
{
    int i = 0;

    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}
// encripts the text using the key
char *fcipher(string plain, int ckey)
{
    int lplain = strlen(plain);
    string ciphertext = plain;
    for (int i = 0; i < lplain; i++)
    {
        int cipherchar = 0;
        // encription for uppercase
        if ((plain[i] > 64) && (plain[i] < 91))
        {
            cipherchar = (int) plain[i] + ckey;
            if (cipherchar > 90)
            {
                cipherchar = cipherchar - 26;
            }
        }
        // encription for lowercase
        else if (((plain[i] > 96) && (plain[i] < 123)))
        {
            cipherchar = (int) plain[i] + ckey;
            if (cipherchar > 122)
            {
                cipherchar = cipherchar - 26;
            }
        }
        // leaves every character that is not a letter as it is
        else
        {
            cipherchar = plain[i];
        }
        ciphertext[i] = cipherchar;
    }
    return (ciphertext);
}
