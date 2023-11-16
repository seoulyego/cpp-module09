#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>
#include <utility>

class BitcoinExchange {
	public:
		static const std::map<std::string, float>& getBtcDB();

		static bool validateDate(std::string date);
		static bool validateValue(std::string value);
		static void checkCsvBuffer(const std::string& buffer, const std::string& delim, std::pair<std::string, float> *dataPair);
		static void loadCsv();
		static void checkInputBuffer(const std::string& buffer, const std::string& delim, std::pair<std::string, float> *inputPair);
		static void printBitcoin(std::pair<std::string, float> inputPair);
		static void processInputFile(char *fpath);

		static std::string generalErrorMessage(const std::string& message);

		class OpenFileException : public std::exception {
			public:
				const char *what() const throw();
		};
		class EmptyDataException : public std::exception {
			public:
				const char *what() const throw();
		};
		class NegativeNumberException : public std::exception {
			public:
				const char *what() const throw();
		};
		class TooLargeNumberException : public std::exception {
			public:
				const char *what() const throw();
		};
		class UnsupportedDataException : public std::exception {
			public:
				const char *what() const throw();
		};
		class BadFormatException : public std::exception {
			public:
				BadFormatException(const std::string& inputStr);
				~BadFormatException() throw();

				const char *what() const throw();

			private:
				std::string _message;

				BadFormatException();
		};
		class BadInputException : public std::exception {
			public:
				BadInputException(const std::string& inputStr);
				~BadInputException() throw();

				const char *what() const throw();

			private:
				std::string _message;

				BadInputException();
		};

	private:
		static std::map<std::string, float> _bitcoinDB;

		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& object);
		BitcoinExchange& operator=(const BitcoinExchange& object);
		~BitcoinExchange();
};

#endif  // BITCOINEXCHANGE_HPP
