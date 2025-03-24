#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//закомментированные параметры пока неактивны, тк относятся к другой части кода
struct NPC
{
    //mob MOB;			//что за моб(гоблин,скелет и тд
    //mobClass MOBCLASS;		//тип моба(игрок, житель или враг)
    char* name = new char[30];      //имя
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
    //COORD coordinations;            //координаты
    bool Death;                     //Смерт
    int* Buffs;			//Баффы по дефолту отсутствуют 
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
    int AUTO_SAVE_INTERVAL; // Интервал автосохранения в секундах
};
struct QUEST
{
    int ID;
    bool is_completed;
    int step;
};
//templ больше не используется
struct MAP
{
    int size;
    int* MAP_int;
    char* MAP_char;
};
std::string Get_Current_Date_Time();
void Write_Config();
void Read_Config(const char* filename);
void Write_Save(NPC* npc, MAP maps, int npc_count, QUEST quests, bool is_auto);
void AutoSave();
void StartAutoSave();
void StopAutoSave();
void Read_Save(const char* filename);
Templ GET_CONFIG();
Templ GET_QUESTS();
Templ GET_MAPS();
Templ GET_NPC();
