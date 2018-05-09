#include <iostream>
#include <stdlib.h>

using namespace std;

class Board
{
	int size;
	char ** arr;
	public:
		Board(int s)
		{
			size=s;
			int i,j;
			arr = (char**) malloc(size * sizeof(char*));
			for(i=0;i<size;i++)
				arr[i] = (char*) malloc(size*sizeof(char));
			for(i=0;i<size;i++)
				for(j=0;j<size;j++)
					arr[i][j]='+';
		}
		void show(void)
		{	
			int i,j;
			for(i=0;i<size;i++)
			{
				for(j=0;j<size;j++)
					cout<<arr[i][j]<<" ";
				cout<<endl;
			}
			cout<<endl;
		}
		bool is_legal(int x, int y)
		{
			return true;
		}
		void put(int x, int y)
		{
			arr[x][y]='X';
		}
	
};

int main()
{
	Board board(5);
	board.show();
	board.put(4,4);
	board.show();
	return 0;
}
