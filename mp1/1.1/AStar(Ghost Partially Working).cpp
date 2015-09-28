#include <iostream>
#include <iomanip>
#include <math.h>
#include <ctime>
#include <string>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;
int w,h=0;
int endx,endy;
int startx, starty=0;
int Ghostx,Ghosty;
int smallx=-1,bigx=-1;
int Gdirection=1;//1: move right   -1: move left

const int IDIM = 38; // horizontal size of the squares
const int JDIM = 38; // vertical size size of the squares
const int NDIR = 4; // number of possible directions to go at any position

// if NDIR = 4
const int iDir[NDIR] = {1, 0, -1, 0};
const int jDir[NDIR] = {0, 1, 0, -1};
//const int iDir[NDIR] = {0, -1, 0, 1};
//const int jDir[NDIR] = {1, 0, -1, 0};
int cost = 0;
int numNodes = 0;
// if NDIR = 8
//const int iDir[NDIR] = {1, 1, 0, -1, -1, -1, 0, 1};
//const int jDir[NDIR] = {0, 1, 1, 1, 0, -1, -1, -1};

// int squares[IDIM][JDIM];
int Maze[IDIM][JDIM];

// list of closed (check-out) nodes
int closedNodes[IDIM][JDIM];

// list of open (not-yet-checked-out) nodes
int openNodes[IDIM][JDIM];

// map of directions (0: East, 1: North, 2: West, 3: South) 
int dirMap[IDIM][JDIM];

struct Location
{
    int row, col;

    Location()
    {
        row = col = 0;
    };

    Location(int r, int c)
    {
        row = r;
        col = c;
    };
};

class Node
{
    // current position
    int rPos;
    int cPos;

    // total distance already travelled to reach the node
    int GValue;

    // FValue = GValue + remaining distance estimate
    int FValue;  // smaller FValue gets priority

    public:
        Node(const Location &loc, int g, int f) 
            {rPos = loc.row; cPos = loc.col; GValue = g; FValue = f;}
    
		Location getLocation() const {return Location(rPos,cPos);}
        int getGValue() const {return GValue;}
        int getFValue() const {return FValue;}

        void calculateFValue(const Location& locDest)
        {
             FValue = GValue + getHValue(locDest); 
        }
        void setFValue(int f){
        	FValue=f;
        }

        void setGValue(int g){
        	GValue=g;
        }
        
        void updateGValue(const int & i, int prev) // i: direction
        {
            /*if(prev==i){
                //didn't change direction
            }
            else if(abs(prev-i)==2){
                //turn 180 degree
                GValue += 2;
            }
            else{
                //turn 90 degree
                GValue += 1
            }*/
            GValue += 1;//forward cost2
        }
        
        // Estimation function for the remaining distance to the goal.
        const int & getHValue(const Location& locDest) const
        {
            static int rd, cd, d;
            rd = locDest.row - rPos;
            cd = locDest.col - cPos;         

            // Euclidian Distance
            // d = static_cast<int>(sqrt((double)(rd*rd+cd*cd)));

            // Manhattan distance
            d = abs(rd) + abs(cd);
            
            // Chebyshev distance
            //d = max(abs(rd), abs(cd));

            return(d);
        }

	// Determine FValue (in the priority queue)
	friend bool operator<(const Node & a, const Node & b)
	{
	    return a.getFValue() > b.getFValue();
	}
};

void moveGhost(){
    //int ngx = Ghostx+Gdirection;
    //Maze[Ghosty][Ghostx]=0;
    if(Maze[Ghosty][Ghostx+Gdirection]==1){
        //wall
        Gdirection=-Gdirection;
    }
     Ghostx+=Gdirection;
}

bool touchGhost(int row, int col, int nexti, int nextj){
    if(nexti==Ghostx&&nextj==Ghosty){
        cout<<"Touch Ghost!!!!!!!!!!!!!!!!!"<<endl;
        return true;
    }
    //cross
    int prevx=Ghostx;
    if(Maze[Ghosty][Ghostx-Gdirection]==1){
        prevx+=Gdirection;
    }
    else{
        prevx-=Gdirection;
    }
    if((Ghostx==row&&Ghosty==col)&&nexti==prevx&&nextj==Ghosty){
     cout<<"Corss Ghost!!!!!!!!!!!!!!!!!"<<endl;
        return true;
    }
    return false;

}
// A-star algorithm.
// The path returned is a string of direction digits.
string pathFind( const Location &locStart , 
                 const Location &locFinish )
				
