#pragma once
#include <vector>
#include "Message.h"
#include <fstream>

class User
{
private:
	std::string _name;
	std::string _login;
	std::string _pass;
	std::vector<Message> _messages;

public:
	User() :_name(""), _login(""), _pass(""){}
	User(const std::string& name, const std::string& login,const std::string& pass);
	virtual ~User();
	std::string GetName();
	void SetName(const std::string& name);
	std::string Getpass();
	std::string Getlog();
	bool IsEmpty(); // получение наличия сообщений
	void Setmessage(const Message& message); //получение сообщения 
	void PrintMessages();	// чтение сообщений 
	friend std::fstream& operator >>(std::fstream& is, User& obj);
	friend std::ostream& operator <<(std::ostream& os, const User& obj);
	bool operator ==(User& other) {
		if (_login == other.Getlog()) { return true; }
		return false;
	}
	void operator = (User& other) {
		_name = other.GetName();
		_login = other.Getlog();
		_pass = other.Getpass();
	}

	void addmessages();
};
