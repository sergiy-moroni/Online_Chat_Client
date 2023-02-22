#include "Message.h"
#include <iostream>
#include <string>

	Message::Message() : _sender(""), _reciever(""), _text("") {}
	Message::Message(const std::string& sender, const std::string text, const std::string& reciever) : _sender(sender), _text(text), _reciever(reciever) {}
	Message::~Message() {}

	void Message:: PrintM()
	{
		std::cout << "from " << _sender << ": " << _text << std::endl;
	}
	void Message::operator = (Message& other) {
		_sender = other._sender;
		_reciever = other._reciever;
		_text = other._text;
	}
	bool Message::operator ==(Message& other) {
		if (_sender == other._sender &&
			_reciever == other._reciever &&
			_text == other._text) {
			return true;
		}
		return false;

	}

	std::fstream& operator >> (std::fstream& is, Message& obj)
	{
		is >> obj._sender;
		is >> obj._reciever;
		std::getline(is, obj._text, '\n');
		//is >> obj._text;
		return is;
	}


	std::ostream& operator <<(std::ostream& os, const Message& obj)
	{
		os << obj._sender;
		os << ' ';
		os << obj._reciever;
		os << ' ';
		os << obj._text;
		os << std::endl;
		return os;
	}
