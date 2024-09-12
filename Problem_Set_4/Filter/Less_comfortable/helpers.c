#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float round = 0.5;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float temp =
                (float) ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) /
                         3.0) +
                round;
            image[i][j].rgbtBlue = (int) (temp);
            image[i][j].rgbtGreen = (int) (temp);
            image[i][j].rgbtRed = (int) (temp);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float round = 0.5;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float tempBlue =
                (float) ((0.131 * image[i][j].rgbtBlue) + (0.534 * image[i][j].rgbtGreen) +
                         (0.272 * image[i][j].rgbtRed)) +
                round;
            float tempGreen =
                (float) ((0.168 * image[i][j].rgbtBlue) + (0.686 * image[i][j].rgbtGreen) +
                         (0.349 * image[i][j].rgbtRed)) +
                round;
            float tempRed =
                (float) ((0.189 * image[i][j].rgbtBlue) + (0.769 * image[i][j].rgbtGreen) +
                         (0.393 * image[i][j].rgbtRed)) +
                round;
            if (tempBlue > 255)
            {
                tempBlue = 255;
            }
            if (tempGreen > 255)
            {
                tempGreen = 255;
            }
            if (tempRed > 255)
            {
                tempRed = 255;
            }
            image[i][j].rgbtBlue = (int) (tempBlue);
            image[i][j].rgbtGreen = (int) (tempGreen);
            image[i][j].rgbtRed = (int) (tempRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempPix;
    for (int i = 0; i < height; i++)
    {
        int Pixreflect = width - 1;
        for (int j = 0; j < width / 2; j++)
        {
            if (Pixreflect > j)
            {
                tempPix = image[i][Pixreflect];
                image[i][Pixreflect] = image[i][j];
                image[i][j] = tempPix;
                Pixreflect--;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float round = 0.5;
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avrgRed = 0;
            float avrgGreen = 0;
            float avrgBlue = 0;
            float count = 0;

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    int x = i + dx;
                    int y = j + dy;

                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        avrgRed += copy[x][y].rgbtRed;
                        avrgGreen += copy[x][y].rgbtGreen;
                        avrgBlue += copy[x][y].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = (int) ((avrgRed / count) + round);
            image[i][j].rgbtGreen = (int) ((avrgGreen / count) + round);
            image[i][j].rgbtBlue = (int) ((avrgBlue / count) + round);
        }
    }
    return;
}
