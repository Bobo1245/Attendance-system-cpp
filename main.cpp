#include <cstdlib> 
#include <cstring> 
#include <ctime> 
#include <fstream> 
#include <iostream> 
#include <string> 

using namespace std; 

	void mainmenu();
	void adminLogin(); 
	void adminMenu();
	void addStudent();
	int isfileexist(string); 
	void attendencelist();
	void attendenceStatus(string); 
	void markAttendence();
	void studentlogin(); 

int isfileexist(string filename) 
{ 
	fstream f; 
	f.open(filename, ios::in); 
	if (f) { 
		f.close(); 
		return 0; 
	} 
	f.close(); 
	return 1; 
} 

void addStudent() {
	system("cls");
	int year, month, day, pa; 
	string matricNumber, name; 
	cout << "Add New Student" << endl;
	cout << "Enter Student ID Number: ";
	cin >> matricNumber; 
	cout << "Enter Student Name: ";
	cin >> name; 
	string filename = matricNumber + ".txt"; 
	time_t now = time(0); 
	tm* ltm = localtime(&now); 
	year = ltm->tm_year + 1900; 
	month = ltm->tm_mon + 1; 
	day = ltm->tm_mday; 
	pa = 2; 
	if (!isfileexist(filename)) { 
		cout << "\nStudent already enrolled\n"; 
 	} 
	else { 
		fstream seperatef, commonf, matricNumberf; 
		seperatef.open(filename, ios::out); 
		seperatef << matricNumber << "\t" << name << "\t" << pa << "\t" << day << "\t" << month << "\t" << year << "\n"; 
		commonf.open("studentlist.txt", ios::app); 
		commonf << matricNumber << "\t" << name << "\n"; 
		matricNumberf.open("matricNumberFile.txt", ios::app); 
		matricNumberf << matricNumber << "\n"; 
		commonf.close(); 
		matricNumberf.close(); 
		seperatef.close(); 
		cout << "\nStudent successfully Added!\n"; 
	} 
}



void attendencelist() { 
	string matricNumber, name; 
	int totaldays = 0, p = 0, a = 0, flag = 0, pa, day, 
		month, year; 
	float per = 0.0; 
	fstream sepf, matricNumberf; 
	matricNumberf.open("matricNumberFile.txt", ios::in); 
	system("cls");
	cout << "Attendance Details" << endl;
	while (matricNumberf >> matricNumber) { 
		flag = 0; 
		p = 0; 
		a = 0; 
		per = 0; 
		totaldays = 0; 
		matricNumber = matricNumber + ".txt"; 
		sepf.open(matricNumber, ios::in); 
		while (sepf >> matricNumber >> name >> pa >> day >> month 
			>> year) { 
			if (flag == 0) { 
				cout << "\nMatric Number:" << matricNumber << "\t" << "Name: " << name << endl; 
				flag = 1; 
				continue; 
			} 
			totaldays++; 
			if (pa == 1) 
				p++; 
			else
				a++; 
		} 
		sepf.close(); 
		per = ((float)p / totaldays) * 100; 
		cout << "Present:" << p << "\tAbsent:" << a  << "\tAttendance percentage:" << per << endl; 
	} 
		system("pause");

	matricNumberf.close(); 
} 



// function to check attendence status 
void attendenceStatus(string filename) 
{ 
	fstream f, matricNumberfile; 
	string matricNumber, name, matricNumberfilename; 
	int pa, day, month, year, pcount, acount, 
		totaldays = 0, p = 0, a = 0, flag = 0; 
	float per = 0.0; 

	matricNumberfile.open(filename, ios::in); 
	while (matricNumberfile >> matricNumber >> name >> pa >> day >> month 
		>> year) { 
		if (flag == 0) { 
			cout << "\nName:" << name 
				<< "Matric Number:" << matricNumber << endl; 
			flag = 1; 
			continue; 
		} 
		totaldays++; 
		if (pa == 1) { 
			p++; 
			cout << day << "-" << month << "-" << year << "\tPresent\n"; 
		} 
		else { 
			a++; 
			cout << day << "-" << month << "-" << year << "\tAbsent\n"; 
		} 
	} 
	matricNumberfile.close(); 
	per = ((float)p / totaldays) * 100; 

	cout << "\n\nPresent:" << p << "\tAbsent:" << a << "\tAttendance percentage:" << per << endl; 
} 


