/*
Jason Domican		X00119321
Robert Fitzgerald	X00123156

ADS1 Practical 1
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <sstream>
#include <vector>
#include "dirent.h"
using namespace std;

int main()
{
	struct SimilarityIndex
	{
		int count_selective = 0; // if, switch
		int count_iterative = 0; // for, while
		string file_name;
		int number_of_lines = 0;

	};

	//https://google.github.io/styleguide/cppguide.html#Constant_Names
	const int kMaxNumFiles = 4;						//number of files to be processed
	SimilarityIndex array_of_indexes[kMaxNumFiles];	//SHOULD WE INCLUDE A STRING (file_name) VARIABLE INSIDE THE STRUCT?
	string directory;
	DIR *pdir = NULL;								// struct in dirent.h (Line 256)
	struct dirent *pent = NULL;
	int count_files = 0;

	do
	{
		cout << "**Plagiarism Detector (MAX " << kMaxNumFiles << " FILES)**";
		cout << "\nInput directory to be scanned: (HINT: Try ./files/ or files/ ... x to exit)" << endl;
		cin >> directory;

		if (directory == "x") // allow user to exit
		{
			cout << "\nExiting...\n";
			system("pause");
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
	//		array_of_indexes[i].file_name = string(pent->d_name);
	//	}
	//}
	int num_skipped = 0;
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
			if (count_files >= kMaxNumFiles)
			{
				//cout << "SKIPPING " << pent->d_name <<", only first " << kMaxNumFiles << " files scanned\n";
				num_skipped++;
			}
			else
			{
				//file_names.push_back(string(pent->d_name));
				array_of_indexes[count_files].file_name = string(pent->d_name);
				count_files++;
			}
		}
	}
	cout << "\n* " << num_skipped << " files were skipped*\n";

	closedir(pdir); //close the directory when done reading

	/***************************************************************************************
	*    Usage: based on
	*    Title: How do you make an array of structs in C?
	*    Date:  27/10/2016
	*    Availability: http://stackoverflow.com/questions/10468128/how-do-you-make-an-array-of-structs-in-c
	***************************************************************************************/

	for (int i = 0; i < count_files; i++)
	{
		string string_in; //reads only a SINGLE string in at a time
		stringstream file_path;
		//file_path << directory << file_names[i]; //ignore . AND .. in file listing
		file_path << directory << array_of_indexes[i].file_name; //ignore . AND .. in file listing

		string line;
		ifstream inFile;		//reading in

		inFile.open(file_path.str()); //READ NUMBER OF LINES
		while (getline(inFile, line))
		{
			array_of_indexes[i].number_of_lines++; //NUMBER OF LINES WITH CODE IN THEM

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
		inFile.close();

		//inFile.open(file_path.str());	//pass in file_path as string
		//while (!inFile.eof()) {			//READ EACH STRING

		//	inFile >> string_in;

		//	//check if contains selective/iterative
		//	if (string_in == "for" || string_in == "while" || string_in == "do while")
		//	{
		//		array_of_indexes[i].count_iterative++;
		//	}

		//	if (string_in == "if" || string_in == "switch" || string_in == "case")
		//	{
		//		array_of_indexes[i].count_selective++;
		//	}

		//}
		//inFile.close(); //remember to close file

		cout << endl << array_of_indexes[i].file_name;
		cout << "\n   FILE CONTAINS: " << array_of_indexes[i].count_iterative << " ITERATIVE STATEMENTS\n";
		cout << "   FILE CONTAINS: " << array_of_indexes[i].count_selective << " SELECTIVE STATEMENTS\n";

		cout << "   Number of lines in text file: " << array_of_indexes[i].number_of_lines;




	}

	cout << endl;
	system("pause");
	return 0;
}


//USE VECTOR, ARRAY OF STRINGS OR STRING VARIABLE IN similarity_index.h?
//HOW MANY COMPARISONS? WHILE? DO? FOR? FOREACH? RETURN? WHICH WAY? find() method?

//http://www.cplusplus.com/reference/string/string/back/
//https://www.daniweb.com/programming/software-development/threads/369727/open-txt-files-one-by-one-from-directory
//http://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
//http://www.dreamincode.net/forums/topic/59943-accessing-directories-in-cc-part-i/
