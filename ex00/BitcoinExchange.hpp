#ifndef BTCEXCHANGE_HPP
# define BTCEXCHANGE_HPP

# include <string>
# include <map>
# include <stdexcept>

class BitcoinExchange {
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& object);
		BitcoinExchange& operator=(const BitcoinExchange& object);
		~BitcoinExchange();

		const std::map<std::string, float>& getBtcDB() const;

		bool validateDate(std::string date);
		bool validateValue(std::string value);
		void openCsvFile();
		bool validateInput(std::string inputStr);
		void openInputFile(char *fpath);

		class OpenFileException : public std::exception {
			public:
				const char *what() const throw();
		};
		class EmptyFileException : public std::exception {
			public:
				const char *what() const throw();
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
		std::map<std::string, float> _bitcoinDB;
};

#endif  // BTCEXCHANGE_HPP
