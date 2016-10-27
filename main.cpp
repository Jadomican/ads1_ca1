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

#include "similarity_index.h"
using namespace std;

int main()
{
	/*
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

	*/
	//string directory;

	cout << "**Plagiarism Detector**\n\n";
	//cout << "Enter the directory to be scanned: ";
	//cin >> directory;

	
	//USES windows.h RATHER THAN DIRENT!!

	const int NUM_FILES = 4;	//number of files to be processed

	SimilarityIndex array_of_indexes[NUM_FILES]; //	NOT YET USED

/***************************************************************************************
*    Usage: based on
*    Title: How do you make an array of structs in C?
*    Date:  27/10/2016
*    Availability: http://stackoverflow.com/questions/10468128/how-do-you-make-an-array-of-structs-in-c
***************************************************************************************/

	array_of_indexes[0].count_iterative = 1;
	array_of_indexes[0].count_selective = 1; //	USE TO COUNT MATCHES OF ITERATIVE AND SELECTIVE


	for (int i = 0; i < NUM_FILES; i++)
	{
		int test = 0;
		stringstream file_path;
		file_path << "./files/file" << i+1 << ".cpp";

		ifstream inFile;		//reading in
		inFile.open(file_path.str()); //pass in file_path as string

		//have while here to read entire file?
			inFile >> test;


		cout << file_path.str() << ": " << test << "\n\n";

		inFile.close(); //remember to close file

	}

	//ofstream outfile; //don't need to write to file? Get rid of it?
	//outfile.open(directory, ios::app);
	//outfile.close();
	
	system("pause");
	return 0;
}
