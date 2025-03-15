#include<iostream>
#include <cstring>
#pragma warning (disable:4996)

using std::cin;
using std::cout;
using std::endl;

namespace constants {
	const int HOURS_SIZE = 2;
	const int MINUTES_SIZE = 2;
	const int SECONDS_SIZE = 2;
	const int HOURS_MID = 24;
	const int DINNER_START_H = 20;
	const int DINNER_START_M = 30;
	const int DINNER_START_S = 0;
	const int DINNER_END_H = 22;
	const int DINNER_END_M = 0;
	const int DINNER_END_S = 0;
	const int PARTY_START_H = 23;
	const int PARTY_START_M = 0;
	const int PARTY_START_S = 0;
	const int PARTY_END_H = 6;
	const int PARTY_END_M = 0;
	const int PARTY_END_S = 0;
}

namespace Char {
	int charToInt(const char ch) {
		return ch - '0';
	}
	int strToInt(const char* str) {
		int i = 0;
		while (*str) {
			i *= 10;
			i += charToInt(*str);
			str++;
		}
		return i;
	}
	char intToChar(int num) {
		return num + '0';
	}
	void intToStr(int num, char* str) {

		int curr = num;

		if (num == 0) {
			*str = '0'; str++;
			*str = '0'; str++;
			*str = '\0';
			return;
		}

		while (num != 0) {
			*str = intToChar(num % 10);
			num /= 10;
			str++;
		}

		if (curr < 10) {
			*str = '0';
			str++;
		}
		
		

		*str = '\0';
	}
	char* reverseStr(char* str) {
		char* l = str;
		char* r = str;
		char* cr = str;

		while (*cr) {
			r++, cr++;
		}
		r--;

		while (l <= r) {
			char swap = *l;
			*l = *r;
			*r = swap;
			l++; r--;
		}
		return str;

	}
}


class Time {

	char hours[constants::HOURS_SIZE + 1];
	char minutes[constants::MINUTES_SIZE + 1];
	char seconds[constants::SECONDS_SIZE + 1];

	bool validStr(const char* str) const {

		if (!str) return false;

		size_t nameSize = strlen(str);

		if (nameSize == constants::HOURS_SIZE) return true;

		return false;
	}
	bool validHour(const char* hours) {
		int h = Char::strToInt(hours);
		if (h >= 24 || h < 0) return false;
		return true;
	}
	bool validMin(const char* minutes) {
		int m = Char::strToInt(minutes);
		if (m > 60 || m < 0) return false;
		return true;
	}
	bool validSec(const char* seconds) {
		int s = Char::strToInt(seconds);
		if (s > 60 || s < 0) return false;
		return true;
	}

	int timeToSec(int min, int h, int sec) {
		int sum = h * 60 * 60 + min * 60 + sec;
		return sum;
	}

	void secToTime(int res, int& resMin, int& resSec, int& resH) {
		resH = res / 3600;
		res -= resH * 3600;
		resMin = res / 60;
		res -= resMin * 60;
		resSec = res;
	}

	int abs(const int n) {
		if (n >= 0) return n;
		else return -n;
	}


public:

	Time() : hours("00"), minutes("00"), seconds("00") {}
	
	Time(const char* hours,const char* min, const char* sec) {
		if (validStr(min) && validStr(sec) && validStr(hours) && validHour(hours) && validMin(min) && validSec(sec)) {
			strcpy(this->hours, hours);
			strcpy(this->minutes, min);
			strcpy(this->seconds, sec);
		}
		else {
			strcpy(this->hours, "00");
			strcpy(this->minutes, "00");
			strcpy(this->seconds, "00");
		}
	}
	

	void setHours(const char* hours) {
		if (validStr(hours) && validHour(hours)) {
			strcpy(this->hours, hours);
		}
	}
	void setMinutes(const char* minutes) {
		if (validStr(minutes) && validMin(minutes)) {
			strcpy(this->minutes, minutes);
		}
	}
	void setSeconds(const char* seconds) {
		if (validStr(seconds) && validSec(seconds)) {
			strcpy(this->seconds, seconds);
		}
	}
	const char* getHours() const {
		return hours;
	}
	const char* getSeconds() const {
		return seconds;
	}
	const char* getMinutes() const {
		return minutes;
	}


	void tilMidnight() {
		//cout << this->getHours() << this->minutes << this->hours;

		int min = Char::strToInt(this->minutes);
		int hours = Char::strToInt(this->hours);
		int seconds = Char::strToInt(this->seconds);

		int sum = timeToSec(min, hours, seconds); // прехвърляне на въведеното време в секунди

		int secMid = constants::HOURS_MID * 60 * 60; // времето до полунощ в секунди

		int res = secMid - sum; // намираме разликата между двете, като идеята е после да го преместим пак в часове, минути и секунди

		int resMin, resHours, resSec;

		secToTime(res, resMin, resSec, resHours);

		

		char minStr[constants::MINUTES_SIZE + 1], secStr[constants::SECONDS_SIZE + 1], hoursStr[constants::HOURS_SIZE + 1];

		Char::intToStr(resMin, minStr);
		Char::intToStr(resSec, secStr);
		Char::intToStr(resHours, hoursStr);

		Char::reverseStr(minStr);
		Char::reverseStr(secStr);
		Char::reverseStr(hoursStr);


		cout << "\nTime to midnight: " << hoursStr << "h, " << minStr << "m, " << secStr << "s";
	}

