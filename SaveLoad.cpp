#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;
bool autoSaveEnabled = true; // Флаг для включения/выключения автосохранения
//закомментированные параметры пока неактивны, тк относятся к другой части кода

NPC* base_npc;
//ITEMS base_items; //структур диалогов и предметов пока нет :(
//DIALOGS base_dialogs;
int npc_count;
NPC* npcs;

int map_count;
MAP map;

CONFIG config;
config.AUTO_SAVE_INTERVAL = 10; //сразу задаем значение по умолчанию

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
//запись базы (вызывать при каждом изменении настроек)
void Write_Config()
{
    string type = ".bin";
    string filename = "SAVE_CONFIG" + type;
    FILE* file = fopen(filename.c_str(), "wb");
    //читается единожды, так как templs писпользовать больше не получится, а точное количество базовых персонажей неизвестно
    fwrite(&config, sizeof(CONFIG), 1, file);
    fwrite(&base_npc, sizeof(NPC), 1, file);
    //fwrite(&base_items, sizeof(ITEMS), 1, file); //базовых предметов и диалогов пока нема
    //fwrite(&base_dialogs, sizeof(DIALOGS), 1, file);
    fclose(file);
}
//чтение базы (вызывать сразу после начала игры!!!)
void Read_Config(const char* filename)
{
    FILE* CONFIG_FILE;
    CONFIG_FILE = fopen(filename, "rb");
    if (!CONFIG_FILE) {
        cerr << "Ошибка: файл конфигурации не найден!" << endl;
        return;
    }
    //читается единожды, так как templs писпользовать больше не получится, а точное количество базовых персонажей неизвестно
    fread(&config, sizeof(CONFIG), 1, CONFIG_FILE);
    fread(&base_npc, sizeof(NPC), 1, CONFIG_FILE);
    //fread(&base_items, sizeof(ITEMS), 1, CONFIG_FILE);
    //fread(&base_dialogs, sizeof(DIALOGS), 1, CONFIG_FILE);
    fclose(CONFIG_FILE);
}
//чтение сохранения
void Write_Save(NPC* npc, MAP maps, int npc_count, QUEST quests, bool is_auto)
{
    string filename;
    if (is_auto == true)
        filename = "AUTO_SAVE.bin";
    else
        filename = "SAVE_" + Get_Current_Date_Time() + ".bin";
    FILE* file = fopen(filename.c_str(), "wb");
    fwrite(&npc_count, sizeof(int), 1, file);
    fwrite(npc, sizeof(NPC), npc_count, file);
  
    fwrite(&maps.size, sizeof(int), 1, file);
    fwrite(maps.MAP_int, sizeof(int), maps.size, file);
    fwrite(maps.MAP_char, sizeof(char), maps.size, file);
  
    fwrite(&quests, sizeof(QUEST), 1, file);
    fclose(file);
    cout << "[AutoSave] Game saved to " << filename << endl;
}
//автосохранения
void AutoSave()
{
    while (autoSaveEnabled)
    {
        this_thread::sleep_for(chrono::seconds(config.AUTO_SAVE_INTERVAL)); //ждем заданный интервал секунд
        if (autoSaveEnabled)
        {
            Write_Save(npcs, map, npc_count, quests, true);
        }
    }
}
//запускаем отдельный поток для автосохранений (я все таки не могу без потоков, но этот реально хороший бро)
void StartAutoSave()
{
    thread autoSaveThread(AutoSave);
    autoSaveThread.detach(); // Запускаем поток в фоне
}
//закрываем поток автосохранений
void StopAutoSave()
{
    autoSaveEnabled = false;  // Завершаем цикл в потоке
    if (autoSaveThread.joinable())
    {
        autoSaveThread.join();  // Ждем завершения потока
    }
}
//чтение сохранения
void Read_Save(const char* filename)
{
    FILE* savefile = fopen(filename, "rb");
    if (!savefile) {
        cerr << "Ошибка: файл сохранения не найден!" << endl;
        return;
    }
    fread(&npc_count, sizeof(int), 1, savefile);
    if (npcs)
        delete[] npcs;
    npcs = (npc_count > 0) ? new NPC[npc_count] : nullptr;
    fread(npcs, sizeof(NPC), npc_count, savefile);
    fread(&map.size, sizeof(int), 1, savefile);
    if(MAP_int)
       delete[] MAP_int;
    map.MAP_int = new int[map.size];
    fread(map.MAP_int, sizeof(int), map.size, savefile);
  if(MAP_char)
       delete[] MAP_char;
    map.MAP_char = new char[map.size];
    fread(map.MAP_char, sizeof(char), map.size, savefile);
    fread(&quests, sizeof(QUEST), 1, savefile);
    fclose(savefile);
}
NPC GET_NPC()
{
    return npc;
}
MAP GET_MAPS()
{
    return map;
}
QUEST GET_QUESTS()
{
    return quests;
}
CONFIG GET_CONFIG()
{
    return config;
}
