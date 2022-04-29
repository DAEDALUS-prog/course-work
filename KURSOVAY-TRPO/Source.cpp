#include <iostream>

#include "ShowData.h"
#include "Modes.h"
#include "Checks.h"
#include "ActionArray.h"
#include "Authorization.h"
#include "DataBase.h"
#include "Calculates.h"

#define _CRT_SECURE_NO_WARNINGS


enum Action {
	Exit,
	SignIn,
	SignUp,
	AboutProgramm,
};

enum AdminMenu {
	Pass,
	Accounts,
	Data,

};

enum UserMenu {
	Pass1,
	ShowData,
	PersonTask,
	Search,
	Sort,
};

enum RoleStatus {
	User,
	Admin,
};


int main()
{
	setlocale(LC_ALL, "Russian");
	std::ofstream fout;
	
	if (!(checkExistsDataBaseLoginData())) fout.open(fileNameLoginData);
	if (!(checkExistsFileDataStudents())) fout.open(fileNameStudentsData);

	
	Student* students = addExistsStudents();
	LoginData* loginData = addLoginStudents();


	int option{};
	do
	{
		showListMenu();
		option = inputCorrectInt();
		switch (option)
		{
		case Action::SignIn: {//in processing
			toSignIn(students, loginData);
			break;
		}
		case Action::SignUp: {
			toSignUp();
			break;
		}
		case Action::AboutProgramm: {
			std::cout << "Process... Reading Information about programm | " << std::endl;
			break;
		}
		case Exit: {
			std::cout << "Process... EXIT | " << std::endl;
			break;
		}
		}
		system("cls");
	} while (option != Exit);

	return 0;
}


void inletAdminMenu(Student* students, LoginData* loginData)
{
	system("cls");
	int option{};
	do
	{
		std::cout << "___Меню___\n1 | Учетные записи\n2 | Данные\n\n0 | Главное меню" << std::endl;
		option = inputCorrectInt();
		switch (option)
		{
		case Accounts: {
			inletAdminsLoginDataMenu(students, loginData);
			break;
		}
		case Data: {
			inletAdminsStudentsDataMenu(students);
			break;
		}
		}
		system("cls");
	} while (option != Exit);	
}


void inletAdminsLoginDataMenu(Student* students, LoginData* loginData)
{
	system("cls");

	int option{};
	do
	{
		std::cout << "___Меню___\n1 | Просмотр\n2 | Добавление\n3 | Редактирование\n4 | Удаление\n\n0 | Назад" << std::endl;
		std::cout << "(Для выхода в главное меню введите 'menu')" << std::endl;

		option = inputCorrectInt();
		switch (option)
		{
		case 1: {
			showLoginDataStudents(loginData, students);
			break;
		}
		case 2: {
			break;
		}
		case 3: {
			break;
		}
		case 4: {
			break;
		}
		}
		system("cls");
	} while (option != Exit);
}


void inletAdminsStudentsDataMenu(Student* students)
{
	system("cls");
	
	int option{};
	do
	{
		std::cout << "___Меню___\n1 | Режим редактирования\n2 | Режим обработки\n\n0 | Назад" << std::endl;
		std::cout << "(Для выхода в главное меню введите 'menu')" << std::endl;

		option = inputCorrectInt();
		switch (option)
		{
		case 1: {
			entryEditingMode(students);
			break;
		}
		case 2: {
			entryTreatmentMode(students);
			break;
		}
		}
		system("cls");
	} while (option != Exit);
}


void inletUserMenu(Student* students)
{
	system("cls");
	int option{};

	do
	{
		std::cout << "___Меню___\n1 | Просмотр\n2 | Индивидульное задание\n3 | Поиск\n4 | Сортировка\n\n0 | Главное меню" << std::endl;
		option = inputCorrectInt();
		switch (option)
		{
		case ShowData: {
			system("cls");
			showStudentsList(students);
			_getch();
			break;
		}
		case PersonTask: {
			//
			break;
		}
		case Search: {
			//
			break;
		}
		case Sort: {
			//
			break;
		}
		}
		system("cls");
	} while (option != Exit);
}


void showStudentsList(Student* students)
{
	
	int countStudents = calculateCountStudents();
	if (countStudents > 0)
	{

		std::cout << "\n" << std::endl;
		std::cout
			<< "ID" << std::setw(13) << "СЕКЦИЯ" << std::setw(18) << "Ф.И.О."
			<< std::setw(23) << "Дата Рождения" << std::setw(13) << "Родитель"
			<< std::setw(15) << "КОНТАКТ" << std::setw(10) << "ОПЛАТА" << std::setw(18) << "ЗАДОЛЖЕННОСТЬ\n" << std::endl;

		int countId = 0;
		for (int index = 0; index < countStudents; index++)
		{
			if (students[index].birth.year != 00) {
				countId++;
				std::cout
					<< countId << std::setw(13) << students[index].nameSection
					<< std::setw(13) << students[index].nameStudent.lastName << " " << students[index].nameStudent.firstName << " " << students[index].nameStudent.patronymic
					<< std::setw(10) << students[index].birth.day << "/" << students[index].birth.month << "/" << students[index].birth.year
					<< std::setw(10) << students[index].nameParent.lastName << " " << students[index].nameParent.firstName << " " << students[index].nameParent.patronymic
					<< std::setw(10) << students[index].contactNumber << std::setw(10) << students[index].costInMonth << std::setw(12) << students[index].costDebt
					<< std::endl;
				std::cout << "\n" << std::endl;

			}
		}
		showContinueMessage();
	}
	else {
		std::cout << "Ни одного студента не добавлено!" << std::endl;
		showContinueMessage();
	}
}


