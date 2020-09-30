/*
 * File:   functions.c
 * Author: mendy_s; soubri_j; martin_m
 *
 * Created on 2 mai 2019
 */

#include "constantes.h"
#include "functions.h"


/**
 * Initialise la SDL et le jeu
 * @return
 */
t_game* game_init() {

    //Initialise la séquence aléatoire
//    srand(time(NULL));

    t_game * game = NULL;
    game = malloc(sizeof (t_game));
    game->infos = malloc(sizeof (t_other));
    game->mapInfos = malloc(sizeof (t_map));
    for (int i = 0; i < 4; i++)
    {
        game->player_infos[i] = malloc(sizeof (t_player_infos));
    }
    // ---------- Partie infos ----------------
    game->infos->screenSize.x = MAP_SIZE_L;                // taille totale de la fenetre
    game->infos->screenSize.y = MAP_SIZE_H;
    game->infos->gameplay.w = 650;                              // taille de la partie jouable
    game->infos->gameplay.h = 650;
    game->infos->gameplay.x = 50;
    game->infos->gameplay.y = 150;
    game->infos->pWindow = NULL;
    game->infos->pRenderer = NULL;
    game->infos->pFont = NULL;

    game->infos->playerPositionRect.w = 50;
    game->infos->playerPositionRect.h = 50;

    game->infos->score = 0;
    game->infos->pTextplayers[4][4] = NULL;
    game->infos->bomberman_current[4] = NULL;

    game->infos->pTextHerbe = NULL;
    game->infos->pTextMur = NULL;
    game->infos->pTextBrique = NULL;
    game->infos->pTextBriqueBase = NULL;
    game->infos->pTextBombe = NULL;
    game->infos->pTextFlamme = NULL;
    game->infos->pTextFondHaut = NULL;
    game->infos->pTextTeteScore = NULL;

    game->infos->pTextDead = NULL;

    game->infos->fondHautRect.x = 0;
    game->infos->fondHautRect.y = 0;
    game->infos->fondHautRect.w = 800;
    game->infos->fondHautRect.h = 150;

    for (int i = 0; i < 4; i++)
    {
        game->infos->teteScorePositionRect[i].y = 20;
        game->infos->teteScorePositionRect[i].w = 50;
        game->infos->teteScorePositionRect[i].h = 70;
    }
    game->infos->teteScorePositionRect[0].x = 75;
    game->infos->teteScorePositionRect[1].x = 200;
    game->infos->teteScorePositionRect[2].x = 500;
    game->infos->teteScorePositionRect[3].x = 625;

    game->infos->herbePositionRect.w = 50;
    game->infos->herbePositionRect.h = 50;

    game->infos->murPositionRect.w = 50;
    game->infos->murPositionRect.h = 50;

    for (int i = 0; i < 4; i++)
    {
        game->infos->briquePositionRect[i].w = 50;
        game->infos->briquePositionRect[i].h = 50;
        game->infos->briquePositionRect[i].x = -550;                // hors champs pour éviter d'afficher un mur au centre de la map
        game->infos->briquePositionRect[i].y = -550;
    }

    game->infos->bombePositionRect.x = -550;
    game->infos->bombePositionRect.y = -550;
    game->infos->bombePositionRect.w = 50;
    game->infos->bombePositionRect.h = 50;

    game->infos->playerDeadPositionRect.x = -550;
    game->infos->playerDeadPositionRect.y = -550;
    game->infos->playerDeadPositionRect.w = 50;
    game->infos->playerDeadPositionRect.h = 50;

//    game->infos->nbr_joueur = nbr_joueur;

    // pour la position de la Bombe et vérifier sur la carte le décord pour les flammes
    game->infos->x_Bombe = 0;
    game->infos->y_Bombe = 0;

    // Animations
    game->infos->frameTime = 0;
    game->infos->frameTimeBrique = 0;
    game->infos->frameTimeDead = 0;
    game->infos->cptAnimation = -1;
    for (int i = 0; i < 8; i++)
        game->infos->briquePresent[i] = 0;

    for (int i = 0; i < 4; i++)
        game->infos->murPresent[i] = 0;

    // pour les déplacements, ne pas aller sur un mur en destruction
    for (int i = 0; i < 8; i++)
    {
        game->infos->tabX[i] = 0;
        game->infos->tabY[i] = 0;
    }

    // ---------- Partie player ----------------

//    for (int i = 0; i < 4; i++)
//    {
////        game->player_infos[i]->connected = 1;                            // Joueur connecté, 0 sinon utile quand il y aura plusieurs joueurs
//        game->player_infos[i]->alive = ALIVE;                            // passe en DEAD si il meurt
//        game->player_infos[i]->playerPositionRect.w = 50;
//        game->player_infos[i]->playerPositionRect.h = 50;
////        switch(i) {
////                case 0 :
////                    game->player_infos[i]->playerPositionRect.x = POSITION_J1_X;
////                    game->player_infos[i]->playerPositionRect.y = POSITION_J1_Y;
////                    break;
////
////                case 1:
////                    game->player_infos[i]->playerPositionRect.x = POSITION_J2_X;
////                    game->player_infos[i]->playerPositionRect.y = POSITION_J2_Y;
////                    break;
////
////                case 2:
////                    game->player_infos[i]->playerPositionRect.x = POSITION_J3_X;
////                    game->player_infos[i]->playerPositionRect.y = POSITION_J3_Y;
////                    break;
////
////                case 3:
////                    game->player_infos[i]->playerPositionRect.x = POSITION_J4_X;
////                    game->player_infos[i]->playerPositionRect.y = POSITION_J4_Y;
////                    break;
////
////                default :
////                    fprintf(stderr, "Erreur dans le nombre de joueur");
////                    break;
////        }
//        game->player_infos[i]->current_dir = BAS;                        // 0 = haut, 1 = bas, 2 = gauche, 3 = droite
//        game->player_infos[i]->current_speed = NORMALE;                  // 0 = vitesse normal, 1 = vitesse rapide, modifiable avec bonus
//        game->player_infos[i]->max_speed = RAPIDE;
//        game->player_infos[i]->bombs_left = 0;                           // 0, aucune bombe posée au début
//        game->player_infos[i]->bombs_capacity = 1;                       // nombre de bombe au début du jeu, modifiable avec bonus
//        game->player_infos[i]->frags = 3;                                // nombre de case que la frag atteint, modifiable avec
//    }


    // ---------- Partie Map -------------------

//    int carte1[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] =
//        {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//        {1,3,0,2,2,2,2,2,2,2,2,2,0,0,1},
//        {1,0,1,2,1,2,1,2,1,0,1,2,1,0,1},
//        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
//        {1,2,1,2,1,2,1,2,1,2,1,2,1,2,1},
//        {1,2,2,0,2,2,2,2,2,2,0,0,2,2,1},
//        {1,2,1,2,1,2,1,2,1,2,1,2,1,2,1},
//        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
//        {1,2,1,2,1,2,1,2,1,0,1,2,1,2,1},
//        {1,2,2,0,2,2,2,2,2,2,2,2,2,2,1},
//        {1,0,1,2,1,2,1,2,1,2,1,2,1,0,1},
//        {1,0,0,2,2,2,2,2,2,2,2,2,0,0,1},
//        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//        };
//
////        {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
////        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
////        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
////        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
////        {1,3,0,2,1,2,2,2,2,2,2,2,0,0,1},
////        {1,0,1,2,1,2,2,2,1,1,1,2,1,1,1},
////        {1,1,2,2,1,2,2,2,2,2,1,2,1,2,1},
////        {1,2,2,1,1,1,1,1,1,2,1,2,1,2,1},
////        {1,2,1,2,2,2,2,2,2,2,1,2,1,2,1},
////        {1,2,1,2,1,1,2,1,1,2,1,2,1,2,1},
////        {1,2,1,2,1,1,2,1,1,2,1,2,2,2,1},
////        {1,2,1,2,1,1,2,1,1,2,1,2,1,2,1},
////        {1,2,2,2,2,2,2,1,1,2,1,2,1,1,1},
////        {1,1,1,1,1,1,1,2,2,2,1,2,2,0,1},
////        {1,0,0,2,2,2,2,2,1,1,1,2,2,0,1},
////        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
////        };
//
//    //Chargement de la carte
//    game_loadMap(game,carte1);
//
//    //recherche de la position du joueur dans la carte
//    game_searchPositionPlayerIntoCarte(game);

    // -----------------------------------------

    //Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Impossible d'initialiser la SDL : %s\n", SDL_GetError());
        game_destroy(game);
        return NULL;
    }

    //Initialisation de TTF
    if (TTF_Init() != 0) {
        fprintf(stderr, "Impossible d'initialiser la SDL_TTF : %s\n", TTF_GetError());
        game_destroy(game);
        return NULL;
    }

    //Initialisation de SDL_Image
    if( !IMG_Init(IMG_INIT_PNG) ) {
        fprintf(stderr,("Impossible d'initialiser SDL_Image: %s\n",SDL_GetError()));
        game_destroy(game);
        return NULL;
    }

    //Charger la police d'écriture
    game->infos->pFont = TTF_OpenFont("src/police/arial.ttf",25);
    if (!game->infos->pFont) {
        fprintf(stderr, "Impossible d'ouvrir arial.ttf : %s\n", TTF_GetError());
        game_destroy(game);
        return NULL;
    }

    //Création de la fenetre
    game->infos->pWindow = SDL_CreateWindow("Bomberman",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            game->infos->screenSize.x, game->infos->screenSize.y, SDL_WINDOW_SHOWN);
    if (game->infos->pWindow) {
        //Créer le renderer
        game->infos->pRenderer = SDL_CreateRenderer(game->infos->pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!game->infos->pRenderer) {
            fprintf(stderr, "Impossible de créer le renderer SDL : %s\n", SDL_GetError());
            game_destroy(game);
            return NULL;
        }
    } else {
        fprintf(stderr, "Impossible de créer la fenetre SDL : %s\n", SDL_GetError());
        game_destroy(game);
        return NULL;
    }


        // Chargement de la texture du joueur HAUT
        game->infos->pTextplayers[0][HAUT] = getTextureFromImagePNG(game,"images/bomberman_up1.png");
        game->infos->pTextplayers[1][HAUT] = getTextureFromImagePNG(game,"images/bomberman_up2.png");
        game->infos->pTextplayers[2][HAUT] = getTextureFromImagePNG(game,"images/bomberman_up3.png");
        game->infos->pTextplayers[3][HAUT] = getTextureFromImagePNG(game,"images/bomberman_up4.png");

        // Chargement de la texture du joueur BAS
        game->infos->pTextplayers[0][BAS] = getTextureFromImagePNG(game,"images/bomberman_down1.png");
        game->infos->pTextplayers[1][BAS] = getTextureFromImagePNG(game,"images/bomberman_down2.png");
        game->infos->pTextplayers[2][BAS] = getTextureFromImagePNG(game,"images/bomberman_down3.png");
        game->infos->pTextplayers[3][BAS] = getTextureFromImagePNG(game,"images/bomberman_down4.png");

        // Chargement de la texture du joueur GAUCHE
        game->infos->pTextplayers[0][GAUCHE] = getTextureFromImagePNG(game,"images/bomberman_left1.png");
        game->infos->pTextplayers[1][GAUCHE] = getTextureFromImagePNG(game,"images/bomberman_left2.png");
        game->infos->pTextplayers[2][GAUCHE] = getTextureFromImagePNG(game,"images/bomberman_left3.png");
        game->infos->pTextplayers[3][GAUCHE] = getTextureFromImagePNG(game,"images/bomberman_left4.png");

        // Chargement de la texture du joueur DROIT
        game->infos->pTextplayers[0][DROITE] = getTextureFromImagePNG(game,"images/bomberman_right1.png");
        game->infos->pTextplayers[1][DROITE] = getTextureFromImagePNG(game,"images/bomberman_right2.png");
        game->infos->pTextplayers[2][DROITE] = getTextureFromImagePNG(game,"images/bomberman_right3.png");
        game->infos->pTextplayers[3][DROITE] = getTextureFromImagePNG(game,"images/bomberman_right4.png");
    //    game->infos->pTextplayer_Test = getTextureFromImagePNG(game,"images/sprite_Bombermen.png");


    // affectation des postions courantes
    for (int i = 0; i < 4; i++)
    {
        game->infos->bomberman_current[i] = game->infos->pTextplayers[i][BAS];
    }

    // Chargement de la texture de l'herbe
    game->infos->pTextHerbe = getTextureFromImagePNG(game,"images/herbe.png");


    // Chargement de la texture du mur
    game->infos->pTextMur = getTextureFromImagePNG(game,"images/mur.png");

    // Chargement de la texture de la brique
    game->infos->pTextBrique = getTextureFromImagePNG(game,"images/tiles_briques.png");
    game->infos->pTextBriqueBase = getTextureFromImagePNG(game,"images/brique.png");
