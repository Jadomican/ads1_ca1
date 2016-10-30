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
#include <sstream>
#include <vector>


#include "similarity_index.h"
using namespace std;

int main()
{
	const int NUM_FILES = 4;	//number of files to be processed
	SimilarityIndex array_of_indexes[NUM_FILES]; //	NOT YET USED

	//string file_names_strings[NUM_FILES];

	vector<string> file_names = vector<string>();

	DIR *pdir = NULL; // struct in dirent.h (Line 256)
	struct dirent *pent = NULL;

	pdir = opendir("./files"); //files folder INSIDE current directory

	if (pdir == NULL)
	{
		cout << "pdir not initialised correctly";
		exit(1);
	}

	int index = 0;
	cout << "LISTING DIRECTORY CONTENTS\n";
	while (pent = readdir(pdir)) //while something left to list
	{
		if (pent == NULL)
		{
			cout << "pent not initialised correctly";
			exit(1);
		}

		file_names.push_back(string(pent->d_name));
	}

	for (int i = 0; i < NUM_FILES; i++)
	{
		cout << file_names[i + 2] << endl;
		//cout << file_names_strings[i] << endl;
	}

	closedir(pdir);

	string directory;
	cout << "**Plagiarism Detector**";
	cout << "Input directory to be scanned: (HINT: Try ./files/)" << endl;
	cin >> directory;

	/***************************************************************************************
	*    Usage: based on
	*    Title: How do you make an array of structs in C?
	*    Date:  27/10/2016
	*    Availability: http://stackoverflow.com/questions/10468128/how-do-you-make-an-array-of-structs-in-c
	***************************************************************************************/

	for (int i = 0; i < NUM_FILES; i++)
	{
		string line;
		stringstream file_path;
		file_path << directory << file_names[i + 2];

		ifstream inFile;		//reading in
		inFile.open(file_path.str()); //pass in file_path as string

		cout << "\n\n" << file_path.str() << " \n";
		while (!inFile.eof()) {

			inFile >> line;

			//check if contains selective/iterative
			if (line == "int")
			{
				array_of_indexes[i].count_iterative++;
			}

			cout << line;

		}

		inFile.close(); //remember to close file

		cout << "\nFILE CONTAINS: " << array_of_indexes[i].count_iterative << " ITERATIVE STATEMENTS\n\n";

	}

	cout << endl;
	system("pause");
	return 0;
}
