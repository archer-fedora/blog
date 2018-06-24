#include <iostream>
#include <vector>

using namespace std;

int MAX = 1000;

int graph[5][5]={
	{MAX,   5, MAX,   5,   7},
	{MAX, MAX,   4, MAX, MAX},
	{MAX, MAX, MAX,   8,   2},
	{MAX, MAX,   8, MAX,   6},
	{MAX,   3, MAX, MAX, MAX},
};

int pathValue(std::vector<int> v)
{
	if (v.empty())
		return 0;
	if (v.size()==1)
	{
		return graph[v[0]][v[0]];
	}
	int sum =0;
	for (int i = 0; i < v.size() - 1; ++i)
	{
		sum += graph[v[i]][v[i+1]];
	}
	return sum;
}
std::vector<std::vector<int> > g_allPath;
std::vector<int> path;
bool visit[5][5]={false};
int depth = 1000;
void dfs(int begin, int end,int dep = 0)
{

	visit[begin][begin] = true;

	for (int i = 0; i < 5; ++i)
	{

		path.push_back(begin);
		if (i == end && graph[begin][i] != MAX)
		{
			
			path.push_back(i);
			g_allPath.push_back(path);
			path.pop_back();
			if (dep > depth)
			{
				cout<<"end"<<endl;
				return;
			}

		}
		if (graph[begin][i] != MAX && (path.size()<=8) )
		{
			//if (visit[begin][i] == false )
			{
				cout<<"i"<<i<<endl;
				cout<<"path value :"<<pathValue(path)<<endl;
				dfs(i,end,dep+1);
				visit[begin][i] == true;
			}
			
				
		}

		path.pop_back();
		
	}

	visit[begin][end] = true;


	
	
}

int main(int argc, char const *argv[])
{
	/* code */
	dfs(2,2,0);
	int sum = 0;
	for (int i = 0; i < g_allPath.size(); ++i)
	{
		if ( pathValue(g_allPath[i]) >= 30)
		{
			continue;
		}

		cout<<"path"<<i<<":"<< pathValue(g_allPath[i])<<endl;
		for(int j = 0; j< g_allPath[i].size();j++)
		{
			cout<<g_allPath[i][j]<<" ";
		}
		cout<<endl;
		sum++;
	}
	cout<<"all path num is: "<<sum<<endl;
	return 0;
}