Student* addExistsStudents()
{
	std::ifstream fin(fileNameStudentsData);

	int countStudents = calculateCountStudents();
	Student* students = new Student[countStudents];

	int index = 0;
	while (index < countStudents)
	{
		fin >> students[index].id;
		fin >> students[index].nameSection;

		fin >> students[index].nameStudent.lastName;
		fin >> students[index].nameStudent.firstName;
		fin >> students[index].nameStudent.patronymic;

		fin >> students[index].birth.day;
		fin >> students[index].birth.month;
		fin >> students[index].birth.year;

		fin >> students[index].nameParent.lastName;
		fin >> students[index].nameParent.firstName;
		fin >> students[index].nameParent.patronymic;

		fin >> students[index].contactNumber;

		fin >> students[index].costInMonth;
		fin >> students[index].costDebt;

		index++;
	}
	fin.close();

	return students;
}


LoginData* addLoginStudents()
{
	std::ifstream fin(fileNameLoginData);
	int countStudents = calculateCountStudents();

	LoginData* loginData = new LoginData[countStudents];

	int index = 0;


	while (index < countStudents)
	{
		fin >> loginData[index].id;
		fin >> loginData[index].login;
		fin >> loginData[index].password;
		fin >> loginData[index].role;

		index++;
	}
	fin.close();

	return loginData;
}


void entryEditingMode(Student* students)
{
	system("cls");
	int option{};

	do
	{
		std::cout << "___Меню___\n1 | Просмотр\n2 | Добавление\n3 | Редактирование\n4 | Удаление\n\n0 | Назад" << std::endl;
		std::cout << "(Для выхода в главное меню введите 'menu')\n\n";

		option = inputCorrectInt();
		switch (option)
		{
		case 1: {
			system("cls");
			showStudentsList(students);
			break;
		}
		case 2: {
			system("cls");
			addStudentToDataBase(students);
			break;
		}
		case 3: {
			//
			break;
		}
		case 4: {
			//
			break;
		}
		}
		system("cls");
	} while (option != Exit);
}


void addStudentToDataBase(Student* students)
{
	int index = calculateCountStudents();
	students = addArraysMemory(students);
	
	std::cout << "\t\tДобавление учащегося" << std::endl;

	std::cout << "Название секции\n> ";
	//students[index].nameSection = inputCorrectString();

	std::cout << "Фамилия учащегося\n> ";
	//students[index].nameStudent.lastName = inputCorrectString();

	std::cout << "Имя учащегося\n> ";
	//students[index].nameStudent.firstName = inputCorrectString();

	std::cout << "Отчество учащегося\n> ";
	//students[index].nameStudent.patronymic = inputCorrectString();

	std::cout << "Дата Дня Рождения учащегося\n(формат XX XX XXXX)\n> ";
	do {
		std::cout << "ДЕНЬ Рождения\n> ";
		students[index].birth.day = inputCorrectInt();
	} while (students[index].birth.day < 01 || students[index].birth.day > 31);

	do {
		std::cout << "МЕСЯЦ Рождения\n> ";
		students[index].birth.month = inputCorrectInt();
	} while (students[index].birth.month < 01 || students[index].birth.month > 12);

	int yearValue = getYearValue();
	std::cout << "ГОД -> " << yearValue << std::endl;
	do {
		std::cout << "ГОД Рождения \n> ";
		students[index].birth.year = inputCorrectInt();

	} while ((yearValue - students[index].birth.year) < 4 || (yearValue - students[index].birth.year) > 17);

	std::cout << "Фамилия родителя учащегося\n> ";
	students[index].nameParent.lastName = inputCorrectString();

	std::cout << "Имя родителя учащегося\n> ";
	students[index].nameParent.firstName = inputCorrectString();

	std::cout << "Отчество родителя учащегося\n> ";
	students[index].nameParent.patronymic = inputCorrectString();

	std::cout << "Контактный номер телефона\n(формат XXX XXX XXX)\n> ";
	students[index].contactNumber = inputCorrectInt();

	std::cout << "Стоимость обучения в месяц\n> ";
	students[index].costInMonth = inputCorrectInt();

	std::cout << "Сумма задолженности\n> ";
	students[index].costDebt = inputCorrectInt();
}

void entryTreatmentMode(Student* students)
{

}