//    game->infos->pTextBrique = getTextureFromImagePNG(game,"images/brique.png");

    // Chargement de la texture de la bombe
    game->infos->pTextBombe = getTextureFromImagePNG(game,"images/bombe.png");

    // Chargement de la texture des flammes
    game->infos->pTextFlamme = getTextureFromImagePNG(game,"images/flammes.png");

    // Chargement de la texture du fond en haut du jeu
    game->infos->pTextFondHaut = getTextureFromImagePNG(game,"images/fond_haut.png");

    // Chargement de la texture de l'image du score du Bomberman 1
    game->infos->pTextTeteScore = getTextureFromImagePNG(game,"images/bomberman_scores.png");

    // Chargement de la texture de l'image du Bomberman qui meurt
    game->infos->pTextDead = getTextureFromImagePNG(game,"images/sprite_dead_J1.png");

    //-------------------- Animation -----------------------

    // pour la découpe des flammes
    SDL_QueryTexture(game->infos->pTextFlamme, NULL, NULL, &game->infos->textureWidthFlamme, &game->infos->textureHeightFlamme);

    // pour la découpe des briques
    SDL_QueryTexture(game->infos->pTextBrique, NULL, NULL, &game->infos->textureWidthBrique, &game->infos->textureHeightBrique);

    // pour la découpe des logos de score
    SDL_QueryTexture(game->infos->pTextTeteScore, NULL, NULL, &game->infos->textureWidthScore, &game->infos->textureHeightScore);

    // pour la découpe des logos de sprite_dead_J1
    SDL_QueryTexture(game->infos->pTextDead, NULL, NULL, &game->infos->textureWidthDead, &game->infos->textureHeightDead);

    // pour la découpe des bombermen
