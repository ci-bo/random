//A multi-file variant on the classic Zelenski RSG (Random Sentence Generator),
//chooses a random line from a file and recursively replaces <bracketed filenames>.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "random.h"
//Please see: https://github.com/effolkronium/random

using namespace std;
using Random = effolkronium::random_static;

ifstream loadfile(string filename)
{
	//Load the file
	ifstream file(filename);
	//...or die trying
	if (!file)
	{
		cout << "Can't open " + filename + "!\n";
		exit(0);
	}

	return file;
}

struct RSG {

	string pickRandom(vector<string> infixes)
	{
		//Count how many lines we copied. Cast size_type to integer.
		int count = static_cast<int>(infixes.size());

		//Choose random element of "tags".
		int choice = Random::get<int>(0, count - 1);

		return infixes[choice];
	}

	string replaceBrackets(string directory, string infix)
	{
		bool replacing = false;
		string temptag, result = "";

		int count = static_cast<int>(infix.size());

		do {
			for (int c = 0; c < count; c++) {
				if (!replacing)
				{
					if (infix[c] == '<')
					{
						replacing = true;
					}
					else
					{
						result += infix[c];
					}
				}
				else
				{
					if (infix[c] == '>') {
						replacing = false;
						temptag = expand(directory, temptag);
						result += temptag;
						temptag = "";
					}
					else
					{
						temptag += infix[c];
					}
				}
			}

		}
		while (result.find('<') != std::string::npos);

		return result;
	}

	string expand(string directory, string filename)
	{
		ifstream file = loadfile(directory + filename);

		//Copy each line into vector of strings
		vector<string> strings;
		string line;

		while (getline(file, line))
		{strings.push_back(line);}

		/*Pull random line*/
		line = pickRandom(strings);
		/*Process lines recursively and return*/
		return replaceBrackets(directory, line);
	}

};

	//STUPID
	string directory(string filename) {
	string filename_directory = filename.substr(0, filename.find_last_of('\\')+1);
	//cout << filename_directory << "\n";
	return filename_directory;
	}
	string onlyfile(string filename) {
	string filename_end = filename.substr(filename.find_last_of('\\')+1, filename.length() - 1);
	//cout << filename_end << "\n";
	return filename_end;
	}


int main(int argc, char* argv[])
{
	//Determine filenames
	if ((argc < 3) | (argc > 4))
	{
		cout << "Arguments: (filename) (output filename) (optional: output count)";
		return -1;
	}

	string filename = argv[1];
	string outfilename = argv[2];
	string totalcount = argv[3];

	bool repeatcount = false;

	int rc = 1;

	if (totalcount != "") {
		if (!stoi(totalcount)) {
			cout << "Couldn't use that number.";
			return -1;
		}
		repeatcount = true;
		rc = stoi(totalcount);
	}

	//Directory garbage
	string filename_directory = "";
	string filename_end = filename;
	if (filename.find('\\') != string::npos)
	{
		filename_directory = directory(filename);
		filename_end = onlyfile(filename);
	}

	//Load first file and get the ball rolling
	ifstream file = loadfile(filename);

	RSG rsg;
	for (int i = rc; i > 0; i--) {

		string line = rsg.expand(filename_directory, filename_end); //Expands recursively. Be careful!

		//Output to cout
		cout << line << "\n\n";

		//Output to file
		ofstream outfile;
		outfile.open(outfilename, ios::app);
		outfile << line + " ";

	}

	return 0;

}
