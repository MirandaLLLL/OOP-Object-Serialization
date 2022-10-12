#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<cstring>
#include<vector>

using namespace std;

class Diary
{
public:
	string date;   //the date of the diary
	vector<string> content;//the exact content of diary
	int num_lines;// the numbers of lines in the diary

public:
	void AddContent(string line) {//add the line into the diary's content
		content.push_back(line);
	}
	friend bool operator==(Diary a, Diary b);//reconstruct the operator"=="
};
bool operator==(Diary a, Diary b) {//reconstruct the operator"=="
	if ((a.date == b.date) && (a.content == b.content) && (a.num_lines = b.num_lines)) {
		return true;
	}
	else
		return false;
}

Diary serialize(Diary p, string s) {  //the function can serialize;p is the input Diary,s is the name of file;
	ofstream fout(s, ios_base::out | ios_base::binary);//open the file as the binary form

	fout.write((char*)&p.num_lines, sizeof(int));//put the p.numlines into the file as the binary form

	size_t len = p.date.size();//get the size of p.date

	fout.write((char*)&len, sizeof size_t); // put the size of p.date into file as binary form
	fout.write(p.date.c_str(), len + 1);  //put the content of p.date  into file as binary form

	int i;
	size_t length;
	for (i = 0; i < p.num_lines; i++) {//put  each line of the vector into file as binary
		length = p.content.at(i).size();//get the size of each line of  p.content;
		fout.write((char*)&length, sizeof size_t);//put the size of each line of p.content
		fout.write(p.content.at(i).c_str(), length + 1);//put the content of each line of p.content
	}

	fout.close();//close the file 
	return p;
}

Diary deserialize(Diary p, string s) {//the function can deserialize p, and output p ,s is the name of file;
	char ch;
	ifstream fin(s, ios_base::in | ios_base::binary);//open the file as the binary form
	size_t len;
	fin.read((char*)&p.num_lines, sizeof size_t);//read the original obeject.num_lines's binary form in the file and return it to p.num_lines 

	fin.read((char*)&len, sizeof size_t);   //read the length of original object.date  
	int i;
	for (i = 0; i < len; i++) {      //read the next "length" bytes one by one ,then put it into p.date;
		fin.read((char*)&ch, 1);
		p.date += ch;
	}

	string getline[100];
	char kongge;
	int j;
	size_t length;
	for (i = 0; i < p.num_lines; i++) {
		fin.read((char*)&kongge, sizeof(char));//read the length of each line of original object.content; 
		fin.read((char*)&length, sizeof size_t);// read the length of each line of original object.date
		for (j = 0; j < length; j++) {          //read the next "length" bytes one by one ,then put it into p.content[i];
			fin.read((char*)&ch, sizeof(char));
			getline[i] += ch;
		}
		p.content.push_back(getline[i]);//put each line into p.content
	}
	fin.close();//close the file
	return p;
}



