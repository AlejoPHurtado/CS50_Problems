#import <cs50.h>
#import <ctype.h>
#import <stdio.h>
#import <string.h>

int invalidkey(char *ikey);
char *substitution(char *skey, char *splain);

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (invalidkey(argv[1]) == 1)
        {
            return 1;
        }
        else
        {
            string plaintext = get_string("plaintext:  ");
            string ciphertext = substitution(argv[1], plaintext);
            printf("ciphertext: %s\n", ciphertext);
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

int invalidkey(char *ikey)
{
    const int LEN = 26;
    if (strlen(ikey) == 26)
    {
        for (int i = 0; i < LEN; i++)
        {

            if (isalpha(ikey[i]) == 0)
            {
                printf("The key is not alphabetical.\n");
                return 1;
            }
            for (int j = i + 1; j < LEN; j++)
            {
                if (toupper(ikey[i]) == toupper(ikey[j]))
                {
                    printf("Each letter should be exactly once.\n");
                    return 1;
                }
            }
        }
    }
    else
    {
        printf("The key must have 26 alphabetical characters.\n");
        return 1;
    }
    return 0;
}

char *substitution(char *skey, char *splain)
{
    char *scipher = splain;
    int lentext = strlen(splain);
    for (int i = 0; i < lentext; i++)
    {
        int schar = 0;
        if ((splain[i] > 64) && (splain[i] < 91))
        {
            schar = (int) splain[i] - 65;
            scipher[i] = toupper(skey[schar]);
        }
        else if ((splain[i] > 96) && (splain[i] < 123))
        {
            schar = (int) splain[i] - 97;
            scipher[i] = tolower(skey[schar]);
        }
    }
    return (scipher);
}