	void addOneSec() {
		int min = Char::strToInt(this->minutes);
		int hours = Char::strToInt(this->hours);
		int seconds = Char::strToInt(this->seconds);

		int sum = timeToSec(min, hours, seconds); // прехвърляне на въведеното време в секунди

		sum += 1; // добавяме една секунда към времето

		int resMin, resHours, resSec;

		secToTime(sum, resMin, resSec, resHours);

		char minStr[constants::MINUTES_SIZE + 1], secStr[constants::SECONDS_SIZE + 1], hoursStr[constants::HOURS_SIZE + 1];

		if (resHours == 24) resHours = 0;

		Char::intToStr(resMin, minStr);
		Char::intToStr(resSec, secStr);
		Char::intToStr(resHours, hoursStr);

		Char::reverseStr(minStr);
		Char::reverseStr(secStr);
		Char::reverseStr(hoursStr);

		this->setHours(hoursStr);
		this->setMinutes(minStr);
		this->setSeconds(secStr);
		cout << "\nAdded one second:\t" << hoursStr << ":" << minStr << ":" << secStr;

	}
	void printTime() {
		cout << endl;
		cout << this->getHours() << ":" << this->getMinutes() << ":" << this->getSeconds();
		cout << endl;
	}

	bool dinnerTime(){
		int dinnerStartSec = timeToSec(constants::DINNER_START_M, constants::DINNER_START_H, constants::DINNER_START_S);
		int dinnerEndSec = timeToSec(constants::DINNER_END_M, constants::DINNER_END_H, constants::DINNER_END_S);

		int min = Char::strToInt(this->minutes);
		int hours = Char::strToInt(this->hours);
		int seconds = Char::strToInt(this->seconds);

		
		int curr = timeToSec(min, hours, seconds);

		/*cout << dinnerStartSec << endl;
		cout << curr << endl;
		cout << dinnerEndSec << endl;*/

		if (curr >= dinnerStartSec && curr <= dinnerEndSec) return true;
		

		return false;
	}

	bool partyTime(){
		int partyStartSec = timeToSec(constants::PARTY_START_M, constants::PARTY_START_H, constants::PARTY_START_S);
		int partyEndSec = timeToSec(constants::PARTY_END_M, constants::PARTY_END_H, constants::PARTY_END_S);

		int min = Char::strToInt(this->minutes);
		int hours = Char::strToInt(this->hours);
		int seconds = Char::strToInt(this->seconds);


		int curr = timeToSec(min, hours, seconds);

		if (curr >= partyStartSec || curr <= partyEndSec) return true;

		return false;
	}

	void compareTo(const Time& other){
		int minOther = Char::strToInt(other.minutes);
		int hoursOther = Char::strToInt(other.hours);
		int secondsOther = Char::strToInt(other.seconds);

		int sumOther = timeToSec(minOther, hoursOther, secondsOther); // прехвърляне на въведеното време в секунди
	
		int minThis = Char::strToInt(this->minutes);
		int hoursThis = Char::strToInt(this->hours);
		int secondsThis = Char::strToInt(this->seconds);

		int sumThis = timeToSec(minThis, hoursThis, secondsThis);

		int res = sumThis - sumOther;
		res = abs(res);

		int resMin, resSec, resHours;

		secToTime(res, resMin, resSec, resHours);

		char minStr[constants::MINUTES_SIZE + 1], secStr[constants::SECONDS_SIZE + 1], hoursStr[constants::HOURS_SIZE + 1];

		Char::intToStr(resMin, minStr);
		Char::intToStr(resSec, secStr);
		Char::intToStr(resHours, hoursStr);

		Char::reverseStr(minStr);
		Char::reverseStr(secStr);
		Char::reverseStr(hoursStr);


		cout << "\nCompared: " << hoursStr << "h, " << minStr << "m, " << secStr << "s";

	}

};

void newline();
int main() {
	Time time;

	//cout << time.getHours();

	time.setHours("12");
	time.setMinutes("18");
	time.setSeconds("14");



	time.tilMidnight();


	newline();

	time.printTime();
	time.addOneSec();
	time.printTime();
	time.addOneSec();
	time.printTime();

	time = { "12","18","59" }; time.printTime();
	time.addOneSec();
	time.printTime();

	time = { "12","59","59" }; time.printTime();
	time.addOneSec();
	time.printTime();
	
	time = { "00","01","59" }; time.printTime();
	time.addOneSec();
	time.printTime();

	time = { "24","01","01" };
	time.printTime();

	newline();

	time = { "19","30","00" };

	cout << time.dinnerTime();

	time = { "19","59","59" };

	cout << endl <<  time.partyTime();
	time.tilMidnight();
	newline();

	time.compareTo({ "23","59","59" }); // sruvnqva ot po malkoto do po - golqmoto
	

	return 0;
}
void newline() {
	cout << endl << endl;
}