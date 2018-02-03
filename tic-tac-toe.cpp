// C++ program to find the next optimal move for
// a player
#include<bits/stdc++.h>
using namespace std;

int minSearch(char board[][3]);
int maxSearch(char board[][3]);

struct Move
{
	int row, col;
};

char player = 'x', ai = 'o', space = '_';

bool checkTie(char board[][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == space || board[i][1] == space || board[i][2] == space)
            return false;
    }
    return true;
}

void displayBoard(char board[][3])
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout<<board[i][j];
		}
		cout<<endl;
	}	
}

void initBoard(char board[][3])
{
	cout<<"Board initialized";
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			board[i][j] = space;
		}
	}
}


bool isMovesLeft(char board[3][3])
{
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (board[i][j]==space)
				return true;
	return false;
}

bool checkWin(char board[][3], char pla)
{
    for ( int i = 0; i < 3; i++)
    {
        // Check horizontals
        if (board[i][0] == pla && board[i][1] == pla && board[i][2] == pla)
            return true;

        // Check verticals
        if (board[0][i] == pla && board[1][i] == pla && board[2][i] == pla)
            return true;
    }

    // Check diagonals
    if (board[0][0] == pla && board[1][1] == pla && board[2][2] == pla)
        return true;

    if (board[0][2] == pla && board[1][1] == pla && board[2][0] == pla)
        return true;

    return false;
}


int minSearch(char board[][3])
{
    if (checkWin(board, player)) { return 10; }
        else if (checkWin(board, ai)) { return -10; }
        else if (checkTie(board)) { return 0; }

    int score = numeric_limits<int>::max();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == space)
            {
                board[i][j] = 'o';
                score = min(score, maxSearch(board));
                board[i][j] = space;
            }
        }
    }

    return score;
}

int maxSearch(char board[][3]) 
{
	if (checkWin(board, player)) { return 10; }
        else if (checkWin(board, ai)) { return -10; }
        else if (checkTie(board)) { return 0; }

    int score = numeric_limits<int>::min();

    for ( int i = 0; i < 3; i++)
    {
        for ( int j = 0; j < 3; j++)
        {
            if (board[i][j] == space)
            {
                board[i][j] = 'x';
                score = max(score, minSearch(board));
                board[i][j] = space;
            }
        }
    }

    return score;
}

// This will return the best possible move for the player
Move minimax(char board[][3]) 
{
    int score = numeric_limits<int>::max();
    Move move;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == space)
            {
                board[i][j] = ai;

                int temp = maxSearch(board);

                if (temp < score)
                {
                    score = temp;
                    move.row = i;
                    move.col = j;
                }
                board[i][j] = space;
            }
        }
    }

    return move;
}


//Start the game
void startGame(char board[][3])
{
	int row, column, score;
	while(isMovesLeft(board))
	{
		cout<<"\nEnter the row and column: ";
		cin>>row>>column;
		//check validation of cell before inserting
		board[row-1][column-1] = 'x';
		displayBoard(board);
		if(checkWin(board, player))
		{
			cout<<"Player wins!!!"<<endl;
			return;
		}
		Move bestMove = minimax(board);
		board[bestMove.row][bestMove.col] = 'o';
		displayBoard(board);
		if(checkWin(board, ai))
		{
			cout<<"Computer wins!!!"<<endl;
			return;	
		}
		if (checkTie(board))
		{
		    std::cout << "\n*** Tie ***\n";
		}	
	}
}

// Driver code
int main()
{
	char board[3][3];
	char choice;
	do{
		initBoard(board);
		cout<<"Would you like to play a game of tic-tac-toe: \n1).Y(Yes)\n2).N(No)?\n";
		cin>>choice;
		if(choice == 'n' || choice == 'N')
			break;
		cout<<"======================="<<endl;
		cout<<"Welcome to tic-tac-toe!"<<endl;
		cout<<"======================="<<endl;
		startGame(board);
	} while(choice == 'y' || choice == 'Y');
	return 0;
}
