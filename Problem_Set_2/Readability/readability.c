#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float count_letters(string ltext);
float count_words(string wtext);
float count_sentences(string stext);

int main(void)
{
    string text = get_string("Text: ");

    float nletters = count_letters(text);
    float nwords = count_words(text);
    float nsentences = count_sentences(text);

    float l = (nletters / nwords) * 100.0;
    float s = (nsentences / nwords) * 100.0;

    float Col_index = (0.0588 * l) - (0.296 * s) - 15.8;

    if (Col_index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (Col_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        int rounded = (int) (Col_index + 0.5);
        printf("Grade %i\n", (int) rounded);
    }
}

float count_letters(string ltext)
{
    int i = 0;
    int lcount = 0;

    while (ltext[i] != '\0')
    {
        char letter = toupper(ltext[i]);
        int nletter = (int) letter;

        if ((nletter > 64) && (nletter < 91))
        {
            lcount++;
        }
        i++;
    }
    return lcount;
}

float count_words(string wtext)
{
    int i = 0;
    int wcount = 1;

    while (wtext[i] != '\0')
    {
        char letter = toupper(wtext[i]);
        int nletter = (int) letter;

        if (nletter == 32)
        {
            wcount++;
        }
        i++;
    }
    return wcount;
}

float count_sentences(string stext)
{
    int i = 0;
    int scount = 0;

    while (stext[i] != '\0')
    {
        char letter = toupper(stext[i]);
        int nletter = (int) letter;

        switch (nletter)
        {
            case 33:
                scount++;
                break;
            case 46:
                scount++;
                break;
            case 63:
                scount++;
                break;
            default:
                break;
        }
        i++;
    }
    return scount;
}
