#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NPC
{
    char name[30] = "";            //èìÿ
    int health;                     //òåêóùåå çäîðîâüå
    int endurace;                   //òåêóùàÿ âûíîñëèâîñòü
    int mana;                       //ìàíà
    int strength;                   //ñèëà
    int intelligence;               //èíòåëëåêò
    int dexterity;                  //ëîâêîñòü
    int money;                      //äåíüãè
    int experience;                 //îïûò èãðîêà
    int experienceFromMonster;      //ñ ìîíñòðîâ
    int levelPlayer;                //óðîâåíü èãðîêà
    int levelNPC;                   //óðîâåíü íïñ
    int speed;                      //ñêîðîñòü ïåðñîíàæà
    int attackSpeed;                //ñêîðîñòü àòàêè ïåðñîíàæà
    int vision;                     //ïîëå çðåíèå
    int aggression;                 //àãðåññèÿ
    bool Death;                     //Ñìåðò
    int Buffs;  	            	//Áàôôû ïî äåôîëòó îòñóòñòâóþò 
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
struct Templ
{
    int count;
    int* pointer;
};
struct INVENTORY
{

};
struct BASE_NPC
{
    int health;
    int stregth;
};
struct BASE_ITEMS
{
    int health;
    int stregth;
};
struct BASE_DIALOGS
{
    int health;
    int stregth;
};
struct MAP
{
    int size;
    int* MAP_int;
    char* MAP_char;
};
std::string Get_Current_Date_Time();
void Write_Config(CONFIG config);
void Read_Config(CONFIG& config);
void Write_Save(NPC* npc, MAP* maps, int npc_count, QUEST quests);
void Read_Save(const char* filename);
Templ GET_CONFIG();
Templ GET_QUESTS();
Templ GET_MAPS();
Templ GET_NPC();
