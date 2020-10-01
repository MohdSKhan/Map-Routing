#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
#include<string>
#include<algorithm>
using namespace std;
#define MAX 200001
#define infinity (long double)1e18
vector<vector<pair<long double,int> > > Adjacency_List;
vector<pair<int,int>>Vertices;
int vertices,edges;
#include "Binary_heap.h"
#include "Dijkstra.h"
vector<int>A,B,C,D;
void Read_Map()
{
	clock_t start_Map=clock();
	int V,X,Y,From,To,N;
	cin>>vertices>>edges;
	Adjacency_List.resize(vertices);
	Vertices.resize(vertices);
	for(int i=0 ; i<Vertices.size() ; i++)
	{
		cin>>V>>X>>Y;
		Vertices[V].first=X;
		Vertices[V].second=Y;
	}
	for(int i=0 ; i<edges ; i++)
	{
		cin>>From>>To;
		pair<long double,int>Ver;
		Ver.second=To;
		Ver.first=Calculate_Distance(Vertices[From],Vertices[To]);
		Adjacency_List[From].push_back(Ver);
		Ver.second=From;
		Adjacency_List[To].push_back(Ver);
	}
	clock_t end_Map=clock();
	cout<<"Map is ready\n";
	cout<<"Execution time = "<<end_Map-start_Map<<"ms\n\n";
}
void Read_Routes()
{
	int N,From,To,Path_Lenth;
	clock_t Total_Dijkstra=0,Total_Dijkstra_Idea_3=0,Total_Dijkstra_Idea_1_3=0,Total_Dijkstra_Idea_1_2_3=0;
	cin>>N;
	int I=1;
	while (N--)
	{
		cin>>From>>To;
		////Dijkstra
		clock_t Start_Dijkstra=clock();
		long double Dijkstra_Time = Dijkstra(From,To);
		clock_t End_Dijkstra=clock();

		////Dijkstra (Idea 3)
		clock_t Start_Dijkstra_Idea_3=clock();
		long double Idea_3 = Dijkstra_Idea_3(From,To);
		clock_t End_Dijkstra_Idea_3=clock();

		////Dijkstra (Idea 1 & 3)
		clock_t Start_Dijkstra_Idea_1_3=clock();
		long double Idea_1_3 = Dijkstra_Idea_1_3(From,To);
		clock_t End_Dijkstra_Idea_1_3=clock();

		////Dijkstra (Idea 1 & 2 & 3)
		clock_t Start_Dijkstra_Idea_1_2_3=clock();
		long double Idea_1_2_3 = Dijkstra_Idea_1_2_3(From,To);
		clock_t End_Dijkstra_Idea_1_2_3=clock();


		cout<<"Shortest path from "<<From<<" to "<<To<<" = ";
		for(int i=0 ; i<Shortest_Path.size() ; i++)
		{
			cout<<Shortest_Path[i];
			if(i<Shortest_Path.size()-1)
				cout<<"-";
			else
				cout<<endl;
		}
		cout<<"Dijkstra :-\n";
		cout<<"Execution time = "<<End_Dijkstra-Start_Dijkstra<<"ms\n";
		cout<<"Total Cost = "<<Dijkstra_Time<<endl;
		////
		cout<<"Dijkstra (Idea 3):-\n";
		cout<<"Execution time = "<<End_Dijkstra_Idea_3-Start_Dijkstra_Idea_3<<"ms\n";
		cout<<"Total Cost = "<<Idea_3<<endl;
		////
		cout<<"Dijkstra (Idea 1 & 3):-\n";
		cout<<"Execution time = "<<End_Dijkstra_Idea_1_3-Start_Dijkstra_Idea_1_3<<"ms\n";
		cout<<"Total Cost = "<<Idea_1_3<<endl;
		////
		cout<<"Dijkstra (Idea 1 & 2 & 3):-\n";
		cout<<"Execution time = "<<End_Dijkstra_Idea_1_2_3-Start_Dijkstra_Idea_1_2_3<<"ms\n";
		cout<<"Total Cost = "<<Idea_1_2_3<<endl;
		////

		cout<<endl;
		Total_Dijkstra+=(End_Dijkstra-Start_Dijkstra);
		Total_Dijkstra_Idea_3+=(End_Dijkstra_Idea_3-Start_Dijkstra_Idea_3);
		Total_Dijkstra_Idea_1_3+=(End_Dijkstra_Idea_1_3-Start_Dijkstra_Idea_1_3);
		Total_Dijkstra_Idea_1_2_3+=(End_Dijkstra_Idea_1_2_3-Start_Dijkstra_Idea_1_2_3);
	}
	cout<<"\nDijkstra :-\n";
	cout<<"Total execution time of routing requests = "<<Total_Dijkstra<<"ms\n";
	cout<<"Dijkstra (Idea 3):-\n";
	cout<<"Total execution time of routing requests = "<<Total_Dijkstra_Idea_3<<"ms\n";
	cout<<"Dijkstra (Idea 1 & 3):-\n";
	cout<<"Total execution time of routing requests = "<<Total_Dijkstra_Idea_1_3<<"ms\n";
	cout<<"Dijkstra (Idea 1 & 2 & 3):-\n";
	cout<<"Total execution time of routing requests = "<<Total_Dijkstra_Idea_1_2_3<<"ms\n";
}
void INPUT()
{
	clock_t start=clock();
	string line;
	ifstream Map ("Map.txt");
	ifstream Routes ("Routes.txt");
	ofstream All ("All.txt");
	if (Map.is_open())
	{
		while ( getline (Map,line) )
		{
			if (All.is_open())
				All << line << '\n';
		}
		Map.close();
	}
	if (Routes.is_open())
	{
		while ( getline (Routes,line) )
		{
			if (All.is_open())
				All << line << '\n';
		}
		Routes.close();
	}
	All.close();
	clock_t end=clock();
	cout<<"Read 2 input files and put input in 1 file\n";
	cout<<"Execution time = "<<end-start<<"ms\n\n";
}
int main()
{
	clock_t Start_Map_Routing=clock();
	//freopen("OutPut.txt","w",stdout);
	INPUT();
	////---------------------------
	freopen("All.txt","r",stdin);
	Read_Map();
	Read_Routes();
	//use manual clock function here
	clock_t End_Map_Routing=clock();
	cout<<"\nAll Done\nMap_Routing\n";
	cout<<"Total program time = "<<End_Map_Routing-Start_Map_Routing<<"ms\n\n";
}
