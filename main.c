#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include "jeux.h"
#include "autotests.h"
#include <conio.h>
#include <time.h>

// Prototypes des fonctions � d�velopper
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
    unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL];    // [0]=position courante x / [1] =position y / [2]=nbre de vies restantes / [3]=vitalit� / [4]=virus / [5]=nbre de pi�ces d'or trouv�es
    unsigned int ennemi1[NBRE_PROPRIETES_ENNEMI];                             // [0]=position x / [1]=position y / [2]=direction / [3]=ralentissement
    unsigned int ennemi2[NBRE_PROPRIETES_ENNEMI];                             // [0]=position x / [1]=position y / [2]=direction / [3]=ralentissement
    unsigned int ennemi3[NBRE_PROPRIETES_ENNEMI];                             // [0]=position x / [1]=position y / [2]=direction / [3]=ralentissement
    unsigned int tempsattente=25;
    unsigned int tempsmsec=0;
    // variable pour deplacer personnage
    int touche;


    nettoyer_la_scene(scene);
    ajouter_contour(scene);
    ajouter_obstacles(scene);
    int x_debut=5;
    int y_debut=2;
    ajouter_personnage_principal(scene,personnage_principal,x_debut,y_debut);
    x_debut=16;
    y_debut=11;
    ajouter_ennemi(scene, ennemi1,x_debut,y_debut, SENS_DEPLACEMENT_BAS);
    x_debut=20;
    y_debut=30;
    ajouter_ennemi(scene, ennemi2,x_debut,y_debut, SENS_DEPLACEMENT_HAUT);
    x_debut=45;
    y_debut=25;
    ajouter_ennemi(scene, ennemi3,x_debut,y_debut, SENS_DEPLACEMENT_GAUCHE);

    //Parametrer vies restantes
    personnage_principal[INDEX_PERSONNAGE_NBRE_VIES_RESTANTES] = 3;
    personnage_principal[INDEX_PERSONNAGE_VITALITE] = 100;
    unsigned int nbre_de_pieces=7;
    ajouter_pieces_or(scene,nbre_de_pieces);

    unsigned int nbre_fioles=2;
    ajouter_vitalite(scene,nbre_fioles);

    while ( 1 )
    {
        afficher_scene(scene);
        debug_personnage_principal(personnage_principal);
        afficher_informations_jeu(tempsmsec,personnage_principal[INDEX_PERSONNAGE_VITALITE],personnage_principal[INDEX_PERSONNAGE_NBRE_PIECES_RECOLTEES],personnage_principal[INDEX_PERSONNAGE_NBRE_VIES_RESTANTES]);
        Sleep(25);  // Ajuste la vitesse d'animation du jeu
        calculer_vitalite(personnage_principal,tempsmsec);

        //***deplacer personnage
        switch(touche_appuyee()) {
        case key_UP:
            touche = SENS_DEPLACEMENT_HAUT;
            break;
        case key_DOWN:
            touche = SENS_DEPLACEMENT_BAS;
            break;
        case key_LEFT:
            touche = SENS_DEPLACEMENT_GAUCHE;
            break;
        case key_RIGHT:
            touche = SENS_DEPLACEMENT_DROITE;
            break;
        case AUCUNE_TOUCHE_APPUYEE:
            touche = AUCUNE_TOUCHE_APPUYEE;
        }
        //printf("\n\n\n%d\n\n\n", touche); //debug
        deplacer_personnage(scene, personnage_principal, touche);

        //***annimer ennemi
        animer_ennemi(scene, ennemi1);
        animer_ennemi(scene, ennemi2);
        animer_ennemi(scene, ennemi3);

        //***detecter collision
        if (detecter_collision(personnage_principal, ennemi1) == 1) personnage_principal[INDEX_PERSONNAGE_NBRE_VIES_RESTANTES]--;
        if (detecter_collision(personnage_principal, ennemi2) == 1) personnage_principal[INDEX_PERSONNAGE_NBRE_VIES_RESTANTES]--;
        if (detecter_collision(personnage_principal, ennemi3) == 1) personnage_principal[INDEX_PERSONNAGE_NBRE_VIES_RESTANTES]--;

        //***durée jeu
        Sleep(tempsattente);
        tempsmsec=tempsmsec+25;

        //***diminuer  la vie en permanence
        int i;
        i++;
        if (i==3){
            i=0;
            //personnage_principal[INDEX_PERSONNAGE_VITALITE]--;
        }
    }

    return 0;
}


// _________________________________________________________________________
/** \brief Cr�er une sc�ne vierge (efface le contenu du tableau)
 *
 * \param[in,out] scene le tableau contenant la scene � effacer
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
/** \brief Place le personnage principal sur la sc�ne et initialise ses propri�t��
 *
 * \param[in,out] scene[TAILLE_SCENE_X][TAILLE_SCENE_Y] la sc�ne sur laquelle ajouter le personnage principal
 * \param personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL] le tableau de propri�t�s du personnage principal
 * \return --
 *
 */
