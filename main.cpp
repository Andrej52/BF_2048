#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

using namespace std;
int board[4][4];

class User
{
public:
    int score, numTurns,highestNum;
    string name;

    void loadStats()
    {
        string line;
        int userStats[3] = {this->highestNum, this->score, this->numTurns};   
        ifstream stats( this->name + ".txt");
        getline(stats, line);
        for (int i = 0; i < (int) line.length(); i++)
        {
            if (isdigit(line[i]))
            {
                for (int j = 0; j < (int) sizeof(userStats); j++)
                    userStats[j] = stoi(line);
            }
        }
        stats.close();
    }

    void saveStats()
    {
        ofstream stats( this->name + ".txt");
        stats << "Highest Number: "<< "\n";
        stats << this->highestNum <<"\n";
        stats << "score: "<< "\n";
        stats << this->score << "\n";
        stats << "Turns: "<< "\n";
        stats << this->numTurns << "\n";
        stats.close();
    }
    void setName(string name)
    {
        this->name = name;
    }

    void initStats()
    {
        this->score = 0;
        this->numTurns = 0;
        this->highestNum = 0;
    }

    void setHighestNum(int num)
    {
        this->highestNum = num;
    }

    void updateScore(int a , int b)
    {
        this->score = a + b;
    }

    void updateTurns(int turn)
    {
        this->numTurns =  this->numTurns + turn;
    }

    void showStats()
    {
        cout << this->name << "'s stats:" << "\n";
        cout << "Score:" <<  this->score << "\n";
        cout << "Number of turns" <<  this->numTurns << "\n";
        if ( this->highestNum > 0)
        cout << "Highest number" <<  this->highestNum << "\n";
    }

};

string getDir(int key)
{

        if (key == 0 || key == 224) {
            key = _getch(); // Capture second character for arrow keys
            switch (key) {
                case 72: // up Arrow
                    return "U"; 
                case 80: // down Arrow
                    return "D";
                case 75: // Left Arrow
                    return "L";
                case 77: // Right Arrow
                    return "R";
                default:
                    return  "none";
            }
        } else {
           return "none";
        }
}



// printing the board
void printBoard()
{
    for (int i = 0; i < 4; i++)
    {
        
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
                cout<<"| " << " "<<" |";    
            else
                cout << "| "<<board[i][j]<<" |";
        }  
        cout << "\n";
    }
}
// game over
void gameOver(User player) 
{
    cout << "Game Over! \n";
    player.saveStats();
    return;
}

//generating random number
void generateNum()
{
        int randRow = rand() % 4;
        int randCol = rand() % 4;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if ((board[i][j] == 0 ) && (i == randRow) && (j == randCol) )
                {
                    board[randRow][randCol] = (rand() % 2 + 1) * 2;
                }   
            }
        }

}

int isFull()
{
    int counter = 0;
        for (int i = 0; i < 4; i++) // row
        {
            for (int j = 0; j < 4; j++) // col
            {
                    if (board[i][j] > 0)
                        counter++;
            }
        }
        counter = counter -1;
        if (counter == 16)
            return 1;
    return 0;
}

void newGame()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = 0;
        }  
    }
    generateNum();
    generateNum();
    printBoard();}

/* 
//part of code for shifting

 if (i > 0 &&  direction == "L")
                    {
                        board[i + modifierY][j + modifierX - 1] = board[i + modifierY][j + modifierX];
                        board[i + modifierY][j + modifierX] = 0;
                    }
                    else if (i < 4 && direction == "R")
                    {
                            board[i + modifierY][j + modifierX + 1] = board[i + modifierY][j + modifierX];
                            board[i + modifierY][j + modifierX] = 0;
                    }
                    else if (j > 0 &&  direction == "D")
                    {
                        board[i + modifierY -1][j + modifierX ] = board[i + modifierY][j + modifierX];
                        board[i + modifierY][j + modifierX] = 0;
                    }
                    else if (j < 4 && direction == "U" )
                    {
                            board[i + modifierY + 1][j + modifierX] = board[i + modifierY][j + modifierX];
                            board[i + modifierY][j + modifierX] = 0;
                    }
                }



*/
/*
ISSUES:
                if (isOccupied(i + modifierY, j + modifierX) == 1)
                {
                    board[(i-i)+modifierY][(j-j)+ modifierX] = board[i][j] ;  
                }
                else
                {
                    board[i][j] = 0;
                }
*/

