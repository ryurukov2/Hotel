#include<iostream>
#include<string>
#include<algorithm>
#include<sstream>
#include<stdio.h>
#include<fstream>
using namespace std;
string lines[100];

class Room {
public:
	int roomId, beds, takenBeds;
	int takenStatus;
	string note, fromDate, toDate;
	int lastRoomId();
	void addRooms(int n);
};

string removeFirstAst(string str) {
	return str.substr(str.find_first_of("*") + 1);
}
string removeFirstWord(string str) {
return str.substr(str.find_first_of(" \t") + 1);
}



bool is_number(string str) {
	//https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
	string::const_iterator it = str.begin();
	while (it != str.end() && isdigit(*it)) {
		it++;
	}
	return !str.empty() && it == str.end();
}

bool iss_empty(ifstream& pFile)
{
	//https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
	return pFile.peek() == fstream::traits_type::eof();
}

bool compareStr(string str, const char* ch) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	const char* compArr = str.c_str();
	return strcmp(ch, compArr);
}

int strToInt(string str) {
	if (str == "") {
		return NULL;
	}
	int result = 0;
	for (auto x : str) {
		if (x == '*') {
			break;
		}
		else if (x >= '0' && x <= '9') {
			result = 10 * result + (x - '0');
		}
		else {
			return NULL;
		}
	}
	return result;
}

