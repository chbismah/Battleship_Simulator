#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
char board[10][10];
char board2[10][10];

char shiplabel1[10][10];
char shiplabel2[10][10];
// Initialize the board with '~' in every cell
void initializeBoard(char board[10][10]);
// Display the board (optionally hide ships)
void printBoard(char board[10][10], bool hideShips);
// Clear the console screen
void clearScreen();
// Randomly places all ships (used for computer or player 2)
void setRandomShips(char board[10][10]);
// Handles Player vs Computer mode
void vsComputer(char playerBoard[10][10], char computerBoard[10][10]);
// Handles Player vs Player mode
void vsPlayer(char board1[10][10], char board2[10][10]);
// Executes player attack; invalid if cell already attacked
void playerAttack(char opponentBoard[10][10], int &playerScore);
// Computer attacks a random valid cell
void computerAttack(char playerBoard[10][10], int &computerScore);
// Updates player score after each hit
void updateScore(int &score);
// Displays main game menu and lets user select mode
void showGameMenu();
// Compares final scores and displays the winner or draw

// Clears all cells on the board to '~'
void clearBoard(char board[10][10]);
// WINDOWS
//  Set text and background color in Windows console

// For clearing Screen
void clearScreen()
{
    //    system("clear");  //For Mac /Linux;
    system("CLS"); // For Windows
}
void setColor(int textColor, int bgColor);
void StartNewGame();
void Instructions();
void ViewLeaderboard();
void placementofships(char board[10][10], char shiplabel[10][10]);
void fullBoard(char board[10][10], char board1[10][10], char board2[10][10]);
bool shipsunk(char board[10][10], char label);
int hitcounter(char board[10][10]);

string name;
string name2;
int player1shipcolor;
int player2shipcolor;
int playerturn;

const int BLACK = 0;
const int BLUE = 9;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;

