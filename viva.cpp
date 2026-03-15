#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;
void develop();          //Menu
void instructions();     //MENU
void board_size();
void board_displayer(int size);
void GO(int size);
bool validTurn(int r, int c, int size);
void capture(int r, int c, int size, char opponentStone);
bool hasLiberty(int r, int c, int size, char stone, bool visited[][19]);
void calculateScore(int size);
void floodFillTerritory(int r, int c, int size, char opponent, bool visited[][19], char territoryOwner[][19]);
bool isKO(int size);  // New function to check for KO
bool sucide(int r, int c, int size);
char game[19][19];
bool turn = true;
int blackCaptured = 0, whiteCaptured = 0, blackScore = 0, whiteScore = 0;
char previousGame[19][19];  // New variable to store the previous board state

int main() {                              //MENU +LOGO+INITIALIZATION OF BOARD
    system("color 60");
    char menu;

    // Initialize the board
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            game[i][j] = '-';
        }
    }

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    // "G" Logo
    cout << setw(97) << setfill(' ') << "GGGGG   OOOOO       GGGGG       A       M   M   EEEEE " << endl;
    cout << setw(97) << setfill(' ') << "G       O   O       G          A A      MM MM   E     " << endl;
    cout << setw(97) << setfill(' ') << "G  GG   O   O       G  GG     AAAAA     M M M   EEEEE " << endl;
    cout << setw(97) << setfill(' ') << "G  GG   O   O       G  GG    A     A    M   M   E     " << endl;
    cout << setw(97) << setfill(' ') << "GGGGG   OOOOO       GGGGG   A       A   M   M   EEEEE " << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    cout << "Welcome to F24-0020's Go Game" << endl;
    cout << setw(76) << setfill('-') << "Menu" << setw(93) << setfill('-') << " " << endl;
    cout << "1) Press S to start game" << endl;
    cout << "2) Press I for instructions" << endl;
    cout << "3)Press A for About the developer" << endl;
    cout << "4) Press E to exit" << endl;
    cin >> menu;

    if (menu == 'S' || menu == 's')
    {
        board_size();
    }
    else if (menu == 'I' || menu == 'i')
    {
        instructions();
    }
    else if (menu == 'A' || menu == 'a')
    {
        develop();
    }
    else if (menu == 'E' || menu == 'e')
    {
        cout << "Exiting game." << endl;
        return 0;
    }
    else
    {
        cout << "error start game again" << endl;
        system("color 4");
    }

}

void instructions()                   //INSTRUCTIONS
{
    cout << "   INSTURCTIONS:" << endl;
    cout << "Objective: The goal of Go is to control more territory on the board than your opponent. Players do this by placing stones on the intersections of the grid, with the aim of surrounding empty areas and capturing the opponent's stones." << endl;
    cout << "Players: Go is played by two players.One player uses black stones, and the other uses white stones.Black typically goes first" << endl;
    cout << "Board : The standard Go board has a 19x19 grid of lines.Smaller boards, such as 9x9 or 13x13, are also used for beginners or shorter games" << endl;
    cout << "Placing Stones : Players take turns placing their stones on any empty intersection on the board.Once a stone is placed, it remains there unless it is captured." << endl;
    cout << " Liberties : Each stone has liberties, which are the empty points directly adjacent to it horizontally or vertically.A group of stones shares liberties.If a stone or a group of stones has no liberties(i.e., all adjacent points are occupied by the opponent’s stones), they are captured and removed from the board " << endl;
    cout << "Capture : A stone or group of stones is captured and removed from the board when it is surrounded on all four sides by the opponent’s stones.For example, if a group of stones has no liberties left, they are captured and removed" << endl;
    cout << " Ko Rule : A special rule called the Ko rule prevents the game from cycling indefinitely.If a player captures a stone and the board position is identical to the previous one, the opponent cannot immediately recapture the stone in the same way.This would create a loop, so the player must make another move before returning to the original position." << endl;
    cout << " Suicide : A player cannot place a stone in a position that would immediately result in the stone’s own capture unless doing so would capture opponent stones and create liberties for the placed stone." << endl;
    cout << " End of the Game : The game ends when both players consecutively pass their turns, indicating that they believe no further moves can be made to gain territory or capture stones.The game is then scored, and the player with the most territory(empty points surrounded by their stones, plus captured stones) wins." << endl;
    cout << "Scoring : There are two common scoring systems " << endl;
    cout << "	Territory Scoring : The score is the total number of empty intersections controlled by a player, plus the number of opponent’s stones captured" << endl << endl << endl << endl;
    char back;
    cout << "Press M to go back to menu" << endl;
    cin >> back;
    if (back == 'M')
    {
        main();
    }
    else
    {
        cout << "wrong letter entered ,taking u to menu again" << endl;
        main();
    }
}

