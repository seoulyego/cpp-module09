#ifndef BTCEXCHANGE_HPP
# define BTCEXCHANGE_HPP

# include <stdexcept>
# include <map>

class BtcExchange {
	public:
		BtcExchange();
		BtcExchange(const BtcExchange& object);
		BtcExchange& operator=(const BtcExchange& object);
		~BtcExchange();

		const std::map<std::string, float>& getBtcDB() const;

		bool validateDate(std::string date);
		bool validateValue(std::string value);
		void openCsvFile();
		void openInputFile(char *fpath);

		class OpenFileException : public std::exception {
			public:
				const char *what() const throw();
		};
		class EmptyFileException : public std::exception {
			public:
				const char *what() const throw();
		};
		class FileFormatException : public std::exception {
			public:
				const char *what() const throw();
		};
		class InvalidDateException : public std::exception {
			public:
				const char *what() const throw();
		};
		class InvalidInputException : public std::exception {
			public:
				const char *what() const throw();
		};
		class ExchangeRateException : public std::exception {
			public:
				const char *what() const throw();
		};

	private:
		std::map<std::string, float> _bitcoinDB;
};

#endif  // BTCEXCHANGE_HPP