int shipColor()
{
    int choice;
    do
    {

        cout << " Choose your Battleship Color: " << endl;
        ;
        cout << "1. Blue" << endl;
        cout << "2. Green" << endl;
        cout << "3. Cyan" << endl;
        cout << "4. Red" << endl;
        cout << "5. Magenta" << endl;
        cout << "6. Yellow" << endl;
        cout << "7. White" << endl;

        cout << "Enter your color choice(1-7): ";
        cin >> choice;
        if (choice == 1)
        {
            return BLUE;
        }
        if (choice == 2)
        {
            return GREEN;
        }
        if (choice == 3)
        {
            return CYAN;
        }
        if (choice == 4)
        {
            return RED;
        }
        if (choice == 5)
        {
            return MAGENTA;
        }
        if (choice == 6)
        {
            return YELLOW;
        }
        if (choice == 7)
        {
            return WHITE;
        }
        if (choice < 1 || choice > 7)
        {
            cout << endl
                 << " Invalid number to select is entered.Please select 1-7 " << endl;
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7);
}

//---------------------------------------------------------------------------------------------------------
void ShowGameMenu()
{
    clearScreen();
    int choice;
    do
    {

        cout << endl;
        cout << "========================================================================================" << endl
             << endl;
        setColor(5, 0);
        cout << "                           WELCOME TO BATTLESHIP GAME                             " << endl
             << endl;
        setColor(7, 0);
        cout << "========================================================================================" << endl;

        setColor(9, 0);
        cout << "                                    MAIN MENU                   " << endl;
        setColor(7, 0);
        cout << "========================================================================================" << endl;
        cout << endl;
        setColor(12, 0);
        cout << "1";
        setColor(7, 0);
        cout << ". Start New Game" << endl;

        setColor(12, 0);
        cout << "2";
        setColor(7, 0);
        cout << ". Instructions" << endl;

        setColor(12, 0);
        cout << "3";
        setColor(7, 0);
        cout << ". View Leaderboard" << endl;

        setColor(12, 0);
        cout << "4";
        setColor(7, 0);
        cout << ". Exit" << endl;
        cout << "_" << endl;
        cout << "Enter your choice(1-4): ";
        cin >> choice;
        if (choice == 1)
        {
            StartNewGame();
        }
        if (choice == 2)
        {
            Instructions();
        }
        if (choice == 3)
        {
            ViewLeaderboard();
        }

        if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
        {
            cout << "Please input a valid choice(1-4)" << endl;
        }
        if (choice == 4)
        {
            cout << "Exiting Game........." << endl;
            break;
        }
    } while (choice != 1 && choice != 2 && choice != 3);
}
void StartNewGame()
{
    clearScreen();
    int choice;

    cout << "======================================" << endl
         << endl;
    cout << "           Start New Game        " << endl
         << endl;
    cout << "======================================" << endl;
    cout << "Enter the Player Name: ";
    cin.ignore(1000, '\n');
    cin >> name;
    cout << endl;
    cout << endl;
    do
    {
        cout << "-------------------------------------------" << endl;
        cout << endl
             << "Select Game Mode (1-2): " << endl;
        cout << "1.Player vs Computer" << endl;
        cout << "2.Player vs Player" << endl;
        cin >> choice;

        if (choice == 1)
        {

            vsComputer(board, board2);
        }
        if (choice == 2)
        {
            vsPlayer(board, board2);
        }
        if (choice != 1 && choice != 2)
        {
            cout << "Enter valid choice" << endl;
        }
    } while (choice != 1 && choice != 2);
}
void Instructions()
{
    clearScreen();
    cout << "=====================================================" << endl
         << endl;
    cout << "               Instructions        " << endl
         << endl;
    cout << "=====================================================" << endl;
    cout << "1. Place your ships on the board." << endl;
    cout << "2.You and the enemy take turns firing shots." << endl;
    cout << "3. 'O' means MISS, 'X' means HIT " << endl;
    cout << "5. Your score is based on accuracy and speed." << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "(Press Any Button To Return To Main Manu)";
    getch();
    clearScreen();
    ShowGameMenu();
}

void manualplacement(char board[10][10], char board2[10][10], int sizes, string sname, char shiplabel)
{
    int row;
    int col;
    int direction;
    bool allow = false;
    do
    {

        allow = true;

        cout << endl
             << "Enter starting row (1-10) " << sname << ": ";
        cin >> row;

        cout << endl
             << "Enter starting column(1-10) for " << sname << ":";
        cin >> col;

        if (row < 0 || row > 9 || col < 0 || col > 9 || col + sizes > 10)
        {
            cout << "Ship wont fit horizontally" << endl;
            allow = false;
            continue;
        }
        for (int i = 0; i < sizes; i++)
        {

            if (board[row][col + i] != '~')
            {
                cout << "There is a ship there,try vertically" << endl;
                allow = false;
                break;
            }
        }
        if (allow == true)
        {

            for (int i = 0; i < sizes; i++)
            {
                board[row][col + i] = 'S';
            }

            printBoard(board, false);
            for (int i = 0; i < sizes; i++)
            {
                board[row][col + i] = '~';
            }
        }
        cout << "Choose direction: 1.Horizontal   2.Vertical" << endl;
        cin >> direction;

        if (direction != 1 && direction != 2)
        {
            cout << "Enter either 1 or 2 only" << endl;
            allow = false;
            continue;
        }
        if (direction == 1)
        {
            if (col + sizes > 10)
            {

                cout << "Ship wont fit horizontally" << endl;
                allow = false;
                continue;
            }
            for (int i = 0; i < sizes; i++)
            {
                if (board[row][col + i] != '~')
                {
                    cout << "There is already a ship here " << endl;
                    allow = false;
                    break;
                }
            }

            if (allow == true)
            {
                for (int i = 0; i < sizes; i++)
                {
                    board[row][col + i] = 'S';
                    board2[row][col + i] = shiplabel;
                }
            }
        }
        if (direction == 2)
        {
            if (row + sizes > 10)
            {

                cout << "ship wont fit vertically" << endl;
                allow = false;
                continue;
            }
            for (int i = 0; i < sizes; i++)
            {

                if (board[row + i][col] != '~')
                {
                    cout << "There is already a ship here" << endl;
                    allow = false;
                    break;
                }
                else
                {
                    allow = true;
                }
            }
            if (allow == true)
            {
                for (int i = 0; i < sizes; i++)
                {
                    board[row + i][col] = 'S';
                    board2[row + i][col] = shiplabel;
                }
            }
        }
        if (allow == true)
        {
            cout << "ship placed!" << endl;
            printBoard(board, false);
        }
        if (allow == false)
        {
            cout << "Try Again" << endl;
        }

    } while (allow == false);
}
int remainingships(char shiplabel[10][10])
{
    char labels[5] = {'A', 'B', 'D', 'E', 'F'};
    int remaining_ships = 0;

    for (int i = 0; i < 5; i++)
    {

        char check_label = labels[i];
        bool shipblock = false;
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                if (shiplabel[j][k] == check_label)
                {
                    shipblock = true;
                    break;
                }
            }

            if (shipblock == true)
            {
                break;
            }
        }
        if (shipblock == true)
        {
            remaining_ships++;
        }
    }
    return remaining_ships;
}
int hitcounter(char board[10][10])
{
    int hits = 0;
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            if (board[r][c] == 'X' || board[r][c] == 'P')
            {
                hits++;
            }
        }
    }
    return hits;
}
void saveScore(string playerName, int score)
{
    ofstream outFile("leaderboard.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << playerName << " " << score << endl;
        outFile.close();
    }
}
void displayResult(int player1Score, int player2Score)
{
    clearScreen();
    cout << "==============================================================" << endl;
    cout << "                    BATTLESHIP - GAME RESULT                   " << endl;
    cout << "==============================================================" << endl;
    cout << endl;
    cout << "Final Scores: " << endl;
    cout << " ----------------------------------" << endl;
    cout << "Player 1 Score: " << player1Score << endl;
    cout << "  Player 2 Score: " << player2Score << endl;
    cout << " ----------------------------------" << endl;
    cout << endl;
    if (player1Score > player2Score)
    {
        cout << "WINNER: Player 1 !! Congratulations!" << endl;
        saveScore(name, player1Score);
    }
    else if (player2Score > player1Score)
    {
        cout << "WINNER: Player 2 !! Congratulations!" << endl;

        saveScore("Player_2", player2Score);
    }
    else
    {
        cout << "The match is a DRAW! Both players performed equally well." << endl;
    }

    cout << endl;
    cout << "Press any key to return to the main menu..." << endl;
    getch();
    clearScreen();
    ShowGameMenu();
}
void playerAttack(char oppboard[10][10], int &playerscore)
{
    int row;
    int col;
    bool valid = false;
    cout << endl
         << "                                      ...Attack Your Enemy..." << endl;
    while (valid == false)
    {
        cout << "Enter the row that u want to attack" << endl;
        cin >> row;
        cout << "Enter the coloumn that u want to attack" << endl;
        cin >> col;
        if (row < 0 || row > 9 || col < 0 || col > 9)
        {
            cout << "Invalid number entered. Please choose a row and column between 0 and 9." << endl;
            continue;
        }

        char target = oppboard[row][col];
        if (target == 'O' || target == 'X')
        {

            cout << " u have already attacked this block choose another one " << endl;
            continue;
        }
        valid = true;
        if (target == 'S')
        {
            cout << "u have hit opponent's ship!!!" << endl;
            oppboard[row][col] = 'X';
            playerscore += 10;

            if (playerturn == 1)
            {
                char sinklabel = shiplabel2[row][col];
                shiplabel2[row][col] = 'X';

                if (shipsunk(shiplabel2, sinklabel))
                {
                    cout << "You sunk the opponent's ship!" << endl;
                    for (int r = 0; r < 10; r++)
                        for (int c = 0; c < 10; c++)
                            if (shiplabel2[r][c] == 'X' && board2[r][c] == 'X')
                                shiplabel2[r][c] = 'P';
                }
            }
            else
            {
                char sinklabel = shiplabel1[row][col];
                shiplabel1[row][col] = 'X';

                if (shipsunk(shiplabel1, sinklabel))
                {
                    cout << "You sunk the opponent's ship!" << endl;
                    for (int r = 0; r < 10; r++)
                        for (int c = 0; c < 10; c++)
                            if (shiplabel1[r][c] == 'X' && board[r][c] == 'X')
                                shiplabel1[r][c] = 'P';
                }
            }
        }
        else
        {
            cout << "MISS! :(" << endl;
            oppboard[row][col] = 'O';
            playerscore -= 1;
        }
    }
}
void vsPlayer(char board1[10][10], char board2[10][10])
{
    clearScreen();
    int p1score = 0;
    int p2score = 0;
    int tships = 17;
    cout << "Name of player 1 is " << name << endl;
    player1shipcolor = shipColor();
    initializeBoard(shiplabel1);
    initializeBoard(shiplabel2);
    initializeBoard(board1);
    playerturn = 1;
    printBoard(board, false);
    placementofships(board, shiplabel1);

    cout << endl
         << "all ships of " << name << " has been placed!!" << endl;
    cout << "Press any key for Player 2.............." << endl;
    getch();
    clearScreen();
    cout << endl
         << "Enter your name(player2): ";
    cin >> name2;
    cout << endl;
    cout << name2;
    player2shipcolor = shipColor();
    initializeBoard(board2);
    playerturn = 2;
    printBoard(board2, false);
    placementofships(board2, shiplabel2);
    bool gameOver = false;
    cout << endl
         << "all ships of " << name2 << " has been placed!!" << endl;
    cout << "Press any key to start the Game..........." << endl;
    getch();
    clearScreen();
    cout << endl
         << "                   ---------------- GET READY TO PLAY!! ---------------------" << endl;
    while (hitcounter(board) < tships && hitcounter(board1) < tships)
    {
        playerturn = 1;
        int p1_attacks = remainingships(shiplabel1) + 1;
        cout << "\n========================================" << endl;
        cout << name << "'s TURN! (Ships remaining: " << p1_attacks - 1 << ")" << endl;
        cout << "You have " << p1_attacks << " shots this turn!" << endl;
        cout << "========================================" << endl;
        for (int i = 1; i <= p1_attacks; i++)
        {
            fullBoard(board2, board2, board);
            cout << "Shot " << i << " of " << p1_attacks << endl;
            playerAttack(board2, p1score);
            if (hitcounter(board2) == tships)
            {
                cout << endl
                     << endl
                     << name << " YOU WINNNN!!! against " << name2 << endl;
                gameOver = true;
                break;
            }
            if (i == p1_attacks)
            {
                fullBoard(board2, board2, board);
            }

            getch();
            clearScreen();
        }
        if (gameOver)
            break;
        cout << "Press any key for " << name2 << "'s turn............" << endl;
        getch();
        clearScreen();
        playerturn = 2;
        int p2_attacks = remainingships(shiplabel2) + 1;
        cout << "\n========================================" << endl;
        cout << name2 << "'s TURN! (Ships remaining: " << p2_attacks - 1 << ")" << endl;
        cout << "You have " << p2_attacks << " shots this turn!" << endl;
        cout << "========================================" << endl;
        for (int j = 1; j <= p2_attacks; j++)
        {
            fullBoard(board, board, board2);
            cout << "Shot " << j << " of " << p2_attacks << endl;
            if (hitcounter(board) == tships)
            {
                cout << endl
                     << endl
                     << name2 << " YOU WINNNN!!! against " << name << endl;
                gameOver = true;
                break;
            }
            playerAttack(board, p2score);
            if (j == p2_attacks)
            {
                fullBoard(board, board, board2);
            }

            getch();
            clearScreen();
        }
        if (gameOver)
            break;
        cout << "Press any key for " << name << "'s turn............" << endl;
        getch();
        clearScreen();
    }
    displayResult(p1score, p2score);
}

