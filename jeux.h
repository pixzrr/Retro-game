#ifndef JEUX_H_INCLUDED
#define JEUX_H_INCLUDED

//! Définition de la taille de la scène
#define TAILLE_SCENE_X  50
#define TAILLE_SCENE_Y  40

//! Représentation des éléments de jeu en mémoire
#define CASE_VIDE       0
#define CASE_CONTOUR    1
#define CASE_OBSTACLE   2
#define CASE_PERSONNAGE 3
#define CASE_ENNEMI     4
#define CASE_PIECE_OR   5
#define CASE_VITALITE   6
#define CASE_VIE        7


// Définition de la représentation des éléments sur la scène
#define COULEUR_CASE_VIDE           BLACK
#define COULEUR_CASE_CONTOUR        LIGHT_GRAY
#define COULEUR_CASE_OBSTACLE       BLUE
#define COULEUR_CASE_PERSONNAGE     WHITE
#define COULEUR_CASE_ENNEMI         RED
#define COULEUR_TEXTE_PIECE_OR      YELLOW
#define COULEUR_TEXTE_VITALITE      GREEN

// Sens de déplacement d'un personnage ou ennemi sur le terrain
#define SENS_DEPLACEMENT_HAUT   0
#define SENS_DEPLACEMENT_BAS    1
#define SENS_DEPLACEMENT_GAUCHE 2
#define SENS_DEPLACEMENT_DROITE 3

// Propriétés des personnages
#define NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL    6
// -----------------------------------------------
#define INDEX_PERSONNAGE_POS_X                  0
#define INDEX_PERSONNAGE_POS_Y                  1
#define INDEX_PERSONNAGE_NBRE_VIES_RESTANTES    2
#define INDEX_PERSONNAGE_VITALITE               3
#define INDEX_PERSONNAGE_ETAT_VIRUS             4
#define INDEX_PERSONNAGE_NBRE_PIECES_RECOLTEES  5


#define NBRE_PROPRIETES_ENNEMI                  4
// -----------------------------------------------
#define INDEX_ENNEMI_POS_X                      0
#define INDEX_ENNEMI_POS_Y                      1
#define INDEX_ENNEMI_SENS_DEPLACEMENT           2
#define INDEX_ENNEMI_RALENTISSEMENT_DEPLACEMENT 3


#endif // JEUX_H_INCLUDED