//    SDL_QueryTexture(game->infos->pTextplayer_Test, NULL, NULL, &game->infos->textureWidthBomberman, &game->infos->textureHeightBomberman);

    //bomberman dead
    game->infos->frameWidthDead = (game->infos->textureWidthDead / 6) ;
    game->infos->frameHeightDead = game->infos->textureHeightDead;

    //scores logos
    game->infos->frameWidthScore = game->infos->textureWidthScore / 2;
    game->infos->frameHeightScore = game->infos->textureHeightScore / 2;

    //bomberman
    game->infos->frameWidthBomberman = game->infos->textureWidthBomberman / 18;
    game->infos->frameHeightBomberman = game->infos->textureHeightBomberman / 8;

    //flammes
    game->infos->frameWidthFlamme = game->infos->textureWidthFlamme / 7;
    game->infos->frameHeightFlamme = game->infos->textureHeightFlamme / 4;

    //briques
    game->infos->frameWidthBrique = (game->infos->textureWidthBrique / 7) + 2;
    game->infos->frameHeightBrique = game->infos->textureHeightBrique;


    // position sur l'image du bomberman entrain de mourrir pour l'animation
    game->infos->playerDeadRect.w = game->infos->frameWidthDead;
    game->infos->playerDeadRect.h = game->infos->frameHeightDead;
    game->infos->playerDeadRect.x = game->infos->briqueRect.y = 0;

    game->infos->briqueRect.w = game->infos->frameWidthBrique;
    game->infos->briqueRect.h = game->infos->frameHeightBrique;
    game->infos->briqueRect.x = game->infos->briqueRect.y = 0;

    // retangle des positions des logos de score
    for (int i = 0; i < 4; i++)
    {
        game->infos->teteScoreRect[i].w = game->infos->frameWidthScore;
        game->infos->teteScoreRect[i].h = game->infos->frameHeightScore;
    }
    game->infos->teteScoreRect[0].x = game->infos->teteScoreRect[0].y = 0;
    game->infos->teteScoreRect[1].x = game->infos->frameWidthScore;
    game->infos->teteScoreRect[1].y = 0;
    game->infos->teteScoreRect[2].x = 0;
    game->infos->teteScoreRect[2].y = game->infos->frameHeightScore;
    game->infos->teteScoreRect[3].x = game->infos->frameWidthScore;
    game->infos->teteScoreRect[3].y = game->infos->frameHeightScore;

    // retangle des positions du bomberman
    game->infos->playerRect.w = game->infos->frameWidthBomberman;
    game->infos->playerRect.h = game->infos->frameHeightBomberman;
    game->infos->playerRect.x = game->infos->frameWidthBomberman;
    game->infos->playerRect.y = game->infos->frameHeightBomberman;

    // retangle des positions des flammes
    for (int i = 0; i < 7; i++)
    {
        game->infos->flammeRect[i].w = game->infos->frameWidthFlamme;                         // rectangles qui contiennent les tailles des images des flammes
        game->infos->flammeRect[i].h = game->infos->frameHeightFlamme;
        game->infos->flammeRect[i].y = 0;                                                     // Toutes les flammes sont sur la même ligne y = 0
    }

    // rectangles qui contiennent les tailles des positions des flammes
    for (int i = 0; i < 9; i++)
        game->infos->flammePositionRect[i].w = game->infos->flammePositionRect[i].h = 50;



    // rectangles qui contiennent les images des flammes, on les décales pour récupérer chaque images
    game->infos->flammeRect[0].x = 0;
    for (int i = 1; i < 7; i++)
        game->infos->flammeRect[i].x = game->infos->flammeRect[i-1].x + game->infos->frameWidthFlamme;

    return game;
}

/**
 * Initialise les joueurs
 * @return
 */
