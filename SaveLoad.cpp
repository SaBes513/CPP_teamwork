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
    //if (maps) {
    //    for (int i = 0; i < map_count; i++) {

    //        cout << "MAP " << i << " | Size: " << maps[i].size
    //            << " | MAP_int: " << maps[i].MAP_int
    //            << " | MAP_char: " << maps[i].MAP_char << endl;
    //        //if (maps[i].MAP_int) {
    //        //    delete[] maps[i].MAP_int;
    //        //    maps[i].MAP_int = nullptr;
    //        //}
    //        /*if (maps[i].MAP_int != NULL)
    //        delete [] maps[i].MAP_int;*/
    //        //maps[i].MAP_int = nullptr;
    //        //maps[i].MAP_char = nullptr;
    //    }
    //    delete[] maps;
    //}
    maps = new MAP[map_count];
    for (int i = 0; i < map_count; i++)
    {
        SAVE_FILE.read(reinterpret_cast<char*>(&maps[i].size), sizeof(maps[i].size));
        maps[i].MAP_int = new int[maps[i].size];
        SAVE_FILE.read(reinterpret_cast<char*>(maps[i].MAP_int), sizeof(int) * maps[i].size);
        maps[i].MAP_char = new char[maps[i].size];
        SAVE_FILE.read(reinterpret_cast<char*>(maps[i].MAP_char), sizeof(char) * maps[i].size);
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
int main() {
    setlocale(LC_ALL, "ru");

    //npc_count = 2;
    //npcs = new NPC[npc_count];
    //npcs[0] = { "Warrior", 100, 50, 30, 20, 15, 10, 1000, 200, 50, 1, 1, 5, 3, 8, 2, false, 0, 0 };
    //npcs[1] = { "Mage", 80, 40, 100, 10, 25, 12, 500, 150, 40, 1, 1, 4, 2, 6, 3, false, 1, 1 };
    //
    //map_count = 1;
    //maps = new MAP[map_count];
    //maps[0].size = 5;
    //maps[0].MAP_int = new int[maps[0].size] {1, 2, 3, 4, 5};
    //maps[0].MAP_char = new char[maps[0].size] {'A', 'B', 'C', 'D', 'E'};
    //
    //quest_count = 1;
    //quests = { 1, false, 0 };
    //
    //config = { 50, 50, 10, 10, 20, 1234, 5, 10, 20 };
    //
    //cout << "Сохранение данных..." << endl;
    //Write_Save(map_count, npcs, maps, npc_count, quests);
    //cout << "Данные сохранены." << endl << endl;


    cout << "Чтение сохранения..." << endl;
    ifstream SAVE_FILE("SAVE_2025-03-20_20-47-11.bin", ios::binary);
    Read_Save(SAVE_FILE);
    SAVE_FILE.close();
    cout << "Данные загружены." << endl << endl;
    
    cout << "NPC Count: " << npc_count << endl;
    for (int i = 0; i < npc_count; i++) {
        cout << "NPC " << i + 1 << ": " << npcs[i].name << ", HP: " << npcs[i].health << endl;
    }
    
    cout << "Map Count: " << map_count << endl;
    for (int i = 0; i < map_count; i++) {
        cout << "Map " << i + 1 << ", Size: " << maps[i].size << ", First Char: " << maps[i].MAP_char[0] << endl;
    }
    
    cout << "Quest ID: " << quests.ID << ", Completed: " << (quests.is_completed ? "Yes" : "No") << "stage:" << quests.step << endl;
    cout << "Config MapWidth: " << config.MapWidth << ", MapHeight: " << config.MapHeight << endl;
    
    delete[] npcs;
    for (int i = 0; i < map_count; i++) {
        delete[] maps[i].MAP_int;
        delete[] maps[i].MAP_char;
    }
    delete[] maps;
    
    cout << "\nТест завершен!" << endl;
    return 0;
}
