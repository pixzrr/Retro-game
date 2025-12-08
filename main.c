#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include "jeux.h"
#include "autotests.h"

// Prototypes des fonctions à développer
void nettoyer_la_scene(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y]);
void ajouter_contour(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y]);
void ajouter_obstacles(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y]);
void ajouter_personnage_principal(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL], int x_initial, int y_initial);
void ajouter_ennemi(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int ennemi[NBRE_PROPRIETES_ENNEMI], int x_initial, int y_initial, int sens_deplacement_initial);
void ajouter_vitalite(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], int nbre_fioles);
void calculer_vitalite(unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL], int duree_jeu);
void ajouter_pieces_or(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int nbre_pieces);
void deplacer_personnage(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL], int sens_deplacement);
void animer_ennemi(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int ennemi[NBRE_PROPRIETES_ENNEMI]);
int detecter_collision(unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL], unsigned int ennemi[NBRE_PROPRIETES_ENNEMI]);
void debug_personnage_principal(unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL]);
void afficher_informations_jeu(int duree_jeu, int vitalite, int pieces_or, int vies_restantes);

int main()
{
    unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y];
    unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL];    // [0]=position courante x / [1]=position y / [2]=nbre de vies restantes / [3]=vitalité / [4]=virus / [5]=nbre de pièces d'or trouvées
    //unsigned int ennemi1[NBRE_PROPRIETES_ENNEMI];                             // [0]=position x / [1]=position y / [2]=direction / [3]=ralentissement

    nettoyer_la_scene(scene);
    ajouter_contour(scene);
    ajouter_obstacles(scene);

    while ( 1 )
    {
        afficher_scene(scene);
        debug_personnage_principal(personnage_principal);
        Sleep(25);  // Ajuste la vitesse d'animation du jeu
    }

    return 0;
}


// _________________________________________________________________________
/** \brief Créer une scène vierge (efface le contenu du tableau)
 *
 * \param[in,out] scene le tableau contenant la scene à effacer
 * \return --
 *
 */
void nettoyer_la_scene(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y])
{
    for (int x=0 ; x<TAILLE_SCENE_X ; x++) {
        for (int y=0 ; y<TAILLE_SCENE_Y ; y++) scene[x][y] = CASE_VIDE;
    }
}


// _________________________________________________________________________
/** \brief Ajoute le contour sur la scene
 *
 * \param[in,out] scene[TAILLE_SCENE_X][TAILLE_SCENE_Y] la scene sur laquelle ajouter le contour
 * \return --
 *
 */
void ajouter_contour(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y])
{
    for (int y=0 ; y<TAILLE_SCENE_Y ;y++) scene[0][y] = CASE_CONTOUR;
    for (int y=0 ; y<TAILLE_SCENE_Y ;y++) scene[TAILLE_SCENE_X-1][y] = CASE_CONTOUR;
    for (int x=0 ; x<TAILLE_SCENE_X ;x++) scene[x][0] = CASE_CONTOUR;
    for (int x=0 ; x<TAILLE_SCENE_X ;x++) scene[x][TAILLE_SCENE_Y-1] = CASE_CONTOUR;
}


// _________________________________________________________________________
/** \brief Ajoute les obstacles sur la scene
 *
 * \param[in,out] scene[TAILLE_SCENE_X][TAILLE_SCENE_Y] la scene sur laquelle ajouter l'obstacle
 * \return --
 *
 */
void ajouter_obstacles(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y])
{
    for (int x=10 ; x<=20 ; x++) scene[x][5] = CASE_OBSTACLE;
    for (int y=5 ; y<=15; y++) scene[10][y] = CASE_OBSTACLE;
}


// _________________________________________________________________________
/** \brief Place le personnage principal sur la scène et initialise ses propriétéé
 *
 * \param[in,out] scene[TAILLE_SCENE_X][TAILLE_SCENE_Y] la scène sur laquelle ajouter le personnage principal
 * \param personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL] le tableau de propriétés du personnage principal
 * \return --
 *
 */
void ajouter_personnage_principal(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL], int x_initial, int y_initial)
{
    // fonction à implémenter
}

// _________________________________________________________________________
/** \brief Deplace le personnage principal
 *
 * \param[in,out] scene la scène
 * \param[in,out] personnage_principal le tableau de proprietés du personnage principal
 * \param[in] sens_deplacement le sens de deplacement parmi une des 4 valeurs possibles : SENS_DEPLACEMENT_BAS / SENS_DEPLACEMENT_HAUT / SENS_DEPLACEMENT_GAUCHE / SENS_DEPLACEMENT_DROITE
 * \return --
 *
 */
