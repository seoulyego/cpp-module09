#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>

class BitcoinExchange {
	public:
		static const std::map<std::string, float>& getBtcDB();

		static bool validateDate(std::string date);
		static bool validateValue(std::string value);
		static void openCsvFile();
		static bool validateInput(std::string inputStr);
		static void openInputFile(char *fpath);

		static std::string errorMessage(std::string inputStr);
		static std::string badInputErrorMessage(std::string inputStr);
		static std::string badFormatErrorMessage(std::string inputStr);

		class OpenFileException : public std::exception {
			public:
				const char *what() const throw();
		};
		class EmptyDataException : public std::exception {
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
		class InvalidDateException : public std::exception {
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

	private:
		static std::map<std::string, float> _bitcoinDB;

		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& object);
		BitcoinExchange& operator=(const BitcoinExchange& object);
		~BitcoinExchange();
};

#endif  // BITCOINEXCHANGE_HPP
