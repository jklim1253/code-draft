#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;

list<string> tokenizer(istream& is, const char* _delimiter) {
	list<string> depot;
	string delimiter(_delimiter);
	char c;
	bool need_insert = true;
	while (is.get(c).good()) {
		if (delimiter.find(c) == string::npos) {
			if (need_insert) {
				depot.push_back(string());
				need_insert = false;
			}
			depot.rbegin()->append(1, c);
		}
		else {
			// pass...
			need_insert = true;
		}
	}

	return depot;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Usage : tokenizer [file]" << endl;
		return 0;
	}
	ifstream file(argv[1]);
	if (!file.good()) {
		cerr << "file not found." << endl;
		return 0;
	}

	list<string> depot = tokenizer(file, "\r\n\t; ");

	unsigned index = 0;
	for (string& e : depot) {
		cout << index++ << " : " << e << endl;
	}

	exit(EXIT_SUCCESS);
}