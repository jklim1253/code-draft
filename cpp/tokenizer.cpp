#include <iostream>
#include <string>
#include <list>
#include <set>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

list<string> tokenizer(const string& src, const string& _delimiter) {
	set<char> delimiter;
	delimiter.insert(_delimiter.cbegin(), _delimiter.cend());

	list<string> result(1, "");

	for_each(src.cbegin(), src.cend(), [&](char c) {
		if (delimiter.find(c) == delimiter.end()) {
			result.back().push_back(c);
		}
		else {
			if (!result.back().empty()) {
				result.push_back("");
			}
		}
	});

	return result;
}

#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cout << "Usage : tokenizer [file]" << endl;
		return 1;
	}

	ifstream file(argv[1]);
	string contents;
	
	file.seekg(0, ios_base::end);

	if (file.tellg() > static_cast<streampos>(numeric_limits<string::size_type>::max()))
		contents.reserve(numeric_limits<string::size_type>::max());
	else
		contents.reserve(static_cast<string::size_type>(file.tellg()));

	file.seekg(0, ios_base::beg);

	contents.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	file.close();

	list<string> tokens = tokenizer(contents, " .,\n\t");

	int order = 0;
	for_each(tokens.begin(), tokens.end(), [&] (const string& s){
		cout << "[";
		cout << setw(5) << setfill(' ') << (order++);
		cout << "]  " << s << endl;
	});

	return 0;
}