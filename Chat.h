#pragma once
#include <vector>
#include "User.h"
#include <string>
#include <iostream>
#include <filesystem>

class Chat
{
private:

	std::vector<User> Userslist;//вектор хранит в себе зарегестрированных пользователей чата
	int user_islogin = 0;
	bool inuser = false; // состояние подключения пользователя к чату

public:
	
	Chat();
	~Chat();

	void start();

	//метод поиска пользователя среди зарегестрированных по логину и паролю
	bool FindUser(const std::string& login, const std::string& pass);

	//метод поиска зарегестрированный логин для защиты от повторной регистрации
	bool FindLogin(const std::string& login);

	//метод создания нового пользователя чата
	void CreateNewUser();

	//метод возвращает номер пользователя в списке Userlist по имени
	int FindUserinUserslist(const std::string& name);

};
