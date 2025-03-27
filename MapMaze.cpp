#include <iostream>
#include <Windows.h>
#include "MapMaze.h"
#include "Config.h"
using namespace std;
void mazemake(); 
int deadend(int, int); 
void Init(int, int, int, int, int);
void InitMaze();
void Wave(int, int, int); 
void FindRooms();
void MakeBossMap();
void FindRooms();
void FindFin();
int FindMinInRoom(int, int);
int FindMax();
//void lvlMob(int, int, int, int);

const int wall = -1, pass = 0, room = -4, Start = -2, End = -3;

int XX = 17, YY = 15;
//Дальность видимости
int visibility;
//height - Высота карты, width - ширина карты, rheight - высока комнаты, rwidth - ширина комнаты, k - количество комнат
int height, width, rheight, rwidth, k;
//Bheight - Высота карты босса, Bwidth - ширина карты босса
int Bheight = 15, Bwidth = 15;

//Инициализация карты
void Init(int Height, int Width, int Rheight, int Rwidth, int vis) 
{
    height = Height;
    width = Width;
    rheight = Rheight;
    rwidth = Rwidth;
    k = (height / (rheight * 3)) * (width / (rwidth * 3));
    visibility = vis;
}
//Массив лабиринта типа int
int** maze = new int* [height];
//Массив лабиринта типа char для возврата на отрисовку
char** mazeBuf = new char* [height];
//Массив карты босса типа char
char** bossMap = new char* [height];

//Инициализация массивов карты
void InitMaze()
{
    maze = new int* [height];
    for (int i = 0; i < height; i++)
        maze[i] = new int[width];
    mazeBuf = new char* [height];
    for (int i = 0; i < height; i++)
        mazeBuf[i] = new char[width];
    bossMap = new char* [height];
    for (int i = 0; i < height; i++)
        bossMap[i] = new char[width];
}
//Очистка памяти с массивов карты
void DestroyMap()
{
    for (int i = 0; i < height; i++)
    {
        delete[] maze[i];
    }
    delete[] maze;
    for (int i = 0; i < height; i++)
    {
        delete[] mazeBuf[i];
    }
    delete[] mazeBuf;
    for (int i = 0; i < height; i++)
    {
        delete[] bossMap[i];
    }
    delete[] bossMap;
}
//Создание карты босса
void MakeBossMap() 
{
    //Заполнение всей карты размером с карты лабиринта пустотой(' ')
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bossMap[i][j] = ' ';
        }
    }
    //Создание стенок у карты босса
    for (int i = 0; i < Bheight; i++)
    {
        for (int j = 0; j < Bheight; j++)
        {
            bossMap[0][j] = char(178);
            bossMap[Bheight - 1][j] = char(178);
            bossMap[i][0] = char(178);
            bossMap[i][Bwidth - 1] = char(178);
        }
    }
    //Создание колонн у карты босса
    for (int i = 2; i < Bheight; i += 5)
    {
        for (int j = 2; j < Bwidth; j += 5)
        {
            if (bossMap[i - 2][j] == char(178) or bossMap[i][j - 2] == char(178) or bossMap[i][j + 2] == char(178) or bossMap[i + 2][j] == char(178))
                bossMap[i][j] = char(178);
        }
    }
}
//Создание зоны для отрисовки/возврата
void MakeArea(int XX, int YY, int visibility, int& tempX, int& tempY, int& tempVisX, int& tempVisY)
{
    //Функция определяет зону радиусом visibility
    if (XX - visibility < 0)
        tempX = 0;
    else
        tempX = XX - visibility;
    if (YY - visibility < 0)
        tempY = 0;
    else
        tempY = YY - visibility;
    if (XX + visibility + 1 >= width)
        tempVisX = width - 1;
    else
        tempVisX = XX + visibility;
    if (YY + visibility + 1 >= height)
        tempVisY = height - 1;
    else
        tempVisY = YY + visibility;
}
//Отображение определенной части карты в char массиве
void Rendering(int XX, int YY, int visibility) 
{
    int tempX, tempY, tempVisX, tempVisY;
    //Определяется зона для заполнения карты
    MakeArea(XX, YY, visibility, tempX, tempY, tempVisX, tempVisY);
    //Данная зона заполняется значением 1 и впоследствии будет отображена на отрисовке
    for (int i = tempX; i <= tempVisX; i++)
    {
        for (int j = tempY; j <= tempVisY; j++)
        {
            mazeBuf[i][j] = 1;
        }
    }
}
//Возврат определенной части карты
char** ReturnPartOfMap(int XX, int YY, int visibility)  
{
    int tempX, tempY, tempVisX, tempVisY;
    //Определяется зона для возврата карты
    MakeArea(XX, YY, visibility, tempX, tempY, tempVisX, tempVisY);
    //Высота зоны возврата карты
    int heightBuf = tempVisX - tempX + 1;
    //Ширина зоны возврата карты
    int widthBuf = tempVisY - tempY + 1;
    //Создание динамического массива для возврата части карты
    char** mazeBuftoRet = new char* [heightBuf];
    for (int i = 0; i < heightBuf; i++)
        mazeBuftoRet[i] = new char[widthBuf];
    int k = 0, m = 0;
    //Заполнение этого массива
    for (int i = tempX; i <= tempVisX; i++, k++)
    {
        for (int j = tempY; j <= tempVisY; j++, m++)
        {
            if (maze[i][j] == -1)
                mazeBuftoRet[k][m] = char(178);
            else
                mazeBuftoRet[k][m] = ' ';
        }
    }
    return mazeBuftoRet;
}
//Возврат карты босса
char** ReturnBossMap()  
{
    return bossMap;
}
//Заполнение и возврат всей карты char
bool** VisToRendererMaze() 
{
    //Создание динамического массива типа bool, где 1 - стена, 0 - проход
    bool** buf = new bool* [height];
    for (int i = 0; i < height; i++)
        buf[i] = new bool[width];

    //Если в массиве char mazeBuf элемент был заполнен 1, то этот элемент в массиве bool buf будет заполнен или 1, или 0
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (mazeBuf[i][j] == 1)
            {
                if (maze[i][j] == wall)
                {
                    buf[i][j] = 1;  //1 - стена
                }
                else
                {
                    buf[i][j] = 0; //0 - не стена
                }
            }
        }
    }
    return buf;
}
//Выход из тупиков при создании лабиринта
int deadend(int x, int y) 
{
    //Количество сторон, в которые нельзя пойти, то есть уже есть проходы
    int ways = 0;

    //Проверка влево
    if (x != 1) {
        if (maze[y][x - 2] == pass or maze[y][x - 2] == room)
            ways += 1;
    }
    else ways += 1;

    //Проверка вверх
    if (y != 1) {
        if (maze[y - 2][x] == pass or maze[y][x - 2] == room)
            ways += 1;
    }
    else ways += 1;

    //Проверка вправо
    if (x != width - 2) {
        if (maze[y][x + 2] == pass or maze[y][x - 2] == room)
            ways += 1;
    }
    else ways += 1;

    //Проверка вниз
    if (y != height - 2) {
        if (maze[y + 2][x] == pass or maze[y][x - 2] == room)
            ways += 1;
    }
    else ways += 1;

    //Если ни в какую из 4 сторон нельзя пойти, возвращаем правду
    if (ways == 4)
        return 1;
    else
        return 0;
}
int xx, yy;