bool shipsunk(char board[10][10], char label)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board[i][j] == label)
            {
                return false;
            }
        }
    }

    return true;
}
void placementofships(char board[10][10], char shiplabel[10][10])
{

    string sname[5] = {"Aircraft Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat"};
    int sizes[5] = {5, 4, 3, 3, 2};
    int choice;
    char shiplabels[5] = {'A', 'B', 'D', 'E', 'F'};
    do
    {

        cout << "1. Manual placement(by yourself): " << endl;
        cout << "2. Random Placement" << endl;
        cin >> choice;
        if (choice == 1)
        {

            for (int i = 0; i < 5; i++)
            {

                cout << endl
                     << " Place your " << sname[i] << " of size " << "(" << sizes[i] << ")" << endl;

                manualplacement(board, shiplabel, sizes[i], sname[i], shiplabels[i]);
            }
        }

        if (choice == 2)
        {
            setRandomShips(board);
            printBoard(board, false);
        }
        if (choice != 1 && choice != 2)
        {
            cout << "enter only 1 or 2 please!!!" << endl;
        }

    } while (choice != 1 && choice != 2);
}

void ViewLeaderboard()
{
    clearScreen();
    ifstream inFile("leaderboard.txt");

    cout << "=====================================================" << endl;
    cout << "               BATTLESHIP LEADERBOARD                " << endl;
    cout << "=====================================================" << endl;
    cout << "   " << left << setw(20) << "PLAYER NAME" << "SCORE" << endl;
    cout << "-----------------------------------------------------" << endl;

    string playerName;
    int score;

    if (!inFile)
    {
        cout << "       No records found. Play a game first!          " << endl;
    }
    else
    {
        while (inFile >> playerName >> score)
        {
            cout << "   " << left << setw(20) << playerName << score << endl;
        }
    }

    inFile.close();
    cout << "=====================================================" << endl;
    cout << "\n(Press Any Button To Return To Main Menu)";
    getch();
    clearScreen();
    ShowGameMenu();
}