void ajouter_personnage_principal(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL], int x_initial, int y_initial)
{
    scene[x_initial][y_initial]=CASE_PERSONNAGE;
    personnage_principal[0]=x_initial;
    personnage_principal[1]=y_initial;
}

// _________________________________________________________________________
/** \brief Deplace le personnage principal
 *
 * \param[in,out] scene la sc�ne
 * \param[in,out] personnage_principal le tableau de propriet�s du personnage principal
 * \param[in] sens_deplacement le sens de deplacement parmi une des 4 valeurs possibles : SENS_DEPLACEMENT_BAS / SENS_DEPLACEMENT_HAUT / SENS_DEPLACEMENT_GAUCHE / SENS_DEPLACEMENT_DROITE
 * \return --
 *
 */
void deplacer_personnage(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y],
                         unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL],
                         int sens_deplacement)
{
    int pos_perso_x = personnage_principal[0];
    int pos_perso_y = personnage_principal[1];

    scene[pos_perso_x][pos_perso_y] = CASE_VIDE;

    switch(sens_deplacement) {
        case SENS_DEPLACEMENT_HAUT:
            if (personnage_principal[1]>1 && scene[pos_perso_x][pos_perso_y-1] != CASE_OBSTACLE) personnage_principal[1]--;
            break;
        case SENS_DEPLACEMENT_BAS:
            if (personnage_principal[1]<TAILLE_SCENE_Y-2 && scene[pos_perso_x][pos_perso_y+1] != CASE_OBSTACLE) personnage_principal[1]++;
            break;
        case SENS_DEPLACEMENT_GAUCHE:
            if (personnage_principal[0]>1 && scene[pos_perso_x-1][pos_perso_y] != CASE_OBSTACLE) personnage_principal[0]--;
            break;
        case SENS_DEPLACEMENT_DROITE:
            if (personnage_principal[0]<TAILLE_SCENE_X-2 && scene[pos_perso_x+1][pos_perso_y] != CASE_OBSTACLE) personnage_principal[0]++;
    }

    pos_perso_x = personnage_principal[0];
    pos_perso_y = personnage_principal[1];

     if (scene[pos_perso_x][pos_perso_y] == CASE_PIECE_OR) personnage_principal[INDEX_PERSONNAGE_NBRE_PIECES_RECOLTEES]++;
     if (scene[pos_perso_x][pos_perso_y] == CASE_VITALITE){
        if (personnage_principal[INDEX_PERSONNAGE_VITALITE]<=80) personnage_principal[INDEX_PERSONNAGE_VITALITE]=personnage_principal[INDEX_PERSONNAGE_VITALITE]+20;
        else personnage_principal[INDEX_PERSONNAGE_VITALITE]=100;
     }


    scene[pos_perso_x][pos_perso_y] = CASE_PERSONNAGE;
}


// _________________________________________________________________________
/** \brief Ajoute un ennemi sur la scene
 *
 * \param[in,out] scene[TAILLE_SCENE_X][TAILLE_SCENE_Y] la scene
 * \param[in,out] ennemi[NBRE_PROPRIETES_ENNEMI] le tableau contenant les proprietes de l'ennemi
 * \param[in] x_initial la position initiale en X de l'ennemi sur la sc�ne
 * \param[in] y_initial la position initiale en Y de l'ennemi sur la sc�ne
 * \param[in] sens_deplacement_initial le sens de d�placement parmi une des 4 valeurs possibles : SENS_DEPLACEMENT_BAS / SENS_DEPLACEMENT_HAUT / SENS_DEPLACEMENT_GAUCHE / SENS_DEPLACEMENT_DROITE
 * \return --
 *
 */
void ajouter_ennemi(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int ennemi[NBRE_PROPRIETES_ENNEMI], int x_initial, int y_initial, int sens_deplacement_initial)
{
    scene[x_initial][y_initial]=CASE_ENNEMI;
    ennemi[0]=x_initial;
    ennemi[1]=y_initial;
    ennemi[2] = sens_deplacement_initial;
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
    int i;
    srand( time( NULL ) );
    for (i=0;i<nbre_fioles;i++){
        int valeurx = rand()%48;
        valeurx++;//si cest 0
        int valeury = rand()%38;
        valeury++;//si cest 0
        scene[valeurx][valeury]=CASE_VITALITE;
    }
}

// _________________________________________________________________________

/** \brief G�re la diminution du niveau de vitalit� tout les Xmsec
 *
 * \param[in,out] personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL] les proprietes du personnage principal
 * \param[in] duree_jeu la dur�e du jeu en [millisecondes]
 * \return --
 *
 */