// function to mark attendence with date 
void markAttendence() { 
	string filename, matricNumber, name; 
	int pa, day, month, year; 
	time_t now = time(0); 
	tm* ltm = localtime(&now); 
	year = ltm->tm_year + 1900; 
	month = ltm->tm_mon + 1; 
	day = ltm->tm_mday; 
	system("cls");
	cout << "\nEnter 1 for present and 0 for absent\n\n"; 
	fstream sfile, matricNumberfile; 
	sfile.open("studentlist.txt", ios::in); 

	while (sfile >> matricNumber >> name) { 
		filename = matricNumber + ".txt"; 
		matricNumberfile.open(filename, ios::app); 
		cout << "Matric Number: " << matricNumber << "  Name: " << name << "\t"; 
		cin >> pa; 
		matricNumberfile << matricNumber << "\t" << name << "\t" << pa << "\t" << day << "\t" << month << "\t" << year << "\n"; 
		matricNumberfile.close(); 
	} 

	cout << "\nAll attendance marked\n"; 
	sfile.close(); 
} 


void adminLogin() { 
	int success_flag = 0; 
	cout << "\n--- ADMIN LOGIN ---\n"; 
	string username; 
	string password; 
	cout << "\nEnter username : "; 
	cin >> username; 
	cout << "\nEnter password : "; 
	cin >> password; 
	if (username == "admin" && password == "123456") { 
		cout << "\nLogin successful!!!\n"; 
		success_flag = 1; 
		adminMenu(); 
	} 

	// if login is failed. 
	if (success_flag == 0) { 
		cout << "\n! Invalid Credentials. Please Try Again\n"; 
	} 
} 





void adminMenu() { 
	int choice;
	char x; 
	for (;;) { 
	system("cls");
		cout << "------- ADMIN MENU ------" << endl; 
		cout << "1. Mark attendance" << endl;
		cout << "2. Add students" << endl;
		cout << "3. Student attendance list" << endl;
		cout << "4. Main menu " << endl;
		cout << "0. Exit " << endl;
		cout << "Enter your choice: "; 
		cin >> choice; 
		switch (choice) { 
			case 0: 
				exit(0); 
			case 1: { 
				markAttendence();
				break; 
			}
			case 2: { 
				do {
					addStudent();
					cout << "Add Another [y/n]: ";
					cin >> x;
				} while (x == 'y');
				break; 
			} 
			case 3: { 
				attendencelist();
				break; 
			} 
			case 4: { 
				mainmenu(); 
				break; 
			} 
		} 
	} 
} 

void mainmenu() { 
	int choice; 
	while (1) { 
		system("cls");
		cout << "--- Welcome to Attendence Management System ---\n"; 
		cout << "1.Student login\n2.Admin "
				"login\n0.Exit\n\nEnter your choice: "; 
		cin >> choice; 
		switch (choice) { 
		case 0: 
			exit(0); 
		case 1: 
			studentlogin(); 
			break; 
		case 2: 
			adminLogin(); 
			break; 
		default: 
			cout << "Invalid Option! Pease Try Again.\n"; 
		} 
	} 
}

void studentlogin() { 
	string sname, matricNumber, fMatricNumber, fPassword; 
	int successf = 0; 
	system("cls");
	cout << "\n--- STUDENT LOGIN ---\n"; 
	cout << "\nEnter Matric Number : "; 
	cin >> matricNumber; 
	cout << "\nEnter Name : "; 
	cin >> sname; 
	string filename = matricNumber + ".txt"; 
	ifstream sflogin; 
	sflogin.open("studentlist.txt"); 
	while (sflogin >> fMatricNumber) { 
		if (matricNumber.compare(fMatricNumber) == 0 
			&& matricNumber.compare(fMatricNumber) == 0) { 
			successf = 1; 
			attendenceStatus(filename); 
			sflogin.close(); 
			break; 
		} 
	} 
	if (successf == 0) { 
		sflogin.close(); 
		cout << "\nError ! Invalid Credentials..\n"; 
	} 
		system("pause");
	sflogin.close(); 
} 


int main() {
	system("color f4");
	mainmenu();
	return 0;
}