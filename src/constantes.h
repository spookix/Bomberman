#ifndef __CONSTANTES__
#define __CONSTANTES__

    #define STEP_MOVE 50
    #define TAILLE_BLOC             50
//    #define NB_BLOCS_LARGEUR        16      // map de 13 cases jouables + 3 pour les murs et le gris des cotés
//    #define NB_BLOCS_HAUTEUR        16      // map de 11 cases jouables + 2 pour les murs, et équivalent a 3 cases pour le menu des scores
    #define  NB_BLOCS_LARGEUR 16
    #define  NB_BLOCS_HAUTEUR 16
    #define NB_BLOCS_MAP_LARGEUR    15
    #define NB_BLOCS_MAP_hauteur    16
    #define LARGEUR_FENETRE         TAILLE_BLOC * NB_BLOCS_LARGEUR
    #define HAUTEUR_FENETRE         TAILLE_BLOC * NB_BLOCS_HAUTEUR
    #define MAX_PLAYERS             4
    #define MAP_SIZE_L              TAILLE_BLOC * NB_BLOCS_MAP_LARGEUR
    #define MAP_SIZE_H              TAILLE_BLOC * NB_BLOCS_MAP_hauteur

    #define POSITION_J1_X           350     // en haut a gauche
    #define POSITION_J1_Y           200

    #define POSITION_J2_X           650     // en bas a droite
    #define POSITION_J2_Y           700

    #define POSITION_J3_X           650     // en haut a droite
    #define POSITION_J3_Y           200

    #define POSITION_J4_X           150     // en bas a gauche
    #define POSITION_J4_Y           700

    #define FPS                     60


    enum {ALIVE, DEAD};
    enum {HAUT, BAS, GAUCHE, DROITE};
    enum {NORMALE, RAPIDE};
//    enum {GREEN, MUR, BRIQUE, BOMBERMAN};
    enum {HERBE, MUR, BRIQUE, BOMBERMAN,BOMBE};

#endif
