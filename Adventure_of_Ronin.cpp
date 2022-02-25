#include <iostream>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cmath>
using namespace std;
char boardA[23][140];
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
int boosting = 0;
void boosting_r();
void show_boost();
void store();
//______________________loading game frame from .txt file__________________________________________
char header[12][160];
void show_header()
{
    for (int i = 0; i < 12; i++)
    {

        for (int j = 0; j < 160; j++)
        {

            cout << header[i][j];
        }
        cout << endl;
    }
}
void ronin_header()
{
    string s;
    fstream f;
    f.open("header.txt", ios::in);
    for (int i = 0; i < 12; i++)
    {
        getline(f, s);
        for (int j = 0; j < 160; j++)
        {
            header[i][j] = s[j];
        }
    }
    f.close();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

    show_header();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
}
//--------------------end show header----------------------------------------------------------------------------

void load()
{
    fstream file;
    file.open("Frame.txt", ios::in);
    string line;
    for (int i = 0; i < 23; i++)
    {
        getline(file, line);
        for (int j = 0; j < 140; j++)
        {

            boardA[i][j] = line[j];
        }
    }
    file.close();
}
void board_show()
{

    for (int i = 0; i < 23; i++)
    {

        for (int j = 0; j < 140; j++)
        {

            cout << boardA[i][j];
        }
        cout << endl;
    }
}
//----------------------end new game------------------------------------------------------------
//-------------------------------continue game-----------------------------------------------
void loadCont()
{
    fstream file;
    file.open("Frame_cont.txt", ios::in);
    string line;
    for (int i = 0; i < 23; i++)
    {
        getline(file, line);
        for (int j = 0; j < 140; j++)
        {

            boardA[i][j] = line[j];
        }
    }
    file.close();
}
void board_showCont()
{

    for (int i = 0; i < 23; i++)
    {

        for (int j = 0; j < 140; j++)
        {

            cout << boardA[i][j];
        }
        cout << endl;
    }
}
//_________________________end load and show frame from .txt file____________________________________
//************************decleration of goto funcion to avoid flickring of game frame*************
void gotoxy(int x, int y) // Function Definition
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
//*********************Fuction Prototypes*********************************************
bool gameRunning = true;
char gun = '|';

//*********************************************Ronin movement*******************************************************
void moveRonin_down();
void moveRonin_left();
void moveRonin_up();
void moveRonin_right();
void moveRonin_freefall();
void moveRoninWith_slap();
char Ronin = 1;
int RoninX = 9;
int RoninY = 58;
// ________________________________Plate movement______________________________________________________________
void slapSelf_move();
bool slapSelf_up();
bool slapSelf_down();
int turn = 0;
int slapX = 5;
int slapY = 16;

bool gameRunning_slap_up = true;
//__________________________________________________________________________________
bool gameRunning_slap1 = true;
bool slap1Self_move();
int turn_2 = 0;
int slap1X = 15;
int slap1Y = 73;
int slap2X = 10;
bool slap1Self_move_Up();
bool slap1Self_move_down();
//______________________________________________________________________________________-
int turn_3 = 0;
bool slap2Self_move_Up();
void slap2Self_move();
bool slap2Self_move_down();
// slap 1 movement end____________________________________________________________________

int lives = 3;
bool lives_detect();
void lives_count();
void lives_show();
bool l_detect = true;
//-------------------------------------------------------------------------------------------
int pintchX = 4;
int pintchY = 35;
char pintch = 177;
//--------------pintch end--------------------------------------------------------------------

int gunX = 2;
int gunY = 46;
bool gun_fire();
char bullet = 31;
bool gameRunning_fire = true;
//--------------------gun fire end------------------------------------------------------------
void resetRonin();
//--------------------------jump boosterr------------------------------------------------------
char gravity_ch = 178;
bool gravity_off = false;

int jbY = 125;
int jbX = 21;
//-------------------------------------------------------------------------------------------------------
char dimond = 4;
int fX = 6;
int fY = 131;
int dimond_count = 6;
void remaining_dimond();
char pre_item = ' ';
void gravity();

int change_d = 0;
bool machine_gun();
bool machine_down();
bool machine_up();
int machineX_1 = 19;
int machineX_2 = 20;
int machineY_start = 4;
int machineY_end = 10;