{
    // list of open (not-yet-checked-out) nodes
    static priority_queue<Node> q[2]; 

    // q index
    static int qi; 

    static Node* pNode1;
    static Node* pNode2;
    static int i, j, row, col, iNext, jNext;
    static char c;
    qi = 0;

    // reset the Node lists (0 = ".")
    for(j = 0; j < JDIM; j++) {
        for(i = 0; i < IDIM; i++) {
            closedNodes[i][j] = 0;
            openNodes[i][j] = 0;
        }
    }

    // create the start node and push into list of open nodes
    pNode1 = new Node(locStart, 0, 0); 
    pNode1->calculateFValue(locFinish);
    q[qi].push(*pNode1);
    moveGhost();
    //Maze[Ghosty][Ghostx]=9;
    // A* search
    while(!q[qi].empty()) {

        

        // get the current node w/ the lowest FValue
        // from the list of open nodes
        pNode1 = new Node( q[qi].top().getLocation(), 
                     q[qi].top().getGValue(), q[qi].top().getFValue());

        row = (pNode1->getLocation()).row; 
		col = pNode1->getLocation().col;


        // stop searching when the goal state is reached
        if(row == locFinish.row && col == locFinish.col) {
		// drawing direction map



	    // generate the path from finish to start from dirMap
        
            string path = "";
            while(!(row == locStart.row && col == locStart.col)) {
                j = dirMap[col][row];
                c = '0' + (j + 2) % 4;
                path = c + path;
                Maze[col][row] = 2;
                row += iDir[j];
                col += jDir[j];
                cost++;
            }
            //cout<<"cost: "<<cost<<endl;
            // garbage collection
            delete pNode1;

            // empty the leftover nodes
            while(!q[qi].empty()) q[qi].pop();  
             cout<<"path : "<<path<<endl;         
            return path;
        }

            // remove the node from the open list
        q[qi].pop(); 
        openNodes[col][row] = 0;
        numNodes++;

        // mark it on the closed nodes list
        closedNodes[col][row] = 1;
//moveGhost();
        // generate moves in all possible directions
        for(i = 0; i < NDIR; i++) {
            iNext = row + iDir[i]; 
	        jNext = col + jDir[i];


	        pNode2 = new Node( Location(iNext, jNext), pNode1->getGValue(), pNode1->getFValue());
            int prevdirection = (dirMap[col][row]+ 2) % 4;
            pNode2->updateGValue(i,prevdirection);   
	    // if not wall (obstacle) nor in the closed list
            if(!(iNext < 0 || iNext > IDIM - 1 || jNext < 0 || jNext > JDIM - 1 || 
			Maze[jNext][iNext] == 1 || closedNodes[jNext][iNext] == 1) ) 
			{
   				pNode2->calculateFValue(locFinish);


                // if it is not in the open list then add into that
                bool fail = touchGhost(row,col,iNext,jNext);
                if(fail)pNode2->setGValue(100000);


		// generate a child node
                
                if(openNodes[jNext][iNext] == 0 || (pNode1->getGValue()+1<pNode2->getGValue())) {
                    openNodes[jNext][iNext] = pNode2->getFValue();
                    pNode2->updateGValue(i,prevdirection); 
                    q[qi].push(*pNode2);
                    
                    //Maze[Ghosty][Ghostx]=9;
                   // cout<<"Ghost x, y:"<<Ghostx<<", "<<Ghosty<<endl;


                    // mark its parent node direction
                    dirMap[jNext][iNext] = (i + 2) % 4;
                    if(openNodes[jNext][iNext]==0){
                    	openNodes[jNext][iNext]=1;
                    }
                }
/*
		// already in the open list
                else if(openNodes[jNext][iNext] > pNode2->getFValue()&&(!fail)) {
                    // update the FValue info
                    openNodes[jNext][iNext] = pNode2->getFValue();
                     moveGhost();
                    Maze[Ghosty][Ghostx]=9;
                    cout<<"Ghost x, y:"<<Ghostx<<", "<<Ghosty<<endl;
                    // update the parent direction info,  mark its parent node direction
                    dirMap[jNext][iNext] = (i + NDIR/2) % NDIR;

                    // replace the node by emptying one q to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(q[qi].top().getLocation().row == iNext && 
                        q[qi].top().getLocation().col == jNext)) {                
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();       
                    }

		    // remove the wanted node
                    q[qi].pop(); 

         //           moveGhost();
       // Maze[Ghosty][Ghostx]=9;
                    // empty the larger size q to the smaller one
                    if(q[qi].size() > q[1 - qi].size()) qi = 1 - qi;
                    while(!q[qi].empty()) {                
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();       
                    }
                    qi = 1 - qi;

		    // add the better node instead
                    q[qi].push(*pNode2); 
                }*/
               // else delete pNode2;            
            }
        }
        //delete pNode1; 
    }
    // no path found
    return ""; 
}