void game_init_player(t_game* game)
{
    for (int i = 0; i < game->infos->nbr_joueur; i++)
    {
//        game->player_infos[i]->connected = 1;                            // Joueur connecté, 0 sinon utile quand il y aura plusieurs joueurs
        game->player_infos[i]->alive = ALIVE;                            // passe en DEAD si il meurt
        game->player_infos[i]->playerPositionRect.w = 50;
        game->player_infos[i]->playerPositionRect.h = 50;
//        switch(i) {
//                case 0 :
//                    game->player_infos[i]->playerPositionRect.x = POSITION_J1_X;
//                    game->player_infos[i]->playerPositionRect.y = POSITION_J1_Y;
//                    break;
//
//                case 1:
//                    game->player_infos[i]->playerPositionRect.x = POSITION_J2_X;
//                    game->player_infos[i]->playerPositionRect.y = POSITION_J2_Y;
//                    break;
//
//                case 2:
//                    game->player_infos[i]->playerPositionRect.x = POSITION_J3_X;
//                    game->player_infos[i]->playerPositionRect.y = POSITION_J3_Y;
//                    break;
//
//                case 3:
//                    game->player_infos[i]->playerPositionRect.x = POSITION_J4_X;
//                    game->player_infos[i]->playerPositionRect.y = POSITION_J4_Y;
//                    break;
//
//                default :
//                    fprintf(stderr, "Erreur dans le nombre de joueur");
//                    break;
//        }
        game->player_infos[i]->current_dir = BAS;                        // 0 = haut, 1 = bas, 2 = gauche, 3 = droite
        game->player_infos[i]->current_speed = NORMALE;                  // 0 = vitesse normal, 1 = vitesse rapide, modifiable avec bonus
        game->player_infos[i]->max_speed = RAPIDE;
        game->player_infos[i]->bombs_left = 0;                           // 0, aucune bombe posée au début
        game->player_infos[i]->bombs_capacity = 1;                       // nombre de bombe au début du jeu, modifiable avec bonus
        game->player_infos[i]->frags = 3;                                // nombre de case que la frag atteint, modifiable avec
    }
}

/**
 * Initialise la map
 * @return
 */
