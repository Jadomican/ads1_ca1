/*
*	Jason Domican		X00119321
*	Robert Fitzgerald	X00123156
*	
*	ADS1 Practical 1
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm> //use to sort?
#include "dirent.h"

using namespace std;

int main() //all parts of program coded by Jason and Robert
{
	struct SimilarityIndex
	{
		int count_selective = 0; // count of selective statements
		int count_iterative = 0; // count of iterative statements
		int number_of_lines = 0; //lines of CODE
		int number_of_words = 0; //word count
		string file_name;
		double index_metric; //how you determine similarity
	};

	/***************************************************************************************
	*    Usage: modified
	*    Title: Accessing directories in C/C++ Part I
	*    Date: 29/10/2016
	*    Availability: http://www.dreamincode.net/forums/topic/59943-accessing-directories-in-cc-part-i/
	*
	*    Usage: modified
	*    Title: Open txt files one by one from directory
	*    Date: 29/10/2016
	*    Availability: https://www.daniweb.com/programming/software-development/threads/369727/open-txt-files-one-by-one-from-directory
	***************************************************************************************/

	const int kMaxNumFiles = 4;	 //MAX number of files to be processed
	SimilarityIndex array_of_indexes[kMaxNumFiles];
	string directory;
	DIR *pdir = NULL;			// pointer to a directory
	struct dirent *pent = NULL; //dirent pointer
	int count_files = 0;

	do
	{
		cout << "**Plagiarism Detector (MAX " << kMaxNumFiles << " FILES)**";
		cout << "\nInput directory to be scanned: (HINT: Try ./files/ or files/ ... x to exit)\n\nDirectory: ";
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

	int num_skipped = 0; //number of files in directory skipped based on max files constant

	//http://stackoverflow.com/questions/51949/how-to-get-file-extension-from-string-in-c

	while (pent = readdir(pdir)) //while something left to list - read next directory entry
	{

		if (string(pent->d_name).substr(string(pent->d_name).find_last_of(".") + 1) == "cpp") //if cpp file type
		{
			{

				if (pent == NULL)
				{
					cout << "pent not initialised correctly";
					exit(1);
				}

				if (string(pent->d_name) == "." || string(pent->d_name) == "..") {} //do not include current and parent directory

				else
				{
					if (count_files >= kMaxNumFiles)
					{
						num_skipped++;
					}
					else
					{
						array_of_indexes[count_files].file_name = string(pent->d_name);
						count_files++;
					}
				}
			}
		}

	}

	if (num_skipped > 0)
	{
		cout << "\n*" << num_skipped << " cpp files were skipped*\n";
	}

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
		file_path << directory << array_of_indexes[i].file_name; //ignore . AND .. in file listing

		string line;
		ifstream lines_in_file;		//READ NUMBER OF LINES
		ifstream in_file;			//READ NUMBER OF WORDS/SEL/ITER/

		lines_in_file.open(file_path.str());
		while (getline(lines_in_file, line))
		{
			array_of_indexes[i].number_of_lines++; //NUMBER OF LINES WITH CODE IN THEM
			lines_in_file >> string_in;
		}
		lines_in_file.close();

		in_file.open(file_path.str());	//pass in file_path as string
		while (!in_file.eof()) {			//READ EACH STRING

			in_file >> string_in;
			array_of_indexes[i].number_of_words++;
			////check if contains selective/iterative
			if (string_in == "for" || string_in == "while" || string_in == "do while")
			{
				array_of_indexes[i].count_iterative++;
			}

			if (string_in == "if" || string_in == "switch" || string_in == "case")
			{
				array_of_indexes[i].count_selective++;
			}

		}
		in_file.close(); //remember to close file

		array_of_indexes[i].index_metric =
			(double(array_of_indexes[i].count_iterative) + double(array_of_indexes[i].count_selective))
			* double(array_of_indexes[i].number_of_words) / double(array_of_indexes[i].number_of_lines);

	}

	cout << "\nSORTING BY INDEX METRICS\n";
	/***************************************************************************************
	*    Usage: modified
	*    Title: Sorting an array using selection sort
	*    Date:  1/11/2016
	*    Availability: http://www.learncpp.com/cpp-tutorial/64-sorting-an-array-using-selection-sort/
	***************************************************************************************/

	// Step through each element of the array
	for (int start_index = 0; start_index < count_files; ++start_index)
	{
		// smallestIndex is the index of the smallest element we've encountered so far.
		int smallest_index = start_index;
		// Look for smallest element remaining in the array (starting at startIndex+1)
		for (int current_index = start_index + 1; current_index < count_files; ++current_index)
		{
			// If the current element is smaller than our previously found smallest
			if (array_of_indexes[current_index].index_metric < array_of_indexes[smallest_index].index_metric)
				// This is the new smallest number for this iteration
				smallest_index = current_index;
		}
		// Swap our start element with our smallest element
		swap(array_of_indexes[start_index], array_of_indexes[smallest_index]);
	}

	/***************************************************************************************
	*    Usage: modified
	*    Title: Show two digits after decimal point in c++
	*    Date: 04/11/2016
	*    Availability: http://stackoverflow.com/questions/16280069/show-two-digits-after-decimal-point-in-c
	***************************************************************************************/

	for (int i = 0; i < count_files; i++)
	{
		cout << endl << array_of_indexes[i].file_name;
		cout << "\n   FILE CONTAINS: " << array_of_indexes[i].count_iterative << " ITERATIVE STATEMENTS\n";
		cout << "   FILE CONTAINS: " << array_of_indexes[i].count_selective << " SELECTIVE STATEMENTS\n";
		cout << "   Number of lines (of code) in text file: " << array_of_indexes[i].number_of_lines << endl;
		cout << "   Word count: " << array_of_indexes[i].number_of_words << endl;
		//format print statement to 2 decimal places for readability
		cout << setprecision(2) << fixed << "   INDEX METRIC: " << array_of_indexes[i].index_metric << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}

//http://www.cplusplus.com/reference/string/string/back/
//http://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
