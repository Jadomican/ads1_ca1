/*
Jason Domican		X00119321
Robert Fitzgerald	X00123156

ADS1 Practical 1
*/

#include <cstdlib>
#include <string>
#include <fstream>
#include <Windows.h>
#include <sstream>
#include <vector>
#include "dirent.h"
#include "similarity_index.h"
using namespace std;

int main()
{
	const int NUM_FILES = 4;	//number of files to be processed
	SimilarityIndex array_of_indexes[NUM_FILES]; //SHOULD WE INCLUDE A STRING (file_name) VARIABLE INSIDE THE STRUCT?

	string directory;
	cout << "**Plagiarism Detector**";
	cout << "Input directory to be scanned: (HINT: Try ./files/)" << endl;
	cin >> directory;

	while (directory.back() != '/')
	{
		cout << "Please include a '/' at the end of your directory\n";
		cin >> directory;
	}

	vector<string> file_names = vector<string>();

	DIR *pdir = NULL; // struct in dirent.h (Line 256)
	struct dirent *pent = NULL;

	//cout << directory.back();

	/***************************************************************************************
	*    Usage: modified
	*    Title: Converting String to Cstring in c++
	*    Date: 30/10/2016
	*    Availability: http://stackoverflow.com/questions/11821491/converting-string-to-cstring-in-c
	***************************************************************************************/

	pdir = opendir(directory.c_str()); //files folder INSIDE current directory

	if (pdir == NULL)
	{
		cout << "\npdir not initialised correctly\n";
		system("pause");
		exit(1);
	}

	cout << "LISTING DIRECTORY CONTENTS\n";
	//for (int i = 0; i < NUM_FILES +2; i++) //MAX 4 FILES
	//{
	//	pent = readdir(pdir);
	//	if (pent == NULL)
	//	{
	//		cout << "pent not initialised correctly";
	//		exit(1);
	//	}
	//
	//	file_names.push_back(string(pent->d_name));
	//}

	while (pent = readdir(pdir)) //while something left to list ANY NUMBER OF FILES
	{
		if (pent == NULL)
		{
			cout << "pent not initialised correctly";
			exit(1);
		}

		if (string(pent->d_name) == "." || string(pent->d_name) == "..") //do not include root and parent directory
		{
			//do nothing
		}
		else
		{
			file_names.push_back(string(pent->d_name));
		}

	}

	for (int i = 0; i < NUM_FILES; i++)
	{
		cout << file_names[i] << endl;
		//cout << file_names_strings[i] << endl;
	}

	closedir(pdir); //close the directory when done reading

	/***************************************************************************************
	*    Usage: based on
	*    Title: How do you make an array of structs in C?
	*    Date:  27/10/2016
	*    Availability: http://stackoverflow.com/questions/10468128/how-do-you-make-an-array-of-structs-in-c
	***************************************************************************************/

	for (int i = 0; i < NUM_FILES; i++)
	{
		string string_in; //reads only a SINGLE string in at a time
		stringstream file_path;
		file_path << directory << file_names[i]; //ignore . AND .. in file listing

		ifstream inFile;		//reading in
		inFile.open(file_path.str()); //pass in file_path as string

		cout << "\n\n" << file_path.str() << " \n";
		while (!inFile.eof()) {

			inFile >> string_in;

			//check if contains selective/iterative
			if (string_in == "int")
			{
				array_of_indexes[i].count_iterative++;
			}

			cout << string_in;

		}

		inFile.close(); //remember to close file

		cout << "\nFILE CONTAINS: " << array_of_indexes[i].count_iterative << " ITERATIVE STATEMENTS\n";

	}

	cout << endl;
	system("pause");
	return 0;
}


//http://www.cplusplus.com/reference/string/string/back/