bool machine_fire();
char machine_bullet = 16;
int m_bullet_x = 19;
int m_bullet_y = 10;
int m2_bullet_x = 16;
int m2_bullet_y = 10;
bool Runningfire1 = true;
bool Runningfire2 = true;
bool machine_fire2();
void gravity_jump();
char gravity_on = '@';
char ghostX = 9;
char ghostY = 110;
char previousItemR = ' ';
int ghostDirection();
bool ghostMovementRand();
bool Running_random = true;
int distance(int p_x, int p_y, int g_x, int g_y);
int small_idx();
bool ghost_chase();
bool Running_chasing = true;
int ghostX_2 = ghostX + 1;
int ghostY_2 = ghostY;
char boost = 3;
char previousItem_chase = ' ';
bool fire_down();

int main()
{

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);

//--------------------------------------------------------------------------------------------------
reverse:
    system("cls");
    int option;
    ronin_header();
    cout << "\n";
    cout << "\t\t1.Play New Game\n";
    cout << "\t\t2.Continue Load Game\n";
    cout << "\t\t3.Exit\n\n";
    cout << "Press any option...";
    cin >> option;
    if (option == 1)
    {
        load();

        boardA[9][58] = Ronin; // placing Ronin in board
        //--------------reseting ronin position for game-------------
        RoninX = 9;
        RoninY = 58;
        //-----------------pintch position setting------------------------------

        //-----------------------------------------------------------------
        boardA[1][125] = boost;
        boardA[6][137] = boost;
        boardA[jbX][jbY] = gravity_ch;
        boardA[fX][fY] = dimond;
        boardA[20][65] = dimond;
        boardA[21][10] = dimond;
        boardA[4][3] = dimond;
        boardA[4][37] = dimond;
        boardA[17][132] = dimond;
        boardA[8][97] = dimond;
        boardA[1][115] = gravity_on;
        boardA[ghostX_2][ghostY_2] = '-';
        //-------------
        boardA[pintchX][pintchY] = pintch;

        boardA[21][101] = pintch;

        boardA[18][40] = pintch;

        gotoxy(46, 1);

        cout << gun;
        boardA[ghostX][ghostY] = 'R';

        system("cls");
        board_show();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        gotoxy(pintchY, pintchX);
        cout << pintch;
        gotoxy(101, 21);
        cout << pintch;
        gotoxy(40, 18);
        cout << pintch;

        gotoxy(ghostY, ghostX);
        cout << "R";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    }
    else if (option == 2)
    {
        store();
        loadCont();
        system("cls");
        board_showCont();
    }
    while (lives > 0)
    {

        Sleep(100);
        l_detect = lives_detect();
        remaining_dimond();

        if (l_detect == false || gameRunning_fire == false || Runningfire1 == false || Runningfire2 == false || Running_random == false || Running_chasing == false)
        {
            Beep(600, 500);
            if (boosting == 0)
                lives_count();
            else
            {
                boosting--;
            }
            resetRonin();
        }
        show_boost();
        lives_show();

        if (gameRunning_slap_up)
        {
            slapSelf_move();
        }
        if (gameRunning_slap1)
        {
            slap1Self_move();
        }
        slap2Self_move();
        if (GetAsyncKeyState(VK_LEFT))
        {
            moveRonin_left();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveRonin_right();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveRonin_up();
        }
        if (gravity_off == true)
        {
            if (GetAsyncKeyState(VK_UP))
            {
                gravity_jump();
            }
        }
        if (boardA[RoninX][RoninY + 1] == gravity_on || boardA[RoninX][RoninY - 1] == gravity_on)
        {
            gravity_off = false;
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            system("cls");
            goto reverse;
        }
        if (lives == 0)
        {
            gotoxy(6, 30);
            cout << "Game Over";
            getch();
            goto reverse;
        }
        if (dimond == 0)
        {
            gotoxy(6, 30);
            cout << "You Win";
            getch();
            break;
        }
        moveRonin_freefall();
        moveRoninWith_slap();
        gameRunning_fire = gun_fire();
        gravity();
        machine_gun();
        Runningfire1 = machine_fire();
        Runningfire2 = machine_fire2();

        Running_random = ghostMovementRand();
        Running_chasing = ghost_chase();
    }
}
//---------------------------main end----------------------------------------------------------------------------------------------------------------------

