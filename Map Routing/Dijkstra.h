vector<int>Path,Shortest_Path;
long double Distance[MAX],Distance2[MAX];
void Save_Path(int Destination)
{
	if(Destination==-1)
		return;
	Save_Path(Path[Destination]);
	Shortest_Path.push_back(Destination);	
}
long double Calculate_Distance(pair<int,int> From,pair<int,int> To)
{
	return (long double)sqrt((long double)( pow((From.first-To.first),2)+pow((From.second-To.second),2) ));
}

//O(|E|^2)
long double Dijkstra(int Source,int Destination)
{
	bool Visited[MAX];
	Shortest_Path.clear();
	Path=vector<int>(Vertices.size(),-1);
	fill(Distance, Distance + Adjacency_List.size(), infinity);
	memset(Visited,0,sizeof Visited);
	Distance[Source] = 0;
	int node = Source,nextIndex=0;
	long double  Min;
	vector<pair< long double,int > > Vec;
	Vec.push_back(make_pair(0,Source));
	while(Vec.size())
	{
		Min= infinity;
		Visited[node] = true;
		Vec.erase(Vec.begin()+nextIndex);
		for(int i = 0 ; i < Adjacency_List[node].size() ; ++ i )
		{
			if(!Visited[Adjacency_List[node][i].second] && Distance[node] + Adjacency_List[node][i].first < Distance[Adjacency_List[node][i].second])
			{
				Distance[Adjacency_List[node][i].second] = Distance[node] + Adjacency_List[node][i].first;
				Vec.push_back(make_pair(Distance[Adjacency_List[node][i].second],Adjacency_List[node][i].second));
				Path[Adjacency_List[node][i].second]=node;
			}
		}
		nextIndex=0;
		for (int i = 0; i < Vec.size(); i++)
		{
			if(!Visited[Vec[i].second] && Vec[i].first < Min){
				nextIndex=i;
				node=Vec[i].second;
				Min=Vec[i].first;
			}
		}
	}
	Save_Path(Destination);
	return Distance[Destination];
}

//O( (|E|+|V|) log|V| )
long double Dijkstra_Idea_3(int Source, int Destination)
{
	Shortest_Path.clear();
	Path=vector<int>(Vertices.size(),-1);
	fill(Distance, Distance + Adjacency_List.size(), infinity);
	Distance[Source] = 0;
	priority_queue< pair<long double, int> > Priority_Queue(edges);
	Priority_Queue.push(make_pair(0, Source));
	while (Priority_Queue.size()) 
	{
		int Current_Vertex = Priority_Queue.top().second;
		long double Current_Distance = Priority_Queue.top().first;
		Priority_Queue.pop();
		if (Current_Distance != Distance[Current_Vertex])
			continue;
		for (int i = 0; i < Adjacency_List[Current_Vertex].size(); ++i) 
		{
			int New_Vertex = Adjacency_List[Current_Vertex][i].second;
			long double New_Distance = Current_Distance + Adjacency_List[Current_Vertex][i].first;
			if (Distance[New_Vertex] > New_Distance) 
			{
				Path[New_Vertex] = Current_Vertex;
				Distance[New_Vertex] = New_Distance;
				Priority_Queue.push(make_pair(New_Distance, New_Vertex));
			}
		}
	}
	Save_Path(Destination);
	return Distance[Destination];
}

//O( (|E|+|V|) log|V| )
long double Dijkstra_Idea_1_3(int Source, int Destination)
{
	Shortest_Path.clear();
	Path=vector<int>(Vertices.size(),-1);
	fill(Distance, Distance + Adjacency_List.size(), infinity);
	Distance[Source] = 0;
	priority_queue< pair<long double, int> > Priority_Queue(edges);
	Priority_Queue.push(make_pair(0, Source));
	while (Priority_Queue.size()) 
	{
		int Current_Vertex = Priority_Queue.top().second;
		long double Current_Distance = Priority_Queue.top().first;
		Priority_Queue.pop();
		if (Current_Distance != Distance[Current_Vertex])
			continue;
		if (Current_Vertex == Destination)
		{
			Save_Path(Destination);
			return Distance[Destination];
		}
		for (int i = 0; i < Adjacency_List[Current_Vertex].size(); ++i) 
		{
			int New_Vertex = Adjacency_List[Current_Vertex][i].second;
			long double New_Distance = Current_Distance + Adjacency_List[Current_Vertex][i].first;
			if (Distance[New_Vertex] > New_Distance) 
			{
				Path[New_Vertex] = Current_Vertex;
				Distance[New_Vertex] = New_Distance;
				Priority_Queue.push(make_pair(New_Distance, New_Vertex));
			}
		}
	}
	Save_Path(Destination);
	return Distance[Destination];
}

//O(|E|)
long double Dijkstra_Idea_1_2_3(int Source, int Destination)
{
	long double heuristic_cost_estimate;
	Shortest_Path.clear();
	Path=vector<int>(Vertices.size(),-1);
	fill(Distance, Distance + Adjacency_List.size(), infinity);
	heuristic_cost_estimate=Calculate_Distance(make_pair(Vertices[Source].first,Vertices[Source].second),make_pair(Vertices[Destination].first,Vertices[Destination].second));
	Distance[Source] = 0;
	Distance2[Source] = heuristic_cost_estimate;
	priority_queue< pair<long double, int> > Priority_Queue(edges);
	Priority_Queue.push(make_pair(Distance2[Source], Source));
	while (Priority_Queue.size()) 
	{
		int Current_Vertex = Priority_Queue.top().second;
		Priority_Queue.pop();
		if (Current_Vertex == Destination)
		{
			Save_Path(Destination);
			return Distance[Destination];
		}
		for (int i = 0; i < Adjacency_List[Current_Vertex].size(); ++i) 
		{
			int New_Vertex = Adjacency_List[Current_Vertex][i].second;
			long double New_Distance = Distance[Current_Vertex] + Adjacency_List[Current_Vertex][i].first;
			if (Distance[New_Vertex] > New_Distance) 
			{
				Path[New_Vertex] = Current_Vertex;
				Distance[New_Vertex] = New_Distance;
				heuristic_cost_estimate=Calculate_Distance(make_pair(Vertices[New_Vertex].first,Vertices[New_Vertex].second),make_pair(Vertices[Destination].first,Vertices[Destination].second));
				Distance2[New_Vertex] = Distance[New_Vertex]+heuristic_cost_estimate;
				Priority_Queue.push(make_pair(Distance2[New_Vertex], New_Vertex));
			}
		}
	}
	Save_Path(Destination);
	return Distance[Destination];
}