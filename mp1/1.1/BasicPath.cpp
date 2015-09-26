#include "BasicPath.h"
#include <stack>
#include <queue>
#include <pair>
#include <map>

int Graph::DFS(int startx,int starty int endx, int endy ) {


    //assume the r is the valid node
    std::map<std::pair<int,int>,std::pair<int,int>> track;
    
	std::stack<int> depthx;
	std::stack<int> depthy;
    depthx.push(startx);
    depthy.push(starty);
	auto start =make_pair<startx,starty>;
	track[start]=start;

	while(!depthx.empty() && ! depthy.empty())
	{

		auto footx=depthx.top();
		auto footy=depthy.top();
		depthx.pop();
		depthy.pop();
		auto dot0 =make_pair<footx,footy>
		if(maze[footx][footy]==3)
		{
             //end with the goal, then track back to make the dot;
 			while(track(footx,footy)!=start)
              {
              		auto parent= track(footx,footy);
              		footx=parent.first;
              		footy=parent.second;
              		maze[footx][footy]=2;
              }


		}
		else if(footy-1>=0 && footx!=endx && footy!=endy && maze[footx][footy-1]==0)
		{
			auto dot1=make_pair<footx,footy-1>;//up point
			track[dot1]=dot0;
			depthx.push(footx);
			depthy.push(footy-1);
			maze[footx][footy-1]=4;// shows the point has been covered

		}
		else if(footx+1 <= width && footx!=endx && footy!= endy && maze[footx+1][footy]==0)
		{
			auto dot2=make_pair<footx+1,footy>;//right point
			track[dot2]=dot0;
			depthx.push(footx+1);
			depthy.push(footy);
			maze[footx+1][footy]=4;
		}
		else if(footy+1<=height && footx!=endx && footy!=endy && maze[footx][footy+1]==0)
		{
			auto dot3=make_pair<footx,footy+1>;//down point
			track[dot3]=dot0;
			depthx.push(footx);
			depthy.push(footy+1);
			 maze[footx][footy+1]=4;

		}
		else if(footx-1>=0 && footx!=endx && footy!=endy && maze[footx-1][footy]==0)
		{
			auto dot4=make_pair<footx-1,footy>;//left point
			track[dot4]=dot0;
			depthx.push(footx-1);
			depthy.push(footy);
			maze[footx-1][footy]=4;
		}
	}

     

}

int Graph::BFS(int startx, int starty, int endx, int endy) {
	//assume the node r is a valid node.
	std::map<std::pair<int,int>,std::pair<int,int>> track;// use the map to store the parents of the current pair;
    
	std::queue<int> depthx;//use the queue to store the x
	std::queue<int> depthy;// store the y
    depthx.push(startx);
    depthy.push(starty);
	auto start =make_pair<startx,starty>;// make the start pair
	

	while(!depthx.empty() && ! depthy.empty())
	{

		auto footx=depthx.top();
		auto footy=depthy.top();
		depthx.pop();
		depthy.pop();
		auto dot0 =make_pair<footx,footy>
		if(maze[footx][footy]==3)
		{
             //end with the goal, then track back to make the dot;
 			while(track(footx,footy)!=start)
              {
              		auto parent= track(footx,footy);
              		footx=parent.first;
              		footy=parent.second;
              		maze[footx][footy]=2;
              }


		}
		else if(footy-1>=0 && footx!=endx && footy!=endy && maze[footx][footy-1]==0)
		{
			auto dot1=make_pair<footx,footy-1>;//up point
			track[dot1]=dot0;
			depthx.push(footx);
			depthy.push(footy-1);
			maze[footx][footy-1]=4;// shows the point has been covered

		}
		else if(footx+1 <= width && footx!=endx && footy!= endy && maze[footx+1][footy]==0)
		{
			auto dot2=make_pair<footx+1,footy>;//right point
			track[dot2]=dot0;
			depthx.push(footx+1);
			depthy.push(footy);
			maze[footx+1][footy]=4;
		}
		else if(footy+1<=height && footx!=endx && footy!=endy && maze[footx][footy+1]==0)
		{
			auto dot3=make_pair<footx,footy+1>;//down point
			track[dot3]=dot0;
			depthx.push(footx);
			depthy.push(footy+1);
			 maze[footx][footy+1]=4;

		}
		else if(footx-1>=0 && footx!=endx && footy!=endy && maze[footx-1][footy]==0)
		{
			auto dot4=make_pair<footx-1,footy>;//left point
			track[dot4]=dot0;
			depthx.push(footx-1);
			depthy.push(footy);
			maze[footx-1][footy]=4;
		}
	}

     
}

int Graph::Greedy(node* r) {

}

int Graph::AStar(node* r) {

}

int** maze_reader(char* filename, Graph* G) {

}

void maze_printer(Graph* g) {

}

int main(int argc, char const *argv[])
{
	char* filename = (char*)argv[1];
	Graph* G;
	maze_reader(filename, G);

	return 0;
}










