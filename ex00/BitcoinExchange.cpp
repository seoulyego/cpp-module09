#include "BitcoinExchange.hpp"
#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>

std::map<std::string, float> BitcoinExchange::_bitcoinDB;

const std::map<std::string, float>& BitcoinExchange::getBtcDB() { return BitcoinExchange::_bitcoinDB; }

bool BitcoinExchange::validateDate(std::string dateStr) {
	if (dateStr.length() != 10)
		return false;

	std::istringstream dateStream(dateStr);
	std::string date;

	int year;
	int month;
	int day;
	for (int i = 0; i < 3; i++) {
		std::getline(dateStream, date, '-');
		switch (i) {
			case 0:
				std::istringstream(date) >> year;
				break ;
			case 1:
				std::istringstream(date) >> month;
				break ;
			case 2:
				std::istringstream(date) >> day;
		}
	}

	if (year < 1000 || year > 2023)
		return false;
	if (month < 1 || month > 12)
		return false;
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
		throw EmptyDataException();
	if (buffer != "date,exchange_rate")
		throw BadFormatException(buffer);
	while (std::getline(infile, buffer).eof() == false) {
		int year;
		int month;
		int day;
		float rate;
		if (std::sscanf(buffer.c_str(), "%d-%d-%d,%f", &year, &month, &day, &rate) != 4) {
			throw BadFormatException(buffer);
		}
		std::string date = buffer.substr(0, buffer.find(','));
		if (validateDate(date) == false)
			throw BadFormatException(buffer);
		std::string inputStr = buffer.substr(buffer.find(',') + 1);
		if (validateValue(inputStr) == false)
			throw BadFormatException(buffer);
		_bitcoinDB.insert(std::pair<std::string, float>(date, rate));
	}
	if (_bitcoinDB.empty())
		throw EmptyDataException();
	infile.close();
}

void BitcoinExchange::openInputFile(char *fpath) {
	std::ifstream infile;
	infile.open(fpath);
	if (infile.is_open() == false)
		throw OpenFileException();

	std::string buffer;
	if (std::getline(infile, buffer).eof() == true)
		throw EmptyDataException();
	if (buffer != "date | value")
		throw BadFormatException(buffer);
	const std::string delim = " | ";
	while (std::getline(infile, buffer).eof() == false) {
		int year;
		int month;
		int day;
		float value;
		if (std::sscanf(buffer.c_str(), "%d-%d-%d | %f", &year, &month, &day, &value) != 4) {
			std::cout <<  badInputErrorMessage(buffer) << std::endl;
			continue;
		}
		std::string date = buffer.substr(0, buffer.find(delim));
		if (validateDate(date) == false) {
			std::cout <<  badInputErrorMessage(date) << std::endl;
			continue;
		}
		std::string valueStr = buffer.substr(buffer.find(delim) + delim.length());
		if (validateValue(valueStr) == false) {
			std::cout <<  badInputErrorMessage(buffer) << std::endl;
			continue;
		}
		value = std::strtof(valueStr.c_str(), NULL);
		std::map<std::string, float>::iterator iter = _bitcoinDB.lower_bound(date);
		if (iter == _bitcoinDB.begin() && iter->first != date) {
			std::cout << "no data" << std::endl;
			continue ;
		}
		else if (iter == _bitcoinDB.end() || iter->first != date)
			iter--;
		std::cout << date << " => " << value << " = " << value * iter->second << std::endl;
	}
}

std::string BitcoinExchange::errorMessage(std::string inputStr) {
	return "Error: " + inputStr;
}

std::string BitcoinExchange::badInputErrorMessage(std::string inputStr) {
	return "Error: Bad input => " + inputStr;
}

std::string BitcoinExchange::badFormatErrorMessage(std::string inputStr) {
	return "Error: Bad format data => " + inputStr;
}

const char *BitcoinExchange::OpenFileException::what() const throw() { return "Error: Could not open file."; }

const char *BitcoinExchange::EmptyDataException::what() const throw() { return "Error: No data in file."; }

BitcoinExchange::BadFormatException::BadFormatException(const std::string& inputStr) { _message = "Error: Bad format data => " + inputStr; }

BitcoinExchange::BadFormatException::~BadFormatException() throw() {}

const char *BitcoinExchange::BadFormatException::what() const throw() { return _message.c_str(); }

const char *BitcoinExchange::NegativeNumberException::what() const throw() { return "Error: Not a positive number."; }

const char *BitcoinExchange::TooLargeNumberException::what() const throw() { return "Error: Too large number."; }
