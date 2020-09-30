/*
 * File:   menu.c
 * Author: mendy_s; soubri_j; martin_m
 *
 * Created on 11 mai 2019
 */

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "functions.h"

typedef struct {
    // Textures
    SDL_Texture* pTextMenu;
    SDL_Texture* pTextJeu;
    SDL_Texture* pTextQuitter;
    SDL_Texture* pTextMenuCurrent;
    SDL_Texture* pTextNbrJoueurs;
    SDL_Texture* pTextUnJoueur;
    SDL_Texture* pTextDeuxJoueurs;
    SDL_Texture* pTextTroisJoueurs;
    SDL_Texture* pTextQuattreJoueurs;

    // dimensions/positions
    SDL_Rect menuPosRect;

} t_menu;

    t_menu* menu_init(t_game* game);
    void menu_destroy(t_menu* menu);
    void menu_draw(t_game* game, t_menu* menu);
    int menu_event(t_game* game, t_menu* menu);

#endif // MENU_H_INCLUDED
