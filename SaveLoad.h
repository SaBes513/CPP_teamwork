#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NPC
{
    char name[30] = "";            //имя
    int health;                     //текущее здоровье
    int endurace;                   //текущая выносливость
    int mana;                       //мана
    int strenght;                   //сила
    int intelligence;               //интеллект
    int dexterity;                  //ловкость
    int money;                      //деньги
    int experience;                 //опыт игрока
    int experienceFromMonster;      //с монстров
    int levelPlayer;                //уровень игрока
    int levelNPC;                   //уровень нпс
    int speed;                      //скорость персонажа
    int attackSpeed;                //скорость атаки персонажа
    int vision;                     //поле зрение
    int aggression;                 //агрессия
    bool Death;                     //Смерт
    int Buffs;  	            	//Баффы по дефолту отсутствуют 
    int CountBuffs;
};
struct CONFIG
{
    int MapHeight;
    int MapWidth;
    int RoomHeight;
    int RoomWidth;
    int Wisibility;
    int Seed;
    int RoomsNumber;
    int MenuHeight;
    int Menuwidth;
};
struct QUEST
{
    int ID;
    bool is_completed;
    int step;
};
struct MAP
{
    int size;
    char* MAP_char;
    int* MAP_int;
};
struct Templ
{
    int count;
    int* pointer;
};
struct INVENTORY
{

};
int npc_count;
NPC* npcs;

int map_count;
MAP* maps;

CONFIG config;

int quest_count;
QUEST quests;
std::string Get_Current_Date_Time();
void Write_Config(CONFIG config);
void Read_Config(CONFIG& config);
void Write_Save(int& map_count, NPC* npc, MAP* maps, int npc_count, QUEST quests);
void Read_Save(ifstream& SAVE_FILE);