void setRandomShips(char randomboard[10][10])
{
    int ships = 5;
    int shipsize[ships] = {5, 4, 3, 3, 2};
    srand(time(0));
    char shiplabel[5] = {'A', 'B', 'D', 'E', 'F'};

    for (int i = 0; i < ships; i++)
    {
        bool placed = false;
        while (!placed)
        {
            int row = rand() % 10;
            int col = rand() % 10;
            int pos = rand() % 2;

            bool overlap = false;
            if (pos == 0)
            {
                if (col + shipsize[i] >= 10)
                {
                    col = 10 - shipsize[i];
                }
                for (int j = 0; j < shipsize[i]; j++)
                {
                    if (randomboard[row][col + j] == 'S')
                    {
                        overlap = true;
                        break;
                    }
                }
                if (!overlap)
                {
                    for (int j = 0; j < shipsize[i]; j++)
                    {
                        randomboard[row][col + j] = 'S';
                        if (playerturn == 1)
                        {

                            shiplabel1[row][col + j] = shiplabel[i];
                        }
                        else
                        {

                            shiplabel2[row][col + j] = shiplabel[i];
                        }
                        placed = true;
                    }
                }
            }

            if (pos == 1)
            {
                if (row + shipsize[i] >= 10)
                {
                    row = 10 - shipsize[i];
                }
                for (int j = 0; j < shipsize[i]; j++)
                {
                    if (randomboard[row + j][col] == 'S')
                    {
                        overlap = true;
                        break;
                    }
                }
                if (!overlap)
                {
                    for (int j = 0; j < shipsize[i]; j++)
                    {
                        randomboard[row + j][col] = 'S';
                        if (playerturn == 1)
                        {

                            shiplabel1[row + j][col] = shiplabel[i];
                        }
                        else
                        {

                            shiplabel2[row + j][col] = shiplabel[i];
                        }
                        placed = true;
                    }
                }
            }
        }
    }
}
void computerAttack(char playerBoard[10][10], int &computerScore)
{
    bool attackDone = false;

    while (!attackDone)
    {
        int row = rand() % 10;
        int col = rand() % 10;
        if (playerBoard[row][col] != 'X' && playerBoard[row][col] != 'O' && playerBoard[row][col] != 'P')
        {
            attackDone = true;

            if (playerBoard[row][col] == 'S')
            {
                cout << "Computer hit your ship at (" << row << "," << col << ")!" << endl;
                playerBoard[row][col] = 'X';
                updateScore(computerScore);
                char sinklabel = shiplabel1[row][col];
                shiplabel1[row][col] = 'X';
                if (shipsunk(shiplabel1, sinklabel))
                {
                    cout << "The Computer sunk one of your ships!" << endl;
                    for (int r = 0; r < 10; r++)
                    {
                        for (int c = 0; c < 10; c++)
                        {
                            if (shiplabel1[r][c] == 'X' && playerBoard[r][c] == 'X')
                            {
                                playerBoard[r][c] = 'P';
                            }
                        }
                    }
                }
            }
            else
            {
                cout << "Computer missed at (" << row << "," << col << ")." << endl;
                playerBoard[row][col] = 'O';
                computerScore -= 1;
            }
        }
    }
}
void updateScore(int &score)
{
    score += 10;
}

