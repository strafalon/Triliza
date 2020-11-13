#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char X      = 'X',
           O      = 'O',
           EMPTY  = ' ',
           TIE    = 'T',
           NO_ONE = 'N';


void introduction();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char firstMoveInvitation();
char takeOpponentSymbol(char piece);
void displayBoard(const vector<char>& board);
char checkForWinner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
void displayWinner(char checkForWinner, char computer, char human);
int computerMove(vector<char> board, char computer);



int main()
{
    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);

    introduction();
    char human = firstMoveInvitation();
    char computer = takeOpponentSymbol(human);
    char turn = X;
    displayBoard(board);

    while (checkForWinner(board) == NO_ONE)
    {
        if (turn == human)
        {
            move = humanMove(board, human);
            board[move] = human;
        }
        else
        {
            move = computerMove(board, computer);
            board[move] = computer;
        }
        displayBoard(board);
        turn = takeOpponentSymbol(turn);
    }

    displayWinner(checkForWinner(board), computer, human);

    return 0;
}



void introduction()
{
    cout << "H KINHSH DINETAI PLHKTROLOGWNTAS ENAN ARITHMO (1 - 9).  \n";
    cout << "O ARITHMOS AUTOS ANTISTOIXEI STIS THESEIS TOU PINAKA OPWS FAINETAI PARAKATW:\n\n";
    cout << "       1 | 2 | 3\n";
    cout << "       ---------\n";
    cout << "       4 | 5 | 6\n";
    cout << "       ---------\n";
    cout << "       7 | 8 | 9\n\n";
}



char askYesNo(string question)
{
    char response;
    do
    {
        cout << question << " (N/O): ";
        cin >> response;
    } while (response != 'N' && response != 'O');

    return response;
}



int askNumber(string question, int high, int low)
{
    int number;
    do
    {
        cout << question << " (" << low << " - " << high << "): ";
        cin >> number;
    } while (number > high || number < low);

    return number;
}



char firstMoveInvitation()
{
    char go_first = askYesNo("THES NA PAIXEIS PRWTOS?");
    if (go_first == 'N')
    {
        //cout << "\nOk, you play first.\n";
        return X;
    }
    else
    {
        //cout << "\nOk, I 'll play first.\n";
        return O;
    }
}



inline char takeOpponentSymbol(char piece)
{ return  piece == X ? O : X ; }



void displayBoard(const vector<char>& board)
{
    cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2]
         << "\n\t" << "---------"
         << "\n\t" << board[3] << " | " << board[4] << " | " << board[5]
         << "\n\t" << "---------"
         << "\n\t" << board[6] << " | " << board[7] << " | " << board[8]
         << "\n\n";
}



void displayWinner(char checkForWinner, char computer, char human)
{
	if (checkForWinner == computer)
    {
        cout << checkForWinner << "'s won!\n";
        cout << "NIKITIS EIMAI EGW\n";
    }

	else if (checkForWinner == human)
    {
        cout << checkForWinner << "'s (YOU) won !\n";
        cout << "NIKITIS EISAI ESY\n\n";
    }

	else
        cout << "DEN KERDISE KANEIS!\n\n";
}



char checkForWinner(const vector<char>& board)
{
    const int WINNING_ROWS[8][3] = { {0, 1, 2},
                                     {3, 4, 5},
                                     {6, 7, 8},
                                     {0, 3, 6},
                                     {1, 4, 7},
                                     {2, 5, 8},
                                     {0, 4, 8},
                                     {2, 4, 6} };
    const int TOTAL_ROWS = 8;

    for(int row = 0; row < TOTAL_ROWS; ++row)
    {
        if ( (board[WINNING_ROWS[row][0]] != EMPTY) &&
             (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
             (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]) )
        { return board[WINNING_ROWS[row][0]]; }
    }

    if (count(board.begin(), board.end(), EMPTY) == 0)
       return TIE;

    return NO_ONE;
}



inline bool isLegal(int move, const vector<char>& board)
{ return (board[move] == EMPTY); }



int humanMove(const vector<char>& board, char human)
{
    int move = askNumber("DWSE TIN THESI : ", board.size(),1);
    while (!isLegal(move-1, board))
    {
        cout << "\nAUTH H THESH EXEI HDH SYMPLYRWTHEI\n";
        move = askNumber("DWSE ALLH THESI: ", board.size(),1);
    }

    return move-1;
}



int computerMove(vector<char> board, char computer)
{
    unsigned int move = 0;
    bool found = false;

    while (!found && move < board.size())
    {
        if (isLegal(move, board))
        {
            board[move] = computer;
            found = checkForWinner(board) == computer;
            board[move] = EMPTY;
        }

        if (!found)
           ++move;
    }


    if (!found)
    {
        move = 0;
        char human = takeOpponentSymbol(computer);

        while (!found && move < board.size())
        {
            if (isLegal(move, board))
            {
				   board[move] = human;
               found = checkForWinner(board) == human;
				   board[move] = EMPTY;
            }

            if (!found)
                ++move;
        }
    }


    if (!found)
    {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

        while (!found && i <  board.size())
        {
            move = BEST_MOVES[i];
            if (isLegal(move, board))
            { found = true; }

            ++i;
        }
    }

    cout << "THA KINITHW STIN THESI " << move+1 << endl;
	 return move;
}
