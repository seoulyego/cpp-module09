#include "BitcoinExchange.hpp"
#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

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
	return true;
}

void BitcoinExchange::checkCsvBuffer(const std::string& buffer, const std::string& delim, std::pair<std::string, float> *dataPair) {
	int year;
	int month;
	int day;
	if (std::sscanf(buffer.c_str(), "%d-%d-%d,%f", &year, &month, &day, &dataPair->second) != 4)
		throw BadFormatException(buffer);
	dataPair->first = buffer.substr(0, buffer.find(delim));
	if (validateDate(dataPair->first) == false)
		throw BadFormatException(buffer);
	std::string inputStr = buffer.substr(buffer.find(delim) + delim.length());
	if (validateValue(inputStr) == false)
		throw BadFormatException(buffer);
	if (dataPair->second < 0)
		throw BadFormatException(buffer);
}

void BitcoinExchange::loadCsv() {
	std::ifstream infile;
	infile.open("data.csv");
	if (infile.is_open() == false)
		throw OpenFileException();
	std::string buffer;
	if (std::getline(infile, buffer).eof() == true)
		throw EmptyDataException();
	if (buffer != "date,exchange_rate")
		throw BadFormatException(buffer);
	const std::string delim = ",";
	while (std::getline(infile, buffer).eof() == false) {
		std::pair<std::string, float> dataPair;
		checkCsvBuffer(buffer, delim, &dataPair);
		_bitcoinDB.insert(dataPair);
	}
	if (_bitcoinDB.empty())
		throw EmptyDataException();
	infile.close();
}

void BitcoinExchange::checkInputBuffer(const std::string& buffer, const std::string& delim, std::pair<std::string, float> *inputPair) {
	int year;
	int month;
	int day;
	if (std::sscanf(buffer.c_str(), "%d-%d-%d | %f", &year, &month, &day, &inputPair->second) != 4)
		throw BadInputException(buffer);
	inputPair->first = buffer.substr(0, buffer.find(delim));
	if (validateDate(inputPair->first) == false)
		throw BadInputException(buffer);
	std::string valueStr = buffer.substr(buffer.find(delim) + delim.length());
	if (validateValue(valueStr) == false)
		throw BadInputException(buffer);
	if (inputPair->second < 0)
		throw NegativeNumberException();
	if (inputPair->second > 1000)
		throw TooLargeNumberException();
}

void BitcoinExchange::processInputFile(char *fpath) {
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
		try {
			std::pair<std::string, float> inputPair;
			checkInputBuffer(buffer, delim, &inputPair);
			printBitcoin(inputPair);
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			continue ;
		}
	}
}

void BitcoinExchange::printBitcoin(std::pair<std::string, float> inputPair) {
	std::map<std::string, float>::iterator iter = _bitcoinDB.lower_bound(inputPair.first);
	if (iter == _bitcoinDB.begin() && iter->first != inputPair.first)
		throw UnsupportedDataException();
	else if (iter == _bitcoinDB.end() || iter->first != inputPair.first)
		iter--;
	std::cout << inputPair.first << " => " << inputPair.second << " = " << inputPair.second * iter->second << std::endl;
}

std::string BitcoinExchange::generalErrorMessage(const std::string& inputStr) {
	return "Error: " + inputStr;
}

const char *BitcoinExchange::OpenFileException::what() const throw() { return "Error: Could not open file."; }

const char *BitcoinExchange::EmptyDataException::what() const throw() { return "Error: No data in file."; }

const char *BitcoinExchange::NegativeNumberException::what() const throw() { return "Error: Not a positive number."; }

const char *BitcoinExchange::TooLargeNumberException::what() const throw() { return "Error: Too large a number."; }

const char *BitcoinExchange::UnsupportedDataException::what() const throw() { return "Unsupported Date."; }

BitcoinExchange::BadFormatException::BadFormatException(const std::string& inputStr) { _message = "Error: Bad format data => " + inputStr; }

BitcoinExchange::BadFormatException::~BadFormatException() throw() {}

const char *BitcoinExchange::BadFormatException::what() const throw() { return _message.c_str(); }

BitcoinExchange::BadInputException::BadInputException(const std::string& inputStr) { _message = "Error: Bad input => " + inputStr; }

BitcoinExchange::BadInputException::~BadInputException() throw() {}

const char *BitcoinExchange::BadInputException::what() const throw() { return _message.c_str(); }
