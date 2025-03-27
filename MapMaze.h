#pragma once
#include <iostream>
#include <Windows.h>
#include "SaveLoad.h"
struct MAP
{
    int size;
    char* MAP_char;
    int* MAP_int;
};
struct Templ;
void MapInit(int , int , int , int , int );
void Rendering(int, int, int);
char** ReturnPartOfMap(int, int, int);
char** ReturnBossMap();
bool** VisToRendererMaze();
bool IsWall(int, int);
bool IsPainted(int, int);
void MakeMap();
void Visual();
void DownloadMap_MAP();
int lvlMob(int, int , int , int );
COORD FindFinish();
COORD FindStart();
MAP GET_MAPMAZE_MAP();