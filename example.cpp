#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <wchar.h>
#include "utf8.h"
using namespace std;
int main(int argc, char** argv)
{
    if (argc != 2) {
        cout << "Nevalja! Unesi put do testne datoteke.\n";
        return 0;
    }

    const char* test_file_path = argv[1];
    ifstream fs8(test_file_path);
    if (!fs8.is_open()) {
    cout << "Could not open " << test_file_path << endl;
    return 0;
    }

    unsigned line_count = 1;
    string line;
    while (getline(fs8, line)) {
       // check for invalid utf-8 (for a simple yes/no check, there is also utf8::is_valid function)
        string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
        if (end_it != line.end()) {
            cout << "UTF-8 encoding nevalja na liniji " << line_count << "\n";
            cout << "Ovaj dio je ok: " << string(line.begin(), end_it) << "\n";
        }

        int length = utf8::distance(line.begin(), end_it);
        cout << "Broj znakova linije " << line_count << " je " << length <<  "\n";

        vector<unsigned short> utf16line;
        utf8::utf8to16(line.begin(), end_it, back_inserter(utf16line));
	//std::locale::global (std::locale ("UTF-16"));
	for (std::vector<unsigned short>::const_iterator i = utf16line.begin(); i != utf16line.end(); ++i){
	  cout << "Dec: " << *i << " ";
	  std::stringstream ss;
	  ss<< std::hex << *i;
	  std::string res ( ss.str() );
	  std::cout << "\tHex: " << res <<"\n";
	  //wchar_t c = static_cast<wchar_t>(*i);
	  //std::wcout << "\t" << c <<std::endl;
	}
	
        string utf8line; 
        utf8::utf16to8(utf16line.begin(), utf16line.end(), back_inserter(utf8line));
	std::cout << "Text: " << utf8line << "\n";

        if (utf8line != string(line.begin(), end_it))
            cout << "Error UTF-16 konverzija na liniji: " << line_count << "\n";        

        line_count++;
    }
    return 0;
}