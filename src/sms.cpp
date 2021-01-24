// main

// Call example
// twilio.exe twilio.conf 9166935343 "Ready for appointment"

// Check args
// if less than 3, error
// validate number and message (make sure not empty)

// Open conf file
// Parse file contents
// accountID = 12345, Token = 6789, from_number = 9164208446

// Use twilio's sample code


#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <chrono>
#include "../header/twilio.hh"


// get fromNumber from command line rather than read inf rom file!!!!!!!!!!

// from, to, message, verbose


using namespace std;

int main(int argc, char* argv[]) {

	//if (argc < 5) {
	//	cout << "ERROR: Incorrect number of arguments" << endl;
	//	cout << argc << endl;
	//	for (int i = 0; i < argc; i++) {
	//		cout << i << ". " << argv[i] << endl;
	//	}
	//	return 1;
	//}
	//else {


	//auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());

	//cout << "TIME IS: " << ctime(&timenow) << endl;

	//time_t t = time(NULL);

	//printf("%s", ctime(&t));
	//tm* tPtr = localtime(&t);

	//int date = tPtr->tm_mday;

	//cout << "TODAY IS : " << date << endl;


		ifstream inFile;
		string filename, account, token, fromNum, toNum, message, identifier, day;
		bool simulate = false;
		filename = argv[1];
		fromNum = argv[2];
		toNum = argv[3];
		message = argv[4];
		if (argc > 5) {
			string temp = argv[5];
			transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
			if (temp == "true") {
				simulate = true;
				cout << "TRUEEEE" << endl;
			}
			else {
				simulate = false;
				cout << "FALSEEEEE" << endl;
			}
		}


		//cout << "VERBOSE: " << verbose << endl;

		cout << "FILENAME: " << filename << endl;
		cout << "FROMNUM: " << fromNum << endl;
		cout << "TONUM: " << toNum << endl;
		

		inFile.open(filename);

		if (!inFile.is_open()) {
			cout << "Error opening file" << endl;
			return 1;
		}

		while (inFile >> identifier) {
			if (identifier == "AccountID:") {
				cout << "1." << endl;
				inFile >> account;
			}
			else if (identifier == "Token:") {
				cout << "2." << endl;
				inFile >> token;
			}
			else if (identifier == "Days:") {
				while (inFile >> identifier) {
					cout << "3." << identifier << endl;
					day += identifier;
				}
			}
			//else if (identifier == "From:") {
			//	inFile >> fromNum;
			//}
		}

		cout << "DAYS: " << day << endl;
		cout << "AccountNumber: '" << account << "'" << endl;
		cout << "TokenNumber: '" << token << "'" << endl;
		cout << "FromNumber: '" << fromNum << "'" << endl;

		//sendMessage();



		if (simulate == true) {
			cout << "Not sending message to " << toNum << endl;
			return 0;
		}

		return 0;

		string response;
		//bool verbose = true;
		string picture_url = "";
		
		twilio::Twilio* twilio = new twilio::Twilio(account, token);
		bool verbose = false;
		bool message_success = twilio->send_message(
			toNum,
			fromNum,
			message,
			response,
			picture_url,
			verbose
		);
		//cout << "RESPNSE: " << response << endl;
		//cout << "Message sent: " << message_success << endl;
		delete twilio;

		if (message_success) {
			return 0;
		}

		cerr << "ERROR, " << response << endl;
		return 1;

	//}

	// return 0 on success
	// return 1 on failure

}