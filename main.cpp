#include <iostream>
#include <stdlib.h>
using namespace std;

enum Point{	empty=0, white=1, black=-1 };
enum Play{ pass=0, valid=1, ko=-1, suicide=-2, occupied=-3 };

class Board
{
		int size;
		Point ** arr;
		bool ** visited;
	public:
		Board(){};
		void setup(int s)
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
		void delete_visited(void)
		{
			int i,j;
			for(i=0;i<size;i++)
			for(j=0;j<size;j++)
			if(visited[i][j])
				arr[i][j]=empty;
		}
		void show(void)
		{
			cout<<endl<<endl;
			int i,j;
			for(i=0;i<size;i++)
			{
				cout<<"  ";
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
			cout<<"  ";
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
			visited[x][y] = true;
			if(((0<x-1)&&
				 (arr[x-1][y]==empty
				 || (arr[x-1][y]==arr[x][y] && !visited[x-1][y] && alive(x+1,y))))
			|| ((0<y-1)&&
				 (arr[x][y-1]==empty
				 || (arr[x][y-1]==arr[x][y] && !visited[x][y-1] && alive(x,y-1))))
			|| ((x+1<size)&&
				 (arr[x+1][y]==empty
				 || (arr[x+1][y]==arr[x][y] && !visited[x+1][y] && alive(x+1,y))))
			|| ((y+1<size)&&
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
		void mark_group(int x, int y)
		{
			visited[x][y] = true;
			if( (0<x-1) && arr[x-1][y]==arr[x][y] && !visited[x-1][y] )
				mark_group(x-1,y);
			if( (0<y-1) && arr[x][y-1]==arr[x][y] && !visited[x][y-1] )
				mark_group(x,y-1);
			if( (size>x+1) && arr[x+1][y]==arr[x][y] && !visited[x+1][y] )
				mark_group(x+1,y);
			if( (size>y+1) && arr[x][y+1]==arr[x][y] && !visited[x][y+1] )
				mark_group(x,y+1);				
			return;
		}
		void capture_group(int x, int y)
		{
			cout<<"capturing"<<x<<" "<<y<<endl;
			mark_group(x,y);
			delete_visited();
			cleanup_visited();
		}
		
		Play put(int x, int y,Point value)
		{
			if (x==0 && y==0)
				return pass;
			x-=1;y-=1;
			if (x<size && y<size && arr[x][y]==empty)
			{
				bool capture=false;
				arr[x][y]=value;
				if (x+1<size && arr[x][y]==-arr[x+1][y] && !alive(x+1,y))
				{
					capture_group(x+1,y);
					capture=true;
				}
				if (x-1>0 && arr[x][y]==-arr[x-1][y] && !alive(x-1,y))
				{
					capture_group(x-1,y);
					capture=true;
				}
				if (y+1<size && arr[x][y]==-arr[x][y+1]&& !alive(x,y+1))
				{
					capture_group(x,y+1);
					capture=true;
				}
				if (y-1>0 && arr[x][y]==-arr[x][y-1] && !alive(x,y-1))
				{
					capture_group(x,y-1);
					capture=true;
				}	
				if (!capture && !alive(x,y))
				{
					arr[x][y]=empty;
					return suicide;
				}
			}else{
				return occupied;
			}
			return valid;
		}
};

int main()
{
	int option, size;
	cout<<"Bem vindo! 0 para inicar nova partida padrao, 1 para tabuleiro diferente, 2 para carregar arquivo ";
	cin>>option;
	Board board;
	switch (option)
	{
		case(0):
			size=19;
			board.setup(size);
			break;
		case(1):
			cin>>size;
			board.setup(size);
			break;
		case(2):
			break;
		default:
			break;
	}

	board.show();
	string S="";
	int a=0, b=0;
	Point current_player=black;
	while (a!=-1)
	{
		cout<<"Digite a sua jogada ";
		cin>>a>>b;
		switch(board.put(a,b,current_player))
		{
			case (valid):
				board.show();
				current_player = (Point)-current_player ;
				break;
			case (suicide):
				cout<<"Jogada suicida"<<endl;
				break;
			case (occupied):
				cout<<"Ponto ja ocupado"<<endl;
				break;
			case (ko):
				cout<<"Jogada repetida"<<endl;
				break;
			case (pass):
				cout<<"Passou a vez"<<endl;
				break;
		}
	}
	cout<<board.alive(1,1)<<endl;
	board.cleanup_visited();
	return 0;
}