void game_init_map(t_game* game)
{

int carte1[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] =
                {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,2,2,2,2,2,2,2,2,2,0,0,1},
                {1,0,1,2,1,2,1,2,1,0,1,2,1,0,1},
                {1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                {1,2,1,2,1,2,1,2,1,2,1,2,1,2,1},
                {1,2,2,0,2,2,2,2,2,2,0,0,2,2,1},
                {1,2,1,2,1,2,1,2,1,2,1,2,1,2,1},
                {1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                {1,2,1,2,1,2,1,2,1,0,1,2,1,2,1},
                {1,2,2,0,2,2,2,2,2,2,2,2,2,2,1},
                {1,0,1,2,1,2,1,2,1,2,1,2,1,0,1},
                {1,0,0,2,2,2,2,2,2,2,2,2,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
                };

    if (game->infos->nbr_joueur == 1)
        carte1[4][1] = 3;
    else if (game->infos->nbr_joueur == 2)
    {
        carte1[4][1] = 3;
        carte1[14][13] = 3;
    }
    else if (game->infos->nbr_joueur == 3)
    {
        carte1[4][1] = 3;
        carte1[14][13] = 3;
        carte1[4][13] = 3;
    }
    else
    {
        carte1[4][1] = 3;
        carte1[14][13] = 3;
        carte1[4][13] = 3;
        carte1[14][1] = 3;

    }

    //Chargement de la carte
    game_loadMap(game,carte1);

    //recherche de la position du joueur dans la carte
    game_searchPositionPlayerIntoCarte(game);
}

/**
 * Détruit le jeu puis la SDL
 * @param game
 */
void game_destroy(t_game* game) {

    if (game) {

        if(game->infos->pTextDead) {
            SDL_DestroyTexture(game->infos->pTextDead);
        }

        if(game->infos->pTextTeteScore) {
            SDL_DestroyTexture(game->infos->pTextTeteScore);
        }

        if(game->infos->pTextFondHaut) {
            SDL_DestroyTexture(game->infos->pTextFondHaut);
        }

        if(game->infos->pTextFlamme) {
            SDL_DestroyTexture(game->infos->pTextFlamme);
        }

        if(game->infos->pTextBombe) {
            SDL_DestroyTexture(game->infos->pTextBombe);
        }

        if(game->infos->pTextBriqueBase) {
            SDL_DestroyTexture(game->infos->pTextBriqueBase);
        }

        if(game->infos->pTextBrique) {
            SDL_DestroyTexture(game->infos->pTextBrique);
        }

        if(game->infos->pTextMur) {
            SDL_DestroyTexture(game->infos->pTextMur);
        }

        if(game->infos->pTextHerbe) {
            SDL_DestroyTexture(game->infos->pTextHerbe);
        }

//        if(game->infos->pTextplayer_Test) {
//            SDL_DestroyTexture(game->infos->pTextplayer_Test);
//        }

        for (int i = 0; i < game->infos->nbr_joueur; i++)
        {
            if (game->infos->bomberman_current[i]) {
                SDL_DestroyTexture(game->infos->bomberman_current[i]);
            }
        }

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                if(game->infos->pTextplayers[i][j]) {
                    SDL_DestroyTexture(game->infos->pTextplayers[i][j]);
                }
            }

        if (game->infos->pRenderer) {
            SDL_DestroyRenderer(game->infos->pRenderer);
        }

        if (game->infos->pWindow) {
            SDL_DestroyWindow(game->infos->pWindow);
        }

        if (game->infos->pFont) {
            TTF_CloseFont(game->infos->pFont);
        }

        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        for (int i = 0; i < game->infos->nbr_joueur; i++)
        {
            free(game->player_infos[i]);
        }
        free(game->mapInfos);
        free(game->infos);
        free(game);
    }
}

/**
 * Affichage du jeu
 * @param game
 */
void game_draw(t_game* game) {


    SDL_Rect result;

    //peindre l'écran en vert
    SDL_SetRenderDrawColor(game->infos->pRenderer, 17,122,49,255);
    SDL_RenderClear(game->infos->pRenderer);


    //Afichage de la map
    game_drawMap(game);

    game->infos->frameTime++;
    game->infos->frameTimeBrique++;
    game->infos->frameTimeDead++;

    // afficher le fond jaune en haut du jeu
    SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextFondHaut,NULL,&game->infos->fondHautRect);

    // afficher les logo des scores pour les joueurs
//    for (int i = 0; i < 4; i++)
        SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextTeteScore,&game->infos->teteScoreRect[0],&game->infos->teteScorePositionRect[0]);
        SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextTeteScore,&game->infos->teteScoreRect[1],&game->infos->teteScorePositionRect[1]);
        SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextTeteScore,&game->infos->teteScoreRect[2],&game->infos->teteScorePositionRect[2]);
        SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextTeteScore,&game->infos->teteScoreRect[3],&game->infos->teteScorePositionRect[3]);

    // ---------------- Partie Flammes et bombes -------------------------

     //Afficher la bombe avant les flammes
    if (game->infos->frameTime < 50 && game->infos->cptAnimation == 0)
    {

        SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextBombe,NULL,&game->infos->bombePositionRect);
        if (game->infos->frameTime == 49)
        {
            game->infos->frameTime = 12;
            game->infos->cptAnimation += 1;
        }
    }

    //Afficher les joueur
    for (int i = 0; i < game->infos->nbr_joueur; i++)
    {
        if (game->player_infos[i]->alive == ALIVE)
            SDL_RenderCopy(game->infos->pRenderer, game->infos->bomberman_current[i], NULL, &game->player_infos[i]->playerPositionRect);
    }


    // si l'animation est finis, on sort l'animation et la bombe de l'écran
    if (game->infos->cptAnimation > 3)
        {
            game->infos->bombePositionRect.x = -550;
            game->infos->bombePositionRect.y = -550;
            game->player_infos[0]->bombs_left = 0;
            game->infos->flammePositionRect[0] = game->infos->bombePositionRect;
            game->infos->briqueRect.x = 0;

            // cette boucle permet d'effacer de la carte les briques, seulement après que l'explosion soit finis,
//            pour éviter qu'au moment de l'explosion le joueur passse a travers le mur
            for (int i = 0; i < 8; i++)
                if (game->infos->tabX[i] != 0)
                    game->mapInfos->carte[game->infos->tabX[i]][game->infos->tabY[i]] = 0;

            for (int i = 0; i < 4; i++)
                game->infos->murPresent[i] = 0;
        }

    // permet de mettre les flammes sur la position de la bombe
    if (game->infos->cptAnimation == 0) {

        // le centre
        game->infos->flammePositionRect[0] = game->infos->bombePositionRect;                            // 0

    }

        // x,y  coordonnées du player par rapport à la carte
        int x = game->player_infos[0]->playerPositionRect.x  / TAILLE_BLOC;
        int y = game->player_infos[0]->playerPositionRect.y  / TAILLE_BLOC;


        // vertical haut 1
        game->infos->flammePositionRect[1].x = game->infos->flammePositionRect[0].x;                    // |
        game->infos->flammePositionRect[1].y = game->infos->flammePositionRect[0].y - TAILLE_BLOC;      // 0

        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe-1] == MUR){
            game->infos->flammePositionRect[1].y = -550;    // on le sort du champs si il touche un mur
            game->infos->murPresent[0] = 1;
        }
        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe-1] == BRIQUE)
        {
            // pour stocker le MUR, et le faire disparaitre plus tard
            game->infos->tabX[0] = game->infos->x_Bombe;
            game->infos->tabY[0] = game->infos->y_Bombe-1;

            game->infos->briquePresent[0] = 1;
            // on positionne la brique animé sur la brique de la carte
            game->infos->briquePositionRect[0].x = game->infos->bombePositionRect.x;
            game->infos->briquePositionRect[0].y = game->infos->bombePositionRect.y - TAILLE_BLOC;
        }
        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe-1] == BOMBERMAN && game->infos->cptAnimation < 4 && game->infos->cptAnimation > 1)
            game->player_infos[0]->alive = DEAD;


        // vertical haut 2                                                                              // |
        game->infos->flammePositionRect[2].x = game->infos->flammePositionRect[0].x;                    // |
        game->infos->flammePositionRect[2].y = game->infos->flammePositionRect[1].y - TAILLE_BLOC;      // 0

        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe - 2] == MUR)
           game->infos->flammePositionRect[2].y = -550;
        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe - 2] == BRIQUE && game->infos->briquePresent[0] == 0 && game->infos->murPresent[0] == 0)
        {
            game->infos->tabX[1] = game->infos->x_Bombe;
            game->infos->tabY[1] = game->infos->y_Bombe - 2;

            game->infos->briquePresent[1] = 1;
            game->infos->briquePositionRect[0].x = game->infos->bombePositionRect.x;
            game->infos->briquePositionRect[0].y = game->infos->bombePositionRect.y - (2 * TAILLE_BLOC);
        }
        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe-2] == BOMBERMAN && game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe-1] != BRIQUE && game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe-1] != MUR && game->infos->cptAnimation < 4 && game->infos->cptAnimation > 1)
            game->player_infos[0]->alive = DEAD;



        // vertical bas 1
        game->infos->flammePositionRect[3].x = game->infos->flammePositionRect[0].x;                    // 0
        game->infos->flammePositionRect[3].y = game->infos->flammePositionRect[0].y + TAILLE_BLOC;      // |

        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe + 1] == MUR)
        {
            game->infos->flammePositionRect[3].y = -550;
            game->infos->murPresent[1] = 1;
        }
        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe + 1] == BRIQUE)
        {
            game->infos->tabX[2] = game->infos->x_Bombe;
            game->infos->tabY[2] = game->infos->y_Bombe + 1;

            game->infos->briquePresent[2] = 1;
            game->infos->briquePositionRect[1].x = game->infos->bombePositionRect.x;
            game->infos->briquePositionRect[1].y = game->infos->bombePositionRect.y + TAILLE_BLOC;
        }
        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe+1] == BOMBERMAN && game->infos->cptAnimation < 4 && game->infos->cptAnimation > 1)
            game->player_infos[0]->alive = DEAD;


        // vertical bas 2                                                                               // 0
        game->infos->flammePositionRect[4].x = game->infos->flammePositionRect[0].x;                    // |
        game->infos->flammePositionRect[4].y = game->infos->flammePositionRect[3].y + TAILLE_BLOC;      // |

        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe + 2] == MUR)
            game->infos->flammePositionRect[4].y = -550;

        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe + 2] == BRIQUE && game->infos->briquePresent[2] == 0 && game->infos->murPresent[1] == 0)
        {
            game->infos->tabX[3] = game->infos->x_Bombe;
            game->infos->tabY[3] = game->infos->y_Bombe + 2;

            game->infos->briquePresent[3] = 1;
            game->infos->briquePositionRect[1].x = game->infos->bombePositionRect.x;
            game->infos->briquePositionRect[1].y = game->infos->bombePositionRect.y + (2 * TAILLE_BLOC);
        }
        if(game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe+2] == BOMBERMAN && game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe+1] != BRIQUE && game->mapInfos->carte[game->infos->x_Bombe][game->infos->y_Bombe+1] != MUR && game->infos->cptAnimation < 4 && game->infos->cptAnimation > 1)
            game->player_infos[0]->alive = DEAD;




        // Horizontal droite 1
        game->infos->flammePositionRect[5].x = game->infos->flammePositionRect[0].x + TAILLE_BLOC;      // 0-
        game->infos->flammePositionRect[5].y = game->infos->flammePositionRect[0].y;

        if(game->mapInfos->carte[game->infos->x_Bombe + 1][game->infos->y_Bombe] == MUR)
        {
            game->infos->flammePositionRect[5].x = -550;
            game->infos->murPresent[2] = 1;
        }
        if(game->mapInfos->carte[game->infos->x_Bombe + 1][game->infos->y_Bombe] == BRIQUE)
        {
            game->infos->tabX[4] = game->infos->x_Bombe + 1;
            game->infos->tabY[4] = game->infos->y_Bombe;

            game->infos->briquePresent[4] = 1;
            game->infos->briquePositionRect[2].x = game->infos->bombePositionRect.x + TAILLE_BLOC;
            game->infos->briquePositionRect[2].y = game->infos->bombePositionRect.y;
        }
        if(game->mapInfos->carte[game->infos->x_Bombe+1][game->infos->y_Bombe] == BOMBERMAN && game->infos->cptAnimation < 4 && game->infos->cptAnimation > 1)
            game->player_infos[0]->alive = DEAD;


        // Horizontal droite 2
        game->infos->flammePositionRect[6].x = game->infos->flammePositionRect[5].x + TAILLE_BLOC;      // 0--
        game->infos->flammePositionRect[6].y = game->infos->flammePositionRect[0].y;

        if(game->mapInfos->carte[game->infos->x_Bombe + 2][game->infos->y_Bombe] == MUR)
            game->infos->flammePositionRect[6].y = -550;
        if(game->mapInfos->carte[game->infos->x_Bombe + 2][game->infos->y_Bombe] == BRIQUE  && game->infos->briquePresent[4] == 0 && game->infos->murPresent[2] == 0)
        {
            game->infos->tabX[5] = game->infos->x_Bombe + 2;
            game->infos->tabY[5] = game->infos->y_Bombe;

            game->infos->briquePresent[5] = 1;
            game->infos->briquePositionRect[2].x = game->infos->bombePositionRect.x + (2 * TAILLE_BLOC);
            game->infos->briquePositionRect[2].y = game->infos->bombePositionRect.y;
        }
        if(game->mapInfos->carte[game->infos->x_Bombe+2][game->infos->y_Bombe] == BOMBERMAN && game->mapInfos->carte[game->infos->x_Bombe+1][game->infos->y_Bombe] != BRIQUE && game->mapInfos->carte[game->infos->x_Bombe+1][game->infos->y_Bombe] != MUR && game->infos->cptAnimation < 4 && game->infos->cptAnimation > 1)
            game->player_infos[0]->alive = DEAD;


        // Horizontal gauche 1
        game->infos->flammePositionRect[7].x = game->infos->flammePositionRect[0].x - TAILLE_BLOC;      // -0
        game->infos->flammePositionRect[7].y = game->infos->flammePositionRect[0].y;

        if(game->mapInfos->carte[game->infos->x_Bombe - 1][game->infos->y_Bombe] == MUR)
        {
            game->infos->flammePositionRect[7].x = -550;
            game->infos->murPresent[3] = 1;
        }
        if(game->mapInfos->carte[game->infos->x_Bombe - 1][game->infos->y_Bombe] == BRIQUE)
        {
            game->infos->tabX[6] = game->infos->x_Bombe - 1;
            game->infos->tabY[6] = game->infos->y_Bombe;

            game->infos->briquePresent[6] = 1;
            game->infos->briquePositionRect[3].x = game->infos->bombePositionRect.x - TAILLE_BLOC;
            game->infos->briquePositionRect[3].y = game->infos->bombePositionRect.y;
        }
        if(game->mapInfos->carte[game->infos->x_Bombe-1][game->infos->y_Bombe] == BOMBERMAN && game->infos->cptAnimation < 4 && game->infos->cptAnimation > 1)
            game->player_infos[0]->alive = DEAD;


        // Horizontal gauche 2
        game->infos->flammePositionRect[8].x = game->infos->flammePositionRect[7].x - TAILLE_BLOC;      // --0
        game->infos->flammePositionRect[8].y = game->infos->flammePositionRect[0].y;

        if(game->mapInfos->carte[game->infos->x_Bombe - 2][game->infos->y_Bombe] == MUR)
            game->infos->flammePositionRect[8].y = -550;
        if(game->mapInfos->carte[game->infos->x_Bombe - 2][game->infos->y_Bombe] == BRIQUE && game->infos->briquePresent[6] == 0 && game->infos->murPresent[3] == 0)
        {
            game->infos->tabX[7] = game->infos->x_Bombe - 2;
            game->infos->tabY[7] = game->infos->y_Bombe;

            game->infos->briquePresent[7] = 1;
            game->infos->briquePositionRect[3].x = game->infos->bombePositionRect.x - (2 * TAILLE_BLOC);
            game->infos->briquePositionRect[3].y = game->infos->bombePositionRect.y;
        }
        if(game->mapInfos->carte[game->infos->x_Bombe-2][game->infos->y_Bombe] == BOMBERMAN && game->mapInfos->carte[game->infos->x_Bombe-1][game->infos->y_Bombe] != BRIQUE && game->mapInfos->carte[game->infos->x_Bombe-1][game->infos->y_Bombe] != MUR && game->infos->cptAnimation < 4 && game->infos->cptAnimation > 1)
            game->player_infos[0]->alive = DEAD;


    // si on a posé une bombe, et que l'animation de flammes commence
    if ( game->infos->cptAnimation > 0 )
    {
        if (game->infos->frameTimeBrique > 3 && game->infos->cptAnimation < 4)
        {
            game->infos->briqueRect.x += game->infos->frameWidthBrique;
            if (game->infos->briqueRect.x >= game->infos->textureWidthBrique)
                for (int i = 0; i < 4; i++)
                    game->infos->briquePositionRect[i].x = game->infos->briquePositionRect[i].y = -550;
            game->infos->frameTimeBrique = 0;

        }

        if (game->player_infos[0]->alive == DEAD && game->infos->frameTimeDead > 15)
        {
            game->infos->playerDeadRect.x += game->infos->frameWidthDead;
            if (game->infos->playerDeadRect.x >= game->infos->textureWidthDead)
                    game->infos->playerDeadPositionRect.x = game->infos->playerDeadPositionRect.y = -550;
            game->infos->frameTimeDead = 0;
        }


        // affichage des flammes, pas de boucle car l'indice de flammeRect est different de flammePositionRect
        SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextFlamme,&game->infos->flammeRect[0],&game->infos->flammePositionRect[0]);
        if (game->infos->briquePresent[0] == 0)
            SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextFlamme,&game->infos->flammeRect[1],&game->infos->flammePositionRect[1]);
        if (game->infos->briquePresent[0] == 0 && game->infos->briquePresent[1] == 0)
            SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextFlamme,&game->infos->flammeRect[3],&game->infos->flammePositionRect[2]);
        if (game->infos->briquePresent[2] == 0 )
            SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextFlamme,&game->infos->flammeRect[1],&game->infos->flammePositionRect[3]);
        if (game->infos->briquePresent[2] == 0 && game->infos->briquePresent[3] == 0)
            SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextFlamme,&game->infos->flammeRect[4],&game->infos->flammePositionRect[4]);
        if (game->infos->briquePresent[4] == 0 )
            SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextFlamme,&game->infos->flammeRect[2],&game->infos->flammePositionRect[5]);
        if (game->infos->briquePresent[4] == 0 && game->infos->briquePresent[5] == 0)
            SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextFlamme,&game->infos->flammeRect[5],&game->infos->flammePositionRect[6]);
        if (game->infos->briquePresent[6] == 0)
            SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextFlamme,&game->infos->flammeRect[2],&game->infos->flammePositionRect[7]);
        if (game->infos->briquePresent[6] == 0 && game->infos->briquePresent[7] == 0)
            SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextFlamme,&game->infos->flammeRect[6],&game->infos->flammePositionRect[8]);


        if (game->player_infos[0]->alive == DEAD)
        {
            game->infos->playerDeadPositionRect = game->player_infos[0]->playerPositionRect;
            SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextDead,&game->infos->playerDeadRect,&game->infos->playerDeadPositionRect);
