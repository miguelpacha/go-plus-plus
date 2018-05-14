#include <iostream>
#include <stdlib.h>
using namespace std;

enum Point{
	empty,
	white,
	black,
};

class Board
{
	int size;
	Point ** arr;
	bool ** visited;
	public:
		Board(int s)
		{
			size=s;
			int i,j;
			// Inicializa arr (tabuleiro)
			arr = (Point**) malloc(size * sizeof(Point*));
			for(i=0;i<size;i++)
				arr[i] = (Point*) malloc(size*sizeof(Point));
			for(i=0;i<size;i++)
				for(j=0;j<size;j++)
					arr[i][j]=empty;
			// Inicializa visited
			visited = (bool**) malloc(size * sizeof(bool*));
			for(i=0;i<size;i++)
				visited[i] = (bool*) malloc(size*sizeof(bool));
			cleanup_visited();
		}
		void cleanup_visited(void)
		{
			int i,j;
			for(i=0;i<size;i++)
			for(j=0;j<size;j++)
				visited[i][j]=false;
		}
		void show(void)
		{
			cout<<endl<<endl;
			int i,j;
			for(i=0;i<size;i++)
			{
				for(j=0;j<size;j++)
					switch (arr[i][j])
					{
						case(empty):
							cout<<".  ";
							break;
						case(white):
							cout<<"O  ";
							break;
						case(black):
							cout<<"X  ";
							break;
						default:
							cout<<endl<<"algo errado no codigo "<<endl;
							return;
					}
				cout<<" "<<i+1<<endl<<endl;
			}
			for(j=1;j<=size;j++)
			{
				cout<<j<<" ";
				if (j<10) cout<<" ";
			}
			cout<<endl;
		}
		void show_v(void)
		{
			int i,j;
			for(i=0;i<size;i++)
			{
				for(j=0;j<size;j++)
					cout<<visited[i][j]<<" ";
				cout<<endl;
			}
			cout<<endl;
		}
		bool is_legal(int x, int y)
		{
			return true;
		}
		bool alive(int x, int y)
		{
			x=1; y=1;
			visited[x][y] = true;
			if(((0<x)&&
				 (arr[x-1][y]==empty
				 || (arr[x-1][y]==arr[x][y] && !visited[x-1][y] && alive(x+1,y))))
			|| ((0<y)&&
				 (arr[x][y-1]==empty
				 || (arr[x][y-1]==arr[x][y] && !visited[x][y-1] && alive(x,y-1))))
			|| ((x<size)&&
				 (arr[x+1][y]==empty
				 || (arr[x+1][y]==arr[x][y] && !visited[x+1][y] && alive(x+1,y))))
			|| ((y<size)&&
				 (arr[x][y+1]==empty
				 || (arr[x][y+1]==arr[x][y] && !visited[x][y+1] && alive(x,y+1))))
			)
			{
				cleanup_visited();
				return true;
			}
			cleanup_visited();
			return false;
		}
		bool put(int x, int y,Point value)
		{
			x-=1;y-=1;
			if (arr[x][y]==empty)
			{
				arr[x][y]=value;
			}else{
				return false;
			}
			return true;
		}
};

int main()
{
	Board board(19);
	board.show();
	string S="";
	int a=0, b=0;
	Point current_player=black;
	while (a!=-1)
	{
		cout<<"Digite a sua jogada ";
		cin>>a>>b;
		if(board.put(a,b,current_player))
		{
			board.show();
			current_player = (current_player==black) ? white : black;
		}else{
			cout<<"Jogada invalida"<<endl;
		}
	}
	cout<<board.alive(1,1)<<endl;
	board.cleanup_visited();
	return 0;
}
