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
			int i,j;
			for(i=0;i<size;i++)
			{
				for(j=0;j<size;j++)
					switch (arr[i][j])
					{
						case(empty):
							cout<<"+ ";
							break;
						case(white):
							cout<<"O ";
							break;
						case(black):
							cout<<"X ";
							break;
						default:
							cout<<endl<<"algo errado no codigo "<<endl;
							return;
					}
				cout<<endl;
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
		void put(int x, int y,Point value)
		{
			arr[x][y]=value;
		}
};

int main()
{
	Board board(5);
	board.show();
	board.put(0,0,white);
	board.put(0,1,white);
	board.put(1,0,black);
	string S="";
	while (S!="quit")
	{
		cin>>S;
	}
	board.show();
	cout<<board.alive(0,0)<<endl;
	board.cleanup_visited();
	return 0;
}