//            game->player_infos[0]->alive = ALIVE;
        }


    }

    //changer les flammes, parcoure l'image et découpe les flammes pour réaliser l'animation

    if (game->infos->frameTime == 12 && game->infos->cptAnimation < 4 && game->infos->cptAnimation > 0)
    {
        game->infos->frameTime = 0;
        game->infos->cptAnimation += 1;
        for (int i = 0; i < 7; i ++)
         {
             game->infos->flammeRect[i].y += game->infos->frameHeightFlamme;

             if (game->infos->flammeRect[i].y >= game->infos->textureHeightFlamme)
                game->infos->flammeRect[i].y = 0;
         }


    }

    // ----------------------------------- Fin de partie flammes et bombes -------------------------------------------------------------




//    SDL_RenderCopy(game->infos->pRenderer, game->infos->pTextplayer_Test, &game->infos->playerRect,&game->player_infos[0]->playerPositionRect);

    //Afficher des briques animées
    for (int i = 0; i < 4; i++)
        SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextBrique,&game->infos->briqueRect,&game->infos->briquePositionRect[i]);


    //Afficher le score du jouer
    SDL_Color textColor = {255,255,255,255};
    char text[40];
    snprintf(text, 40, "Score : %d", game->infos->score);
    SDL_Surface* textSurface = TTF_RenderText_Solid(game->infos->pFont, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->infos->pRenderer, textSurface);
    SDL_Rect destinationText = {0,0,100,20};
    SDL_RenderCopy(game->infos->pRenderer, textTexture, NULL, &destinationText);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);

    //Présenter le rendu
    SDL_RenderPresent(game->infos->pRenderer);
}

