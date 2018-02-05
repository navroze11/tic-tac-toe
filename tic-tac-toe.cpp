#include<bits/stdc++.h>
using namespace std;

//Included  prototype since both are recursive functions
int minSearch(char board[][3]);
int maxSearch(char board[][3]);

struct Move
{
	int row, col;
};

char player = 'x', ai = 'o', space = '_';

//Check if game is a tie
bool checkTie(char board[][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == space || board[i][1] == space || board[i][2] == space)
            return false;
    }
    return true;
}

//Display board with 'x' and 'o' values 
void displayBoard(char board[][3])
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout<<"_"<<board[i][j]<<"_"<<"|";
		}
		cout<<endl;
	}	
}

//Initialize board
void initBoard(char board[][3])
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			board[i][j] = space;
		}
	}
}

//Check if there are any moves left to play
bool isMovesLeft(char board[3][3])
{
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (board[i][j]==space)
				return true;
	return false;
}

//Check if ai has won or players has one
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

//AI evaluation criteria
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

//Player evaluation criteria
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
                board[i][j] = player;
                score = max(score, minSearch(board));
                board[i][j] = space;
            }
        }
    }

    return score;
}

// This will return the best possible move for the ai
int minimax(char board[][3],bool isMaxPlayer ,int alpha, int beta) 
{
	if (checkWin(board, player)) { return -10; }
        else if (checkWin(board, ai)) { return +10; }
        else if (checkTie(board)) { return 0; }

    if(isMaxPlayer)
    {
    	int bestVal = INT_MIN;
    	for ( int i = 0; i < 3; i++)
    	{
    	    for ( int j = 0; j < 3; j++)
    	    {
    	        if (board[i][j] == space)
    	        {
    	            board[i][j] = player;
    	            bestVal = max(bestVal, minimax(board, false, alpha, beta));
    	            board[i][j] = space;
    	            alpha = max(alpha, bestVal);
    	            if(alpha >= beta)
    	            	break;
    	        }
    	    }
    	}
    }
    else  
    {
		int bestVal = INT_MAX;
		for ( int i = 0; i < 3; i++)
		{
		    for ( int j = 0; j < 3; j++)
		    {
		        if (board[i][j] == space)
		        {
		            board[i][j] = ai;
		            bestVal = min(bestVal, minimax(board, true, alpha, beta));
		            board[i][j] = space;
		            alpha = min(alpha, bestVal);
		            if(alpha >= beta)
		            {
		            	break;
		            }
		        }
		    }
		}
		return bestVal;
    }
}

// This will return the best possible move for the player
Move findBestMove(char board[][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
 
    // Traverse all cells, evalutae minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if celll is empty
            if (board[i][j]==space)
            {
                // Make the move
                board[i][j] = ai;
 
                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, true, INT_MIN, INT_MAX);
 
                // Undo the move
                board[i][j] = space;
 
                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}


//Start the game
void startGame()
{
	char board[3][3] =
		{
			{ 'o', 'o', 'x' },
			{ '_', 'o', 'x' },
			{ 'x', '_', '_' }
		}; 
	Move bestMove = findBestMove(board);

		printf("ROW: %d COL: %d", bestMove.row,
									bestMove.col );
	// int row, column, score;
	// while(isMovesLeft(board))
	// {
	// 	do{
	// 		cout<<"\nEnter the row[1-3] and column[1-3] | (Example: 2 3) | = ";
	// 		cin>>row>>column;	
	// 		cout<<endl;
	// 	} while((row > 3 || row < 1) || column > 3 || column < 1);
	// 	board[row-1][column-1] = 'x';
	// 	displayBoard(board);
	// 	if(checkWin(board, player))
	// 	{
	// 		cout<<"--------------"<<endl;
	// 		cout<<"Player wins!!!"<<endl;
	// 		cout<<"--------------"<<endl;
	// 		return;
	// 	}
	// 	Move bestMove = findBestMove(board);
	// 	board[bestMove.row][bestMove.col] = 'o';
	// 	cout<<"\nComputer has played: "<<bestMove.row+1<<" "<<bestMove.col+1<<endl<<endl;
	// 	displayBoard(board);
	// 	if(checkWin(board, ai))
	// 	{
	// 		cout<<"----------------"<<endl;
	// 		cout<<"Computer wins!!!"<<endl;
	// 		cout<<"----------------"<<endl<<endl;
	// 		return;	
	// 	}
	// 	if (checkTie(board))
	// 	{
	// 		cout<<"------------------"<<endl;
	// 	    cout << "\n*** MATCH DRAW ***\n";
	// 	    cout<<"------------------"<<endl<<endl;
	// 	}	
	// }
}

// Driver code
int main()
{
	// char board[3][3];
	char choice;
	do{
		// initBoard(board);
		cout<<"Would you like to play a game of tic-tac-toe: \n1).Y(Yes)\n2).N(No)?\n3).Press ctrl+c to exit\n";
		cin>>choice;
		if(choice == 'n' || choice == 'N')
			break;
		cout<<"======================="<<endl;
		cout<<"Welcome to tic-tac-toe!"<<endl;
		cout<<"======================="<<endl;
		startGame();
	} while(choice == 'y' || choice == 'Y');
	return 0;
}
