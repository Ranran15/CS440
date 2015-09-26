#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;
int w,h=0;
int endx,endy;

struct PairComparator {
	bool operator()(pair<int,int> n1,pair<int,int> n2) {
	        //return n1.second>n2.second;
			return ((endx-n1.first)*(endx-n1.first)+(endy-n1.second)*(endy-n1.second))>((endx-n2.first)*(endx-n2.first)+(endy-n2.second)*(endy-n2.second));
	    }
};

int DFS(int ** maze, int startx, int starty, int endx, int endy){

}

int BFS(int ** maze, int startx, int starty, int endx, int endy) {

}

int valid(int x, int y, int ** maze){
	// if wall(1) return 0
	// if visited(2) return 0
	// if out of bound return 0;
	// if unvisited(0) return 1
	// if it's goal(3) return 2

	if(x<0||y<0||x>=w||y>=h)return 0;

	int status = maze[y][x];
	if(status==1||status==2)return 0;
	else if(status==0) return 1;
	return 2;
}

int d(int x, int y, int endx, int endy){
	
	return (endx-x)*(endx-x)+(endy-y)*(endy-y);
}


struct sort_pred {
    bool operator()(const std::pair< pair<int,int>,int> &left, const std::pair< pair<int,int>,int> &right) {
        return left.second > right.second;
    }
};

int Greedy(int ** maze, int startx, int starty) {
	int x = startx;
	int y = starty;

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			cout<<maze[i][j];
		}
		cout<<""<<endl;
	}
	

	pair<int,int>**parent = new pair<int,int>*[38];
	for(int i = 0; i < 38; ++i)
	    parent[i] = new pair<int,int>[38];

	pair <int,int> p;
	p=make_pair(x,y);
	//pair< pair<int,int>,int> point = make_pair(p,-1);

	priority_queue< pair<int,int>,vector<pair<int,int> >,PairComparator> q;

	q.push(p);
	cout<<"start: "<<p.first<<", "<<p.second<<endl;
	int cost = 0;
	
	while(!q.empty()){
		//cout<<q.size()<<endl;

		pair<int,int> cur = q.top();
		q.pop();
		cost++;

		
		//visit right, up, left, down
		// if wall, ignore
		// if goal return cost
		// if visited, ignore
		// if not visited, calculate distance, only add the nodes with shortest distance
		pair<int,int> right = make_pair(cur.first+1,cur.second);
		int status = valid(right.first, right.second, maze);
		parent[right.second][right.first]=cur;
		//cout<<parent[right.first][right.second].first<<", "<<parent[right.first][right.second].second<<endl;
		if(status==2) break;
		else if(status==1){
			//unvisited
			//int curdist = d(right.first,right.second,endx,endy);
			//if(dist<0||dist>curdist)dist=curdist;
			cout<<"add: "<<right.first<<", "<<right.second<<endl;
			maze[right.second][right.first]=2;
			q.push(right);
		}


		//up
		pair<int,int> up = make_pair(cur.first,cur.second+1);
		status = valid(up.first, up.second,maze);
		parent[up.second][up.first]=cur;
		//cout<<parent[up.first][up.second].first<<", "<<parent[up.first][up.second].second<<endl;

		if(status==2) break;
		else if(status==1){
			//unvisited
			maze[up.second][up.first]=2;
						q.push(up);
		}

		//left
		pair<int,int> left = make_pair(cur.first-1,cur.second);
		status = valid(left.first,left.second,maze);
		parent[left.second][left.first]=cur;
		//cout<<parent[left.first][left.second].first<<", "<<parent[left.first][left.second].second<<endl;

		if(status==2) break;
		else if(status==1){
			//unvisited
		maze[left.second][left.first]=2;
			q.push(left);
		}

		//down
		pair<int,int> down = make_pair(cur.first,cur.second-1);
		parent[down.second][down.first]=cur;
		status = valid(down.first,down.second,maze);
		//cout<<parent[down.first][down.second].first<<", "<<parent[down.first][down.second].second<<endl;
		if(status==2) break;
		else if(status==1){
			//unvisited
			maze[down.second][down.first]=2;
			
			q.push(down);
		}

	}
	int t1=endx;
	int t2=endy;

	//doesn't work!!!!
	/*while(!(t1==startx&&t2==starty)){
		maze[t2][t1]=5;
		cout<<"back, xy: "<<t1<<" "<<t2<<endl;
		pair<int,int> prev = parent[t2][t1];
		t1=prev.first;
		t2=prev.second;
	}*/

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			cout<<maze[i][j];
		}
		cout<<""<<endl;
	}

	return cost;
	
}


int AStar(int ** maze, int startx, int starty, int endx, int endy) {

}

int** maze_reader(char* filename) {
	//int ** a = 
}

void maze_printer(int ** result) {

}

int main(int argc, char const *argv[])
{
	char* filename = (char*)argv[1];

	ifstream myReadFile;
	myReadFile.open(filename);
	string s;



	int** maze = new int*[38];
	for(int i = 0; i < 38; ++i)
	    maze[i] = new int[38];

	int startx=0;
	int starty=0;
	

	while(!myReadFile.eof()) // To get you all the lines.
    {
	        getline(myReadFile,s); // Saves the line in STRING.
	        if(h==0)w=s.length();
	        for(int i=0;i<s.length();i++){
	        	if(s.at(i)=='%'){
	        		//wall
	        		maze[h][i]=1;
	        	}
	        	else if(s.at(i)=='.'){
	        		startx=i;
	        		starty=h;
	        		maze[h][i]=2;
	        	}else if(s.at(i)==' ' ){
	        		//empty
	        		maze[h][i]=0;
	        	}else if(s.at(i)=='P'||s.at(i)=='p'){
	        		maze[h][i]=3;
	        		endx=i;
	        		endy=h;
	        	}

	        }
	        h++;
    }
	myReadFile.close();
	cout<<"w: "<<w<<endl;
	cout<<"h: "<<h<<endl;

	cout<<"end x: "<<endx<<endl;
	cout<<"endy: "<<endy<<endl;
/*
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			cout<<maze[i][j];
		}
		cout<<""<<endl;
	}*/

	maze_reader(filename);

	int c = Greedy(maze,startx,starty);
	cout<<"cost: "<<c<<endl;
	/*
		0: Empty
		1: Wall
		2: Dot
		3: Goal
	*/
	return 0;
}