/**
 * Gestion des evenements
 * @param game
 * @return -1 pour quitter
 */
int game_event(t_game* game) {
    int result = 0;


    SDL_Event e;
    //Récuperer un evenement
    if (SDL_PollEvent(&e)) {

        if (e.type == SDL_QUIT) {
            //Quitter l'application
            result = -1;
        } else if (e.type == SDL_KEYDOWN) {

            //Gérer les touche du clavier
            switch(e.key.keysym.sym) {
                case SDLK_ESCAPE :
                    //Quitter l'application
                    result = -1;
                    break;

                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_LEFT:
                case SDLK_RIGHT:
                case SDLK_SPACE:
                    game_movePlayer(game, e.key.keysym.sym);
                    break;
                default :
                    fprintf(stderr, "Touche inconnue %d\n", e.key.keysym.sym);
                    break;
            }

        }

    }

    return result;
}


/**
 * Déplace le joueur
 * @param game
 * @param direction
 */
void game_movePlayer(t_game* game, SDL_Keycode direction) {

    SDL_Rect result;
    // x,y  coordonnées du player par rapport à la carte
    int x = game->player_infos[0]->playerPositionRect.x  / TAILLE_BLOC;
    int y = game->player_infos[0]->playerPositionRect.y  / TAILLE_BLOC;

    // commentaires que sur la première condition car le code se répéte

    if (game->player_infos[0]->alive == ALIVE)
    {
        // si on monte
        if (direction == SDLK_UP) {
            // si on ne va pas dans un mur
            if(game->mapInfos->carte[x][y-1] != MUR && game->mapInfos->carte[x][y-1] != BRIQUE) {
                //on déplace le joueur vers le haut
                game->player_infos[0]->playerPositionRect.y -= STEP_MOVE;
                // on modifie sa position
                game->infos->bomberman_current[0] = game->infos->pTextplayers[0][HAUT];
                // on indique sa direction pour l'envoyer au serveur
                game->player_infos[0]->current_dir = HAUT;
                // on change la place sur la carte du joueur
                game->mapInfos->carte[x][y] = 0;
                game->mapInfos->carte[x][y-1] = 3;
            }

        } else if (direction == SDLK_DOWN) {
            if(game->mapInfos->carte[x][y+1] != MUR && game->mapInfos->carte[x][y+1] != BRIQUE) {
                game->player_infos[0]->playerPositionRect.y += STEP_MOVE;
                game->infos->bomberman_current[0] = game->infos->pTextplayers[0][BAS];
                game->player_infos[0]->current_dir = BAS;
                game->mapInfos->carte[x][y] = 0;
                game->mapInfos->carte[x][y+1] = 3;
            }

        } else if (direction == SDLK_LEFT) {
            if( game->mapInfos->carte[x-1][y] != MUR && game->mapInfos->carte[x-1][y] != BRIQUE ) {
                game->player_infos[0]->playerPositionRect.x -= STEP_MOVE;
                game->infos->bomberman_current[0] = game->infos->pTextplayers[0][GAUCHE];
                game->player_infos[0]->current_dir = GAUCHE;
                game->mapInfos->carte[x][y] = 0;
                game->mapInfos->carte[x-1][y] = 3;
            }

        } else if (direction == SDLK_RIGHT) {
            if( game->mapInfos->carte[x+1][y] != MUR && game->mapInfos->carte[x+1][y] != BRIQUE ) {
                game->player_infos[0]->playerPositionRect.x += STEP_MOVE;
                game->infos->bomberman_current[0] = game->infos->pTextplayers[0][DROITE];
                game->player_infos[0]->current_dir = DROITE;
                game->mapInfos->carte[x][y] = 0;
                game->mapInfos->carte[x+1][y] = 3;
            }

        } else if (direction == SDLK_SPACE) {
            if (game->player_infos[0]->bombs_left != 1 )
            {
                game->infos->bombePositionRect = game->player_infos[0]->playerPositionRect;
                game->infos->x_Bombe = game->infos->bombePositionRect.x / TAILLE_BLOC;
                game->infos->y_Bombe = game->infos->bombePositionRect.y / TAILLE_BLOC;
                game->player_infos[0]->bombs_left = 1;                                       // indique que le joueur a poser une bombe
                game->infos->cptAnimation = 0;
                game->infos->frameTime = 0;
                for (int i = 0; i < 8; i++)
                    game->infos->briquePresent[i] = 0;
            }
        } else {
            fprintf(stderr, "Direction inconnue !\n");
        }
    }
}