void vsComputer(char playerBoard[10][10], char computerBoard[10][10])
{
    clearScreen();
    cout << "-------------------------------- VS COMPUTER MODE ---------------------------" << endl;

    int playerScore = 0, computerScore = 0;
    int tships = 17;

    playerturn = 1;
    player1shipcolor = shipColor();

    initializeBoard(playerBoard);
    initializeBoard(computerBoard);
    initializeBoard(shiplabel1);
    initializeBoard(shiplabel2);

    cout << "Computer is placing ships..." << endl;
    playerturn = 2;
    setRandomShips(computerBoard);

    playerturn = 1; // Back to player
    cout << name << ", place your ships on the board:" << endl;
    printBoard(playerBoard, false);
    placementofships(playerBoard, shiplabel1);

    cout << "\nShips placed! Press any key to start the battle..." << endl;
    getch();
    bool gameOver = false;
    while (gameOver != true)
    {
        clearScreen();
        int p_attacks = remainingships(shiplabel1) + 1;
        cout << "\n========================================" << endl;
        cout << name << "'s TURN! (Ships remaining: " << p_attacks - 1 << ")" << endl;
        cout << "You have " << p_attacks << " shots this turn!" << endl;
        cout << "========================================" << endl;
        for (int i = 1; i <= p_attacks; i++)
        {
            fullBoard(computerBoard, computerBoard, playerBoard);
            cout << "Shot " << i << " of " << p_attacks << endl;
            playerAttack(computerBoard, playerScore);
            if (hitcounter(computerBoard) == tships)
            {
                cout << endl
                     << endl
                     << "\nGAME OVER! CONGRATULATIONS! " << name << " wins!" << endl;
                gameOver = true;
                break;
            }
            if (i == p_attacks)
            {
                fullBoard(computerBoard, computerBoard, playerBoard);
            }

            getch();
            clearScreen();
        }
        if (gameOver)
            break;

        cout << "Press any key for Computer's move.........." << endl;
        getch();

        clearScreen();
        playerturn = 2;
        int c_attacks = remainingships(shiplabel2) + 1;
        cout << "\n========================================" << endl;
        cout << "Computer's TURN! (Ships remaining: " << c_attacks - 1 << ")" << endl;
        cout << "Computer has " << c_attacks << " shots this turn!" << endl;
        cout << "========================================" << endl;
        getch();
        for (int j = 1; j <= c_attacks; j++)
        {

            cout << "Shot " << j << " of " << c_attacks << endl;
            if (hitcounter(playerBoard) == tships)
            {
                cout << endl
                     << endl
                     << "Game Over !! Computer Wins!! " << endl;
                gameOver = true;
                break;
            }
            computerAttack(playerBoard, computerScore);
        }
        fullBoard(playerBoard, playerBoard, computerBoard);
        if (gameOver)
            break;
        else
        {
            cout << "Press any key to continue your turn........." << endl;
            getch();
        }
        clearScreen();
    }
    displayResult(playerScore, computerScore);
}
void clearBoard(char board[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            board[i][j] = '~';
        }
    }
}
void initializeBoard(char board[10][10])
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '~';
}
void setColor(int textColor, int bgColor)