void moveRonin_left()
{

    if (boardA[RoninX + 2][RoninY] == ' ')
    {
        moveRonin_freefall();
    }
    if (boardA[RoninX][RoninY - 1] == dimond)
    {
        boardA[RoninX][RoninY - 1] = ' ';
        gotoxy(RoninY - 1, RoninX);
        cout << " ";
        dimond_count--;
    }

    if (boardA[RoninX][RoninY - 1] == gravity_ch)
    {
        gravity_off = true;
    }
    if (boardA[RoninX][RoninY - 1] == boost)
    {
        boosting_r();
    }
    if (boardA[RoninX][RoninY - 1] == '.')
    {
        // water movement
        boardA[RoninX][RoninY] = pre_item;
        gotoxy(RoninY, RoninX);
        cout << pre_item;
        RoninY = RoninY - 1;
        pre_item = boardA[RoninX][RoninY];
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
    if (boardA[RoninX][RoninY - 1] == ' ')
    {
        boardA[RoninX][RoninY] = ' ';
        gotoxy(RoninY, RoninX);
        cout << " ";
        RoninY = RoninY - 1;
        boardA[RoninX][RoninY] = Ronin;
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
}
//-----------------------------ronin Right move-----------------------------------------------------------------
void moveRonin_right()
{

    if (boardA[RoninX + 1][RoninY] == ' ')
    {
        moveRonin_freefall();
    }
    if (boardA[RoninX][RoninY + 1] == dimond)
    {
        boardA[RoninX][RoninY + 1] = ' ';
        gotoxy(RoninY + 1, RoninX);
        cout << " ";
        dimond_count--;
    }
    if (boardA[RoninX][RoninY + 1] == gravity_ch)
    {
        gravity_off = true;
    }
    if (boardA[RoninX][RoninY + 1] == boost)
    {
        boosting_r();
    }
    if (boardA[RoninX][RoninY + 1] == '.')
    {
        // water movement
        boardA[RoninX][RoninY] = pre_item;
        gotoxy(RoninY, RoninX);
        cout << pre_item;
        RoninY = RoninY + 1;
        pre_item = boardA[RoninX][RoninY];
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
    if (boardA[RoninX][RoninY + 1] == ' ')
    {
        boardA[RoninX][RoninY] = ' ';
        gotoxy(RoninY, RoninX);
        cout << " ";
        RoninY = RoninY + 1;
        boardA[RoninX][RoninY] = Ronin;
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
}
//--------------------------------Ronin down-----------------------------------------------------------------------
void moveRonin_down()
{

    if (boardA[RoninX + 1][RoninY] == '*')
    {
        moveRoninWith_slap();
    }
    if (boardA[RoninX + 1][RoninY] == boost)
    {
        boosting_r();
    }

    if (boardA[RoninX + 2][RoninY] == ' ' && boardA[RoninX + 1][RoninY] == ' ')
    {
        boardA[RoninX][RoninY] = ' ';
        gotoxy(RoninY, RoninX);
        cout << " ";
        RoninX = RoninX + 2;
        boardA[RoninX][RoninY] = Ronin;
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
}
// ronin jumping---------------------------------------------------------
void moveRonin_up()
{
    // for jumping________________________________________________________________
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    if (boardA[RoninX - 2][RoninY] == boosting)
    {
        boosting_r();
    }
    if (boardA[RoninX - 2][RoninY] == '.')
    {
        // water movement
        boardA[RoninX][RoninY] = pre_item;
        gotoxy(RoninY, RoninX);
        cout << pre_item;
        RoninX = RoninX - 2;
        pre_item = boardA[RoninX][RoninY];
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }

    if (boardA[RoninX - 2][RoninY] == ' ' && boardA[RoninX - 1][RoninY] != '%' && boardA[RoninX - 1][RoninY] != '|')
    {
        boardA[RoninX][RoninY] = ' ';
        gotoxy(RoninY, RoninX);
        cout << " ";
        RoninX = RoninX - 2;
        boardA[RoninX][RoninY] = Ronin;
        gotoxy(RoninY, RoninX);
        cout << Ronin;
        Sleep(400);
        if (GetAsyncKeyState(VK_LEFT))
        { // for projectile motion______________________________________________________________-
            if (boardA[RoninX + 1][RoninY] == '*')
            {
                moveRoninWith_slap();
            }
            if (boardA[RoninX][RoninY - 3] == ' ')
            {
                boardA[RoninX][RoninY] = ' ';
                gotoxy(RoninY, RoninX);
                cout << " ";
                RoninY = RoninY - 3;
                boardA[RoninX][RoninY] = Ronin;
                gotoxy(RoninY, RoninX);
                cout << Ronin;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            if (boardA[RoninX + 1][RoninY] == '*')
            {
                moveRoninWith_slap();
            }
            if (boardA[RoninX][RoninY + 3] == ' ')
            {
                boardA[RoninX][RoninY] = ' ';
                gotoxy(RoninY, RoninX);
                cout << " ";
                RoninY = RoninY + 3;
                boardA[RoninX][RoninY] = Ronin;
                gotoxy(RoninY, RoninX);
                cout << Ronin;
            }
        }

        moveRonin_down();
        // end jumping_____________________________________________________________________________
    }
}
///-----------------------------------------------------------------------------------------------------------------------------------------
void moveRonin_freefall()
{

    if (gravity_off == false)
    {
        // moveRonin_down();
        if (boardA[RoninX + 1][RoninY] == '*')
        {
            moveRoninWith_slap();
        }
        if (boardA[RoninX + 1][RoninY] == '.')
        {
            // water movement
            boardA[RoninX][RoninY] = pre_item;
            gotoxy(RoninY, RoninX);
            cout << pre_item;
            RoninX = RoninX + 1;
            pre_item = boardA[RoninX][RoninY];
            gotoxy(RoninY, RoninX);
            cout << Ronin;
        }
        if (boardA[RoninX + 1][RoninY] == dimond)
        {
            boardA[RoninX + 1][RoninY] = ' ';
            gotoxy(RoninY, RoninX + 1);
            cout << " ";
            dimond_count--;
        }
        else if ((boardA[RoninX + 1][RoninY] == ' ' && boardA[RoninX + 1][RoninY] != '*') || (boardA[RoninX + 1][RoninY] == '.'))
        {
            boardA[RoninX][RoninY] = ' ';
            gotoxy(RoninY, RoninX);
            cout << " ";
            RoninX = RoninX + 1;
            gotoxy(RoninY, RoninX);
            boardA[RoninX][RoninY] = Ronin;
            cout << Ronin;
            if (GetAsyncKeyState(VK_LEFT))
            {
                if (boardA[RoninX + 1][RoninY] == '*')
                {
                    moveRoninWith_slap();
                }
                if (boardA[RoninX][RoninY - 1] == ' ')
                {
                    boardA[RoninX][RoninY] = ' ';
                    gotoxy(RoninY, RoninX);
                    cout << " ";
                    RoninY = RoninY - 1;
                    boardA[RoninX][RoninY] = Ronin;
                    gotoxy(RoninY, RoninX);
                    cout << Ronin;
                }
            }
            if (GetAsyncKeyState(VK_RIGHT))
            {
                if (boardA[RoninX + 1][RoninY] == '*')
                {
                    moveRoninWith_slap();
                }
                if (boardA[RoninX][RoninY + 1] == ' ')
                {
                    boardA[RoninX][RoninY] = ' ';
                    gotoxy(RoninY, RoninX);
                    cout << " ";
                    RoninY = RoninY + 1;
                    boardA[RoninX][RoninY] = Ronin;
                    gotoxy(RoninY, RoninX);
                    cout << Ronin;
                }
            }
        }
    }
}
void gravity_jump()
{
    if (GetAsyncKeyState(VK_UP))
    {

        if (boardA[RoninX + 2][RoninY] == ' ')
        {

            boardA[RoninX][RoninY] = ' ';
            gotoxy(RoninY, RoninX);
            cout << " ";
            RoninX = RoninX + 2;
            boardA[RoninX][RoninY] = Ronin;
            gotoxy(RoninY, RoninX);
            cout << Ronin;
        }
    }
}
void boosting_r()
{
    boosting++;
}
void show_boost()
{

    gotoxy(65, 24);
    cout << "Booster:" << boosting;
}
void gravity()
{

    if (gravity_off == true)
    {
        if ((boardA[RoninX - 1][RoninY] == ' ' && boardA[RoninX - 1][RoninY] != '*' && boardA[RoninX - 1][RoninY] != '%') || (boardA[RoninX - 1][RoninY] == '.'))
        {
            boardA[RoninX][RoninY] = ' ';
            gotoxy(RoninY, RoninX);
            cout << " ";
            RoninX = RoninX - 1;
            gotoxy(RoninY, RoninX);
            boardA[RoninX][RoninY] = Ronin;
            cout << Ronin;

            if (GetAsyncKeyState(VK_LEFT))
            {

                if (boardA[RoninX][RoninY - 3] == ' ')
                {
                    boardA[RoninX][RoninY] = ' ';
                    gotoxy(RoninY, RoninX);
                    cout << " ";
                    RoninY = RoninY - 1;
                    boardA[RoninX][RoninY] = Ronin;
                    gotoxy(RoninY, RoninX);
                    cout << Ronin;
                }
            }
            if (GetAsyncKeyState(VK_RIGHT))
            {

                if (boardA[RoninX][RoninY + 3] == ' ')
                {
                    boardA[RoninX][RoninY] = ' ';
                    gotoxy(RoninY, RoninX);
                    cout << " ";
                    RoninY = RoninY + 3;
                    boardA[RoninX][RoninY] = Ronin;
                    gotoxy(RoninY, RoninX);
                    cout << Ronin;
                }
            }
        }
    }
}
void moveRoninWith_slap()
{

    if (boardA[RoninX + 1][RoninY] == '*')
    {

        boardA[RoninX][RoninY] = ' ';
        gotoxy(RoninY, RoninX);
        cout << " ";

        RoninX = RoninX - 1;
        boardA[RoninX][RoninY] = Ronin;
        gotoxy(RoninY, RoninX);
        cout << Ronin;
    }
}
void slapSelf_move()
{
    if (turn == 0)
    {
        slapSelf_down();
    }
    if (turn == 1)
    {
        slapSelf_up();
    }
}
bool slapSelf_down()
{
    if (slapX + 1 == 15)
    {
        turn = 1;
    }
    else
    {
        for (int i = 16; i < 23; i++)
        {

            boardA[slapX][i] = ' ';
            gotoxy(i, slapX);
            cout << " ";
        }

        slapX = slapX + 1;
        for (int i = 16; i < 23; i++)
        {

            boardA[slapX][i] = '*';
            gotoxy(i, slapX);
            cout << "*";
        }
    }
    return true;
}

bool slapSelf_up()
{
    if (slapX - 5 == 0)
    {
        turn = 0;
    }

    else
    {
        for (int j = 16; j < 23; j++)
        {

            boardA[slapX][j] = ' ';
            gotoxy(j, slapX);
            cout << " ";
        }

        // cout << "       ";
        slapX = slapX - 1;
        for (int i = 16; i < 23; i++)
        {

            boardA[slapX][i] = '*';
            gotoxy(i, slapX);
            cout << "*";
        }
    }
    return true;
}
//__________________end 1__________________________________________________________________________________
bool slap1Self_move()
{
    bool result;
    if (turn_2 == 0)
    {
        result = slap1Self_move_Up();
    }
    if (turn_2 == 1)
    {
        result = slap1Self_move_down();
    }
    return result;
}
bool slap1Self_move_down()
{
    if (slap1X == 15)
    {
        turn_2 = 0;
    }
    else
    {
        for (int i = 73; i < 80; i++)
        {
            boardA[slap1X][i] = ' ';
            gotoxy(i, slap1X);
            cout << " ";
        }
        slap1X = slap1X + 1;
        for (int i = 73; i < 80; i++)
        {
            boardA[slap1X][i] = '*';
            gotoxy(i, slap1X);
            cout << "*";
        }
    }
    return true;
}
bool slap1Self_move_Up()
{
    if (slap1X - 10 == 0)
    {
        turn_2 = 1;
    }

    else
    {
        for (int i = 73; i < 80; i++)
        {
            boardA[slap1X][i] = ' ';
            gotoxy(i, slap1X);
            cout << " ";
        }
        slap1X = slap1X - 1;
        for (int i = 73; i < 80; i++)
        {
            boardA[slap1X][i] = '*';
            gotoxy(i, slap1X);
            cout << "*";
        }
    }
    return true;
}

//-----------------------------------------------------------------------------
void slap2Self_move()
{

    if (turn_3 == 0)
    {
        slap2Self_move_Up();
    }
    if (turn_3 == 1)
    {
        slap2Self_move_down();
    }
}
bool slap2Self_move_down()
{
    if (slap2X == 16)
    {
        turn_3 = 0;
    }
    else
    {
        for (int i = 117; i < 125; i++)
        {
            boardA[slap2X][i] = ' ';
            gotoxy(i, slap2X);
            cout << " ";
        }
        slap2X = slap2X + 1;
        for (int i = 117; i < 125; i++)
        {
            boardA[slap2X][i] = '*';
            gotoxy(i, slap2X);
            cout << "*";
        }
    }
    return true;
}
bool slap2Self_move_Up()
{
    if (slap2X - 4 == 0)
    {
        turn_3 = 1;
    }

    else
    {
        for (int i = 117; i < 125; i++)
        {
            boardA[slap2X][i] = ' ';
            gotoxy(i, slap2X);
            cout << " ";
        }
        slap2X = slap2X - 1;
        for (int i = 117; i < 125; i++)
        {
            boardA[slap2X][i] = '*';
            gotoxy(i, slap2X);
            cout << "*";
        }
    }
    return true;
}

//------------------end slap movements-----------------------------------------------------------
void lives_count()
{
    lives--;
}
void lives_show()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(30, 24);
    cout << "Lives Remaining:" << lives;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
}
bool lives_detect()
{
    if (boardA[RoninX + 1][RoninY] == pintch || boardA[RoninX][RoninY + 1] == pintch || boardA[RoninX][RoninY - 1] == pintch || boardA[RoninX - 1][RoninY] == pintch)
    {
        return false;
    }
    return true;
}
void resetRonin()
{

    boardA[RoninX][RoninY] = ' ';
    gotoxy(RoninY, RoninX);
    cout << " ";
    RoninX = 9;
    RoninY = 58;
    boardA[RoninX][RoninY] = Ronin;
    gotoxy(RoninY, RoninX);
    cout << Ronin;
}
bool gun_fire()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    if (true)
    {
        if (boardA[gunX + 1][gunY] == Ronin)
        {

            // cin.get();
            return false;
        }
        if (boardA[gunX + 1][gunY] == ' ')
        {
            boardA[gunX][gunY] = ' ';
            gotoxy(gunY, gunX);
            cout << " ";

            gunX = gunX + 1;
            boardA[gunX][gunY] = bullet;
            gotoxy(gunY, gunX);
            cout << bullet;
        }
        if (boardA[gunX + 1][gunY] == '%')
        {
            boardA[gunX][gunY] = ' ';

            gotoxy(gunY, gunX);
            cout << " ";
            gunX = 2;
            gunY = 46;
            boardA[gunX][gunY] = bullet;
            gotoxy(gunY, gunX);
            cout << bullet;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    return true;
}
void remaining_dimond()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(5, 24);
    cout << "Remaining dimond:" << dimond_count;
    gotoxy(5, 25);
    cout << "Collected Dimond:" << 6 - dimond_count;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
}
bool machine_gun()
{

    bool ans = false;
    if (change_d == 0)
    {
        ans = machine_up();
    }
    if (change_d == 1)
    {
        ans = machine_down();
    }
    return ans;
}
bool machine_up()
{
    if (machineX_1 == 16)
    {
        change_d = 1;
    }

    for (int i = 4; i < 10; i++)
    {
        boardA[machineX_1][i] = ' ';
        gotoxy(i, machineX_1);
        cout << " ";
        if (boardA[machineX_1 - 1][i] == Ronin)
        {
            return false;
        }
    }
    for (int i = 4; i < 10; i++)
    {
        boardA[machineX_2][i] = ' ';
        gotoxy(i, machineX_2);
        cout << " ";
    }
    machineX_1 = machineX_1 - 1;
    machineX_2 = machineX_2 - 1;
    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 - 1][i] == Ronin)
        {
            return false;
        }
        boardA[machineX_1][i] = '|';
        gotoxy(i, machineX_1);
        cout << "|";
    }
    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 - 1][i] == Ronin)
        {
            return false;
        }
        boardA[machineX_2][i] = '/';
        gotoxy(i, machineX_2);
        cout << "/";
    }
    return true;
}
//-----------------------------machine gun moving up and down---------------------------------------------------------------------------
bool machine_down()
{
    // machine gun going down
    if (machineX_2 == 20)
    {
        change_d = 0;
    }

    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 + 1][i] == Ronin)
        {
            return false;
        }
        boardA[machineX_1][i] = ' ';
        gotoxy(i, machineX_1);
        cout << " ";
    }
    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 + 1][i] == Ronin)
        {
            return false;
        }
        boardA[machineX_2][i] = ' ';
        gotoxy(i, machineX_2);
        cout << " ";
    }
    machineX_1 = machineX_1 + 1;
    machineX_2 = machineX_2 + 1;
    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 + 1][i] == Ronin)
        {
            return false;
        }
        boardA[machineX_1][i] = '|';
        gotoxy(i, machineX_1);
        cout << "|";
    }
    for (int i = 4; i < 10; i++)
    {
        if (boardA[machineX_1 + 1][i] == Ronin)
        {
            return false;
        }
        boardA[machineX_2][i] = '/';
        gotoxy(i, machineX_2);
        cout << "/";
    }
    return true;
}
//---------------------------------------------------------------------------------------------------------------------
//-------------------------machine firing-----------------------------------------------------------------
bool machine_fire()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

    if (boardA[m_bullet_x][m_bullet_y + 3] == Ronin || boardA[m_bullet_x][m_bullet_y + 2] == Ronin || boardA[m_bullet_x][m_bullet_y + 1] == Ronin)
    {
        return false;
    }
    if (boardA[m_bullet_x][m_bullet_y + 3] == ' ')
    {
        boardA[m_bullet_x][m_bullet_y] = ' ';
        gotoxy(m_bullet_y, m_bullet_x);
        cout << " ";

        m_bullet_y = m_bullet_y + 3;
        boardA[m_bullet_x][m_bullet_y] = machine_bullet;
        gotoxy(m_bullet_y, m_bullet_x);
        cout << machine_bullet;
    }
    if (boardA[m_bullet_x][m_bullet_y + 3] == '%' || boardA[m_bullet_x][m_bullet_y + 3] == dimond || boardA[m_bullet_x][m_bullet_y + 1] == '%' || boardA[m_bullet_x][m_bullet_y + 1] == dimond || boardA[m_bullet_x][m_bullet_y + 3] == '%' || boardA[m_bullet_x][m_bullet_y + 2] == dimond || boardA[m_bullet_x][m_bullet_y + 2] == pintch || boardA[m_bullet_x][m_bullet_y + 3] == pintch || boardA[m_bullet_x][m_bullet_y + 1] == pintch)
    {
        boardA[m_bullet_x][m_bullet_y] = ' ';

        gotoxy(m_bullet_y, m_bullet_x);
        cout << " ";
        m_bullet_x = machineX_1;
        m_bullet_y = 10;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    return true;
}
bool machine_fire2()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

    if (boardA[m_bullet_x][m2_bullet_y + 3] == Ronin || boardA[m_bullet_x][m2_bullet_y + 2] == Ronin || boardA[m_bullet_x][m2_bullet_y + 1] == Ronin)
    {
        return false;
    }
    if (boardA[m2_bullet_x][m2_bullet_y + 3] == ' ')
    {
        boardA[m2_bullet_x][m2_bullet_y] = ' ';
        gotoxy(m2_bullet_y, m2_bullet_x);
        cout << " ";

        m2_bullet_y = m2_bullet_y + 3;
        boardA[m2_bullet_x][m2_bullet_y] = machine_bullet;
        gotoxy(m2_bullet_y, m2_bullet_x);
        cout << machine_bullet;
    }
    if (boardA[m2_bullet_x][m2_bullet_y + 3] != ' ' || boardA[m2_bullet_x][m2_bullet_y + 2] != ' ' || boardA[m2_bullet_x][m2_bullet_y + 1] != ' ')
    {
        boardA[m2_bullet_x][m2_bullet_y] = ' ';

        gotoxy(m2_bullet_y, m2_bullet_x);
        cout << " ";
        m2_bullet_x = machineX_1;
        m2_bullet_y = 10;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    return true;
}
//--------------------------------------------------------------------------------------------------------------------------------
///----------------------------Random generator----------------------------------------------------------------
int ghostDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}

