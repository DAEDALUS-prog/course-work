#pragma once
#include <iomanip>
#include <windows.h>
#include <string>
#include <conio.h>
#include <fstream>


std::string const fileNameStudentsData = "studentsDATA.txt";
std::string const fileNameLoginData = "loginDATA.txt";


struct LoginData {
	int id;
	std::string login;
	std::string password;
	int role;
};

struct DataBirth {
	int day;
	int month;
	int year;
};

struct NameStudent {
	std::string lastName;
	std::string firstName;
	std::string patronymic;
};

struct NameParent {
	std::string lastName;
	std::string firstName;
	std::string patronymic;
};

struct Student {
	int id;
	std::string nameSection;
	NameStudent nameStudent;
	DataBirth birth;
	NameParent nameParent;
	int contactNumber;
	int costInMonth;
	int costDebt;
	int role;
};

void showListMenu();
void showStudentsList(Student* students);
void showLoginDataStudents(LoginData* loginData, Student* students);
void showContinueMessage();