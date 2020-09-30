/*
 * File:   functions.h
 * Author: mendy_s; soubri_j; martin_m
 *
 * Created on 2 mai 2019
 */

#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct {

    //Variable de la SDL
    SDL_Point screenSize;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    //Police d'écriture
    TTF_Font* pFont;

    //Texture
    SDL_Texture* pTextplayers[4][4];
    SDL_Texture* pTextplayer_Test;
    SDL_Texture* bomberman_current[MAX_PLAYERS];
    SDL_Texture* pTextHerbe;
    SDL_Texture* pTextMur;
    SDL_Texture* pTextBrique;
    SDL_Texture* pTextBriqueBase;           // utile pour afficher les briques sur l'image grise des briques
    SDL_Texture* pTextBombe;
    SDL_Texture* pTextFlamme;
    SDL_Texture* pTextFondHaut;
    SDL_Texture* pTextTeteScore;            // les 4 logos de scores
    SDL_Texture* pTextDead;                 // quand le perso meurt

    //Jeu
    int score;
    SDL_Rect teteScorePositionRect[4];      // les positions des logos
    SDL_Rect teteScoreRect[4];              // position des logos sur l'image bomberman_scores.png
    SDL_Rect playerPositionRect;
    SDL_Rect playerRect;                    // les positions du joueur sur l'image
    SDL_Rect playerDeadPositionRect;        // les positions du joueur entrain de mourrir sur l'écran
    SDL_Rect playerDeadRect;                // les positions du joueur entrain de mourrir sur l'image
    SDL_Rect herbePositionRect;
    SDL_Rect murPositionRect;
    SDL_Rect briquePositionRect[4];         // les 4 murs de briques possibles autour de la bombe
    SDL_Rect bombePositionRect;
    SDL_Rect flammeRect[7];
    SDL_Rect briqueRect;
    SDL_Rect flammePositionRect[9];        // les 9 positions des flammes
    SDL_Rect gameplay;
    SDL_Rect fondHautRect;                 // la partie haute du jeu
    int frameTime;                         // pour afficher les flammes avec un cpt pour l'animation
    int frameTimeBrique;                   // pour afficher les briques, comme il y a plus d'animations que pour les flammes
    int cptAnimation;
    int frameTimeDead;                     // pour l'animation de la mort

    int x_Bombe;
    int y_Bombe;

    //joueurs
    int nbr_joueur;

    // scores
    int frameWidthScore;
    int frameHeightScore;
    int textureWidthScore;
    int textureHeightScore;

    // flammes
    int frameWidthFlamme;
    int frameHeightFlamme;
    int textureWidthFlamme;
    int textureHeightFlamme;

    // bombermens
    int frameWidthBomberman;
    int frameHeightBomberman;
    int textureWidthBomberman;
    int textureHeightBomberman;

    // briques
    int frameWidthBrique;
    int frameHeightBrique;
    int textureWidthBrique;
    int textureHeightBrique;
    int briquePresent[8];                 // les 8 cases des flammes autour du centre
    int murPresent[4];                    // les 4 cases des flammes autour du centre, pour éviter qu'une brique derière un mur ne casse

    // pour la carte et les déplacements
    int tabX[8];
    int tabY[8];

    // dead
    int frameWidthDead;
    int frameHeightDead;
    int textureWidthDead;
    int textureHeightDead;

} t_other;

typedef struct       //s_client_request
{
  unsigned int magic;                   /* Un magic number commun entre le client et le serveur, ou l'identifiant d'un type de structure */
//  int x_pos;                            /* La position x souhaitée par le client */
//  int y_pos;                            /* La position y souhaitée par le client */
  SDL_Rect playerPositionRect;
  int dir;                              /* La direction souhaitée par le client */
  int command;                          /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
  int speed;                            /* La vitesse du joueur */
  int ckecksum;                         /* Un checksum simple */
} t_client_request;

typedef struct 	    //s_player_infos   informations sur les joueurs connectés
{
  char connected;
  char alive;
  SDL_Rect playerPositionRect;
  int current_dir;
  int current_speed;
  int max_speed;
  int bombs_left;
  int bombs_capacity;
  int frags;
} t_player_infos;

typedef struct
{
  int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR];
} t_map;


typedef struct      // s_game
{
  t_player_infos * player_infos[MAX_PLAYERS];
  t_other * infos;
  t_map * mapInfos;
} t_game;


    t_game* game_init();
    void game_init_player(t_game* game);
    void game_init_map(t_game* game);
    void game_destroy(t_game* game);
    void game_draw(t_game* game);
    int game_event(t_game* game);
    void game_movePlayer(t_game* game, SDL_Keycode direction);
    SDL_Texture* getTextureFromImagePNG(t_game* game,const char* pathImagePng);
    void to_server(t_game* game);
    void game_loadMap(t_game* game,int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]);
    void game_drawMap(t_game* game);
    void game_searchPositionPlayerIntoCarte(t_game* game);

#endif