//Создание лабиринта с комнатами
void mazemake()  
{
    //х - координата х, y - координата y, orient - направление, a - счетчик для цикла while
    int x, y, orient, a;
    // Массив карты заполняется стенами
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            maze[i][j] = wall;
    x = 3; y = 3; a = 0;
    while (a < 10000) {
        maze[y][x] = pass; 
        a++;
        //Бесконечный цикл, который прерывается только тупиком
        while (1) {
            //Рандомное определение направления
            orient = rand() % 4;
            switch (orient) {
            //Вверх
            case 0: if (y != 1)
                if (maze[y - 2][x] == wall) {
                    maze[y - 1][x] = pass;
                    maze[y - 2][x] = pass;
                    y -= 2;
                }
            //Вниз
            case 1: if (y != height - 2)
                if (maze[y + 2][x] == wall) {
                    maze[y + 1][x] = pass;
                    maze[y + 2][x] = pass;
                    y += 2;
                }
            //Влево
            case 2: if (x != 1)
                if (maze[y][x - 2] == wall) {
                    maze[y][x - 1] = pass;
                    maze[y][x - 2] = pass;
                    x -= 2;
                }
            //Вправо
            case 3: if (x != width - 2)
                if (maze[y][x + 2] == wall) {
                    maze[y][x + 1] = pass;
                    maze[y][x + 2] = pass;
                    x += 2;
                }
            }
            //Прерываем цикл, если нельзя пойти ни в одно из направлений
            if (deadend(x, y))
                break;
        }
        //Если мы в тупике, то находим новую рандомную точку, которая еще не является проходом и идем от нее
        if (deadend(x, y))
            do {
                x = 2 * (rand() % ((width - 1) / 2)) + 1;
                y = 2 * (rand() % ((height - 1) / 2)) + 1;
            } while (maze[y][x] != pass);
    }
    rheight--; rwidth--;

    bool toContinue;
    //Цикл, совершающий столько итераций, сколько всего комнат
    for (int i = 0; i < k; i++) {
        toContinue = 1;
        while (toContinue) {
            do {
                //Определяем координаты комнаты
                if (rwidth % 4 == 0)
                    x = 2 * (rand() % (width / 2)) + 1;
                else
                    x = 2 * (rand() % (width / 2)) + 2;
                if (rheight % 4 == 0)
                    y = 2 * (rand() % (height / 2)) + 1;
                else
                    y = 2 * (rand() % (height / 2)) + 2;
            } while (x < (rwidth + 2) || x >(width - rwidth - 2) || y < (rheight + 2) || y >(height - rheight - 2));

            toContinue = 0;
            //Если вокруг этих координат есть комната, продолжаем цикл do - while 
            for (int i = (y - rheight - 2); i < (y + rheight + 2); i++)
                for (int j = (x - rwidth - 2); j < (x + rwidth + 2); j++)
                    if (maze[i][j] == room)
                        toContinue = 1;
            if (toContinue)
                continue;
            //Если вокруг этих координат комнат нет, создаем там комнату
            for (int i = (y - rheight / 2); i < (y + rheight / 2 + 1); i++)
                for (int j = (x - rwidth / 2); j < (x + rwidth / 2 + 1); j++)
                    maze[i][j] = room;
        }
    }
    
    //Рандомно определяем точку спавна, что будет необходимо для запуска волнового алгоритма. Находим точку спавна, которая будет не в комнате
    bool toStop = false;
    while(1)
    {
        xx = ((rand() % height) & 65534) + 1, yy = ((rand() % width) & 65534) + 1;
        maze[xx][yy] == room ? toStop = false : toStop = true;
        if (toStop)
            break;
    } 
}
//Запуск волнового алгоритма для определения удаленности точки на карте от спавна
void Wave(int x, int y, int n = 1) 
{
    //Влево, вправо, вверх, вниз
    int left = x - 1, right = x + 1, up = y - 1, down = y + 1;
    maze[x][y] = n;
    if (left > 0) {
        if (maze[left][y] == pass or maze[left][y] == room or maze[left][y] > n + 1)
            Wave(left, y, n + 1);
    }
    if (right < width) {
        if (maze[right][y] == pass or maze[right][y] == room or maze[right][y] > n + 1)
            Wave(right, y, n + 1);
    }
    if (up > 0) {
        if (maze[x][up] == pass or maze[x][up] == room or maze[x][up] > n + 1)
            Wave(x, up, n + 1);
    }
    if (down < width) {
        if (maze[x][down] == pass or maze[x][down] == room or maze[x][down] > n + 1)
            Wave(x, down, n + 1);
    }
}
//Нахождение минимального значения в комнате
int FindMinInRoom(int x, int y)
{
    //Изначально минимальное значение - любая точка в комнате
    int min = maze[y][x];
    //Перебором всех элементов в комнате находим наименьшее
    for (int i = y; i < rheight + y; i++)
    {
        for (int ii = x; ii < rwidth + x; ii++)
        {
            if (maze[i][ii] < min and maze[i][ii] != -1)
            {
                min = maze[i][ii];
            }
        }
    }
    return min;
}
//Нахождение комнат для установления в них одного уровня
void FindRooms() 
{
    //Минимальное значение в комнате, координата x, координата y
    int min, x, y;
    //Первый цикл имеет столько итераций, сколько всего комнат на карте
    for (int kk = 0; kk < k; kk++)
    {
        //Второй и третий цикл ищет комнаты, ходя по карты через каждые 4 элементы 
        for (int i = 4; i < height; i += 4)
        {
            for (int ii = 4; ii < width; ii += 4)
            {
                //Если текущее значение, более правое и более верхнее значения не являются стеной, то это комната
                if (maze[i][ii] != wall)
                {
                    y = i - 1, x = ii - 1;
                    if (maze[i - 2][ii] != wall)
                        y = i - 3;
                    if (maze[i][ii - 2] != wall)
                        x = ii - 3;
                    min = FindMinInRoom(x, y);
                    //Заполняем комнату одним, наименьшим в ней значением
                    for (int k = y; k <= rheight + y; k++)
                    {
                        for (int m = x; m <= rwidth + x; m++)
                        {
                            maze[k][m] = min;
                        }
                    }
                }
            }
        }
    }

}
//Нахождение максимального значения в лабиринте (максимальная удаленность от спавна)
int FindMax() 
{
    //Изначально наибольшее значение на карте - первый элемент
    int max = maze[0][0];
    //Перебором всех элементов находим наибольшее значение
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] > max)
            {
                max = maze[i][j];
            }
        }
    }
    return max;
}
//Нахождение финиша
void FindFin() 
{
    int max = FindMax();
    bool toBreak = false;
    //Находим финиш, обозначаем его концом и заканчиваем цикл
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] == max)
            {
                maze[i][j] = End;
                toBreak = true;
                break;
            }
        }
        if (toBreak)
            break;
    }
}
//Передача уровня моба в зависимости от уровня точки на карте
int lvlMob(int X, int Y, int maxMapLvl, int maxMobLvl) 
{
    //Уровень моба
    int MobLvl;
    //Уровень на карте
    int mapLvl = maze[X][Y];
    //Процент уровня карты в зависимости от наибольшего значения на карте
    double LvlPercent = mapLvl / maxMapLvl;
    //Нахождение уровня моба на текущей точки карты
    MobLvl = maxMobLvl * LvlPercent;
    return MobLvl;
}

