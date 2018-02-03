#include<iostream>
#include<cstdlib>

using namespace std;

void initBoard(int board[][3])
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			board[i][j] = '_';
		}
	}
}

int main(void)
{
	int board[3][3];
	char choice;
	char player;
	do{
		cout<<"Would you like to play a game of tic-tac-toe: \n1).Y(Yes)\n2).N(No)?\n";
		cin>>choice;
		if(choice == 'n' || choice == 'N')
			break;
		cout<<"======================="<<endl;
		cout<<"Welcome to tic-tac-toe!"<<endl;
		cout<<"======================="<<endl;
		do{
			cout<<"Please select your choice: \n1).X(Goes first) \n2).O\n3).S(Stop)\n";
			cin>>player;
			if(player == 'S' || player == 's')
				break;
		} while(player != 'X');
		initBoard(board);
	} while(choice == 'y' || choice == 'Y');
	return 0;
}