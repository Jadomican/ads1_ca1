#ADS1 CA1
##Elapsed CA1 (JASON DOMICAN & ROBERT FITZGERALD)

![FOGGY](http://vignette2.wikia.nocookie.net/looneytunes/images/7/79/Foghorn_Leghorn.jpg/revision/latest?cb=20130223190707)


PROJECT IS TO CREATE A PLAGIARISM DETECTION PROGRAM
B.Sc. in Computing ADS1 Practical 1 18% 17 November 2016
 
 
 
Due Date: Thursday **17 November 2016**

Upload each .h and .cpp file which you have written to Moodle.
Note: You should separate each class you create into .cpp and .h files. And you should
follow the Google C++ style guide
http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml

Note: Clearly comment your code showing which group member coded which part of
the CA.

You have to write a plagiarism detector for a group of C++ files. You program
needs to be able to open a directory and process a maximum of 4 .cpp files
contained in the directory, however, the program should be designed that it works
with **any file name** and could with a simple change be able to process more than
4 files).
You program will:
1. Take as an input a directory location (where the files to be scanned are
stored) i.e. h:\myfiles
2. Open each file and calculate a similarity index for it.
Design your own similarity index, for example, you could do a very
simple index that: makes a count of the number of iterative and
selection statements in the file.
3. Output a report listing the file name and its associated similarity index.
Example output report:
File1.cpp --- contains 3 iterative 2 selection statements
File2.cpp --- contains 1 iterative 3 selection statements
File3.cpp --- contains 1 iterative 1 selection statements
File4.cpp --- contains 4 iterative 2 selection statements
Marks will depend on the design, efficiency, and style of your code and all marks
are dependent on your understanding for the code you submit (assessed by
interview).

Some Suggestions
First of all get your program working for a single file, and then after you have tested
it, process all the files in the directory. You may need dirent.h or windows.h
to work with directories. If you wish to use the dirent.h header file in Visual
Studio you will have to add it in to the include path in the project properties. (see
VC++ Directories Property Page). See the links on Moodle for directory processing
and file access. This link might also help you
http://www.fredosaurus.com/notes-cpp/io/readtextfile.html
Process each file in the directory and calculate a similarity index for it (the index
could be a struct something like the following
typedef struct
{
 int iterativecount;
 int selectioncount;
} SimilarityIndex_t;
You could then make an array of similarity indexes (see example below). If you
then sort this array you will have alike indexes beside each other.
const size_t file_n = 4;
SimilarityIndex_t arrayOfFileIndexes[file_n]; 
