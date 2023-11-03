#include "BtcExchange.hpp"
#include <_ctype.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

BtcExchange::BtcExchange() {}

BtcExchange::BtcExchange(const BtcExchange& object) { *this = object; }

BtcExchange& BtcExchange::operator=(const BtcExchange& object) {
	if (this != &object) {
		return *this;
	}
	return *this;
}

BtcExchange::~BtcExchange() {}

const std::map<std::string, float>& BtcExchange::getBtcDB() const { return _bitcoinDB; }

bool BtcExchange::validateDate(std::string dateString) {
	if (dateString.length() != 10) {
		return false;
	}

	std::istringstream dateStream(dateString);
	std::string date;

	std::getline(dateStream, date, '-');
	int year;
	std::istringstream(date) >> year;
	if (year < 1000 || year > 2023) {
		return false;
	}

	std::getline(dateStream, date, '-');
	int month;
	std::istringstream(date) >> month;
	if (month < 1 || month > 12) {
		return false;
	}

	std::getline(dateStream, date, '-');
	int day;
	std::istringstream(date) >> day;
	if (day < 1 || day > 31 ||
		((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)) {
		return false;
	}
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
		if (month == 2 && day > 29) {
			return false;
		}
	}
	else {
		if (month == 2 && day > 28) {
			return false;
		}
	}

	if (dateStream.eof() == false) {
		return false;
	}
	return true;
}

bool BtcExchange::validateValue(std::string value) {
	char *ptr = NULL;
	double d_value = std::strtod(value.c_str(), &ptr);
	if ((d_value == 0.0 && !std::isdigit(value[0])) ||
		(*ptr != '\0' && std::strcmp(ptr, "f"))) {
		return false;
	}
	if (d_value < 0) {
		return false;
	}
	return true;
}

void BtcExchange::openCsvFile() {
	std::ifstream infile;
	infile.open("data.csv");
	if (infile.is_open() == false) {
		throw OpenFileException();
	}
	std::string buffer;
	if (std::getline(infile, buffer).eof() == true) {
		throw EmptyFileException();
	}
	if (buffer != "date,exchange_rate") {
		throw FileFormatException();
	}
	while (std::getline(infile, buffer).eof() == false) {
		std::string date = buffer.substr(0, buffer.find(','));
		if (validateDate(date) == false) {
			throw InvalidDateException();
		}
		std::string exchangeRate = buffer.substr(buffer.find(',') + 1, buffer.length());
		if (validateValue(exchangeRate) == false) {
			throw InvalidInputException();
		}
		float value;
		std::istringstream(exchangeRate) >> value;
		_bitcoinDB.insert(std::make_pair(date, value));
	}
	infile.close();
}

void BtcExchange::openInputFile(char *fpath) {
	std::ifstream infile;

	infile.open(fpath);
	if (infile.is_open() == false) {
		throw OpenFileException();
	}
	std::string buffer;
	if (std::getline(infile, buffer).eof() == true) {
		throw EmptyFileException();
	}
	if (buffer != "date | value") {
		throw FileFormatException();
	}
	while (std::getline(infile, buffer).eof() == false) {
		std::string date;
		float value;
	}
}

const char *BtcExchange::OpenFileException::what() const throw() { return "Error: Failed to open file."; }

const char *BtcExchange::EmptyFileException::what() const throw() { return "Error: No data in file."; }

const char *BtcExchange::FileFormatException::what() const throw() { return "Error: Invalid file format."; }

const char *BtcExchange::InvalidDateException::what() const throw() { return "Error: ."; }

const char *BtcExchange::InvalidInputException::what() const throw() { return "Error: ."; }

const char *BtcExchange::ExchangeRateException::what() const throw() { return "Error: ."; }
