#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <sstream>
using namespace std;
BASE_NPC base_npc;
BASE_ITEMS base_items;
BASE_DIALOGS base_dialogs;
int npc_count;
NPC* npcs;

int map_count;
MAP map;

CONFIG config;

int quest_count;
QUEST quests;
string Get_Current_Date_Time()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", ltm);
    return string(buffer);
}

void Write_Config()
{
    Templ temples[3];
    temples[0] = GET_MAPMAZE_TEMPL();
    string filename = "SAVE_CONFIG_" + Get_Current_Date_Time() + ".bin";
    FILE* file = fopen(filename.c_str(), "wb");
    fwrite(&config, sizeof(CONFIG), 1, file);
    fclose(file);
}
void Read_Config(ifstream CONFIG_FILE)
{
    Templ temples[3];
    temples[0] = GET_MAPMAZE_TEMPL();
    if (!CONFIG_FILE) {
        cerr << "Ошибка: файл конфигурации не найден!" << endl;
        return;
    }
    fread(&config, sizeof(CONFIG), 1, file);
    fread(&base_npc, sizeof(BASE_NPC), 1, temples[0].sizee);
    fread(&base_items, sizeof(BASE_ITEMS), 1, temples[1].size);
    fread(&base_dialogs, sizeof(BASE_DIALOGS), 1, temples[2].size);
    fclose(file);
}
void Write_Save(NPC* npc, MAP maps, int npc_count, QUEST quests)
{
    string filename = "SAVE_" + Get_Current_Date_Time() + ".bin";
    FILE* file = fopen(filename.c_str(), "wb");
    fwrite(&npc_count, sizeof(int), 1, file);
    fwrite(npc, sizeof(NPC), npc_count, file);
    fwrite(&maps.size, sizeof(int), 1, file);
    fwrite(maps.MAP_int, sizeof(int), maps.size, file);
    fwrite(maps.MAP_char, sizeof(char), maps.size, file);
    fwrite(&quests, sizeof(QUEST), 1, file);
    fclose(file);
}
void Read_Save(const char* filename)
{
    FILE* savefile = fopen(filename, "rb");
    if (!savefile) {
        cerr << "Ошибка: файл сохранения не найден!" << endl;
        return;
    }
    fread(&npc_count, sizeof(int), 1, savefile);
    delete[] npcs;
    npcs = (npc_count > 0) ? new NPC[npc_count] : nullptr;
    fread(npcs, sizeof(NPC), npc_count, savefile);
    //delete[] maps;
    fread(&map.size, sizeof(int), 1, savefile);
    map.MAP_int = new int[map.size];
    fread(map.MAP_int, sizeof(int), map.size, savefile);
    map.MAP_char = new char[map.size];
    fread(map.MAP_char, sizeof(char), map.size, savefile);
    fread(&quests, sizeof(QUEST), 1, savefile);
    fclose(savefile);
}
Templ GET_NPC()
{
    Templ ttt_npc;
    ttt_npc.count = npc_count;
    ttt_npc.pointer = reinterpret_cast<int*>(npcs);
    return ttt_npc;
}
Templ GET_MAPS()
{
    Templ ttt_maps;
    ttt_maps.count = map_count;
    ttt_maps.pointer = reinterpret_cast<int*>(&map);
    return ttt_maps;
}
Templ GET_QUESTS()
{
    Templ ttt_quests;
    ttt_quests.count = quest_count;
    ttt_quests.pointer = reinterpret_cast<int*>(&quests);
    return ttt_quests;
}
Templ GET_CONFIG()
{
    Templ ttt_config;
    ttt_config.count = 1;
    ttt_config.pointer = reinterpret_cast<int*>(&config);
    return ttt_config;
}
