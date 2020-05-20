#include<iostream>
#include<string.h>
#include<algorithm>
#include<sstream>
using namespace std;

bool compareStr(string str, const char* ch) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	const char* compArr = str.c_str();
	return strcmp(ch, compArr);
}

string firstWord(string str)
{
	string saveAs = "save as";
	string word = "", word2 = "";
	for (char x : str)
	{
		if (x == ' ')
		{
			if (compareStr(word, "save") == 0) {
				string secondW = str.substr(str.find_first_of(" \t") + 1);
				cout << secondW << endl;
				for (char y : secondW)
				{
					if (y == ' ')
					{
						if (compareStr(word2, "as") == 0) {
							return saveAs;
						}
					}
					else
					{
						word2 = word2 + y;
					
					}
				}
			}
			if (compareStr(word2, "as") == 0) {
				return saveAs;
			}
			else {
				return word;

			}
		}
		else
		{
			word = word + x;
		}
	}
	return word;
	
}

void 


int main(){
	string input;
	class Room {
	public:
		int roomN;
		int beds;
		bool takenStatus;
		int takenBeds;
	};
	do {
		cout << "Checkin, checkout, availability, report, find, find!, unavailable."<<endl;
		getline(cin, input);
		string firstW = firstWord(input);
		if (compareStr(firstW, "checkin") == 0) {
			//checkin();
			cout << "checkin successful"<<endl;
		}
		if (compareStr(firstW, "checkout") == 0) {
			//checkin();
			cout << "checkout successful" << endl;
		}
		if (compareStr(firstW, "availability") == 0) {
			//checkin();
			cout << "availability successful" << endl;
		}
		if (compareStr(firstW, "report") == 0) {
			//checkin();
			cout << "report successful" << endl;
		}
		if (compareStr(firstW, "find") == 0) {
			//checkin();
			cout << "find successful" << endl;
		}
		if (compareStr(firstW, "find!") == 0) {
			//checkin();
			cout << "find! successful" << endl;
		}
		if (compareStr(firstW, "unavailable") == 0) {
			//checkin();
			cout << "unavailable successful" << endl;
		}
		if (compareStr(firstW, "open") == 0) {
			//checkin();
			cout << "open successful" << endl;
		}
		if (compareStr(firstW, "close") == 0) {
			//checkin();
			cout << "close successful" << endl;
		}
		if (compareStr(firstW, "save") == 0) {
			//checkin();
			cout << "save successful" << endl;
		}
		if (compareStr(firstW, "save as") == 0) {
			//checkin();
			cout << "save as successful" << endl;
		}

	} while (input != "exit");
	
	return 0;
}