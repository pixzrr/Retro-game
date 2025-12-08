#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "console.h"
#include "jeux.h"



void afficher_scene_brut(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y])
{
    int x, y;
    for(x=0; x < TAILLE_SCENE_X; x++) {
        for (y=0; y <  TAILLE_SCENE_Y; y++) {
            gotoxy(x, y);
            putchar(scene[x][y]);
        }
    }
}
// ----------------------------------------------------------------------



// Le tableau old_scene permet de ne mettre à jour la console que pour les
// cases qui ont changé depuis la dernière mise à jour.
// Cela évite l'effet de clignotement pour un meilleur rendu de jeu
void afficher_scene(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y])
{
    static unsigned char old_scene[TAILLE_SCENE_X][TAILLE_SCENE_Y];
    static unsigned char first_time = 1; // pour initialiser la tableau la première fois

    if (first_time)
    {
        first_time = 0;
        int x, y;
        for(x=0; x < TAILLE_SCENE_X; x++) {
            for (y=0; y <  TAILLE_SCENE_Y; y++) {
               old_scene[x][y] = -1; // valeur inutilisée en fonctionnement nominal pour s'assurer que toute la scène sera mise à jour la première fois
            }
        }
    }

    int x,y;
    for(x=0; x < TAILLE_SCENE_X; x++) {
        for (y=0; y <  TAILLE_SCENE_Y; y++) {
            if (old_scene[x][y] == scene[x][y]) continue;  // pas de rafraichissement si la case n'a pas changé
            old_scene[x][y] = scene[x][y];

            gotoxy(x, y);
            switch(scene[x][y]) {
            case CASE_VIDE :
                setCarForeGroundAndBackGroundColor(' ', BLACK, COULEUR_CASE_VIDE);
                break;
            case CASE_CONTOUR :
                setCarForeGroundAndBackGroundColor(' ', BLACK, COULEUR_CASE_CONTOUR);
                break;
           case CASE_OBSTACLE :
                setCarForeGroundAndBackGroundColor(' ', BLACK, COULEUR_CASE_OBSTACLE);
                break;
            case CASE_PERSONNAGE :
                setCarForeGroundAndBackGroundColor(' ', BLACK, COULEUR_CASE_PERSONNAGE);
                break;
            case CASE_ENNEMI :
                setCarForeGroundAndBackGroundColor(' ', BLACK, COULEUR_CASE_ENNEMI);
                break;
            case CASE_PIECE_OR :
                setCarForeGroundAndBackGroundColor('o', COULEUR_TEXTE_PIECE_OR, BLACK);
                break;
            case CASE_VITALITE :
                setCarForeGroundAndBackGroundColor('V', COULEUR_TEXTE_VITALITE, BLACK);
                break;
            default :
                setCarForeGroundAndBackGroundColor('?', WHITE, RED);
                break;
            }
        }
    }
}


//*****************************************************************************
//*                                                                           *
//*****************************************************************************

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setcolor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void setForeGroundAndBackGroundColor(int ForeGroundColor,int BackGroundColor)
{
    int color=16*BackGroundColor+ForeGroundColor;
    setcolor(color);
}

void setCarForeGroundAndBackGroundColor(unsigned char car, int ForeGroundColor,int BackGroundColor)
{
    setForeGroundAndBackGroundColor(ForeGroundColor, BackGroundColor);
    putchar(car);
}

void clrscr()
{
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}


/** \brief Positionne le curseur à un endroit donné avec la couleur de fond et de texte donné en vu d'afficher du texte
 *
 * \param x la coordonnée X à laquelle positionner le curseur
 * \param y la coordonnée Y à laquelle positionner le curseur
 * \param ForeGroundColor la couleur du texte parmi
 * \param BackGroundColor la couleur de fond du texte
 * \remark les couleurs possibles sont des labels BLACK, WHITE, YELLOW, ...
 * \return --
 *
 */
void init_text_cursor(int x, int y, int ForeGroundColor,int BackGroundColor)
{
    gotoxy(x, y);
    setForeGroundAndBackGroundColor(WHITE, BLACK);
    printf("\t\t\t\t\t\t\t\t\t\t"); // efface les anciennes traces de texte à cet endroit
    setForeGroundAndBackGroundColor(ForeGroundColor, BackGroundColor);
    gotoxy(x, y);
}


/** \brief Vérifie si une touche a été appuyée et renvoie le code touche si c'est le cas.
 * \remark la fonction rend la main immédiatement, qu'une touche soit appuyée ou non
 *
 * \return AUCUNE_TOUCHE_APPUYEE si aucune touche n'est appuyee / le code ASCII de la touche si une touche est appuyée
 *
 */
int touche_appuyee()
{
    int keypress = AUCUNE_TOUCHE_APPUYEE; // valeur par défaut renvoyée si pas de touche appuyée
    if (kbhit()) keypress = getch();
    return keypress;
}