{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);
}

void printBoard(char board[10][10], bool hideShips)
{
    cout << "       0     1     2     3     4     5     6     7     8     9  " << endl;

    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "   " << i << "|";
        for (int j = 0; j < 10; j++)
        {
            char cell = board[i][j];
            if (cell == 'X')
            {
                setColor(15, 12);
                cout << "  X  ";
                // setColor(7, 0);
            }
            else if (cell == 'O')
            {
                setColor(0, 8);
                cout << "  O  ";
                // setColor(7, 0);
            }
            else if (cell == 'S' && hideShips == false)
            {
                if (playerturn == 1)
                {
                    setColor(15, player1shipcolor);
                }
                else
                {
                    setColor(15, player2shipcolor);
                }

                cout << "  S  ";
            }
            else
            {
                setColor(7, 1);
                cout << "  ~  ";
            }
            setColor(7, 0);
            cout << "|";
        }

        cout << endl;
        cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    }
    cout << endl;
}
void fullBoard(char board[10][10], char board1[10][10], char board2[10][10])
{
    cout << endl;
    cout << "             ENEMY BOARD                                      OPPONENT                                         PLAYER BOARD" << endl
         << endl;
    cout << "                                         0     1     2     3     4     5     6     7     8     9  " << endl;
    cout << "   0  1  2  3  4  5  6  7  8  9";
    cout << "       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << "       0  1  2  3  4  5  6  7  8  9" << endl;

    for (int i = 0; i < 10; i++)
    {
        //  ENEMY
        cout << i << " ";
        for (int j = 0; j < 10; j++)
        {
            char cell = board[i][j];

            if (cell == 'X')
            {
                cout << " X ";
            }
            else if (cell == 'O')
            {
                cout << " O ";
            }
            else
            {
                cout << " . ";
            }
        }

        cout << "    ";

        // GAME BOARD

        cout << i << " |";

        for (int k = 0; k < 10; k++)

        {

            char cell = board1[i][k];

            if (cell == 'X' || cell == 'P')
            {
                if (cell == 'P' || shiplabel1[i][k] == 'P' || shiplabel2[i][k] == 'P')
                {
                    setColor(15, 13);
                    cout << "  X  ";
                }
                else
                {
                    setColor(15, 12);
                    cout << "  X  ";
                }
                setColor(7, 0);
            }
            else if (cell == 'O')
            {
                setColor(0, 8);
                cout << "  O  ";
                setColor(7, 0);
            }
            else
            {
                setColor(7, 1);
                cout << "  ~  ";
                setColor(7, 0);
            }
            cout << "|";
        }
        cout << "    ";
        // PLAYER
        cout << i << " ";
        for (int m = 0; m < 10; m++)
        {
            char cell = board2[i][m];

            if (cell == 'X')
            {
                cout << " X ";
            }
            else if (cell == 'O')
            {
                cout << " O ";
            }
            else
            {
                cout << " . ";
            }
        }

        cout << endl;

        cout << "                                      +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    }
}

int main()
{

    ShowGameMenu();
    return 0;
}