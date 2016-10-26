/*
Jason Domican		X00119321
Robert Fitzgerald	X00123156

ADS1 Practical 1
*/

#include <cstdlib>
#include <string>
#include <fstream>
#include <Windows.h>
#include "dirent.h"

#include "similarity_index.h"
using namespace std;

int main()
{

	DIR *pdir = NULL; // struct in dirent.h (Line 256)
	struct dirent *pent = NULL;

	//char *directory = NULL;
	//directory = "./files";

	pdir = opendir("./files"); //files folder INSIDE current directory

	if (pdir == NULL)
	{
		cout << "pdir not initialised correctly";
		exit(1);
	}

	cout << "LISTING DIRECTORY CONTENTS\n";
	while (pent = readdir(pdir)) //while something left to list
	{
		if (pent == NULL)
		{
			cout << "pent not initialised correctly";
			exit(1);
		}

		
		cout << pent->d_name << endl;
	}

	closedir(pdir);

	/*
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
	*/

	system("pause");
	return 0;
}