//Возврат уровня определенной точки на карте
int MapLvl(int X, int Y) 
{
    return maze[X][Y];
}
//Проверка, является ли точка стеной
bool IsWall(int x, int y) 
{
    bool iswall;
    if (maze[x][y] == -1)
        iswall = true;
    else
        iswall = false;
    return iswall;
}
//Проверка, закрашена ли точка
bool IsPainted(int x, int y) 
{
    bool ispainted;
    if (maze[x][y] >= 1)
        ispainted = false;
    else
        ispainted = true;
    return ispainted;
}
//Возврат координат финиша
COORD FindFinish() 
{
    COORD end = { 0,0 };
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] == End)
            {
                end.X = i;
                end.Y = j;
            }
        }
    }
    return end;
}
//Возврат координат старта
COORD FindStart() 
{
    COORD st = { 0,0 };
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] == Start)
            {
                st.X = i;
                st.Y = j;
            }
        }
    }
    return st;
}
//Сохранение карты
MAP GET_MAPMAZE_MAP() {  
    //Создание переменной типа MAP
    MAP MAP_maps;
    //Создание переменной равной размеру карты
    int ttt_size = width * height;
    MAP_maps.size = ttt_size;
    //Выделяем память под сохранение карты
    MAP_maps.MAP_int = new int[ttt_size];
    MAP_maps.MAP_char = new char[ttt_size];
    //Переменная, необходимая для следующего цикла. Равна либо ширине, либо высоте
    int WidthOrHeight = height > width ? width : height;
    //Сохраняем каждый элемент карты
    for (int i = 0; i < ttt_size; i++)
    {
        MAP_maps.MAP_int[i] = maze[i % WidthOrHeight][i / WidthOrHeight];
        MAP_maps.MAP_char[i] = mazeBuf[i % WidthOrHeight][i / WidthOrHeight];
    }
    return MAP_maps;
}
//Загрузка сохраненной карты
void DownloadMap_MAP() 
{
    //Создаем переменную типа MAP и получаем значение от функциии GET_MAPMAZES
    MAP ttt_maps = GET_MAPMAZES();
    //Переменная, необходимая для следующего цикла. Равна либо ширине, либо высоте
    int WidthOrHeight = height > width ? width : height;
    //Заполняем каждый элемент карты
    for (int i = 0; i < width * height; i++)
    {
        maze[i % WidthOrHeight][i / WidthOrHeight] = ttt_maps.MAP_int[i];
        mazeBuf[i % WidthOrHeight][i / WidthOrHeight] = ttt_maps.MAP_char[i];
    }
}
//Инициализация карты
void MapInit(int Height, int Width, int Rheight, int Rwidth, int vis)
{
    Init( Height,  Width,  Rheight,  Rwidth,  vis);
    InitMaze();

}
//Создание карты, где вызываются все необходимые для создания карты функции
void MakeMap() 
{
    MakeBossMap();
    mazemake();
    Wave(xx, yy);
    FindRooms();
    FindFin();
}

void Visual() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            switch (maze[i][j]) {
            case wall: cout << char(178) << char(178); break;
            case pass: cout << " " << " "; break;
            case room: cout << " " << " "; break;
                // case -1: cout << "ST"; break;
            case End: cout << "EN"; break;
            default: cout << "  "; break;
            }
        cout << endl;
    }
    cout << endl;
}