void MazeReader(char* filename) {


/*
 *Maze Reader starts here:
 read file and put it in maze array
*/

 /*
        0: Empty
        1: Wall
        2: Dot
        3: Goal
    */
    ifstream myReadFile;
    myReadFile.open(filename);
    string s;

    while(!myReadFile.eof()) // To get you all the lines.
    {
            getline(myReadFile,s); // Saves the line in STRING.
            if(h==0)w=s.length();
            for(int i=0;i<s.length();i++){
                if(s.at(i)=='%'){
                    //wall
                    Maze[h][i]=1;
                }
                else if(s.at(i)=='.'){
                    startx=i;
                    starty=h;
                    Maze[h][i]=2;
                }else if(s.at(i)==' '||s.at(i)=='p'){
                    //empty
                    Maze[h][i]=0;
                }else if(s.at(i)=='P'){
                    Maze[h][i]=3;
                    endx=i;
                    endy=h;
                }else if(s.at(i)=='G'||s.at(i)=='g'){
                	if(smallx==-1){
                		smallx=i;
                		bigx=i;
                	}else{
                		smallx = i<smallx?i:smallx;
                		bigx=i>bigx?i:bigx;
                	}
                	if(s.at(i)=='G'){
	                    Ghostx=i;
	                    Ghosty=h;
                	}
                    Maze[h][i]=0;
                }

            }
            h++;
    }
    myReadFile.close();
    cout<<"w: "<<w<<endl;
    cout<<"h: "<<h<<endl;

    cout<<"Ghost bound: "<<smallx<<", "<<bigx<<endl;
    cout<<"endx: "<<endx<<endl;
    cout<<"endy: "<<endy<<endl;
}

void MazeWriter() {
    ofstream myfile;
    myfile.open ("solution.txt");
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            //if(startx==j&&starty==i)myfile<<".";
            if(Maze[i][j]==1)
                myfile<<"%";
            else if(Maze[i][j]==2)
                myfile<<".";
            else if(Maze[i][j]==0)
                myfile<<" ";
        }
        myfile<<"\n";
    }
    myfile.close();
}


int main(int argc, char const *argv[])
{
    char* filename = (char*)argv[1];

    MazeReader(filename);

    // starting and ending positions
    int iStart = startx,jStart = starty;
	int iEnd = endx,jEnd = endy;

    cout << "Grid Size (IDIM,JDIM): "<< IDIM<< "," << JDIM << endl;
    cout << "Start: " << iStart<<","<< jStart << endl;
    cout << "Finish: " << iEnd<<","<< jEnd << endl;
 
    // clock_t start = clock();

    // get the path
    string path = pathFind(Location(iStart, jStart), Location(iEnd, jEnd));


 cout<< "Number of Nodes expanded: " << numNodes <<endl;
    cout<< "Cost of Path: " << cost << endl;
    MazeWriter();
    return(0);
}