void develop()                          //ABOUT ME
{
    cout << "ABOUT THE DEVELOPER" << endl;
    cout << "Language used:c++" << endl;
    cout << "The sole owner of this game is Abdullah Tahir roll number 24F-0020 is a student of bachelors in Artificial Intelligence at Fast National University, Chiniot Faisalabad campus.It's his final project for his core course programming fundamentals lab .The developer of this game has made this game working really hard for almost 10 days and has designed in such a way to provide best user interface with yellow color and black text color.The developer has used basics of c++ language or u can say the fundamentals of programming language.No part of this game can't be copied under the owner's privacy policy.We hope u will get best experience from that game and will reccomend others to play such a classy game." << endl;
    cout << endl << endl << endl << endl << endl << endl;
    cout << "GO GAME BY 0020 ,ALL RIGHTS RESERVED" << endl;
}


void board_size()                      //this is to take board size from the user and the board displayer
{
    int size;
    cout << "Enter 19 for 19x19 board, 13 for 13x13 board, or 9 for 9x9 board: ";
    cin >> size;

    if (size == 19 || size == 13 || size == 9)
    {
        board_displayer(size);
    }
    else
    {
        cout << "Invalid input. Try again." << endl;
        board_size();
    }
}

void board_displayer(int size)       //it will display the board for the first time with all areas unoccupied and then it will call the GO function which will take inputs
{

    cout << "                                ";
    for (int i = 0; i < size; i++)
    {
        cout << i + 1;
        if (i + 1 < 10)
        {
            cout << "  ";
        }
        else cout << " ";
    }
    cout << endl << "                             ";

    for (int i = 0; i < size; i++)
    {
        cout << i + 1;
        if (i + 1 < 10)
        {
            cout << "  ";
        }
        else cout << " ";
        for (int j = 0; j < size; j++)
        {
            cout << game[i][j] << "  ";
        }
        cout << endl << "                             ";

    }

    GO(size);
}

bool validTurn(int r, int c, int size) {
    if (r < 1 || r > size || c < 1 || c > size || game[r - 1][c - 1] != '-') {
        return false;
    }
    return true;
}
bool sucide(int r, int c, int size)
{
    if (turn == true)
    {

        if (r > 1 && game[r - 2][c - 1] == '-' || game[r - 2][c - 1] == 'B') return true;
        else if (r < size && game[r][c - 1] == '-' || game[r - 2][c - 1] == 'B') return true;
        else if (c > 1 && game[r - 1][c - 2] == '-' || game[r - 2][c - 1] == 'B') return true;
        else if (c < size && game[r - 1][c] == '-' || game[r - 2][c - 1] == 'B') return true;
        else return false;
    }
    else
    {
        if (r > 1 && game[r - 2][c - 1] == '-' || game[r - 2][c - 1] == 'W') return true;
        else if (r < size && game[r][c - 1] == '-' || game[r - 2][c - 1] == 'W') return true;
        else if (c > 1 && game[r - 1][c - 2] == '-' || game[r - 2][c - 1] == 'W') return true;
        else if (c < size && game[r - 1][c] == '-' || game[r - 2][c - 1] == 'W') return true;
        else return false;
    }
}





void capture(int r, int c, int size, char opponentStone) {
    bool visited[19][19] = { false };
    if (!hasLiberty(r, c, size, opponentStone, visited)) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (visited[i][j]) {
                    game[i][j] = '-';
                    if (opponentStone == 'B') {
                        whiteCaptured++;
                    }
                    else if (opponentStone == 'W') {
                        blackCaptured++;
                    }
                }
            }
        }
    }
}

bool hasLiberty(int r, int c, int size, char stone, bool visited[][19]) {
    if (r < 1 || r > size || c < 1 || c > size || visited[r - 1][c - 1] || game[r - 1][c - 1] != stone) {
        return false;
    }

    visited[r - 1][c - 1] = true;

    if (r > 1 && game[r - 2][c - 1] == '-') return true;
    if (r < size && game[r][c - 1] == '-') return true;
    if (c > 1 && game[r - 1][c - 2] == '-') return true;
    if (c < size && game[r - 1][c] == '-') return true;

    return hasLiberty(r - 1, c, size, stone, visited) ||
        hasLiberty(r + 1, c, size, stone, visited) ||
        hasLiberty(r, c - 1, size, stone, visited) ||
        hasLiberty(r, c + 1, size, stone, visited);
}

