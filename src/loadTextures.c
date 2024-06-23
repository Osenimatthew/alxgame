#include "maze.h"

/**
 * loadImages - loads images from file and puts element information in buffer
 * @mapName: name of map loaded
 * Return: void
 */
void loadImages(char *mapName)
{
        SDL_Surface *imgSrc[TOTAL_TEXTURE]; /* array of loaded textures */
        uint8_t *element; /* color value of element at given coordinate */
        int a, b, c; /* loop counters */

        if (strcmp(mapName, "maps/maze_01") == 0)
        {
                imgSrc[0] = IMG_Load("textures/wall1.png");
                imgSrc[1] = IMG_Load("textures/wall2.png");
                imgSrc[2] = IMG_Load("textures/window1.png");
                imgSrc[3] = IMG_Load("textures/window2.png");
                imgSrc[4] = IMG_Load("textures/ceiling.png");
                imgSrc[5] = IMG_Load("textures/floorboard.png");
        }
        else
        {
                imgSrc[0] = IMG_Load("textures/wall1.png");
                imgSrc[1] = IMG_Load("textures/wall2.png");
                imgSrc[2] = IMG_Load("textures/window1.png");
                imgSrc[3] = IMG_Load("textures/window2.png");
                imgSrc[4] = IMG_Load("textures/ceiling.png");
                imgSrc[5] = IMG_Load("textures/floorboard.png");
        }

        /* get colors from texture elements and put in array */
        for (a = 0; a < TOTAL_TEXTURE; a++)
        {
                for (b = 0; b < TEX_HEIGHT; b++)
                {
                        for (c = 0; c < TEX_WIDTH; c++)
                        {
                                element = (uint8_t *)imgSrc[a]->pixels
                                        + c * imgSrc[a]->pitch + b *
                                        imgSrc[a]->format->BytesPerPixel;

tiles[a][b][c] = element[0] | element[1] << 8
                                        | element[2] << 16;
                        }
                }
        }

        /* free SDL_Surfaces */
        for (a = 0; a < TOTAL_TEXTURE; a++)
        {
                SDL_FreeSurface(imgSrc[a]);
                imgSrc[a] = NULL;
        }
}

