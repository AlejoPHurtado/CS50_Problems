#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Create a buffer for a block of data
int FAT = 512;
int chunk = 4;
typedef uint8_t BYTE;
typedef enum { false, true } bool;

bool its_jpeg(BYTE array[chunk]);

int main(int argc, char *argv[])
{
    BYTE buffer[FAT];
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *rawfile = fopen(argv[1], "r");
    if (rawfile == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    // Name of new jpeg.
    int numJPG = 0;
    char nameJPG[8];
    sprintf(nameJPG, "%03i.jpg", numJPG);

    // Open output file for first jpeg.
    FILE *outjpeg = fopen(nameJPG, "w");
    if (outjpeg == NULL)
    {
        printf("Could not open %s.\n", nameJPG);
        return 1;
    }

    // While there's still data left to read from the memory card
    while (fread(&buffer, 1, FAT, rawfile) != 0)
    {
        if (its_jpeg(buffer) != false)
        {
            fclose(outjpeg);
            // Create JPEGs from the data

            sprintf(nameJPG, "%03i.jpg", numJPG);
            outjpeg = fopen(nameJPG, "w");
            if (outjpeg == NULL)
            {
                printf("Could not open %s.\n", nameJPG);
                return 1;
            }

            fwrite(&buffer, FAT, 1, outjpeg);
            numJPG += 1;
        }
        else
        {
            fwrite(&buffer, FAT, 1, outjpeg);
        }
    }
    fclose(rawfile);
    fclose(outjpeg);
}

bool its_jpeg(BYTE array[FAT])
{
    if ((array[0] == 0xff) && (array[1] == 0xd8) && (array[2] == 0xff) &&
        ((array[3] & 0xf0) == 0xe0))
    {
        return true;
    }
    return false;
}
