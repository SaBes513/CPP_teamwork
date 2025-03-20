#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
int change_config();
std::string ENTER_NAME();
//-2 вверх, -3 вниз, -4 влево, -5 вправо, 1 ентер, -1 esc, 2 инвентарь, 3 инвентарь, 4 взаимодействие, 0 пробел, 5 атака
int READKEY();