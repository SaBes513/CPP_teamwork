#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <sstream>
using namespace std;

string Get_Current_Date_Time()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", ltm);
    return string(buffer);
}
void Write_Config(CONFIG config)
{
    string type = ".bin";
    string filename = "SAVE_CONFIG_" + type;
    const char* FILE_NAME = filename.c_str();
    ofstream SAVE_FILE(FILE_NAME, ios::binary);
    SAVE_FILE.write(reinterpret_cast<const char*>(&config), sizeof(CONFIG));
    SAVE_FILE.close();
}
void Read_Config(CONFIG& config)
{
    ifstream CONFIG_FILE("SAVE_CONFIG.bin", ios::binary);
    if (!CONFIG_FILE) {
        cerr << "Ошибка: файл конфигурации не найден!" << endl;
        return;
    }
    CONFIG_FILE.read(reinterpret_cast<char*>(&config), sizeof(CONFIG));
    CONFIG_FILE.close();
}
void Write_Save(int& map_count, NPC* npc, MAP* maps, int npc_count, QUEST quests)
{
    string filename = "SAVE_" + Get_Current_Date_Time() + ".bin";
    const char* FILE_NAME = filename.c_str();
    ofstream SAVE_FILE(filename, ios::binary);
    SAVE_FILE.write(reinterpret_cast<const char*>(&npc_count), sizeof(int));
    SAVE_FILE.write(reinterpret_cast<const char*>(npc), sizeof(NPC) * npc_count);
    SAVE_FILE.write(reinterpret_cast<const char*>(&map_count), sizeof(int));
    for (int i = 0; i < map_count; i++) {
        SAVE_FILE.write(reinterpret_cast<const char*>(&maps[i].size), sizeof(maps[i].size));
        SAVE_FILE.write(reinterpret_cast<const char*>(maps[i].MAP_int), sizeof(int) * maps[i].size);
        SAVE_FILE.write(reinterpret_cast<const char*>(maps[i].MAP_char), sizeof(char) * maps[i].size);
    }
    SAVE_FILE.write(reinterpret_cast<const char*>(&quests), sizeof(QUEST));
    SAVE_FILE.close();
}
void Read_Save(ifstream& SAVE_FILE)
{
    if (!SAVE_FILE) {
        cerr << "Ошибка: файл сохранения не найден!" << endl;
        return;
    }
    SAVE_FILE.read(reinterpret_cast<char*>(&npc_count), sizeof(int));
    if (npcs) {

        delete[] npcs;
        npcs = nullptr;
    }
    if (npc_count > 0)
        npcs = new NPC[npc_count];
    SAVE_FILE.read(reinterpret_cast<char*>(npcs), sizeof(NPC) * npc_count);
    SAVE_FILE.read(reinterpret_cast<char*>(&map_count), sizeof(int));
    if (maps) {
    for (int i = 0; i < map_count; i++)
    {
        if (maps[i].MAP_int) {
            delete[] maps[i].MAP_int;
            maps[i].MAP_int = nullptr;
        }
        if (maps[i].MAP_char) {
            delete[] maps[i].MAP_char;
            maps[i].MAP_char = nullptr;
        }
    }
    delete[] maps;
    maps = nullptr;
}
if (map_count <= 0) {
    cerr << "Ошибка: map_count отрицательный!" << endl;
    return;
}
else
{
    maps = new MAP[map_count];
    for (int i = 0; i < map_count; i++)
    {
        SAVE_FILE.read(reinterpret_cast<char*>(&maps[i].size), sizeof(maps[i].size));
        maps[i].MAP_int = new int[maps[i].size];
        SAVE_FILE.read(reinterpret_cast<char*>(maps[i].MAP_int), sizeof(int) * maps[i].size);
        maps[i].MAP_char = new char[maps[i].size];
        SAVE_FILE.read(reinterpret_cast<char*>(maps[i].MAP_char), sizeof(char) * maps[i].size);
    }
}
    SAVE_FILE.read(reinterpret_cast<char*>(&quests), sizeof(QUEST));
}
Templ GET_NPC(NPC* npcs, int npc_count)
{
    Templ ttt_npc;
    ttt_npc.count = npc_count;
    ttt_npc.pointer = reinterpret_cast<int*>(npcs);
    return ttt_npc;
}
Templ GET_MAPS(MAP* maps, int map_count)
{
    Templ ttt_maps;
    ttt_maps.count = map_count;
    ttt_maps.pointer = reinterpret_cast<int*>(maps);
    return ttt_maps;
}
Templ GET_QUESTS(QUEST* quests, int quest_count)
{
    Templ ttt_quests;
    ttt_quests.count = quest_count;
    ttt_quests.pointer = reinterpret_cast<int*>(quests);
    return ttt_quests;
}
Templ GET_CONFIG(CONFIG* config)
{
    Templ ttt_config;
    ttt_config.count = 1;
    ttt_config.pointer = reinterpret_cast<int*>(config);
    return ttt_config;
}
