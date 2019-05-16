/**********************************************
* Program:  maze.h                           *
* Author:   Michael Elkins                     *
* Date:                               *
*                                             *
* Abstract: Class for PA4 *
*            *
**********************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
using namespace std;


class Maze{
	public:
		Maze();
			//see below
		bool OpenAndLoad(char * filename);
			//see below
		void DisplayMaze();
			//see below
		void solve();
			//see below
		
	private:
		int rows;			// number of rows in the maze
		int columns;		//number of columns in the maze
		char * maze;		//pointer to where maze is stored
		int mrow;			//row where mouse is
		int mcol;			//column where mouse is
		char mdir;			//direction mouse is facing
		void Usolve();
			//see below
		void Dsolve();
			//see below
		void Lsolve();
			//see below
		void Rsolve();
			//see below
};


 Maze::Maze() {
	//Intent: Constructor
	//pre: none
	//Post: variables are initialized to zero
	
	rows = 0;
	columns = 0;
	maze = 0;
}


bool Maze::OpenAndLoad(char * filename){
	//Intent: Open file given by user and store in maze pointer
	//Pre:filename is the name of the file being opened
	//Post:return false if file fails to open and both stores file in character pointer
	//and returns true if file opens properly
	
	//Open
	
	ifstream inFile(filename);
	
	if(!inFile){
		
		return false;
	}
	
	//Load
	
	inFile >> rows;
	inFile >> columns;
	
	maze = new char[rows * columns];
	for(int i = 0; i < rows; i++){
		for(int n = 0; n < columns; n++){
			inFile >> *(maze + i * columns + n);
		}
				
	}
	
	return true;
}


void Maze::DisplayMaze(){
	//Intent: Prints out maze stored in char pointer
	//Pre: None(Open and Load should have been called to store maze already)
	//Post:Maze prints out 
	
	for(int i = 0; i < rows; i++){
		for(int n = 0; n < columns; n++){
			cout << setw(2) << *(maze + i * columns + n);
		}
		cout << endl;
		
	}
	sleep(1);
	cout << endl;
}



void Maze::solve(){
	//To place mouse and begin chain of calling solve methods to solve maze
	//Pre:OpenAndLoad needs to have been called
	//Post:mouse is at facing exit of maze
	cout << "Enter the row (1 - " << rows << ")"
	"and column (1 - " << columns << ") where the mouse is located: "<< endl;
 
	cin >> mrow;
	cin >> mcol;
	
	
	//Check if valid entries
	while(cin.fail() || cin.peek() != '\n'){
		cerr << "You did not enter two integers." << endl;
		cout << "Enter the row (1 - " << rows << ")"
	"and column (1 - " << columns << ") where the mouse is located: "<< endl;
		cin.clear();
		cin.ignore(80,'\n');
		cin >> mrow;
		cin >> mcol;
		
	}
	
	while(mrow < 1 || mrow > rows || mcol < 1 || mcol >> columns || *(maze + (mrow - 1) * columns + (mcol - 1)) == '#' ){
		cout << "Enter the row (1 - " << rows << ")"
	"and column (1 - " << columns << ") where the mouse is located: "<< endl;
		cin.clear();
		cin.ignore(80,'\n');
		cin >> mrow;
		cin >> mcol;
		
	}
	
	//adjusting mouse position to match maze pointer dimensions
	mrow = mrow - 1;
	mcol = mcol - 1;
	
	cout << "What direction should the mouse be facing? (U,D,L,R)" << endl;
	cin >> mdir;
	
	//checking direction entered
	while(cin.peek() != '\n' || (mdir != 'U' && mdir != 'D' && mdir != 'L' && mdir != 'R')){
		cout << "What direction should the mouse be facing? (Entry must be one of U,D,L,R)" << mdir << endl;
		cin.clear();
		cin.ignore(80,'\n');
		cin >> mdir;
		
	}
	//begin solving maze by following wall on right side
	if (mdir == 'U' ){
		*(maze + mrow * columns + mcol) = '^';
		DisplayMaze();
		Usolve();
	}
	
	if (mdir == 'D'){
		*(maze + mrow  * columns + mcol) ='V';
		DisplayMaze();
		Dsolve();
	}
	
	if (mdir == 'L'){
		*(maze + mrow * columns + mcol) = '<';	
		DisplayMaze();
		Lsolve();
	}
	
	if (mdir == 'R'){
		*(maze + mrow  * columns + mcol) = '>';	
		DisplayMaze();
		Rsolve();
	}
	
	
}

void Maze::Usolve(){
	//Intent: Handle all possible mouse movements when the mouse is pointing up
	//Pre:Maze should be loaded and mouse should be facing up
	//Post: Mouse makes next move and calls the method for the correct direction
	//If facing exit nothing should be done
	
	//kicks out of loop when facing exit
	//pick mouse up
	*(maze + mrow  * columns + mcol) = '.';
	
	//Exit Condition
	if((mrow == 0 && mdir == 'U') || (mrow == rows - 1 && mdir == 'D') || (mcol == 0 && mdir == 'L') || (mcol == columns - 1 && mdir == 'R')){
		mdir = 'x';
	}
	
	while(mdir != 'x'){
		//open space to the right
		if( *(maze + mrow * columns + mcol + 1) == '.'){
			mcol = mcol + 1;
			mdir = 'R';
			*(maze + mrow  * columns + mcol) ='>';
			DisplayMaze();
			Rsolve();
			break;
		}
		//corner to right
		if((*(maze + (mrow - 1) * columns + mcol + 1) == '.') && (*(maze + (mrow - 1) * columns + mcol) == '.') ){
			mcol = mcol + 1;
			mrow = mrow - 1;
			mdir = 'R';
			*(maze + mrow  * columns + mcol) = '>';
			DisplayMaze();
			Rsolve();
			break;
		}
		//straight
		if(*(maze + (mrow - 1) * columns + mcol) == '.'){
			mrow = mrow - 1;
			*(maze + mrow  * columns + mcol) = '^';
			DisplayMaze();
			Usolve();
			break;
		}
		//turn left
		if(*(maze + (mrow - 1) * columns + mcol) == '#'){
			mdir = 'L';
			*(maze + mrow  * columns + mcol) = '<';
			DisplayMaze();
			Lsolve();
			break;
		}
	}
	
}

void Maze::Rsolve(){
	//Intent:Handle all possibilities if mouse is facing right
	//Pre:Maze loaded and mouse facing right
	//Post:Mouse makes proper move of if facing exit does nothing
	
	
	//kicks out of loop when facing exit
	//pick mouse up
	*(maze + mrow  * columns + mcol) = '.';
	
	//Exit Condition
	if((mrow == 0 && mdir == 'U') || (mrow == rows - 1 && mdir == 'D') || (mcol == 0 && mdir == 'L') || (mcol == columns - 1 && mdir == 'R')){
		mdir = 'x';
	}
	
	while(mdir != 'x'){
		//open space to the right
		if( *(maze + (mrow + 1) * columns + mcol) == '.'){
			mrow = mrow + 1;
			mdir = 'D';
			*(maze + mrow  * columns + mcol) ='V';
			DisplayMaze();
			Dsolve();
			break;
		}
		//corner to right
		if((*(maze + (mrow + 1) * columns + mcol + 1) == '.') && (*(maze + (mrow) * columns + mcol +1) == '.')){
			mcol = mcol + 1;
			mrow = mrow + 1;
			mdir = 'D';
			*(maze + mrow  * columns + mcol) = 'V';
			DisplayMaze();
			Dsolve();
			break;
		}
		//straight
		if(*(maze + (mrow) * columns + mcol +1) == '.'){
			mcol = mcol + 1;
			*(maze + mrow  * columns + mcol) = '>';
			DisplayMaze();
			Rsolve();
			break;
		}
		//turn left
		if(*(maze + (mrow) * columns + mcol + 1) == '#'){
			mdir = 'U';
			*(maze + mrow  * columns + mcol) = '^';
			DisplayMaze();
			Usolve();
			break;
		}
	}
	
}

void Maze::Dsolve(){
	//Intent:Handle all possibilities if mouse is pointing down
	//Pre:Maze is loaded and mouse is pointed down
	//Post:Mouse makes proper move or does nothing if mouse facing exit
	
	//kicks out of loop when facing exit
	//pick mouse up
	*(maze + mrow  * columns + mcol) = '.';
	
	//Exit Condition
	if((mrow == 0 && mdir == 'U') || (mrow == rows - 1 && mdir == 'D') || (mcol == 0 && mdir == 'L') || (mcol == columns - 1 && mdir == 'R')){
		mdir = 'x';
	}
	
	while(mdir != 'x'){
		//open space to the right
		if( *(maze + mrow * columns + mcol - 1) == '.'){
			mcol = mcol - 1;
			mdir = 'L';
			*(maze + mrow  * columns + mcol) ='<';
			DisplayMaze();
			Lsolve();
			break;
		}
		//corner to right
		if((*(maze + (mrow + 1) * columns + mcol - 1) == '.') && (*(maze + (mrow + 1) * columns + mcol) == '.')){
			mcol = mcol - 1;
			mrow = mrow + 1;
			mdir = 'L';
			*(maze + mrow  * columns + mcol) = '<';
			DisplayMaze();
			Lsolve();
			break;
		}
		//straight
		if(*(maze + (mrow + 1) * columns + mcol) == '.'){
			mrow = mrow + 1;
			*(maze + mrow  * columns + mcol) = 'V';
			DisplayMaze();
			Dsolve();
			break;
		}
		//turn left
		if(*(maze + (mrow + 1) * columns + mcol) == '#'){
			mdir = 'R';
			*(maze + mrow  * columns + mcol) = '>';
			DisplayMaze();
			Rsolve();
			break;
		}
	}
}

void Maze::Lsolve(){
	//Intent:Handle all possibilities if mouse is pointed left
	//Pre:Maze is loaded and mouse is pointed left
	//Post:Mouse makes proper move or does nothing if mouse is facing exit
	
	//kicks out of loop when facing exit
	//pick mouse up
	*(maze + mrow  * columns + mcol) = '.';
	//Exit Condition
	if((mrow == 0 && mdir == 'U') || (mrow == rows - 1 && mdir == 'D') || (mcol == 0 && mdir == 'L') || (mcol == columns - 1 && mdir == 'R')){
		mdir = 'x';
	}
	
	while(mdir != 'x'){
		//open space to the right
		if( *(maze + (mrow - 1) * columns + mcol) == '.'){
			mrow = mrow - 1;
			mdir = 'U';
			*(maze + mrow  * columns + mcol) ='^';
			DisplayMaze();
			Dsolve();
			break;
		}
		//corner to right
		if(((*(maze + (mrow - 1) * columns + mcol - 1) == '.')) && (*(maze + mrow * columns + mcol - 1) == '.')){
			mcol = mcol - 1;
			mrow = mrow - 1;
			mdir = 'U';
			*(maze + mrow  * columns + mcol) = '^';
			DisplayMaze();
			Usolve();
			break;
		}
		//straight
		if(*(maze + mrow * columns + mcol - 1) == '.'){
			mcol = mcol - 1;
			*(maze + mrow  * columns + mcol) = '<';
			DisplayMaze();
			Lsolve();
			break;
		}
		//turn left
		if(*(maze + mrow * columns + mcol - 1) == '#'){
			mdir = 'D';
			*(maze + mrow  * columns + mcol) = 'V';
			DisplayMaze();
			Dsolve();
			break;
		}
	
	}
	
}