bool ghostMovementRand()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    int value = ghostDirection();

    if (value == 1)
    {
        // move left in random movement
        if (boardA[ghostX][ghostY - 1] != '*' && boardA[ghostX][ghostY - 1] != '%')
        {
            if (boardA[ghostX][ghostY - 1] == ' ' || boardA[ghostX][ghostY - 1] == '.' || boardA[ghostX][ghostY - 1] == Ronin)
            {
                boardA[ghostX][ghostY] = previousItemR;
                gotoxy(ghostY, ghostX);
                cout << previousItemR;
                ghostY = ghostY - 1;
                previousItemR = boardA[ghostX][ghostY];
                if (previousItemR == Ronin)
                {
                    previousItemR = ' ';
                    resetRonin();

                    return false;
                }
                boardA[ghostX][ghostY] = 'R';
                gotoxy(ghostY, ghostX);
                cout << "R";
            }
        }
        return true;
    }
    if (value == 2)
    {
        // move right in random movement
        if (boardA[ghostX][ghostY + 1] != '*' && boardA[ghostX][ghostY + 1] != '*')
        {
            if (boardA[ghostX][ghostY + 1] == ' ' || boardA[ghostX][ghostY + 1] == '.' || boardA[ghostX][ghostY + 1] == Ronin)
            {
                boardA[ghostX][ghostY] = previousItemR;
                gotoxy(ghostY, ghostX);
                cout << previousItemR;
                ghostY = ghostY + 1;
                previousItemR = boardA[ghostX][ghostY];
                if (previousItemR == Ronin)
                {
                    previousItemR = ' ';
                    resetRonin();
                    return false;
                }
                boardA[ghostX][ghostY] = 'R';
                gotoxy(ghostY, ghostX);
                cout << "R";
            }
        }
        return true;
    }
    if (value == 3)
    {
        // move up in random movements
        if (boardA[ghostX - 1][ghostY] != '*' || boardA[ghostX - 1][ghostY] != '%')
        {
            if (boardA[ghostX - 1][ghostY] == ' ' || boardA[ghostX - 1][ghostY] == '.' || boardA[ghostX - 1][ghostY] == Ronin)
            {

                boardA[ghostX][ghostY] = previousItemR;
                gotoxy(ghostY, ghostX);
                cout << previousItemR;
                ghostX = ghostX - 1;
                previousItemR = boardA[ghostX][ghostY];
                if (previousItemR == Ronin)
                {
                    previousItemR = ' ';

                    return false;
                }
                boardA[ghostX][ghostY] = 'R';
                gotoxy(ghostY, ghostX);
                cout << "R";
            }
        }
        return true;
    }
    if (value == 4)
    {
        // move down in random movement
        if (boardA[ghostX + 1][ghostY] != '*' && boardA[ghostX + 1][ghostY] != '%')
        {
            if ((boardA[ghostX + 1][ghostY] == ' ' || boardA[ghostX + 1][ghostY] == ' ' || boardA[ghostX + 1][ghostY] == '.') && boardA[ghostX + 1][ghostY] != '*')
            {
                boardA[ghostX][ghostY] = previousItemR;
                gotoxy(ghostY, ghostX);
                cout << previousItemR;
                ghostX = ghostX + 1;
                previousItemR = boardA[ghostX][ghostY];
                if (previousItemR == Ronin)
                {
                    previousItemR = ' ';

                    return false;
                }
                boardA[ghostX][ghostY] = 'R';
                gotoxy(ghostY, ghostX);
                cout << "R";
            }
        }
        return true;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
}
//-----------------------------------------------------------------------------------------------------
//***********************************************************************************************************************************************
bool ghost_chase()

