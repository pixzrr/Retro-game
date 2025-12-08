#ifndef _HEADER_CONSOLE_H_
#define _HEADER_CONSOLE_H_

#include <windows.h>
#include <windef.h>
#include <wincon.h>

#include "jeux.h"

// constantes

// Codes touches renvoyées par la fonction touche_appuyee()
#define AUCUNE_TOUCHE_APPUYEE -1
#define key_F1      59
#define key_UP      72
#define key_DOWN    80
#define key_LEFT    75
#define key_RIGHT   77
#define key_SPACE   32
#define key_ENTER   13
#define key_ESCAPE  27
#define key_TAB     9
#define key_INSERT  82


// Constantes des couleurs
#define BLACK           0
#define BLUE            1
#define GREEN           2
#define CYAN            3
#define RED             4
#define MAGENTA         5
#define YELLOW          6
#define LIGHT_GRAY      7
#define DARK_GRAY       8
#define LIGHT_BLUE      9
#define LIGHT_GREEN     10
#define LIGHT_CYAN      11
#define LIGHT_RED       12
#define LIGHT_MAGENTA   13
#define LIGHT_YELLOW    14
#define WHITE           15



// prototype des fonctions exportées
void gotoxy(int x, int y);
void setcolor(WORD color);
void setForeGroundAndBackGroundColor(int ForeGroundColor,int BackGroundColor);
void setCarForeGroundAndBackGroundColor(unsigned char car, int ForeGroundColor,int BackGroundColor);

void clrscr();
void init_text_cursor(int x, int y, int ForeGroundColor,int BackGroundColor);


void afficher_scene_brut(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y]);
void afficher_scene(unsigned char scene[TAILLE_SCENE_X][TAILLE_SCENE_Y]);

int touche_appuyee();

#endif // _HEADER_CONSOLE_H_


