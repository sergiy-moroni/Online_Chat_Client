#include "Chat.h"
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта

namespace fs = std::filesystem;
using namespace std;

int socket_file_descriptor, connection;
struct sockaddr_in serveraddress, client;
char TEXT_MESSAGE[MESSAGE_LENGTH];

Chat::Chat() {};
Chat::~Chat() {};

void Chat::start() {

	socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_file_descriptor == -1) {
		cout << "Creation of Socket failed!" << endl;
		exit(1);
	}
	// Установим адрес сервера
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	// Зададим номер порта
	serveraddress.sin_port = htons(PORT);
	// Используем IPv4
	serveraddress.sin_family = AF_INET;
	// Установим соединение с сервером
	connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	if (connection == -1) {
		cout << "Connection with the server failed.!" << endl;
		exit(1);
	}

	std::cout << "Welcome to Chat!" << std::endl;
	std::fstream user_file = std::fstream("user.txt", std::ios::in | std::ios::out);
	if (!user_file) 
		// Если файла нет, то создаем
		user_file = std::fstream("user.txt", std::ios::in | std::ios::out | std::ios::trunc);
	User obj;
	User objcnrl;
	user_file >> obj;
	while (true) {
		if (obj==objcnrl) { break; }
		objcnrl = obj;
		Userslist.push_back(obj);
		user_file >> obj;	
	}
	while (true)
	{
		std::cout << std::endl;
		std::cout << "Number of Reistered users: " << size(Userslist) << std::endl;
		std::cout << "Select an Action: \n1 - Enter.\n2 - New User Registration \n0 - Exit" << std::endl;
		int c;
		std::cin >> c;
		if (c != 0 && c != 2 && c != 1)
		{
			std::cout << "Invalid Input!" << std::endl;
			continue;
		}
		// регистрация нового пользователя
		if (c == 2)
		{
			CreateNewUser();
			continue;
		}
		if (c == 0) {
			break;
		}

		//вход по логину ипаролю
		if (c == 1)
		{
			std::string log;
			std::string pas;
			std::cout << "Login: ";
			std::cin >> log;
			std::cout << "Password: ";
			std::cin >> pas;
			if (FindUser(log, pas))
			{
				while (true)
				{
					inuser = true;
					std::cout << std::endl;
					//выбор пользователем желаемого действия
					std::cout << "Select an Action: " << std::endl;
					std::cout << "1 - Read Incoming Messages" << std::endl;
					std::cout << "2 - Write a message" << std::endl;
					std::cout << "0 - Exit" << std::endl;
					int c = 0;
					std::cin >> c;
					if (c == 0)
					{
						std::cout << "Good Bye, " << Userslist[user_islogin].GetName() << "!" << std::endl;
						break;
					}
					switch (c)
					{

					case 1:
							bzero(TEXT_MESSAGE, sizeof(TEXT_MESSAGE));
							read(socket_file_descriptor, TEXT_MESSAGE, sizeof(TEXT_MESSAGE));
							cout << "Received from " << TEXT_MESSAGE << endl;
						break;

					case 2:
								cout << "Enter the message you want to send: " << endl;
								bzero(TEXT_MESSAGE, sizeof(TEXT_MESSAGE));
								for (int i = 0; i < Userslist[user_islogin].GetName().length(); i++) {
									TEXT_MESSAGE[i] = Userslist[user_islogin].GetName()[i];
								}
								char TEXT[MESSAGE_LENGTH];
								cin.getline(TEXT, MESSAGE_LENGTH, '\n');
								cin.getline(TEXT, MESSAGE_LENGTH, '\n');
								
								
								TEXT_MESSAGE[Userslist[user_islogin].GetName().length()] = ':';
								TEXT_MESSAGE[Userslist[user_islogin].GetName().length()+1] = ' ';
								strcat(TEXT_MESSAGE, TEXT);
								
								ssize_t bytes = write(socket_file_descriptor, TEXT_MESSAGE, sizeof(TEXT_MESSAGE));
								if (bytes >= 0) {
									cout << "Data successfully sent!" << endl;
								}
						break;
					}
				}
			}
			else
			{
				inuser = false;
			}
		}
	}
}

bool Chat::FindUser(const std::string& login, const std::string& pass)
{
	int i = 0;
	bool j = false;

	for (auto it = Userslist.begin(); it != Userslist.end(); ++it)
	{
		std::string l = it->Getlog();
		std::string p = it->Getpass();
		if (login == l && pass == p)
		{
			std::cout << std::endl << "Hello, " << it->GetName() << "!" << std::endl << std::endl;
			user_islogin = i;
			j = true;
			return j;
		}
		else
		{
			i++;
		}
	}
	if (j == false) {
		std::cout << "\nIncorrect PASS or LOGIN!" << std::endl;
	}
	return j;
}

bool Chat::FindLogin(const std::string& login)
{
	
	for (auto it = Userslist.begin(); it != Userslist.end(); ++it)
	{
		if (it->Getlog() == login)
		{
			return true;
		}
	}return false;
}

//метод создания нового пользователя чата
void Chat::CreateNewUser()
{
	std::cout << "ENTER DATA FOR REGISTRATION: " << std::endl;
	std::cout << "Name: ";
	std::string name;
	std::string login;
	std::string pass;
	std::getline(std::cin, name, '\n');
	std::getline(std::cin, name, '\n');
	std::cout << "Login: ";
	bool l = true;
	while (l)
	{
		std::cin >> login;
		if (FindLogin(login))
		{
			std::cout << "Login is busy!" << std::endl;
			std::cout << "Login: ";
		}
		else
		{
			l = false;
		}
	}
	std::cout << "Password: ";
	std::cin >> pass;
	User U(name, login, pass);
	std::cout << "Welcome to Chat!" << std::endl;
	std::fstream user_file = std::fstream("user.txt", ios::in | ios::app);
	user_file << U;
	Userslist.push_back(U);
	std::cout << "User Registrated!" << std::endl << std::endl;
}

//метод возвращает номер пользователя в списке Userlist по имени
int Chat::FindUserinUserslist(const std::string& name)
{
	int index = 0;
	for (auto it = Userslist.begin(); it != Userslist.end(); ++it)
	{
		if (it->GetName() == name)
		{
			return index;
		}
		else
		{
			index++;
		}
	}
	return -1;
}
