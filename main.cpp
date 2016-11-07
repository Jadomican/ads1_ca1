/*
*	ADS1 CA1
*
*	Jason Domican		X00119321
*	Robert Fitzgerald	X00123156
*
*	Utilises dirent.h by Toni Rönkkö https://github.com/tronkko
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "dirent.h"  // Used to access directories
using namespace std;

int main()  // All parts of program coded by Jason and Robert
{
	struct SimilarityIndex
	{
		int count_selective = 0;  // Count of selective statements
		int count_iterative = 0;  // Count of iterative statements
		int number_of_lines = 0;  // Lines (of code)
		int word_count = 0;
		string file_name;
		double index_metric;  // Determines similarity
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

	const int kMaxNumFiles = 4;                      // Max number of files to be processed
	SimilarityIndex array_of_indexes[kMaxNumFiles];  // Array of structs
	string directory;								 // Directory to be scanned
	DIR *pdir = NULL;								 // Pointer to a directory
	struct dirent *pent = NULL;						 // Dirent pointer
	int count_files;
	int num_skipped;						 // Number of files in directory skipped based on max files constant
	const double kPlagiarismPercent = 0.15;  // Percentage of similarity checked
	bool continue_run = true;				 // Condition to continue running
	char choice;							 // User input to continue program

	cout << "**Plagiarism Detector (Max " << kMaxNumFiles << " .cpp files)**\n";

	while (continue_run)
	{
		cout << "Input directory to be scanned or press x to exit)\n\n";
		count_files = 0;  // Set variables to 0 at beginning of program for re-run
		num_skipped = 0;
		do
		{
			cout << "Directory: ";
			cin >> directory;

			if (directory == "x" || directory == "X")  // Allow user to exit
			{
				cout << "\nExiting...\n";
				system("pause");
				exit(1);
			}

			/***************************************************************************************
			*    Usage: modified
			*    Title: String back() method
			*    Date: 30/10/2016
			*    Availability: http://www.cplusplus.com/reference/string/string/back/
			***************************************************************************************/

			if (directory.back() != '/')  // Ensure last character is a '/' ('\' works too)
			{
				directory += '/';
			}

			/***************************************************************************************
			*    Usage: modified
			*    Title: Converting String to Cstring in c++
			*    Date: 30/10/2016
			*    Availability: http://stackoverflow.com/questions/11821491/converting-string-to-cstring-in-c
			***************************************************************************************/

			pdir = opendir(directory.c_str());  // Opens specified directory

			if (pdir == NULL)  // If no directory found, notify user
			{
				cout << "\nDirectory not found, try again\n\n";
			}
		} while (pdir == NULL);

		/***************************************************************************************
		*    Usage: modified
		*    Title: How to get file extension from string in C++
		*    Date: 03/11/2016
		*    Availability: http://stackoverflow.com/questions/51949/how-to-get-file-extension-from-string-in-c
		***************************************************************************************/

		while (pent = readdir(pdir))  // While something left to list - read next directory entry
		{
			if (string(pent->d_name).substr(string(pent->d_name).find_last_of(".") + 1) == "cpp")  // If .cpp file type
			{
				if (count_files >= kMaxNumFiles)  // Only process max number of files
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

		if (count_files < 1)  // If no cpp files found
		{
			cout << "\n*No .cpp files found*\n";
		}
		else  // Else continue
		{
			if (num_skipped > 0)
			{
				cout << "\n*" << num_skipped << " .cpp files were skipped*\n";
			}

			closedir(pdir);  // Close the directory when done reading

			/***************************************************************************************
			*    Usage: based on
			*    Title: How do you make an array of structs in C?
			*    Date:  27/10/2016
			*    Availability: http://stackoverflow.com/questions/10468128/how-do-you-make-an-array-of-structs-in-c
			***************************************************************************************/

			// Loop to scan each file for index metric
			for (int i = 0; i < count_files; i++)
			{
				array_of_indexes[i].count_selective = 0;  // Reset values (if user decides to run again)
				array_of_indexes[i].count_iterative = 0;
				array_of_indexes[i].number_of_lines = 0;
				array_of_indexes[i].word_count = 0;
				array_of_indexes[i].index_metric = 0;

				string string_in;		 // Reads only a single string in at a time
				stringstream file_path;
				string line;
				ifstream lines_in_file;  // Read number of lines
				ifstream in_file;		 // Read number of words/selective/iterative

				file_path << directory << array_of_indexes[i].file_name;

				lines_in_file.open(file_path.str());  // Open file to count number of lines

				while (getline(lines_in_file, line))  // While another line to read
				{
					array_of_indexes[i].number_of_lines++;  // Number of lines (of code)
					lines_in_file >> string_in;
				}

				lines_in_file.close();  // Remember to close file

				in_file.open(file_path.str());	 // Pass in file_path as string

				while (!in_file.eof()) {		 // Read each string

					in_file >> string_in;
					array_of_indexes[i].word_count++;
					// Check if contains selective/iterative
					if (string_in == "for" || string_in == "while" || string_in == "do")
					{
						array_of_indexes[i].count_iterative++;
					}

					if (string_in == "if" || string_in == "switch" || string_in == "case")
					{
						array_of_indexes[i].count_selective++;
					}
				}

				in_file.close();  // Remember to close file

				// Calculate similarity index metric
				array_of_indexes[i].index_metric =
					((array_of_indexes[i].count_iterative) + (array_of_indexes[i].count_selective))
					* double(array_of_indexes[i].word_count) / (array_of_indexes[i].number_of_lines);
			}

			/***************************************************************************************
			*    Usage: modified
			*    Title: Sorting an array using selection sort
			*    Date:  1/11/2016
			*    Availability: http://www.learncpp.com/cpp-tutorial/64-sorting-an-array-using-selection-sort/
			***************************************************************************************/

			//Sort by index metric
			cout << "\nSorting by index metrics:\n";
			for (int start_index = 0; start_index < count_files; start_index++)
			{
				// Smallest_index is the index of the smallest element encountered so far.
				int smallest_index = start_index;
				// Look for smallest element remaining in the array (starting at start_index+1)
				for (int current_index = start_index + 1; current_index < count_files; current_index++)
				{
					// If the current element is smaller than the previously found smallest
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
				cout << "\n" << array_of_indexes[i].file_name;
				cout << "\n   File contains: " << array_of_indexes[i].count_iterative << " Iterative statements\n";
				cout << "   File contains: " << array_of_indexes[i].count_selective << " Selective statements\n";
				cout << "   Number of lines (of code) in text file: " << array_of_indexes[i].number_of_lines << "\n";
				cout << "   Word count: " << array_of_indexes[i].word_count << "\n";
				// Format print statement to 2 decimal places for readability
				cout << setprecision(2) << fixed << "   Index Metric: " << array_of_indexes[i].index_metric << "\n";
			}

			if (count_files > 1)
			{
				for (int i = 0; i < count_files; i++)  // Determine similarity
				{
					for (int j = i + 1; j < count_files + 1; j++)
					{
						if (array_of_indexes[i].index_metric < 
							(array_of_indexes[j].index_metric + array_of_indexes[j].index_metric * kPlagiarismPercent)
							&& (array_of_indexes[i].index_metric >
							(array_of_indexes[j].index_metric - array_of_indexes[j].index_metric * kPlagiarismPercent)))
						{
							cout << "\n" << array_of_indexes[i].file_name << " and " << array_of_indexes[j].file_name
								<< " may be plagiarised (within " << kPlagiarismPercent * 100 << "%)" << "\n";
						}
					}
				}
			}
			else
			{
				cout << "\n*Only one file found, similarity cannot be determined*";
			}
		}

		cout << "\nWould you like to go again? Y to continue...\nChoice: ";
		cin >> choice;

		if (choice == 'Y' || choice == 'y')
		{
			continue_run = true;
			system("cls");

		}
		else
		{
			continue_run = false;
		}

	}

	cout << endl;
	system("pause");
	return 0;
}
