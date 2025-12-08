#include <stdio.h>
#include "autotests.h"

// __________________________________________________________________________________
int nettoyer_la_scene_autotest(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y])
{
    int x,y;
    int scene_vide = 1;
    printf("\n-------------------------------------\n");
    printf("Fonction autotest nettoyer_la_scene\n");
    for (x=0; x<TAILLE_SCENE_X; x++)
    {
        for (y=0; y<TAILLE_SCENE_Y; y++)
        {
            if (scene[x][y] != CASE_VIDE)
            {
                printf("[Erreur] Case non vide : x=%d / y=%d\n", x, y);
                scene_vide = 0;
            }
        }
    }
    if (scene_vide)     printf("  => Autotest OK\n");
    else                printf("  => Autotest KO\n");
    return scene_vide;
}


// __________________________________________________________________________________
int ajouter_contour_autotest(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y])
{
    int x,y;
    int erreur = 0;
    printf("\n-------------------------------------\n");
    printf("Fonction autotest ajouter_contour\n");

    for (x=0; x<TAILLE_SCENE_X; x++)
    {
        for (y=0; y<TAILLE_SCENE_Y; y++)
        {
            int contour = 0;
            // Recherche si la case est un contour
            if ( (y==0) || (x==0) || (y==TAILLE_SCENE_Y-1) || (x==TAILLE_SCENE_X-1) )
            {
                contour = 1;
            }

            if (contour)   // La case devrait être un contour mais ne l'est pas
            {
                if (scene[x][y] != CASE_CONTOUR)
                {
                    printf("[Erreur] La case x=%d / y=%d devrait etre une CASE_CONTOUR\n", x, y);
                    erreur++;
                }
            }
            else
            {
                if (scene[x][y] == CASE_CONTOUR)
                {
                    printf("[Erreur] La case x=%d / y=%d est une CASE_CONTOUR et ne devrait pas\n", x, y);
                    erreur++;
                }
            }
        }
    }

    if (erreur==0)      printf("  => Autotest OK\n");
    else                printf("  => Autotest KO - %d erreurs\n", erreur);
    return (erreur == 0);
}


// __________________________________________________________________________________
int ajouter_obstacles_autotest(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y])
{
    int x,y;
    int erreur = 0;
    printf("\n-------------------------------------\n");
    printf("Fonction autotest ajouter_obstacles\n");

    for (x=0; x<TAILLE_SCENE_X; x++)
    {
        for (y=0; y<TAILLE_SCENE_Y; y++)
        {
            int obstacle = 0;
            // Recherche si la case est un contour
            if ( ((x==10) && (y>=5)  && (y<15)) ||
                 ((y==5)  && (x>=10) && (x<20)))
            {
                obstacle = 1;
            }

            if (obstacle)   // La case devrait être un contour mais ne l'est pas
            {
                if (scene[x][y] != CASE_OBSTACLE)
                {
                    printf("[Erreur] La case x=%d / y=%d devrait etre une CASE_OBSTACLE\n", x, y);
                    erreur++;
                }
            }
            else
            {
                if (scene[x][y] == CASE_OBSTACLE)
                {
                    printf("[Erreur] La case x=%d / y=%d est une CASE_OBSTACLE et ne devrait pas\n", x, y);
                    erreur++;
                }
            }
        }
    }

    if (erreur==0)      printf("  => Autotest OK\n");
    else                printf("  => Autotest KO - %d erreurs\n", erreur);
    return (erreur == 0);
}

