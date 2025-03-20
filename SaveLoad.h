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
    int strenght;                   //ñèëà
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
Templ GET_CONFIG(CONFIG* config);
Templ GET_QUESTS(QUEST* quests, int quest_count);
Templ GET_MAPS(MAP* maps, int map_count);
Templ GET_NPC(NPC* npcs, int npc_count);
