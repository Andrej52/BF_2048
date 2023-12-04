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
        for (int i = 0; i < line.length(); i++)
        {
            if (isdigit(line[i]))
            {
                for (int j = 0; j < 2; j++)
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
        this->numTurns + turn;
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

void newGame()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = 0;
        }  
    }
}

void printBoard()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] = 0)
                cout << " ";   
            else
                cout << board[i][j];
            cout << "\n";
        }  
    }
}

void gameOver(User player) 
{
    cout << "Game Over! \n";
    player.saveStats();
    return;
}

void generateNum()
{
    int randRow = rand() % 4;
    int randCol = rand() % 4;
    board[randRow][randCol] = (rand() % 2 + 1) * 2;
}

int main()
{
    int key;
    string direction;
    string name;
    User  player;

    cout <<"New game [n]\n";
    cout << "Show stats [s]";
    key = _getch(); // zaznamenava stlacenie klavesy
    cout << "Enter player name\n";
    cin >> name;
    
    if ( key == 78 || key == 110) // new game
    {
        player.initStats();
        player.setName(name);
        newGame();
    }
    else if (key == 83 || key == 115) // show stats
    {
        player.showStats();
    }
    
    key = 0;
    
    do {
        key = _getch(); // zaznamenava stlacenie klavesy
        printBoard();
        direction = getDir(key); // navratova hodnota je  charakter R, U, L, D 
        generateNum(); // toto presun inde
        if (direction == "R")
        {
            
        }

    } while (key != 27); // ak stlacime esc vypnutie
    
    
    return 0;
}
