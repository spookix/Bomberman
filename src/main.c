/*
 * File:   main.c
 * Author: mendy_s; soubri_j; martin_m
 *
 * Created on 2 mai 2019
 */

#include "constantes.h"
#include "functions.h"
#include "menu.h"

/*
    Commpilation:
    windows
        gcc src/*.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2main -lSDL2

    linux Mac
        gcc *.c -o prog $(sdl2-config --cflags --libs)
 */



int main(int argc,char **argv)
{
//    int nbr_joueur = 2;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    t_game* game = game_init();
    t_menu* menu = menu_init(game);

    int quit = 0;
    while(quit != -1 && quit != 1 ) {

        frameStart = SDL_GetTicks();

        //Dessiner le Menu
        menu_draw(game,menu);

        //Gerer les evenement
        quit = menu_event(game, menu);

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game_init_player(game);
    game_init_map(game);

    if (quit == 1){
        while( quit != -1 ) {

            frameStart = SDL_GetTicks();

            //Dessiner le jeu
            game_draw(game);

            //Gerer les evenement
            quit = game_event(game);

            frameTime = SDL_GetTicks() - frameStart;
            if(frameDelay > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }

    menu_destroy(menu);
    game_destroy(game);

    return (EXIT_SUCCESS);
}
