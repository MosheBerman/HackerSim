#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<time.h>
#include<libc.h>

#define MAX_MILLISECONDS_BETWEEN_PRINTS 150
#define MAX_CHARS_TO_READ 10
#define MAX_TRIES 3
#define SCREEN_LINES 50
#define DENY_MIN 42
#define DENY_MAX 100
#define DENY_LEVEL 25

void clear(int numLines){

	for(int i=0;i<numLines;i++){
		std::cout << "\n";
	}

	std::cout << std::endl;
}


void simulatePause(){
	int randomDuration = rand()%MAX_MILLISECONDS_BETWEEN_PRINTS+1;
	usleep(1000*randomDuration);
}

void deny(){

	clear(SCREEN_LINES);

	std::cout << std::endl;

	static int tries = 0;
	
	std::cout << "-------------------------" << "\n";
	std::cout << "-                       -" << "\n";
	std::cout << "-     ACCESS DENIED     -" << "\n";
	std::cout << "-                       -" << "\n";
	std::cout << "-------------------------" << "\n";
	
	if(tries < MAX_TRIES){
		std::cout << "Sign in attempt has been logged. You may try again " << MAX_TRIES - tries << " time(s).\n";
		tries++;	
	}else{
		std::cout << "Maximum tries exceeded. The appropriate authorities have been notified." << "\n";
	}
}


void grant(){

//	clear(SCREEN_LINES);
	
	std::cout << "-------------------------" << "\n";
	std::cout << "-                       -" << "\n";
	std::cout << "-    ACCESS GRANTED     -" << "\n";
	std::cout << "-                       -" << "\n";
	std::cout << "-------------------------" << "\n";
	
	std::cout << "Press any key to continue." << "\n";
}

void printSomeCharsFromFile(std::ifstream& fileStream){

	std::cout.setf(std::ios::unitbuf);

	std::string chars;
	std::string::size_type lengthOfLine = chars.size();
	int pos = 0;

	static int deny_level = 0;

	if(fileStream){				
		getline(fileStream, chars);
		lengthOfLine = chars.size();
		pos = 0;

		while(pos < lengthOfLine){
			simulatePause();
			int randomLength = rand()%lengthOfLine+1;
			randomLength = (randomLength > MAX_CHARS_TO_READ) ?  MAX_CHARS_TO_READ : randomLength;
			std::cout << chars.substr(pos,randomLength);
			pos += randomLength;
		}
		
		std::cout << "\n";
	}

	deny_level++;

	if(deny_level%DENY_LEVEL == 0){	
		int deny_threshhold = rand()%DENY_MAX+1;

		if(deny_threshhold > DENY_MIN){
			deny();
		}
	}
}

void autoPrint(std::ifstream& fileStream){
	while(fileStream){
		printSomeCharsFromFile(fileStream);
	}
}

int main(int argc, char** argv){

	//Instructions are for idiots.
	if(argc < 1){
		std::cout << "Usage: hacker [filename]" << "\n";
		std::cout << "There's no man page, don't bother." << "\n";
		return 1;
	}

	std::string file_path(argv[1] ? argv[1] : "");
	std::string path = file_path;
	std::ifstream inputStream;

	if(file_path == ""){		

		
	std::cout << "-   ENTER A FILE PATH:" << "\n";
		std::cin >> file_path;
	}
	
	std::cout << "ATTEMPTING CLASSIFIED READ..." << "\n";

	inputStream.open(file_path.c_str());

	std::cout << "SEEDING GENERATOR..." <<"\n";
	srand(time(NULL));

	if(!inputStream){
		std::cerr << "There's been a fatal error. That file doesn't exist.\n";
		std::cerr << "First you will be baked. Then there will be cake." << "\n";
		return 3;
	}

	for(int i=0;i<1000;i++){
		std::cout << "\n";
	}

	autoPrint(inputStream);
	inputStream.close();

	grant();

	return 0;
}

