#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
int change_config()
{
    int parameter;
    std::cin >> parameter;
    return parameter;
}
std::string ENTER_NAME()
{
    std::string name;
    getline(std::cin, name);
    if (name.empty()) {
        name = "Player";
    }
    return name;
}
int READKEY() {

    int key = _getch();
    if (key == 224)
    {
        key = _getch();
        switch (key)
        {
        case 72:
            return -2;
            break;
        case 80:
            return -3;
            break;
        case 75:
            return -4;
            break;
        case 77:
            return -5;
            break;
        default:
            break;
        }
       
        }
    }
    swicth(key)
    {
        case 13: //ENTER
            return 1;
            break;
        case 27: //ESC
            return -1;
            break;
        case 'I':
        case 'i':
            return 2;
            break;
        case 'J':
        case 'j':
            return 3;
            break;
        case 'F':
        case 'f':
            return 4;
            break;
        case 32: //SPACE
            return 0;
            break;
        case 'A':
        case 'a':
            return 5;
            break;
        default:
            break;
    }
}