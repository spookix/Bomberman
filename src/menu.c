/*
 * File:   menu.c
 * Author: mendy_s; soubri_j; martin_m
 *
 * Created on 11 mai 2019
 */

#include "constantes.h"
#include "menu.h"

/**
 * Initialise le menu
 * @return
 */

t_menu* menu_init(t_game* game)
{
    t_menu * menu = NULL;
    menu = malloc(sizeof (t_menu));

    // Textures
    menu->pTextMenu = NULL;
    menu->pTextJeu = NULL;
    menu->pTextQuitter = NULL;
    menu->pTextMenuCurrent = NULL;
    menu->pTextNbrJoueurs = NULL;

    // Positions
    menu->menuPosRect.w = 800;
    menu->menuPosRect.h = 800;
    menu->menuPosRect.x = 0;
    menu->menuPosRect.y = 0;

    //jeu
    game->infos->nbr_joueur = 0;



    // Chargement des textures
    //-------------------------------------------------------------------------
    // Menu principal
    menu->pTextMenu = getTextureFromImagePNG(game,"images/menu1.png");
    menu->pTextJeu = getTextureFromImagePNG(game,"images/menu_jouer.png");
    menu->pTextQuitter = getTextureFromImagePNG(game,"images/menu_quitter.png");

    menu->pTextNbrJoueurs = getTextureFromImagePNG(game,"images/nbr_joueur.png");
    menu->pTextUnJoueur = getTextureFromImagePNG(game,"images/1joueur.png");
    menu->pTextDeuxJoueurs = getTextureFromImagePNG(game,"images/2joueurs.png");
    menu->pTextTroisJoueurs= getTextureFromImagePNG(game,"images/3joueurs.png");
    menu->pTextQuattreJoueurs = getTextureFromImagePNG(game,"images/4joueurs.png");
    //-------------------------------------------------------------------------

    menu->pTextMenuCurrent = menu->pTextMenu;
}

void menu_destroy(t_menu* menu)
{
    if (menu) {

        if(menu->pTextQuattreJoueurs) {
            SDL_DestroyTexture(menu->pTextQuattreJoueurs);
        }

        if(menu->pTextTroisJoueurs) {
            SDL_DestroyTexture(menu->pTextTroisJoueurs);
        }

        if(menu->pTextDeuxJoueurs) {
            SDL_DestroyTexture(menu->pTextDeuxJoueurs);
        }

        if(menu->pTextUnJoueur) {
            SDL_DestroyTexture(menu->pTextUnJoueur);
        }

        if(menu->pTextNbrJoueurs) {
            SDL_DestroyTexture(menu->pTextNbrJoueurs);
        }

        if(menu->pTextMenuCurrent) {
            SDL_DestroyTexture(menu->pTextMenuCurrent);
        }

        if(menu->pTextQuitter) {
            SDL_DestroyTexture(menu->pTextQuitter);
        }

        if(menu->pTextJeu) {
            SDL_DestroyTexture(menu->pTextJeu);
        }

        if(menu->pTextMenu) {
            SDL_DestroyTexture(menu->pTextMenu);
        }
        free(menu);
    }
}

/**
 * Affichage du menu
 * @param game
 */
void menu_draw(t_game* game, t_menu* menu)
{
    SDL_RenderClear(game->infos->pRenderer);

    SDL_RenderCopy(game->infos->pRenderer,menu->pTextMenuCurrent,NULL,&menu->menuPosRect);

    SDL_RenderPresent(game->infos->pRenderer);
}

/**
 * Gestion des evenements
 * @param game
 * @return -1 pour quitter
 */
int menu_event(t_game* game, t_menu* menu)
{
    int result = 0;
    static int var = 0;


    SDL_Event e;
    //Récuperer un evenement
    if (SDL_PollEvent(&e)) {

        if (e.type == SDL_QUIT) {
            //Quitter l'application
            result = -1;
        } else  {

            //Gérer les touche du clavier
            switch(e.type) {
                case SDL_KEYDOWN :
                    if ( e.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
                    //Quitter l'application
                        result = -1;
                    break;

//                case SDLK_UP:
//                case SDLK_DOWN:
                case SDL_MOUSEMOTION:

                        if (var == 0)
                        {
                            if (e.motion.x > 300 && e.motion.x < 460 && e.motion.y > 435 && e.motion.y < 490)
    //                            fprintf(stdout, "\tposition : %d;%d\n",e.motion.x,e.motion.y);
                                menu->pTextMenuCurrent = menu->pTextJeu;
                            else if (e.motion.x > 300 && e.motion.x < 540 && e.motion.y > 470 && e.motion.y < 590)
    //                            fprintf(stdout, "\tposition : %d;%d\n",e.motion.x,e.motion.y);
                                menu->pTextMenuCurrent = menu->pTextQuitter;
                            else
                                menu->pTextMenuCurrent = menu->pTextMenu;
                        } else if (var == 2)
                        {
                            if (e.motion.x > 270 && e.motion.x < 470 && e.motion.y > 400 && e.motion.y < 450)
                                menu->pTextMenuCurrent = menu->pTextUnJoueur;
                            else if (e.motion.x > 270 && e.motion.x < 490 && e.motion.y > 480 && e.motion.y < 525)
                                menu->pTextMenuCurrent = menu->pTextDeuxJoueurs;
                            else if (e.motion.x > 270 && e.motion.x < 490 && e.motion.y > 560 && e.motion.y < 600)
                                menu->pTextMenuCurrent = menu->pTextTroisJoueurs;
                            else if (e.motion.x > 270 && e.motion.x < 490 && e.motion.y > 635 && e.motion.y < 685)
                                menu->pTextMenuCurrent = menu->pTextQuattreJoueurs;
                            else
                                menu->pTextMenuCurrent = menu->pTextNbrJoueurs;
                        }
                    break;

                case SDL_MOUSEBUTTONUP:
                        if (var == 0)
                        {
                            if (e.button.x > 300 && e.button.x < 460 && e.button.y > 435 && e.button.y < 490)
                                {
                                    var = 2;
                                    menu->pTextMenuCurrent = menu->pTextNbrJoueurs;
                                }
                            else if (e.button.x > 300 && e.button.x < 540 && e.button.y > 470 && e.button.y < 590)
                                result = -1;
                        }else if (var == 2)
                        {
                            if (e.button.x > 270 && e.button.x < 470 && e.button.y > 400 && e.button.y < 450)
                            {
                                result = 1;
                                game->infos->nbr_joueur = 1;
                            }
                            else if (e.button.x > 270 && e.button.x < 490 && e.button.y > 480 && e.button.y < 525)
                            {
                                result = 1;
                                game->infos->nbr_joueur = 2;
                            }
                            else if (e.button.x > 270 && e.button.x < 490 && e.button.y > 560 && e.button.y < 600)
                            {
                                result = 1;
                                game->infos->nbr_joueur = 3;
                            }
                            else if (e.button.x > 270 && e.button.x < 490 && e.button.y > 635 && e.button.y < 685)
                            {
                                result = 1;
                                game->infos->nbr_joueur = 4;
                            }
                        }
                    break;

//                default :
//                    fprintf(stderr, "Touche inconnue %d\n", e.key.keysym.sym);
//                    break;
            }

        }

    }
    return result;

}
