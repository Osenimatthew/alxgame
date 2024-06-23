#include "maze.h"

/* global variables */
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
uint32_t tiles[TOTAL_TEXTURE][TEX_HEIGHT][TEX_WIDTH];
point_t pos;
point_t dir;
point_t plane;
double time;

/**
 * main - renders maze
 * @argc: number of arguments
 * @argv: pointer to array of arguments
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
        int *maze; /* 2D array defining maze map */
        char *mapName;
        bool textured;

        /* initial values for global variables */
        pos.x = 1;
        pos.y = 12;
        dir.x = 1;
        dir.y = -0.66;
        plane.x = 0;
        plane.y = 0.66;
        time = 0;

        /* check user arguments and set options */
        mapName = "maps/maze_01";
        textured = true;
        if (argc >= 2)
        {
                mapName = argv[1];
                if (argc == 3 && strcmp(argv[2], "no_tex") == 0)
                {
                       textured = false;
                }
        }

        /* start SDL and create window and renderer */
        if (!initializeSDL())
                return (1);

        /* parse maze file */
        maze = NULL;
        maze = parseMap(mapName, maze);
        if (maze == NULL)
                return (1);

        if (textured)
                loadImages(mapName);

        /* loops until user exits by ESC or closing window */
        while (!end())
        {
                if (!textured)
                        renderBGFlat();

                /* draw walls, textured floor, and textured ceiling */
                raycaster(maze, textured);

                /* handles user input */
                movement(maze);
        }

        /* close SDL, renderer, and window */
        endSDL();
        free(maze);
        return (0);
}

