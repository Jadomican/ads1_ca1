/*
Jason Domican		X00119321
Robert Fitzgerald	X00123156

ADS1 Practical 1
*/

#include <cstdlib>
#include <string>
#include <fstream>
#include <Windows.h>
#include "similarity_index.h"
using namespace std;

int main()
{
	string directory;

	cout << "**Plagiarism Detector**\n";
	cout << "Enter the directory to be scanned: ";
	//cin >> directory;

	//ifstream inFile;		//reading in
	//inFile.open("files/file1.cpp");
	//inFile.close();

	ofstream outfile;
	outfile.open("files/file1.cpp", ios::app);
	outfile.close();


	system("pause");
	return 0;
}