void calculer_vitalite(unsigned int personnage_principal[NBRE_PROPRIETES_PERSONNAGE_PRINCIPAL], int duree_jeu)
{
    if (duree_jeu%75==0){
         personnage_principal[INDEX_PERSONNAGE_VITALITE]--;
    }
    if (personnage_principal[INDEX_PERSONNAGE_VITALITE]==0){
        personnage_principal[INDEX_PERSONNAGE_NBRE_VIES_RESTANTES]--;

        personnage_principal[INDEX_PERSONNAGE_VITALITE]=100;
        init_text_cursor(0, TAILLE_SCENE_Y+7, RED, BLACK);
        printf("La vitalite est de 0 : vous avez perdu une vie!");
        sleep(2);
        init_text_cursor(0, TAILLE_SCENE_Y+7, BLACK, BLACK);
        printf("La vitalité est de 0 : vous avez perdu une vie!");
    }
}

// _________________________________________________________________________
/** \brief Ajoute un nombre de pieces d'or sur la scene
 *
 * \param[in,out] scene[TAILLE_SCENE_X][TAILLE_SCENE_Y] la scene
 * \param[in] nbre_pieces le nombre de pi�ces � cr�er sur la sc�ne
 * \return --
 *
 */
void ajouter_pieces_or(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y], unsigned int nbre_pieces)
{
    int i;
    srand( time( NULL ) );
    for (i=0;i<nbre_pieces;i++){
        int valeurx = rand()%48;
        valeurx++;//si cest 0
        int valeury = rand()%38;
        valeury++;//si cest 0
        scene[valeurx][valeury]=CASE_PIECE_OR;
    }
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
    int pos_ennemi_x = ennemi[0];
    int pos_ennemi_y = ennemi[1];

    scene[pos_ennemi_x][pos_ennemi_y] = CASE_VIDE;

    switch(ennemi[INDEX_ENNEMI_SENS_DEPLACEMENT]) {
        case SENS_DEPLACEMENT_HAUT:
            if (ennemi[1]>1 && scene[pos_ennemi_x][pos_ennemi_y-1] != CASE_OBSTACLE) ennemi[1]--;
            else {
                    ennemi[1]++;
                    ennemi[INDEX_ENNEMI_SENS_DEPLACEMENT] = SENS_DEPLACEMENT_BAS;
            }
            break;
        case SENS_DEPLACEMENT_BAS:
            if (ennemi[1]<TAILLE_SCENE_Y-2 && scene[pos_ennemi_x][pos_ennemi_y+1] != CASE_OBSTACLE) ennemi[1]++;
            else {
                    ennemi[1]--;
                    ennemi[INDEX_ENNEMI_SENS_DEPLACEMENT] = SENS_DEPLACEMENT_HAUT;
            }
            break;
        case SENS_DEPLACEMENT_GAUCHE:
            if (ennemi[0]>1 && scene[pos_ennemi_x-1][pos_ennemi_y] != CASE_OBSTACLE) ennemi[0]--;
            else {
                    ennemi[0]++;
                    ennemi[INDEX_ENNEMI_SENS_DEPLACEMENT] = SENS_DEPLACEMENT_DROITE;
            }
            break;
        case SENS_DEPLACEMENT_DROITE:
            if (ennemi[0]<TAILLE_SCENE_X-2 && scene[pos_ennemi_x+1][pos_ennemi_y] != CASE_OBSTACLE) ennemi[0]++;
            else {
                ennemi[0]--;
                ennemi[INDEX_ENNEMI_SENS_DEPLACEMENT] = SENS_DEPLACEMENT_GAUCHE;
            }
            break;
    }

    pos_ennemi_x = ennemi[0];
    pos_ennemi_y = ennemi[1];

    scene[pos_ennemi_x][pos_ennemi_y] = CASE_ENNEMI;
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

        if (personnage_principal[0] == ennemi[0] && personnage_principal[1] == ennemi[1]){
                Sleep(1500);
                collision = 1;

        }

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
    init_text_cursor(0, TAILLE_SCENE_Y+2, WHITE, BLACK);
    printf("Duree du jeu :%d ",duree_jeu);
    if (vitalite>=25) init_text_cursor(0, TAILLE_SCENE_Y+3, GREEN, BLACK);
    else if (vitalite<25&&vitalite>=10) init_text_cursor(0, TAILLE_SCENE_Y+3, YELLOW, BLACK);
    else init_text_cursor(0, TAILLE_SCENE_Y+3, RED, BLACK);
    printf("Vitalite :%d pct", vitalite);
    init_text_cursor(0, TAILLE_SCENE_Y+4, WHITE, BLACK);
    printf("Pieces d'or :%d ", pieces_or);
    init_text_cursor(0, TAILLE_SCENE_Y+5, WHITE, BLACK);
    printf("Vies_restantes :%d ", vies_restantes);
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
