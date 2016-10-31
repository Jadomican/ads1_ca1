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
	const int MAX_NUM_FILES = 4;						//number of files to be processed
	SimilarityIndex array_of_indexes[MAX_NUM_FILES];	//SHOULD WE INCLUDE A STRING (file_name) VARIABLE INSIDE THE STRUCT?
	vector<string> file_names = vector<string>();	//NOT NECCESSARILY NEEDED
	string directory;
	DIR *pdir = NULL;								// struct in dirent.h (Line 256)
	struct dirent *pent = NULL;
	int count = 0;

	do
	{
		cout << "**Plagiarism Detector**";
		cout << "\nInput directory to be scanned: (HINT: Try ./files/ or files/ ...... type x to exit)" << endl;
		cin >> directory;

		if (directory == "x")
		{
			exit(1);
		}

		if (directory.back() != '/') //last character of string
		{
			directory += '/';
		}


		/***************************************************************************************
		*    Usage: modified
		*    Title: Converting String to Cstring in c++
		*    Date: 30/10/2016
		*    Availability: http://stackoverflow.com/questions/11821491/converting-string-to-cstring-in-c
		***************************************************************************************/

		pdir = opendir(directory.c_str()); //opens specified directory

		if (pdir == NULL)
		{
			cout << "\npdir not initialised correctly\n";
			cout << "\nTRY AGAIN\n";
		}
	} while (pdir == NULL);

	cout << "LISTING DIRECTORY CONTENTS\n";

	//FOR LOOP OR WHILE LOOP?????
	//for (int i = 0; i < NUM_FILES + 2; i++) //IGNORE . AND .. (max 4 files)
	//{
	//	pent = readdir(pdir);
	//	if (pent == NULL)
	//	{
	//		cout << "pent not initialised correctly";
	//		exit(1);
	//	}
	//
	//	if (string(pent->d_name) == "." || string(pent->d_name) == "..") //do not include root and parent directory
	//	{
	//		//do nothing
	//	}
	//	else
	//	{
	//		file_names.push_back(string(pent->d_name));
	//		array_of_indexes[i].file_name = string(pent->d_name);
	//	}
	//}

	while (pent = readdir(pdir)) //while something left to list ANY NUMBER OF FILES
	{
		if (pent == NULL)
		{
			cout << "pent not initialised correctly";
			exit(1);
		}

		if (string(pent->d_name) == "." || string(pent->d_name) == "..") //do not include current and parent directory
		{
			//do nothing
		}
		else
		{
			if (count >= MAX_NUM_FILES)
			{
				cout << "Only first " << MAX_NUM_FILES << " files scanned\n";
			}
			else
			{
				file_names.push_back(string(pent->d_name));
				count++;
			}
		}
	}
	//if (count < NUM_FILES)
	//{
	//	cout << "*** Number of files in the directory must match NUM_FILES constant ***";
	//	system("pause");
	//	exit(1);
	//}

	for (int i = 0; i < count; i++)
	{
		cout << file_names[i] << endl;
		array_of_indexes[i].file_name = file_names[i]; //COPY FILE NAMES INTO struct
	}

	closedir(pdir); //close the directory when done reading

/***************************************************************************************
*    Usage: based on
*    Title: How do you make an array of structs in C?
*    Date:  27/10/2016
*    Availability: http://stackoverflow.com/questions/10468128/how-do-you-make-an-array-of-structs-in-c
***************************************************************************************/

	for (int i = 0; i < count; i++)
	{
		string string_in; //reads only a SINGLE string in at a time
		stringstream file_path;
		file_path << directory << file_names[i]; //ignore . AND .. in file listing

		ifstream inFile;		//reading in
		inFile.open(file_path.str()); //pass in file_path as string

		while (!inFile.eof()) {

			inFile >> string_in;

			//check if contains selective/iterative
			if (string_in == "for" || string_in == "while" || string_in == "do while")
			{
				array_of_indexes[i].count_iterative++;
			}

			if (string_in == "if" || string_in == "switch" || string_in == "case")
			{
				array_of_indexes[i].count_selective++;
			}

		}

		inFile.close(); //remember to close file

		cout << endl << array_of_indexes[i].file_name;
		cout << "\n   FILE CONTAINS: " << array_of_indexes[i].count_iterative << " ITERATIVE STATEMENTS\n";
		cout << "   FILE CONTAINS: " << array_of_indexes[i].count_selective << " SELECTIVE STATEMENTS\n";

	}

	cout << endl;
	system("pause");
	return 0;
}


//http://www.cplusplus.com/reference/string/string/back/
//https://www.daniweb.com/programming/software-development/threads/369727/open-txt-files-one-by-one-from-directory
//http://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
