#include "maze.h"

/**
 * movement - checks for the keys pressed by user for movement
 * @maze: 2D array defining maze map
 * Return: void
 */
void movement(int *maze)
{
        const uint8_t *keystate; /* key state */
        double prevTime; /* time of previous frame */
        double frameTime; /* time the frame has taken in seconds */
        double prevDirX, prevPlaneX; /* previous direction in x and plane in x */
        double Speed; /* how fast the player moves */
        double turningSpeed; /* speed at which the player rotates */

        keystate = SDL_GetKeyboardState(NULL);
        prevTime = time;
        time = SDL_GetTicks();
        frameTime = (time - prevTime) / 1000.0;
        Speed = (frameTime * 5.0) / 2;
        turningSpeed = (frameTime * 3.0) / 2;

        /* key for moving forward if no wall is in front */
        if (keystate[SDL_SCANCODE_W])
        {
                if (!*((int *)maze + (int)(pos.x + dir.x * Speed)
                       * MAP_WIDTH + (int)pos.y))
                        pos.x += dir.x * Speed;
                if (!*((int *)maze + (int)pos.x * MAP_WIDTH +
                       (int)(pos.y + dir.y * Speed)))
                        pos.y += dir.y * Speed;
        }

        /* key for moving backwards if no wall is behind */
        if (keystate[SDL_SCANCODE_S])
        {
                if (!*((int *)maze + (int)(pos.x - dir.x * Speed) *
                       MAP_WIDTH + (int)(pos.y)))
                        pos.x -= dir.x * Speed;
                if (!*((int *)maze + (int)(pos.x) * MAP_WIDTH +
                       (int)(pos.y - dir.y * Speed)))
		pos.y -= dir.y * Speed;
        }

        /* key for moving to the left */
        if (keystate[SDL_SCANCODE_Q])
        {
                if (!*((int *)maze + (int)(pos.x - plane.x * Speed) *
                       MAP_WIDTH + (int)(pos.y)))
                        pos.x -= plane.x * Speed;
                if (!*((int *)maze + (int)(pos.x) * MAP_WIDTH +
                       (int)(pos.y - plane.y * Speed)))
                        pos.y -= plane.y * Speed;
        }

        /* key for moving to the right */
        if (keystate[SDL_SCANCODE_E])
        {
                if (!*((int *)maze + (int)(pos.x + plane.x * Speed) *
                       MAP_WIDTH + (int)(pos.y)))
                        pos.x += plane.x * Speed;
                if (!*((int *)maze + (int)(pos.x) * MAP_WIDTH +
                       (int)(pos.y + plane.y * Speed)))
                        pos.y += plane.y * Speed;
        }

        /* key for turning to the left */
        if (keystate[SDL_SCANCODE_D])
        {
                /* rotating camera direction the left */
                prevDirX = dir.x;
                dir.x = dir.x * cos(turningSpeed) - dir.y * sin(turningSpeed);
                dir.y = prevDirX * sin(turningSpeed) + dir.y * cos(turningSpeed);

                /* rotating camera plane */
                prevPlaneX = plane.x;
                plane.x = plane.x * cos(turningSpeed) - plane.y * sin(turningSpeed);
                plane.y = prevPlaneX * sin(turningSpeed) + plane.y * cos(turningSpeed);
        }
/* key for turning to the right */
        if (keystate[SDL_SCANCODE_A])
        {
                /* rotating camera direction to the right */
                prevDirX = dir.x;
                dir.x = dir.x * cos(-turningSpeed) - dir.y * sin(-turningSpeed);
                dir.y = prevDirX * sin(-turningSpeed) + dir.y * cos(-turningSpeed);

                /* rotating camera plane */
                prevPlaneX = plane.x;
                plane.x = plane.x * cos(-turningSpeed) - plane.y * sin(-turningSpeed);
                plane.y = prevPlaneX * sin(-turningSpeed) + plane.y * cos(-turningSpeed);
        }
}

/**
 * end - checks if user ended the event
 * Return: True if user ends the event, else False
 */
bool end(void)
{
        SDL_Event event; /* event listener */
        bool end;
        uint32_t windowFlags;

        end = false;
        while (SDL_PollEvent(&event) != 0)
        {
                /* if window's close button is pressed */
                if (event.type == SDL_QUIT)
                        end = true;

                /* if ESC is pressed */
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        end = true;

                /* toggles between windowed and fullscreens */
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
                {
 windowFlags = SDL_GetWindowFlags(window);

                        if (windowFlags & SDL_WINDOW_FULLSCREEN)
                                SDL_SetWindowFullscreen(window, SDL_FALSE);
                        else
                                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
        }

        return (end);
}

