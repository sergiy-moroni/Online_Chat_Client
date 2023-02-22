#pragma once
#include <iostream>
#include <fstream>
struct Message 
{
	std::string _sender;
	std::string _reciever;
	std::string _text;
	Message();
	Message(const std::string& sender, const std::string text, const std::string& reciever);
	~Message();
	void PrintM();
	void operator = (Message& other);
	bool operator ==(Message& other);
	friend std::fstream& operator >>(std::fstream& is, Message& obj);
	friend std::ostream& operator <<(std::ostream& os, const Message& obj);
};