/*
* Charge la texture des PNG
* @param game
* @param pathImagePng
*/
SDL_Texture* getTextureFromImagePNG(t_game* game,const char* pathImagePng)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(pathImagePng);
    if(surface == NULL) {
        fprintf(stderr,"Impossible de charger l'image: %s\n",IMG_GetError());
        game_destroy(game);
        return NULL;
    } else {
        texture = SDL_CreateTextureFromSurface(game->infos->pRenderer,surface);
        if(!texture) {
           fprintf(stderr,"Erreur du traitement de la texture: %s\n",IMG_GetError());
            game_destroy(game);
            return NULL;
        }
        SDL_FreeSurface(surface);
    }
    return texture;
}

void to_server(t_game* game)
{
    t_client_request * client_request = NULL;
    client_request = malloc(sizeof (t_client_request));

//    client_request->magic = ?
    client_request->playerPositionRect = game->player_infos[0]->playerPositionRect;
    client_request->dir = game->player_infos[0]->current_dir;
    client_request->command = game->player_infos[0]->bombs_left;
    client_request->speed = game->player_infos[0]->current_speed;
//    client_request->ckecksum = ?
}


/*
* Charge la carte
* @param game
* @param carte
*/
void game_loadMap(t_game* game,int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR])
{
    for(int i = 0; i < NB_BLOCS_LARGEUR; i++)
    {
       for(int j = 0; j < NB_BLOCS_HAUTEUR; j++)
       {
           game->mapInfos->carte[j][i] = carte[i][j];
       }

    }

}

/*
* Dessine la carte
* @param game
*/
void game_drawMap(t_game* game)
{
    SDL_Rect position;
    int type = 0;
    for(int i = 0; i < NB_BLOCS_LARGEUR; i++)
    {
       for(int j = 0; j < NB_BLOCS_HAUTEUR; j++)
       {
           position.x = TAILLE_BLOC * j;
           position.y = (TAILLE_BLOC * i) ;
           position.w = TAILLE_BLOC;
           position.h = TAILLE_BLOC;
           type = game->mapInfos->carte[j][i];
           switch (type)
           {
                case HERBE:
                    SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextHerbe,NULL,&position);
                break;
                case MUR:
                    SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextMur,NULL,&position);
                break;
                case BRIQUE:
//                    SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextBrique,&game->infos->briqueRect,&position);
                    SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextBriqueBase,NULL,&position);
                break;
                case BOMBE:
                    SDL_RenderCopy(game->infos->pRenderer,game->infos->pTextBombe,NULL,&position);
                break;

               default:
                   break;
           }
       }
    }
}

void game_searchPositionPlayerIntoCarte(t_game* game)
{
    for(int i = 0; i < NB_BLOCS_LARGEUR; i++)
    {
       for(int j = 0; j < NB_BLOCS_HAUTEUR; j++)
       {
           if(game->mapInfos->carte[j][i] == BOMBERMAN) {
                if (j < 5 && i < 5)
               {
                   game->player_infos[0]->playerPositionRect.x = j * TAILLE_BLOC;
                   game->player_infos[0]->playerPositionRect.y = i * TAILLE_BLOC;
                   game->mapInfos->carte[j][i] = HERBE;
               }else if (j > 5 && i > 5)
               {
                   game->player_infos[1]->playerPositionRect.x = j * TAILLE_BLOC;
                   game->player_infos[1]->playerPositionRect.y = i * TAILLE_BLOC;
                   game->mapInfos->carte[j][i] = HERBE;
               }else if (j > 5 && i < 5)
               {
                   game->player_infos[2]->playerPositionRect.x = j * TAILLE_BLOC;
                   game->player_infos[2]->playerPositionRect.y = i * TAILLE_BLOC;
                   game->mapInfos->carte[j][i] = HERBE;
               }else if (j < 5 && i > 5)
               {
                   game->player_infos[3]->playerPositionRect.x = j * TAILLE_BLOC;
                   game->player_infos[3]->playerPositionRect.y = i * TAILLE_BLOC;
                   game->mapInfos->carte[j][i] = HERBE;
               }
           }
       }
    }
}