void showLoginDataStudents(LoginData* loginData, Student* students)
{
	int countStudents = calculateCountStudents();
	if (countStudents > 0) 
	{
		std::cout << "\n" << std::endl;
		std::cout
			<< "ID" << std::setw(18)
			<< "LOGIN" << std::setw(23)
			<< "Ф.И.О." << std::setw(23)
			<< "Дата Рождения"
			<< std::endl;
		int countId = 1;
		for (int index = 0; index < countStudents; index++)
		{
			if (loginData[index].role == 0) {
				std::cout << countId << std::setw(18)
					<< loginData[index].login << std::setw(18)
					<< students[index].nameStudent.lastName << " " << students[index].nameStudent.firstName << " " << students[index].nameStudent.patronymic << std::setw(10)
					<< students[index].birth.day << "." << students[index].birth.month << "." << students[index].birth.year << std::endl;
				countId++;
			}
		}
	}
	else {
		std::cout << "В списке нет записей!" << std::endl;
		_getch();
	}
	_getch();
}


bool checkExistsDataBaseLoginData()
{
	std::ifstream fin;
	fin.open(fileNameLoginData);

	if (fin.is_open()) {
		fin.close();
		return true;
	}

	return false;
}


bool checkExistsFileDataStudents()
{
	std::ifstream fin;
	fin.open(fileNameStudentsData);

	if (fin.is_open()){
		fin.close();
		return true;
	}

	return false;
}


int calculateCountStudents()
{
	int count = 0;
	std::ifstream fin(fileNameStudentsData);
	std::string str;
	while (getline(fin, str)) count++;
	fin.close();
	
	return count;
}


void showListMenu()
{
	std::cout << "___Меню___" << std::endl;
	std::cout << "1 | Вход\n2 | Регистрация\n3 | О программе\n\n0 | Выход" << std::endl;
}


void showContinueMessage()
{
	std::cout << "Нажмите ENTER для продолжения.." << std::endl;
	_getch();
}


void toSignIn(Student* students, LoginData* loginData)
{
	system("cls");

	std::string login{}, password{};
	int role = -1;
	while (true)
	{
		system("cls");
		std::cout << "Вход | ЛОГИН\n(Для выхода в главное меню введите 'menu')\n\n> ";
 		std::cin >> login;
		system("cls");
		if (login == "menu") break;

		std::cout << "Вход | ПАРОЛЬ\n(Для выхода в главное меню введите 'menu')\n\n> ";
		std::cin >> password;
		system("cls");
		if (password == "menu") break;
		
		bool resultSignIn = checkSignInDataStudents(login, password, role);
		if (resultSignIn) {
			std::cout << "Вход успешно выполнен!" << std::endl;
			showContinueMessage();
			break;
		}
		else {
			std::cout << "Неверный логин или пароль!" << std::endl;
			showContinueMessage();
		}
	}

	switch (role) {
	case RoleStatus::User: {
		inletUserMenu(students);
		break;
	}
	case RoleStatus::Admin: {
		inletAdminMenu(students, loginData);
		break;
	}
	}
}


bool checkSignInDataStudents(std::string login, std::string password, int& role)
{
	std::ifstream fin("loginDATA.txt");

	std::string str;
	std::string checkLogin, checkPassword;
	int id;
	int checkRole{};
	while (getline(fin, str)) 
	{
		fin >> id >> checkLogin >> checkPassword >> checkRole;
		if (checkLogin == login && checkPassword == password) {
			role = checkRole;
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}


void toSignUp()
{
	system("cls");

	std::string login{}, password{};
	while (true)
	{
		std::cout << "Регистрация | ЛОГИН\n(Для выхода в главное меню введите 'menu')\n\n> ";
		std::cin >> login;
		system("cls");
		if (login == "menu") break;

		std::cout << "Регистрация | ПАРОЛЬ\n(Для выхода в главное меню введите 'menu')\n\n> ";
		std::cin >> password;
		system("cls");
		if (password == "menu") break;

		writeToDataBase(login, password);
		std::cout << "Регистрация прошла успешно!" << std::endl;
		showContinueMessage();
		break;
	}
}


void writeToDataBase(std::string login, std::string password)
{
	std::ofstream fout;
	fout.open("loginDATA.txt", std::ios::app);
	int id = calculateCountStudents();
	fout << id << " " << login << " " << password << " 0" << "\n";
	fout.close();
}


//checkInputNumber()
int inputCorrectInt()
{
	int value;
	while (!(std::cout << "> ", std::cin >> value) or std::cin.get() != '\n')
	{
		std::cout << "\nValue must be INTEGER type!" << std::endl;
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	return value;
}


std::string inputCorrectString()
{
	std::string value;
	while (!(std::cout << "> ", std::cin >> value) or std::cin.get() != '\n')
	{
		std::cout << "\nValue must be STRING type!" << std::endl;
		std::cin.clear();
		while (std::cin.get() != '\n');
	}
	return value;
}


int getYearValue()
{
	struct tm newTime{};
	return 1970 + newTime.tm_year;
}


Student* addArraysMemory(Student* students) {
	int countStudents = calculateCountStudents();

	Student* newListStudents = new Student[countStudents + 1];
	newListStudents = students;
	delete[] students;

	return newListStudents;
}