bool isKO(int size) {
    // Check if the current board is the same as the previous board
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (game[i][j] != previousGame[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void GO(int size) { //to take inputs and option to end the game 
    int r, c;

    cout << (turn ? "Black's turn (B)" : "White's turn (W)") << endl;
    cout << "Enter row and column (or 0 0 to end): ";
    cin >> r >> c;

    if (r == 0 && c == 0)
    {
        int over;
        cout << "Game is going to end as done by one player who had the turn,other player please enter 0 to end the game";
        cin >> over;
        calculateScore(size);
        cout << "Game Over! Final Scores:" << endl;
        if (blackScore == 80)
        {
            cout << "Black: " << 80 - blackScore << endl;
            cout << "White: " << whiteScore << endl;

            return;
        }
        else
        {
            cout << "Black: " << blackScore << endl;
            cout << "White: " << whiteScore << endl;
            if (blackScore > whiteScore)
            {
                cout << "BLACK WON" << endl;
            }
            else if (blackScore < whiteScore)
            {
                cout << "WHITE WON" << endl;
            }
            cout << "THANKS FOR PLAYING" << endl;
            return;
        }
    }

    if (!validTurn(r, c, size))                      //checking for bounds,calls the valid turn function
    {
        cout << "Invalid move. Try again." << endl;
        system("color 4");
        cout << "..........." << endl;
        system("color 60");
        GO(size);
        return;
    }
    else if (!sucide(r, c, size))
    {
        cout << "sucidal move. Try again." << endl;
        system("color 4");
        cout << "..........." << endl;
        system("color 60");
        GO(size);
        return;
    }
    // Save the current board state before making the move
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            previousGame[i][j] = game[i][j];
        }
    }

    game[r - 1][c - 1] = turn ? 'B' : 'W';

    char opponentStone = turn ? 'W' : 'B';     //gpt

    // Check for KO rule (if the move causes the game to return to the previous state)
    if (isKO(size)) {
        cout << "KO rule violation! You cannot make this move." << endl;
        game[r - 1][c - 1] = '-';  // Undo the move
        GO(size);
        return;
    }

    // Check captures
    if (r > 1) capture(r - 1, c, size, opponentStone);
    if (r < size) capture(r + 1, c, size, opponentStone);
    if (c > 1) capture(r, c - 1, size, opponentStone);
    if (c < size) capture(r, c + 1, size, opponentStone);

    turn = !turn;

    board_displayer(size);
}

void calculateScore(int size)
{
    bool visitedBlack[19][19] = { false };
    bool visitedWhite[19][19] = { false };
    char territoryBlack[19][19] = {};
    char territoryWhite[19][19] = {};

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            territoryBlack[i][j] = '-';
            territoryWhite[i][j] = '-';
        }
    }
    blackScore = 0;
    whiteScore = 0;

    blackScore += blackCaptured;
    whiteScore += whiteCaptured;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (!visitedBlack[i][j] && game[i][j] == 'B')
                floodFillTerritory(i, j, size, 'W', visitedBlack, territoryBlack);
            if (!visitedWhite[i][j] && game[i][j] == 'W')
                floodFillTerritory(i, j, size, 'B', visitedWhite, territoryWhite);
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (territoryBlack[i][j] == 'X' && territoryWhite[i][j] == 'X') {
                territoryBlack[i][j] = '-';
                territoryWhite[i][j] = '-';
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (territoryBlack[i][j] == 'X')
            {
                blackScore++;
            }
            if (territoryWhite[i][j] == 'X')
            {
                whiteScore++;
            }
        }
    }
    if (blackScore == 80)
    {
        cout << "Black Score: " << blackScore - 80 << endl;
        cout << "White Score: " << whiteScore << endl;
    }
    else
    {
        cout << "Black Score: " << blackScore << endl;
        cout << "White Score: " << whiteScore << endl;
    }
}

void floodFillTerritory(int r, int c, int size, char opponent, bool visited[][19], char territoryOwner[][19])
{
    if (r < 0 || r >= size || c < 0 || c >= size || territoryOwner[r][c] == true || visited[r][c] == true || game[r][c] == opponent)
        return;

    if (game[r][c] == '-' && territoryOwner[r][c] == '-')
    {
        territoryOwner[r][c] = 'X';
    }
    visited[r][c] = true;

    floodFillTerritory(r - 1, c, size, opponent, visited, territoryOwner);
    floodFillTerritory(r + 1, c, size, opponent, visited, territoryOwner);
    floodFillTerritory(r, c - 1, size, opponent, visited, territoryOwner);
    floodFillTerritory(r, c + 1, size, opponent, visited, territoryOwner);
}

