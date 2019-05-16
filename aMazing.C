/**********************************************
* Program:  aMAzing.C                           *
* Author:Michael Elkins                        *
* Date:                               *
*                                             *
* Abstract:driver for maze.h  *
*            *
**********************************************/
#include <iostream>
#include "maze.h"
#include <cstring>
#include <unistd.h>


using namespace std;

int main(int argc, char * argv[]) {
	
	char filename[30];
	char answer;
	//Prepared for command line argument but asks for file from user if no argument found
	if(argc == 1 ){
		cout << "Enter a file name" << endl;
		cin >> filename;
		
	}
	else
		strcpy(filename,argv[1]);
	Maze MAZE;
	
	
	
	if(MAZE.OpenAndLoad(filename)){
		
		MAZE.DisplayMaze();
		
	}
	else{
		cerr << "File not found" << endl;
		return 0;
	}
	
	
	
	MAZE.solve();
	
	//option to keep dropping mice into maze
	
	cout << "Would you like to drop another mouse? (y,n)" << endl;
	cin >> answer;
	
	while(answer == 'y'){
		MAZE.solve();
		cout << "Would you like to drop another mouse? (y,n)" << endl;
		cin >> answer;
	}
	
	
	
	return 0;
}