void deplacer_personnage(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y],
                         unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL],
                         int sens_deplacement)
{
    switch (sens_deplacement) {
        case :
    }
}


// _________________________________________________________________________
/** \brief Ajoute un ennemi sur la scene
 *
 * \param[in,out] scene[TAILLE_SCENE_X][TAILLE_SCENE_Y] la scene
 * \param[in,out] ennemi[NBRE_PROPRIETES_ENNEMI] le tableau contenant les proprietes de l'ennemi
 * \param[in] x_initial la position initiale en X de l'ennemi sur la scène
 * \param[in] y_initial la position initiale en Y de l'ennemi sur la scène
 * \param[in] sens_deplacement_initial le sens de déplacement parmi une des 4 valeurs possibles : SENS_DEPLACEMENT_BAS / SENS_DEPLACEMENT_HAUT / SENS_DEPLACEMENT_GAUCHE / SENS_DEPLACEMENT_DROITE
 * \return --
 *
 */
void ajouter_ennemi(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int ennemi[NBRE_PROPRIETES_ENNEMI], int x_initial, int y_initial, int sens_deplacement_initial)
{
    // fonction à implémenter
}


// _________________________________________________________________________
/** \brief Ajoute un nombre de fioles sur la scene
 *
 * \param[in,out] scene[TAILLE_SCENE_X][TAILLE_SCENE_Y] la scene
 * \param[in] nbre_fioles le nombre fioles a ajouter sur la scene
 * \return --
 *
 */
void ajouter_vitalite(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], int nbre_fioles)
{
    // fonction à implémenter
}

// _________________________________________________________________________

/** \brief Gère la diminution du niveau de vitalité tout les Xmsec
 *
 * \param[in,out] personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL] les proprietes du personnage principal
 * \param[in] duree_jeu la durée du jeu en [millisecondes]
 * \return --
 *
 */
void calculer_vitalite(unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL], int duree_jeu)
{
    // fonction à implémenter
}

// _________________________________________________________________________
/** \brief Ajoute un nombre de pieces d'or sur la scene
 *
 * \param[in,out] scene[TAILLE_SCENE_X][TAILLE_SCENE_Y] la scene
 * \param[in] nbre_pieces le nombre de pièces à créer sur la scène
 * \return --
 *
 */
void ajouter_pieces_or(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int nbre_pieces)
{
    // fonction à implémenter
}


// _________________________________________________________________________
/** \brief Anime l'ennemi dont les proprietes sont passees en parametre
 *
 * \param[in,out] scene[TAILLE_SCENE_X][TAILLE_SCENE_Y] la scene
 * \param[in,out] ennemi[NBRE_PROPRIETES_ENNEMI] le tableau contenant les proprietes de l'ennemi
 * \return --
 *
 */
void animer_ennemi(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int ennemi[NBRE_PROPRIETES_ENNEMI])
{
    // fonction à implémenter
}


// _________________________________________________________________________
/** \brief Detecte une collision (positions coincidentes) entre le personnage principal et un ennemi
 *
 * \param[in] personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL] le tableau contenant les proprietes du personnqge principal
 * \param[in] ennemi[NBRE_PROPRIETES_ENNEMI] le tableau contenant les proprietes de l'ennemi
 * \return 0 si aucune collision detectee / 1 si une collision a ete detectee entre le personnage principal et l'ennemi considere
 *
 */
int detecter_collision(unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL], unsigned int ennemi[NBRE_PROPRIETES_ENNEMI])
{
    int collision = 0;

    // fonction à completer

    return collision;
}

// _________________________________________________________________________
/** \brief Affiche la position du personnage principal
 *
 * \param[in] duree_jeu La duree du jeu en msec
 * \param[in] vitalite le niveau de vitalite restant en pourcent
 * \param[in] pieces_or le nombre de pieces d'or
  * \param[in] vies_restantes le nombre de vies restantes
 * \return --
 *
 */
void afficher_informations_jeu(int duree_jeu, int vitalite, int pieces_or, int vies_restantes)
{

}


// _________________________________________________________________________
/** \brief Affiche la position du personnage principal
 *         Completez si besoin cette fonction
 *
 * \param[in] personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL] le tableau contenant les proprietes du personnage principal
 * \return --
 *
 */
void debug_personnage_principal(unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL])
{
    init_text_cursor(0, TAILLE_SCENE_Y+1, WHITE, BLACK);
    printf("Position personnage {x=%d ; y=%d}", personnage_principal[INDEX_PERSONNAGE_POS_X], personnage_principal[INDEX_PERSONNAGE_POS_Y]);
}