// mb not needed
int isOccupied(int row , int col )
{
    if (board[row][col]  != 0)
        return 1;
    return 0;
}

void shiftLeft() {
    for (int i = 0; i < 4; ++i) {
        int k = 0;
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] != 0) {
                board[i][k++] = board[i][j];
            }
        }
        while (k < 4) {
            board[i][k++] = 0;
        }
    }
}

void shiftRight() {
    for (int i = 0; i < 4; ++i) {
        int k = 3;
        for (int j = 3; j >= 0; --j) {
            if (board[i][j] != 0) {
                board[i][k--] = board[i][j];
            }
        }
        while (k >= 0) {
            board[i][k--] = 0;
        }
    }
}

void shiftUp() {
    for (int j = 0; j < 4; ++j) {
        int k = 0;
        for (int i = 0; i < 4; ++i) {
            if (board[i][j] != 0) {
                board[k++][j] = board[i][j];
            }
        }
        while (k < 4) {
            board[k++][j] = 0;
        }
    }
}
void shiftDown() {
    for (int j = 0; j < 4; ++j) {
        int k = 3;
        for (int i = 3; i >= 0; --i) {
            if (board[i][j] != 0) {
                board[k--][j] = board[i][j];
            }
        }
        while (k >= 0) {
            board[k--][j] = 0;
        }
    }
}

int main()
{
    int key;
    string direction;
    string name;
    User  player;
    player.initStats();
    int turn = player.numTurns;

    cout <<"New game [0] \n";
    cout << "Show stats [1] \n";
    key = _getch(); // zaznamenava stlacenie klavesy
    cout << "Enter player name\n";
    cin >> name;
    
    if ( key == 48) // new game
    {
        player.initStats();
        player.setName(name);
        newGame();
    }
    else if (key == 49) // show stats
    {
        player.setName(name);
        player.showStats();
    }
    
    do {
        key = _getch(); // zaznamenava stlacenie klavesy
        direction = getDir(key); // navratova hodnota je  charakter R, U, L, D 
        if (direction == "none")
            break;
        cout << "direction is: " << direction <<"\n";
        int modifierX = 0;
        int modifierY = 0;

        if (direction == "L")
            modifierX = -1;
        else if(direction == "R")
            modifierX = 1;
        else if(direction == "U")
            modifierY = -1;
        else if(direction == "D")
            modifierY = 1;
        
        for (int i = 0; i < 4; i++) // row
        {
            for (int j = 0; j < 4; j++) // col
            {
                if (j + modifierX < 0 || j + modifierX > 4 || i + modifierY < 0 || i + modifierY > 4)
                    continue;

                if (direction == "L") {
                    shiftLeft();
                } else if (direction == "R") {
                    shiftRight();
                } else if (direction == "D") {
                    shiftDown();
                } else if (direction == "U") {
                    shiftUp();
                }
                if (board[i][j] == board[i + modifierY][j + modifierX])
                {
                    board[i + modifierY][j + modifierX] = board[i][j] * 2;
                    player.updateScore(player.score, board[i + modifierY][j + modifierX]);
                    board[i][j] = 0;
                }
                player.updateTurns(turn++); 
            }
            int status = isFull();
            if (status == 1)
            {
            gameOver(player);
            return 0; 
            }
        }
        generateNum();
        printBoard();
    } while (key != 27); // ak stlacime esc vypnutie
    player.saveStats();
    return 0;
}