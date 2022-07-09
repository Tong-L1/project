#include <iostream>
using namespace std;

bool isDegital(string str) { //判断是否为整数
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == '-' && str.size() > 1)
			continue;
		if (str.at(i) > '9' || str.at(i) < '0')
			return false;
	}
	return true;
}

bool isLeap(int year) {  //是否闰年
	if (year % 4 == 0){
		if (year % 100 == 0){
			if (year % 400 == 0)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}

bool yearIsRight(string year) {
	if (isDegital(year)) {
		int result = atoi(year.c_str()); //转为int
		if (result >= 1920 && result <= 2050) {
			return true;
		}
		else {
			cout << "year应为整数且1920≤year≤2050";
			return false;
		}
	}
	else {
		cout << "year应为整数且1920≤year≤2050";
		return false;
	}
}

bool monthIsRight(string month) {
	if (isDegital(month)) {
		int result = atoi(month.c_str()); //转为int
		if (result >= 1 && result <= 12) {
			return true;
		}
		else {
			cout << "month应为整数且1≤year≤12";
			return false;
		}
	}
	else {
		cout << "month应为整数且1≤year≤12";
		return false;
	}
}

bool dayIsRight(int year,int month,string sday) {
	if (isDegital(sday)) {
		int day = atoi(sday.c_str()); //转为int
		switch (month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (day >= 1 && day <= 31) {
				return true;
			}
			else {
				return false;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if (day >= 1 && day <= 30) {
				return true;
			}
			break;
		case 2:
			if (isLeap(year)) {
				if (day >= 1 && day <= 29) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (day >= 1 && day <= 28) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		}

	}
	else {
		cout << "day应为整数且1≤year≤31";
		return false;
	}
}

int getDayNumberDate(int year,int month,int day) {
	int num=0;
	switch (month) {
	case 4:
	case 6:
	case 9:
	case 11:
		num = 30;
		break;
	case 2:
		if (isLeap(year)) {
			num = 29;
		}
		else {
			num = 28;
		}
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		num = 31;
		break;
	}
	return num;
}

void nextDate(int year,int month,int day) {
	if (day < getDayNumberDate(year,month,day)) {
		day++;
	}
	else {
		day = 1;
		if (month < 12) {
			month++;
		}
		else {
			month = 1;
			year++;
		}
	}
	cout << "明天是：" << year << "年" << month << "月" << day << "日" << endl;
}

int main() {
	string syear="", smonth = "", sday = "";
	while (!yearIsRight(syear)) {
		cout << endl << "year:";
		cin >> syear;
	}
	int year = atoi(syear.c_str());//int year
	while (!monthIsRight(smonth)) {
		cout << endl << "month:";
		cin >> smonth;
	}
	int month = atoi(smonth.c_str());//int month
	while (!dayIsRight(year,month,sday)) {
		cout << endl << "day:";
		cin >> sday;
	}
	int day = atoi(sday.c_str());//int day
	nextDate(year, month, day);

	return 0;
}