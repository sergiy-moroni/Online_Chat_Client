#include "User.h"

User::User(const std::string& name, const  std::string& login, const  std::string& pass) :
	_name(name), _login(login), _pass(pass){}

User::~User() {}
std::string User::GetName()
{
	return _name;
}
void User::SetName(const std::string& name) 
{
	_name = name;
}
std::string User::Getpass() 
{
	return _pass;
}
std::string User::Getlog() 
{
	return _login;
}

//получение наличия сообщений
bool User::IsEmpty() 
{
	bool i = true;
	if (size(_messages) > 0)
	{
		i = false;
	}
	return i;
}

//получение сообщения 
void User::Setmessage(const Message& message)
{
	_messages.push_back(message);
}

// чтение сообщений 
void User::PrintMessages()
{
	std::cout << std::endl;
	for (int i = 0; i < size(_messages); ++i)
	{
		_messages[i].PrintM();
	}
	std::cout << std::endl;
}

std::fstream& operator >>(std::fstream& is, User& obj)
{
	is >> obj._name;
	is >> obj._login;
	is >> obj._pass;
	return is;
}

std::ostream& operator <<(std::ostream& os, const User& obj)
{
	os << obj._name;
	os << ' ';
	os << obj._login;
	os << ' ';
	os << obj._pass;
	os << std::endl;
	return os;
}

void User::addmessages() {

	std::fstream user_file2 = std::fstream("Messages.txt", std::ios::in);

	Message obj;
	Message objcnrl;
	user_file2 >> obj;
	while (true) {
		if (obj == objcnrl) { break; }
		objcnrl = obj;
		if (obj._reciever == _name || obj._reciever == "all") {
		_messages.push_back(obj);
		}
		user_file2 >> obj;
	}
}
