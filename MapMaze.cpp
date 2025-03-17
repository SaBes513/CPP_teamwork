#include<iostream>
#include "MapMaze.h"
using namespace std;
void InitMaze();
int deadend(int, int);
void mazemake();
void Wave(int, int, int);
void FindRooms();
void Init(int, int, int, int, int);
void InitMaze();
void MakeBossMap();
void FindRooms();
void FindStFin();
int FindMin(int, int);
int FindMax();
void MazeBufInit();
void lvlMob(int, int, int, int)
//void visual(int**, int, int);
const int wall = -1, pass = 0, room = -4, Start = -2, End = -3;

struct COORD
{
    short x;
    short y;
};

int XX = 17, YY = 15;
int visibility;
int height, width, rheight, rwidth, k;
int Bheight = 15, Bwidth = 15;
void Init(int Height, int Width, int Rheight, int Rwidth, int vis)
{
    height = Height;
    width = Width;
    rheight = Rheight;
    rwidth = Rwidth;
    k = (height / (rheight * 3)) * (width / (rwidth * 3));
    int** maze = new int* [height];
    for (int i = 0; i < height; i++)
        maze[i] = new int[width];
    visibility = vis;
}
int** maze = new int* [height];
char** mazeBuf = new char* [height];
char** bossMap = new char* [height];
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

void MakeBossMap()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bossMap[i][j] = ' ';
        }
    }
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
    for (int i = 2; i < Bheight; i += 5)
    {
        for (int j = 2; j < Bwidth; j += 5)
        {
            if (bossMap[i - 2][j] == char(178) or bossMap[i][j - 2] == char(178) or bossMap[i][j + 2] == char(178) or bossMap[i + 2][j] == char(178))
                bossMap[i][j] = char(178);
        }
    }
}

void Rendering(int XX, int YY, int visibility)
{
    int tempX, tempY, tempVisX, tempVisY;
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
    for (int i = tempX; i <= tempVisX; i++)
    {
        for (int j = tempY; j <= tempVisY; j++)
        {
            mazeBuf[i][j] = 1;
        }
    }
}

char** ReturnPartOfMap(int XX, int YY, int visibility)
{
    int tempX, tempY, tempVisX, tempVisY;
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
    int heightBuf = visibility * 2 + 1;
    char** mazeBuftoRet = new char* [heightBuf];
        for (int i = 0; i < heightBuf; i++)
            mazeBuftoRet[i] = new char[heightBuf];
    int k=0, m=0;
    for (int i = tempX; i <= tempVisX; i++, k++)
    {
        for (int j = tempY; j <= tempVisY; j++, m++)
        {
            mazeBuftoRet[k][m] = mazeBuf[i][j];
        }
    }
    return mazeBuftoRet;
}

char** VisToRendererMaze()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (mazeBuf[i][j] == 1)
            {
                switch (maze[i][j]) {
                case wall: mazeBuf[i][j] = char(178); break;
                case pass: mazeBuf[i][j] = ' '; break;
                default: mazeBuf[i][j] = ' '; break;
                }
            }
        }
    }
    return mazeBuf;
}
char** VisToRendererBoss()
{
    return bossMap;
}
int deadend(int x, int y) {
    int a = 0;

    if (x != 1) {
        if (maze[y][x - 2] == room ||
            maze[y][x - 2] == pass)
            a += 1;
    }
    else a += 1;

    if (y != 1) {
        if (maze[y][x - 2] == room ||
            maze[y - 2][x] == pass)
            a += 1;
    }
    else a += 1;

    if (x != width - 2) {
        if (maze[y][x - 2] == room ||
            maze[y][x + 2] == pass)
            a += 1;
    }
    else a += 1;

    if (y != height - 2) {
        if (maze[y][x - 2] == room ||
            maze[y + 2][x] == pass)
            a += 1;
    }
    else a += 1;

    if (a == 4)
        return 1;
    else
        return 0;
}
int xx, yy;

