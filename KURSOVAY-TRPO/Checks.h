#pragma once

int inputCorrectInt();
std::string inputCorrectString();
bool checkExistsDataBaseLoginData();
bool checkExistsFileDataStudents();
bool checkSignInDataStudents(std::string login, std::string password, int& role);
bool checkIsUser(int id);
