#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ncurses.h>

using namespace std;

class pNumber{
	public:
		string PhoneNumber;
		string Name;
		string SecondName;
};

string getString(){
	char buffer[100];
	getnstr(buffer, 100-1);
	buffer[100-1] = '\0';
	return string(buffer);
}


pNumber insertNumber(string number,string name,string secondname){
	pNumber sample;
	sample.PhoneNumber = number;
	sample.Name = name; 
	sample.SecondName = secondname;
	return sample;
}


pNumber getNumber(){
	pNumber sample;
	printw("Write Number\n");
	sample.PhoneNumber = getString();
	printw("Write Name\n");
	sample.Name = getString(); 
	printw("Write SecondName\n");
	sample.SecondName = getString();
	return sample;
}

string returnNumber(pNumber number){

	string sample = number.PhoneNumber + " " + number.Name + " " + number.SecondName;
	return sample;
}

void dumpTable(vector<pNumber> list){
	if(list.size() ==0){printw("List is empty");return;}
	for(int i=0;i<list.size();i++){
	printw("%s\n",returnNumber(list[i]).c_str());
	}
}

int main(void){

	vector<pNumber> list;
	
	initscr();			/* Start curses mode 		  */

	char c;
	do{
	clear();	

	printw("q - quit  1 - Hello World 2 - add number 3 - list numbers 4 - save to file 5 - read from file\n");
	
	if(c == '1'){
	printw("Hello World");
	}
	if(c == '2'){
	list.push_back(getNumber());
	}
	if(c == '3'){
	dumpTable(list);
	}
	if(c == '4'){
		ofstream MyFile(getString()+".txt");
		for(int i=0;i<list.size();i++){
		MyFile << returnNumber(list[i]) << endl; 
		}
		MyFile.close();
	
	}
	if(c == '5'){
	list.clear();

	ifstream MyFile(getString()+".txt");	

	string buffer;
	vector<string> words;
	while(getline(MyFile,buffer,' ')){
		words.push_back(buffer);	
		if(words.size() == 3){list.push_back(insertNumber(words[0],words[1],words[2])); words.clear();}
	}
	MyFile.close();
	}


	refresh();
	}
	while( (c=getch()) != 'q');
	refresh();			/* Print it on to the real screen */
	endwin();			/* End curses mode		  */
	return 0;

}