void mazemake() {
    int x, y, c, a;
    bool b, swap = 1;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            maze[i][j] = wall;
    x = 3; y = 3; a = 0;
    while (a < 10000) {
        maze[y][x] = pass; a++;
        while (1) {
            c = rand() % 4;
            switch (c) {
            case 0: if (y != 1)
                if (maze[y - 2][x] == wall) {
                    maze[y - 1][x] = pass;
                    maze[y - 2][x] = pass;
                    y -= 2;
                }
            case 1: if (y != height - 2)
                if (maze[y + 2][x] == wall) {
                    maze[y + 1][x] = pass;
                    maze[y + 2][x] = pass;
                    y += 2;
                }
            case 2: if (x != 1)
                if (maze[y][x - 2] == wall) {
                    maze[y][x - 1] = pass;
                    maze[y][x - 2] = pass;
                    x -= 2;
                }
            case 3: if (x != width - 2)
                if (maze[y][x + 2] == wall) {
                    maze[y][x + 1] = pass;
                    maze[y][x + 2] = pass;
                    x += 2;
                }
            }
            if (deadend(x, y))
                break;
        }

        if (deadend(x, y))
            do {
                x = 2 * (rand() % ((width - 1) / 2)) + 1;
                y = 2 * (rand() % ((height - 1) / 2)) + 1;
            } while (maze[y][x] != pass);
    }
    rheight--; rwidth--;

    for (int l = 0; l < k; l++) {
        b = 1;
        while (b) {
            do {
                if (rwidth % 4 == 0)
                    x = 2 * (rand() % (width / 2)) + 1;
                else
                    x = 2 * (rand() % (width / 2)) + 2;
                if (rheight % 4 == 0)
                    y = 2 * (rand() % (height / 2)) + 1;
                else
                    y = 2 * (rand() % (height / 2)) + 2;
            } while (x < (rwidth + 2) || x >(width - rwidth - 2) ||
                y < (rheight + 2) || y >(height - rheight - 2));

            b = 0;
            for (int i = (y - rheight - 2); i < (y + rheight + 2); i++)
                for (int j = (x - rwidth - 2); j < (x + rwidth + 2); j++)
                    if (maze[i][j] == room)
                        b = 1;

            if (b)
                continue;

            for (int i = (y - rheight / 2); i < (y + rheight / 2 + 1); i++)
                for (int j = (x - rwidth / 2); j < (x + rwidth / 2 + 1); j++)
                    maze[i][j] = room;

            c = rand() % 4;

            if (c == 0) maze[y + rheight / 2 + 1][x - rwidth / 2 + 2 * (rand() % (rwidth / 2 + 1))] = room;
            if (c == 1) maze[y - rheight / 2 - 1][x - rwidth / 2 + 2 * (rand() % (rwidth / 2 + 1))] = room;
            if (c == 2) maze[y - rheight / 2 + 2 * (rand() % (rheight / 2 + 1))][x + rwidth / 2 + 1] = room;
            if (c == 3) maze[y - rheight / 2 + 2 * (rand() % (rheight / 2 + 1))][x - rwidth / 2 - 1] = room;

            if (swap) {
                rheight += rwidth;
                rwidth = rheight - rwidth;
                rheight -= rwidth;
            }
        }
    }

    xx = ((rand() % height) & 65534) + 1, yy = ((rand() % width) & 65534) + 1;

}

void Wave(int x, int y, int n = 1)
{
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


void visual() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            switch (maze[i][j]) {
            case wall: cout << char(178) << char(178); break;
            case pass: cout << " " << " "; break;
            case room: cout << " " << " "; break;
                // case -1: cout << "ST"; break;
            case End: cout << "EN"; break;
            default: cout << (maze[i][j] < 10 ? " " : "") << maze[i][j]; break;
            }
        cout << endl;
    }
    cout << endl;
}

int FindMin(int x, int y)
{
    int min = maze[y][x];
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

void FindRooms()
{
    int min, x, y;
    bool isBreak = false;
    for (int kk = 0; kk < k; kk++)
    {
        for (int i = 4; i < height; i += 4)
        {
            for (int ii = 4; ii < width; ii += 4)
            {
                if (maze[i][ii] != wall)
                {
                    y = i - 1, x = ii - 1;
                    if (maze[i - 2][ii] != wall)
                        y = i - 3;
                    if (maze[i][ii - 2] != wall)
                        x = ii - 3;
                    min = FindMin(x, y);
                    isBreak = true;
                    for (int k = y; k < rheight + y; k++)
                    {
                        for (int m = x; m < rwidth + x; m++)
                        {
                            maze[k][m] = min;
                        }
                    }
                    break;
                }
            }
        }
    }

}

int FindMax()
{
    int max = maze[0][0];
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

void FindStFin()
{
    int max = FindMax();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] == 1)
            {
                maze[i][j] = Start;
            }
            if (maze[i][j] == max)
            {
                maze[i][j] = End;
                max = -99999;
            }
        }
    }
}
void MazeBufInit()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            switch (maze[i][j]) {
            case wall: mazeBuf[i][j] = char(178); break;
            case Start:mazeBuf[i][j] = 'S'; break;
            case End:mazeBuf[i][j] = 'E'; break;
            default: mazeBuf[i][j] = ' '; break;
            }
        }
    }

}

void lvlMob(int X, int Y, int maxMapLvl, int maxMobLvl)
{
    int MobLvl;
    int mapLvl = maze[x][y];
    double LvlPercent = mapLvl / maxMapLvl;
    MobLvl = maxMobLvl * LvlPercent;
    //функция артема на создание моба
}

bool IsPainted(int x, int y)
{
    bool ispainted;
    if (maze[x][y] >= 1)
        ispainted = false;
    else
        ispainted = true;
    return ispainted;
}

COORD Finish()
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

struct Templ
{
    int count;
    int* pointer;
};
struct MAP
{
    int size;
    char* MAP_char;
    int* MAP_int;
};
void GetMap(Templ)
{

}

Templ GET_MAPS() {
    Templ ttt_maps;
    ttt_maps.count = map_count;
    ttt_maps.pointer = reinterpret_cast<int*>(maps);
    return ttt_maps;
}

void DownloadMap()
{
    Templ ttt = GET_MAPS();
    maze = (int*)ttt.pointer;
    for (int i = 0; i < width * height; i++)
    {
        maze[i % width][i / width] = (int*)ttt.pointer[i];
    }
    char* rrr = (char*)ttt.pointer + sizeof(int) * (height * width);
    for (int i = 0; i < width * height; i++)
    {
        maze[i % width][i / width] = rrr[i];
    }
}

void MakeMap()
{
    srand(time(NULL));
    Init(21, 31, 5, 5, 7);
    InitMaze();
    MakeBossMap();
    mazemake();
    Wave(xx, yy);
    FindRooms();
    FindStFin();
    MazeBufInit();
}


int main() {

    MakeMap();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << bossMap[i][j] << bossMap[i][j];
        }

        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << mazeBuf[i][j] << mazeBuf[i][j];
        }
        cout << endl;
    }
}