string firstWord(string str)
{
	string saveAs = "save as";
	string word = "", word2 = "";
	for (auto x : str)
	{
		if (x == ' ' || x == '*')
		{
			if (compareStr(word, "save") == 0) {
				string secondW = removeFirstWord(str);
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

int getId(string str) {
	int answer = strToInt(firstWord(str));
	return answer;
	}
int getBeds(string str) {
	string beds;
	int astCount = 0;
	for (auto x : str) {
		if (x == '*') {
				astCount++;
				if (astCount == 1) {
					continue;
				}
		}
		if (astCount == 0 || x == ' ') {
			
			continue;
		}
		
		if (astCount == 1 && x != '*') {
			beds = beds + x;
		}
		if(astCount == 1 && x == '*') {
			return strToInt(beds);
		}

	}
	return strToInt(beds);
}



void parseDate(string str, string& y, string& m, string& d) {
	int dashCount = 0;

	for (auto x : str) {

		if (dashCount == 0) {
			if (x == '-') {
				int n = y.length();
				if (n == 4) {
					while (isdigit(y[y.length() - n])) {
						n--;
					}
					if (n == 0) {
						dashCount++;
						continue;
					}
					else {
						cout << "1Incorrect year format." << endl;
						return;
					}
				}
				else {
					cout << "6Incorrect year format." << endl;
					return;
				}

			}
			else {
				y = y + x;

			}

		}
		if (dashCount == 1) {

			if (x == '-') {
				int n = m.length();
				if (n == 2) {
					while (isdigit(m[m.length() - n])) {
						n--;
					}
					if (n == 0) {
						dashCount++;
						continue;
					}

					else {
						cout << "2Incorrect month format." << endl;
						return;
					}
				}
				else {
					cout << "3Incorrect month format." << endl;
					return;
				}
			}
			else {
				m = m + x;
			}
		}
		if (dashCount == 2) {

			if (x == ' ') {
				int n = d.length();
				if (n == 2) {
					while (isdigit(d[d.length() - n])) {
						n--;
					}
					if (n == 0) {
						dashCount++;
						continue;
					}

					else {
						cout << "4Incorrect month format." << endl;
						return;
					}
				}
				else {
					cout << "5Incorrect month format." << endl;
					return;
				}

			}
			else {
				d = d + x;
			}
		}

	}

}



bool compareDates(int y1, int m1, int d1, int y2, int m2, int d2) {
	if (y1 < y2) {
		return true;
	}
	else if (y1 == y2) {
		if (m1 < m2) {
			return true;
		}
		else if (m1 == m2) {
			if (d1 == d2) {
				return true;
			}
			if (d1 < d2) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void checkin(string str) {
	//					checkin 6 2020-03-23 2020-03-31 The Simpsons
	Room curr;
	bool isFine = 1;
	curr.note = "";
	string substr = removeFirstWord(str);

	string room = "", fromY = "", fromM = "", fromD = "", toY = "", toM = "", toD = "", numberOfPeople;
	int element = 0;
	while (element<4) {
		if(element == 0){
			//getting room number
			for (auto x : substr) {
				if (x == ' ') {
					int n = room.length();
					while (isdigit(room[room.length() - n])) {
						n--;
					}
					if (n == 0) {
						break;
					}
					else {
						cout << "Room number should be a number."<<endl;
						isFine = 0;
						return;
					}
				}
				else {
					room = room + x;
				}
			}
			
		}
		else if (element == 1) {
			parseDate(substr, fromY, fromM, fromD);
			//getting dates from 
			}
		else if (element == 2) {
		parseDate(substr, toY, toM, toD);
		if (!compareDates(strToInt(fromY), strToInt(fromM), strToInt(fromD), strToInt(toY), strToInt(toM), strToInt(toD)) ){
		
			 cout<< "Checkout date should be after checkin date."<<endl;
			 isFine = 0;
			 return;
		}
		//getting dates to

		}
		else {
			if (is_number(substr.substr(substr.length() - 1)) && substr[substr.length() - 2] == ' ') {
				numberOfPeople = substr[substr.length() - 1];
				cout << "people = " << numberOfPeople << endl;
				curr.note = substr.substr(0, substr.length() - 2);

			}
			else {
				curr.note = substr;
			}
		}
	

		
		element++;
		substr = removeFirstWord(substr);
	
	}	cout <<"From: "<< fromY << "-" << fromM << "-" << fromD << endl;
		cout << "To: "<<toY << "-" << toM << "-" << toD << endl;
		cout << "note = " << curr.note << endl;
		ifstream strm;
		int i = 0;
		string f;
		strm.open("rooms.txt");
		while (!strm.eof()) {
			getline(strm, f);

			if (i == (strToInt(room) - 1)) {
				if (getBeds(f) < strToInt(numberOfPeople)) {
					isFine = 0;
				}
			}
			i++;
		}
		strm.close();
		
		if (isFine == 1) {

			curr.roomId = strToInt(room);
			curr.takenBeds = strToInt(numberOfPeople);

			if (fromM.length() == 1) {
				fromM = "0" + fromM;
			}
			if (fromD.length() == 1) {
				fromD = "0" + fromD;
			}
			curr.fromDate = fromY + "-" + fromM + "-" + fromD;
			if (toM.length() == 1) {
				toM = "0" + toM;
			}
			if (toD.length() == 1) {
				toD = "0" + toD;
			}
			curr.toDate = toY + "-" + toM + "-" + toD;
			curr.takenStatus = 2; 

			ifstream istrm;
			istrm.open("rooms.txt");
			ofstream ostrm;
			ostrm.open("rooms1.txt");
			while (!istrm.eof()) {
				getline(istrm, f);

				if (strToInt(firstWord(f)) == (strToInt(room)) ){
					curr.beds = getBeds(f);
					ostrm << curr.roomId << "*" << curr.beds << "*" << curr.takenBeds << "*" << curr.takenStatus << "*" << curr.note << "*" << curr.fromDate << "*" << curr.toDate << "*\n";
				}
				else {
					ostrm<<f<<"\n";
				}
			}
			
			istrm.close();
			ostrm.close();
			if (remove("rooms.txt") != 0) {
				cout << "Cant delete file." << endl;
			}
			if (rename("rooms1.txt", "rooms.txt") != 0) {
				cout << "Cant rename files." << endl;
			}
			cout << "Checkin successful."<<endl;
		}
		else{
			cout << "Checkin unsuccessful." << endl;
		}
}
				
void checkout(string str) {
	int rId = strToInt(removeFirstWord(str));
	string lines[100];
	ifstream myS;
	int i = 0;
	myS.open("rooms.txt");
	while (!myS.eof()) {
		getline(myS, lines[i]);
		
		
		if (strToInt(firstWord(lines[i])) == rId) {
			string tempB = firstWord(removeFirstAst(lines[i]));
			lines[i] = to_string(rId) + "*" + tempB + "*0*0***";
		}
		i++;
	}
	myS.close();
	ofstream newS;
	newS.open("rooms1.txt");
	for (int k = 0; k < i; k++) {
		int l = 0;
		if (lines[k] == "") {
			l++;
			continue;
		}
		lines[k - l] = lines[k];
		newS << lines[k] << endl;
	}
	newS.close();
	if (remove("rooms.txt")!=0) {
		cout << "Can't delete file.";
	}
	if (rename("rooms1.txt", "rooms.txt") != 0) {
		cout << "Can't rename file.";
	}
	cout << "checkout successful" << endl;
}
string getDateFromRooms(string str) {
	string str1 = removeFirstAst(removeFirstAst(removeFirstAst(removeFirstAst(removeFirstAst(str)))));
	return str1.substr(0, str1.find("*"));

}
string getDateToRooms(string str) {
	string str1 = removeFirstAst(removeFirstAst(removeFirstAst(removeFirstAst(removeFirstAst(removeFirstAst(str))))));
	return str1.substr(0, str1.find("*"));
}
void availability(string str) {
	string checkY="", checkM="", checkD="";
	parseDate(removeFirstWord(str), checkY, checkM, checkD);
	ifstream myS;
	string line;
		int i = 0;
	myS.open("rooms.txt");
	cout << "Rooms that are free on that day.";
	while (!myS.eof()) {
		string compY="", compM="", compD="", compToY ="", compToM="", compToD="";
		getline (myS, line);
		parseDate(getDateFromRooms(line), compY, compM, compD);
		parseDate(getDateToRooms(line), compToY, compToM, compToD);
		
		if (compareDates(strToInt(checkY), strToInt(checkM), strToInt(checkD), strToInt(compY), strToInt(compM), strToInt(compD)) ||
			!compareDates(strToInt(checkY), strToInt(checkM), strToInt(checkD), strToInt(compToY), strToInt(compToM), strToInt(compToD)))
		{
			cout << firstWord(line) << endl;
		}
		

	}
	myS.close();
}
int checkDays(int fromY, int fromM) {

	if (fromM == 1 || fromM == 3 || fromM == 5 || fromM == 7 || fromM == 8 || fromM == 10 || fromM == 12) {
		return 31;
	}
	else if (fromM == 2 && fromY % 4 == 0) {
		return 29;
	}
	else if (fromM == 2 && fromY % 4 != 0) {
		return 28;
	}
	else {
		return 30;
	}
}
int countDays(int fromY, int fromM, int fromD, int toY, int toM, int toD) {
	int days = 0;
	if (fromY == toY) {

		if (fromM == toM) {
			return toD - fromD;
		}
		else {
			
			for (int i = fromM; i < toM; i++) {
				int monthDays = checkDays(fromY, fromM);
				days = days + monthDays + (toD-fromD);
			}
			return days;
		}
	}
	else {
		for (int i = fromY; i < toY; i++) {
			if (i % 4 == 0) {
				days = days + 366;
			}
			else {
				days = days + 365;
			}
			for (int k = fromM; k < toM; k++) {
				int monthDays = checkDays(fromY, fromM);
				days = days + monthDays;
			}

		}
		days = days + (toD - fromD);
		return days;
	}
	return days;
}

void report(string str) {
	//report 2020-03-25 2020-04-12
	//       2020-03-23 2020-03-31
	//fromX, toX = input date
	//compX, compToX = line date
	
	string fromY, fromM, fromD, toY, toM, toD, line;
	parseDate(firstWord(removeFirstWord(str)), fromY, fromM, fromD);
	parseDate(removeFirstWord(removeFirstWord(str)), toY, toM, toD); 
	ifstream myS;
	myS.open("rooms.txt");
	while (!myS.eof()) {
		int countDay = 0;
		string compY = "", compM = "", compD = "", compToY = "", compToM = "", compToD = "";
		getline(myS, line);
		parseDate(getDateFromRooms(line), compY, compM, compD);
		
		parseDate(getDateToRooms(line), compToY, compToM, compToD);
		if (compareDates(strToInt(fromY), strToInt(fromM), strToInt(fromD), strToInt(compY), strToInt(compM), strToInt(compD)) &&
			!compareDates(strToInt(toY), strToInt(toM), strToInt(toD), strToInt(compY), strToInt(compM), strToInt(compD)) &&
			compareDates(strToInt(toY), strToInt(toM), strToInt(toD), strToInt(compToY), strToInt(compToM), strToInt(compToD)))
		{
			// a < c; c < b < d
			countDay = countDays(strToInt(compY), strToInt(compM), strToInt(compD), strToInt(toY), strToInt(toM), strToInt(toD));
		}
		else if (!compareDates(strToInt(fromY), strToInt(fromM), strToInt(fromD), strToInt(compY), strToInt(compM), strToInt(compD)) &&
			compareDates(strToInt(toY), strToInt(toM), strToInt(toD), strToInt(compToY), strToInt(compToM), strToInt(compToD)))
		{
			// a > c; b < d
			countDay = countDays(strToInt(fromY), strToInt(fromM), strToInt(fromD), strToInt(toY), strToInt(toM), strToInt(toD));
		}
		else if (!compareDates(strToInt(fromY), strToInt(fromM), strToInt(fromD), strToInt(compY), strToInt(compM), strToInt(compD)) &&
			!compareDates(strToInt(toY), strToInt(toM), strToInt(toD), strToInt(compToY), strToInt(compToM), strToInt(compToD)))
		{
			// d > a > c; b > d
			countDay = countDays(strToInt(fromY), strToInt(fromM), strToInt(fromD), strToInt(compToY), strToInt(compToM), strToInt(compToD));
		}
		else if (compareDates(strToInt(fromY), strToInt(fromM), strToInt(fromD), strToInt(compY), strToInt(compM), strToInt(compD)) &&
			!compareDates(strToInt(toY), strToInt(toM), strToInt(toD), strToInt(compToY), strToInt(compToM), strToInt(compToD)))
		{
			//a < c; b > d
			countDay = countDays(strToInt(compY), strToInt(compM), strToInt(compD), strToInt(compToY), strToInt(compToM), strToInt(compToD));

		}
		if (countDay > 0) {
			cout << "Room " << line.substr(0, line.find("*")) << " is taken for " << countDay << " days." << endl;
		}

	}


	myS.close();
}
void find(string str) {
	//find 4 2020-03-18 2020-03-21
	int beds = strToInt(firstWord(removeFirstWord(str)));
	string fromY, fromM, fromD, toY, toM, toD, line;
	int minRoom = 0, minBed = INT_MAX;
	parseDate(firstWord(removeFirstWord(removeFirstWord(str))), fromY, fromM, fromD);
	parseDate(removeFirstWord(removeFirstWord(removeFirstWord(str))), toY, toM, toD);
	ifstream myS;
	myS.open("rooms.txt");
	while (!myS.eof()) {
		getline(myS, line);
		string compY = "", compM = "", compD = "", compToY = "", compToM = "", compToD = "";
		int currBeds = strToInt(firstWord(removeFirstAst(line)));
		parseDate(getDateFromRooms(line), compY, compM, compD);
		parseDate(getDateToRooms(line), compToY, compToM, compToD);
		string t = removeFirstAst(removeFirstAst(removeFirstAst(line)));
		if (strToInt(t.substr(0, t.find("*"))) == 0) {
			if (currBeds >= beds && (currBeds - beds) < minBed) {
				minRoom = getId(line);
				minBed = currBeds - beds;
			}
		}
		else if (compareDates(strToInt(fromY), strToInt(fromM), strToInt(fromD), strToInt(compY), strToInt(compM), strToInt(compD)) &&
			compareDates(strToInt(toY), strToInt(toM), strToInt(toD), strToInt(compY), strToInt(compM), strToInt(compD))) {
			if (currBeds >= beds && (currBeds - beds) < minBed) {
				minRoom = getId(line);
				minBed = currBeds - beds;
			}
		}
		else if (!compareDates(strToInt(fromY), strToInt(fromM), strToInt(fromD), strToInt(compToY), strToInt(compToM), strToInt(compToD)) &&
			compareDates(!strToInt(toY), strToInt(toM), strToInt(toD), strToInt(compToY), strToInt(compToM), strToInt(compToD))) {
			if (currBeds >= beds && (currBeds - beds) < minBed) {
				minRoom = getId(line);
				minBed = currBeds - beds;
			}
		}
			
	}
	if (minRoom == 0) {
		cout << "No suitable room";
	}
	else {
		cout << "\n Best room:" << minRoom << endl;
	}
	myS.close();
}

void unavailable(string str) {
	//unavailable 3 2020-03-21 2020-04-20 remont
	string note = "";
	string substr = removeFirstWord(str);
	string fromY = "", fromM = "", fromD = "", toY = "", toM = "", toD = "", line;
	int element = 0;
	int room= strToInt(firstWord(removeFirstWord(str)));
	parseDate(firstWord(removeFirstWord(removeFirstWord(str))), fromY, fromM, fromD);
	parseDate(firstWord(removeFirstWord(removeFirstWord(removeFirstWord(str)))), toY, toM, toD);
	note = removeFirstWord(removeFirstWord(removeFirstWord(removeFirstWord(str))));
	if (!compareDates(strToInt(fromY), strToInt(fromM), strToInt(fromD), strToInt(toY), strToInt(toM), strToInt(toD))) {
		return;
	}

	cout << room<<endl;
	cout << fromY << " " << fromM << " " << fromD << endl;
	cout << toY << " " << toM << " " << toD << endl;
	cout << "note = " << note << endl;	
	int i = 0;	
	ofstream myS;
	myS.open("rooms1.txt");
	ifstream strm;
	strm.open("rooms.txt");

	while (!strm.eof()) {
		getline(strm, line);
		if (i == room - 1) {
			int tempBeds = strToInt(firstWord(removeFirstAst(line)));
			myS << room << "*" << tempBeds << "*0*1*" << note << "*" << fromY << "-" << fromM << "-" << fromD << "*" << toY << "-" << toM << "-" << toD << "*\n";
		}
		else {
			myS << line<<"\n";
		}
		i++;
	}
	myS.close();
	strm.close();
	if (remove("rooms.txt") != 0) {
		cout << "Cant delete file." << endl;
	}
	if (rename("rooms1.txt", "rooms.txt") != 0) {
		cout << "Cant rename files." << endl;
	}

}

void openF(string str) {
	str = removeFirstWord(str);
	cout << endl << str << endl;
	string fileName = firstWord(str);
	fstream myS;
	string line;
	int i = 0;
	myS.open(fileName);
	while (!myS.eof()) {
		getline(myS, line);
		lines[i] = line;
		cout << i + 1 << ". " << lines[i] << endl;
		i++;
	}
	myS.close();

	string inp;
	int addcounter = 0;
	do {
		cout << "1. remove a line\n 2. change a line\n 3. insert a line\n Close = exit open function.\n";
	
		getline(cin, inp);
		int ins = strToInt(inp);
		if (ins == 1) {
			int nrLine;
			cout << "Enter the number of the line you want to remove.\n";
			cin >> nrLine;
			lines[nrLine - 1] = "";
		}
		else if (ins == 2) {
			int nrLine;
			cout << "Enter the number of the line you want to change.\n";
			cin >> nrLine;
			string change;
			cout << "Type the new line.\n";
			cin.ignore();
			getline(cin, change);
			cout << change << endl;
			lines[nrLine - 1] = change;
		}
		else if (ins == 3) {
			addcounter++;
			cout << "Enter the number of the line you want to insert after.\n";
			int nrLine;
			cin >> nrLine;
			if (nrLine > i + 1) {
				return;
			}
			string addline;
			cout << "Enter your line: ";
			cin.ignore();
			getline(cin, addline);
			for (int j = 0; j < i - nrLine + 1; j++) {
				lines[i - j + 1] = lines[i - j];
			}
			lines[nrLine] = addline;
		}
		else if (compareStr(firstWord(inp), "close") == 0) {
			for (int o = 0; o < 100; o++) {
				lines[o] = "";
				system("CLS");
				cout << "\nUse open again to access files.\n";
				return;
			}
		}
		else if (compareStr(firstWord(inp), "save") == 0) {
			myS.open("temp.txt", ios::out | ios::app);
			for (int k = 0; k < i + addcounter; k++) {
				int l = 0;
				if (lines[k] == "") {
					l++;
					continue;
				}
				lines[k - l] = lines[k];
				myS << lines[k] << endl;
			}
			myS.close();
			if (remove(fileName.c_str()) != 0) {
				cout << "Can't remove file.\n";
			}
			if (rename("temp.txt", fileName.c_str()) != 0) {
				cout << "Can't rename file.\n";

			}
		}
		else if (compareStr(firstWord(inp), "save as") == 0) {
			cout << "\n save as \n";
			string inp1 = removeFirstWord(removeFirstWord(inp));
			myS.open(inp1, ios::out | ios::app);
			for (int k = 0; k < i+addcounter; k++) {
				int l = 0;
				if (lines[k] == "") {
					l++;
					continue;
				}
				lines[k - l] = lines[k];
				myS << lines[k] << endl;
			}
			myS.close();
		}
		else if (compareStr(firstWord(inp), "help") == 0) {
			system("CLS");
			cout << "\n open <file>	opens <file> \nclose			closes currently opened file \nsave			saves the currently open file\nsave as <file>	saves the currently open file in <file> \nhelp			prints this information";
		}
		else if (compareStr(firstWord(inp), "exit") == 0) {
			exit(0);
		}
	} while (true);

}

string getLastLine(ifstream& in)
{
	string line;
	while (in >> ws && getline(in, line)); 
	cout << "line: " << line << endl;
	return line;
}

int Room::lastRoomId() {
	ifstream myFiles;
	myFiles.open("rooms.txt");
	if (iss_empty(myFiles)) {
		return 0;
	}
	else {
		int lastId = getId(getLastLine(myFiles));
		cout << lastId << endl;;
		return lastId;
	
	}
}
void Room::addRooms(int n) {
	ofstream myFile;
	
	Room room;
		room.roomId = lastRoomId() + 1;
		myFile.open("rooms.txt", ios::app);
		cin >> room.beds;
		room.takenBeds = 0;
		room.takenStatus = 0;
		room.note = "";
		room.fromDate = "";
		room.toDate = "";
		cout << "hi" << endl;
		myFile << room.roomId << "*" <<room.beds << "*" << room.takenBeds << "*" << room.takenStatus << "*" << room.note << "*" << room.fromDate << "*" << room.toDate << "*\n";
		myFile.close();

}

int main(){
	string d1 = "2020-05-21", d2 = "2020-06-13";
	string input;
	Room room;
	int n, i=0;
	//cin >> n;
	//room.addRooms(n);

	//ifstream strm;
	//string f;
	//strm.open("rooms.txt");
	//while (!strm.eof()) {
	//	getline(strm, f);
	//
	//	if (i == 6) {
	//		cout << "Beds:" <<  getBeds(f);
	//	}
	//	i++;
	//}
	//strm.close();


	do {
		cout << "Checkin, checkout, availability, report, find, find!, unavailable."<<endl;
		getline(cin, input);
		string firstW = firstWord(input);
		if (compareStr(firstW, "checkin") == 0) {
			checkin(input);
			
		}
		if (compareStr(firstW, "checkout") == 0) {
			checkout(input);
			
		}
		if (compareStr(firstW, "availability") == 0) {
			availability(input);

		}
		if (compareStr(firstW, "report") == 0) {
			report(input);

		}
		if (compareStr(firstW, "find") == 0) {
			find(input);

		}
		if (compareStr(firstW, "unavailable") == 0) {
			unavailable(input);

		}
		if (compareStr(firstW, "open") == 0) {
			openF(input);

		}

	} while (input != "exit");
	
	return 0;
}