{

    bool ans = fire_down();

    return ans;
}

bool fire_down()
{
    if (boardA[ghostX_2 + 1][ghostY_2] == Ronin)
    {

        return false;
    }
    if (boardA[ghostX_2 + 1][ghostY_2] == ' ')
    {
        boardA[ghostX_2][ghostY_2] = ' ';
        gotoxy(ghostY_2, ghostX_2);
        cout << " ";

        ghostX_2 = ghostX_2 + 1;
        boardA[ghostX_2][ghostY_2] = bullet;
        gotoxy(ghostY_2, ghostX_2);
        cout << bullet;
    }
    else if (boardA[ghostX_2 + 1][ghostY_2] != ' ')
    {
        boardA[ghostX_2][ghostY_2] = ' ';

        gotoxy(ghostY_2, ghostX_2);
        cout << " ";
        ghostX_2 = ghostX + 1;
        ghostY_2 = ghostY;
        boardA[ghostX_2][ghostY_2] = bullet;
        gotoxy(ghostY_2, ghostX_2);
        cout << bullet;
    }
    return true;
}

void store()
{
    fstream file;
    string row;
    file.open("Frame_cont.tX_1t", ios::out);

    for (int i = 0; i < 23; i++)
    {

        for (int j = 0; j < 140; j++)
        {

            row = row + boardA[i][j];
        }
        file << row << endl;
        row = " ";
    }
}
