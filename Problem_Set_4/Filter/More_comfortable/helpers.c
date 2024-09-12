#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            float GxRed = 0;
            float GxGreen = 0;
            float GxBlue = 0;
            float GyRed = 0;
            float GyGreen = 0;
            float GyBlue = 0;

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    int x = i + dx;
                    int y = j + dy;

                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        switch (dx)
                        {
                            case -1:
                                switch (dy)
                                {
                                    case -1:
                                        GxRed += -1 * (copy[x][y].rgbtRed);
                                        GxGreen += -1 * (copy[x][y].rgbtGreen);
                                        GxBlue += -1 * (copy[x][y].rgbtBlue);
                                        GyRed += -1 * (copy[x][y].rgbtRed);
                                        GyGreen += -1 * (copy[x][y].rgbtGreen);
                                        GyBlue += -1 * (copy[x][y].rgbtBlue);
                                        break;
                                    case 0:
                                        GxRed += 0 * (copy[x][y].rgbtRed);
                                        GxGreen += 0 * (copy[x][y].rgbtGreen);
                                        GxBlue += 0 * (copy[x][y].rgbtBlue);
                                        GyRed += -2 * (copy[x][y].rgbtRed);
                                        GyGreen += -2 * (copy[x][y].rgbtGreen);
                                        GyBlue += -2 * (copy[x][y].rgbtBlue);
                                        break;
                                    case 1:
                                        GxRed += 1 * (copy[x][y].rgbtRed);
                                        GxGreen += 1 * (copy[x][y].rgbtGreen);
                                        GxBlue += 1 * (copy[x][y].rgbtBlue);
                                        GyRed += -1 * (copy[x][y].rgbtRed);
                                        GyGreen += -1 * (copy[x][y].rgbtGreen);
                                        GyBlue += -1 * (copy[x][y].rgbtBlue);
                                        break;
                                }
                                break;
                            case 0:
                                switch (dy)
                                {
                                    case -1:
                                        GxRed += -2 * (copy[x][y].rgbtRed);
                                        GxGreen += -2 * (copy[x][y].rgbtGreen);
                                        GxBlue += -2 * (copy[x][y].rgbtBlue);
                                        GyRed += 0 * (copy[x][y].rgbtRed);
                                        GyGreen += 0 * (copy[x][y].rgbtGreen);
                                        GyBlue += 0 * (copy[x][y].rgbtBlue);
                                        break;
                                    case 0:
                                        GxRed += 0 * (copy[x][y].rgbtRed);
                                        GxGreen += 0 * (copy[x][y].rgbtGreen);
                                        GxBlue += 0 * (copy[x][y].rgbtBlue);
                                        GyRed += 0 * (copy[x][y].rgbtRed);
                                        GyGreen += 0 * (copy[x][y].rgbtGreen);
                                        GyBlue += 0 * (copy[x][y].rgbtBlue);
                                        break;
                                    case 1:
                                        GxRed += 2 * (copy[x][y].rgbtRed);
                                        GxGreen += 2 * (copy[x][y].rgbtGreen);
                                        GxBlue += 2 * (copy[x][y].rgbtBlue);
                                        GyRed += 0 * (copy[x][y].rgbtRed);
                                        GyGreen += 0 * (copy[x][y].rgbtGreen);
                                        GyBlue += 0 * (copy[x][y].rgbtBlue);
                                        break;
                                }
                                break;
                            case 1:
                                switch (dy)
                                {
                                    case -1:
                                        GxRed += -1 * (copy[x][y].rgbtRed);
                                        GxGreen += -1 * (copy[x][y].rgbtGreen);
                                        GxBlue += -1 * (copy[x][y].rgbtBlue);
                                        GyRed += 1 * (copy[x][y].rgbtRed);
                                        GyGreen += 1 * (copy[x][y].rgbtGreen);
                                        GyBlue += 1 * (copy[x][y].rgbtBlue);
                                        break;
                                    case 0:
                                        GxRed += 0 * (copy[x][y].rgbtRed);
                                        GxGreen += 0 * (copy[x][y].rgbtGreen);
                                        GxBlue += 0 * (copy[x][y].rgbtBlue);
                                        GyRed += 2 * (copy[x][y].rgbtRed);
                                        GyGreen += 2 * (copy[x][y].rgbtGreen);
                                        GyBlue += 2 * (copy[x][y].rgbtBlue);
                                        break;
                                    case 1:
                                        GxRed += 1 * (copy[x][y].rgbtRed);
                                        GxGreen += 1 * (copy[x][y].rgbtGreen);
                                        GxBlue += 1 * (copy[x][y].rgbtBlue);
                                        GyRed += 1 * (copy[x][y].rgbtRed);
                                        GyGreen += 1 * (copy[x][y].rgbtGreen);
                                        GyBlue += 1 * (copy[x][y].rgbtBlue);
                                        break;
                                }
                                break;
                        }
                    }
                }
            }
            int edgeRed = (int) (sqrt(pow(GxRed, 2) + pow(GyRed, 2)) + round);
            int edgeGreen = (int) (sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)) + round);
            int edgeBlue = (int) (sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)) + round);

            if (edgeRed > 255)
            {
                edgeRed = 255;
            }
            if (edgeGreen > 255)
            {
                edgeGreen = 255;
            }
            if (edgeBlue > 255)
            {
                edgeBlue = 255;
            }

            image[i][j].rgbtRed = edgeRed;
            image[i][j].rgbtGreen = edgeGreen;
            image[i][j].rgbtBlue = edgeBlue;
        }
    }
    return;
}
