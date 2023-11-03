#include "BitcoinExchange.hpp"
#include <_ctype.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <utility>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& object) { *this = object; }

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& object) {
	if (this != &object)
		return *this;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

const std::map<std::string, float>& BitcoinExchange::getBtcDB() const { return _bitcoinDB; }

bool BitcoinExchange::validateDate(std::string dateStr) {
	if (dateStr.length() != 10)
		return false;

	std::istringstream dateStream(dateStr);
	std::string date;

	std::getline(dateStream, date, '-');
	int year;
	std::istringstream(date) >> year;
	if (year < 1000 || year > 2023)
		return false;

	std::getline(dateStream, date, '-');
	int month;
	std::istringstream(date) >> month;
	if (month < 1 || month > 12)
		return false;

	std::getline(dateStream, date, '-');
	int day;
	std::istringstream(date) >> day;
	if (day < 1 || day > 31 ||
		((month == 4 || month == 6 || month == 9 || month == 11) && day == 31))
		return false;
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
		if (month == 2 && day > 29)
			return false;
	}
	else {
		if (month == 2 && day > 28)
			return false;
	}

	if (dateStream.eof() == false)
		return false;
	return true;
}

bool BitcoinExchange::validateValue(std::string value) {
	char *ptr = NULL;
	double d_value = std::strtod(value.c_str(), &ptr);
	if ((d_value == 0.0 && !std::isdigit(value[0])) ||
		(*ptr != '\0' && std::strcmp(ptr, "f")))
		return false;
	if (d_value < 0)
		return false;
	return true;
}

void BitcoinExchange::openCsvFile() {
	std::ifstream infile;
	infile.open("data.csv");
	if (infile.is_open() == false)
		throw OpenFileException();
	std::string buffer;
	if (std::getline(infile, buffer).eof() == true)
		throw EmptyFileException();
	if (buffer != "date,exchange_rate")
		throw BadInputException(buffer);
	while (std::getline(infile, buffer).eof() == false) {
		int year;
		int month;
		int day;
		float rate;
		if (std::sscanf(buffer.c_str(), "%d-%d-%d,%f", &year, &month, &day, &rate) != 4)
			throw BadInputException(buffer);
		std::string date = buffer.substr(0, buffer.find(','));
		if (validateDate(date) == false)
			throw BadInputException(buffer);
		std::string inputStr = buffer.substr(buffer.find(',') + 1);
		if (validateValue(inputStr) == false)
			throw BadInputException(buffer);
		_bitcoinDB.insert(std::pair<std::string, float>(date, rate));
	}
	infile.close();
}

void BitcoinExchange::openInputFile(char *fpath) {
	std::ifstream infile;
	infile.open(fpath);
	if (infile.is_open() == false)
		throw OpenFileException();

	std::string buffer;
	if (std::getline(infile, buffer).eof() == true)
		throw EmptyFileException();
	if (buffer != "date | value")
		throw BadInputException(buffer);
	const std::string delim = " | ";
	while (std::getline(infile, buffer).eof() == false) {
		int year;
		int month;
		int day;
		float value;
		if (std::sscanf(buffer.c_str(), "%d-%d-%d | %f", &year, &month, &day, &value))
			throw BadInputException(buffer);
		std::string date = buffer.substr(0, buffer.find(delim));
		if (validateDate(date) == false)
			throw BadInputException(date);
		std::string valueStr = buffer.substr(buffer.find(delim) + delim.length());
		if (validateValue(valueStr) == false)
			throw BadInputException(buffer);
		value = std::strtof(valueStr.c_str(), NULL);
		std::map<std::string, float>::iterator iter = _bitcoinDB.lower_bound(date);
		if (iter == _bitcoinDB.begin() && iter->first != date)
			throw ;
		else if (iter == _bitcoinDB.end())
			iter--;
		std::cout << date << " => " << value << " = " << value * iter->second << std::endl;
	}
}

const char *BitcoinExchange::OpenFileException::what() const throw() { return "Error: Could not open file."; }

const char *BitcoinExchange::EmptyFileException::what() const throw() { return "Error: No data in file."; }

BitcoinExchange::BadInputException::BadInputException(const std::string& inputStr) { _message = "Error: Bad input => " + inputStr; }

BitcoinExchange::BadInputException::~BadInputException() throw() {}

const char *BitcoinExchange::BadInputException::what() const throw() { return _message.c_str(); }

const char *BitcoinExchange::NegativeNumberException::what() const throw() { return "Error: Not a positive number."; }

const char *BitcoinExchange::TooLargeNumberException::what() const throw() { return "Error: Too large number."; }
