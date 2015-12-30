#pragma once

#include "TimeSpan.h"
#include "format.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <time.h>

const int SINCE_YEAR = 1900;

const int MIN_MONTH = 1;
const int MAX_MONTH = 12;

const int MIN_DAY = 1;
const int MAX_DAY = 30;

const int MIN_WEEKDAY = 0;
const int MAX_WEEKDAY = 7;

const int MIN_HOUR = 0;
const int MAX_HOUR = 24;

const int MIN_MINUTE = 0;
const int MAX_MINUTE = 60;

const int MIN_SECOND = 0;
const int MAX_SECOND = 60;

const int MIN_MILLISECOND = 0;
const int MAX_MILLISECOND = 1000;

namespace DayOfWeek
{
	enum Day
	{
		Sunday,
		Monday,
		Thuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday
	};
}

namespace Months
{
	enum Month
	{
		January,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December
	};
}

class DateTime
{
public:
	DateTime();
	DateTime(int month, int day, int year);
	DateTime(int month, int day, int year, int hour, int minute, int second);
	DateTime(int month, int day, int year, int hour, int minute, int second, int millisecond);

	virtual ~DateTime();
	static DateTime Now();

	int GetYear() const
	{
		return _year;
	}
	int GetMonth() const
	{
		return _month;
	}
	int GetDay() const
	{
		return _day;
	}
	int GetHour() const
	{
		return _hour;
	}
	int GetMinute() const
	{
		return _minute;
	}
	int GetSecond() const
	{
		return _second;
	}
	int GetMillisecond() const
	{
		return _millisecond;
	}

	void Add(const TimeSpan& ts);
	void Subtract(const TimeSpan& timeSpan);

	void AddYears(const int & years);
	void SubtractYears(const int& years);
	void AddMonths(const int & months);
	void SubtractMonths(const int & months);
	void AddDays(const int & days);
	void SubtractDays(const int& days);
	void AddHours(const int & hours);
	void SubtractHours(const int& hours);
	void AddMinutes(const int & minutes);
	void SubtractMinutes(const int & minutes);
	void AddSeconds(const int & seconds);
	void SubtractSeconds(const int & seconds);
	void AddMilliseconds(const int & milliseconds);
	void SubtractMilliseconds(const int & milliseconds);

	static TimeSpan CalculateTimeSpan(DateTime& from, DateTime& to);

	bool IsLeapYear();
	bool IsLeapYear(const int & year);

	DayOfWeek::Day GetDayOfWeek();
	DayOfWeek::Day GetDayOfWeek(int year, const int& month, const int& day);

	int GetDayOfYear();
	int GetDayOfYear(const int& year, const int& month, const int& day);

	int GetDaysOfMonth();
	int GetDaysOfMonth(const int & month, const int & year);

	std::string GetNameOfDay();
	std::string GetNameOfDay(const int & day);

	std::string GetNameOfMonth(const int & month);
	std::string GetNameOfMonth();

	bool operator<(const DateTime & dateTime) const;
	bool operator>(const DateTime & dateTime) const;
	bool operator<=(const DateTime & dateTime) const;
	bool operator>=(const DateTime & dateTime) const;
	bool operator==(const DateTime & dateTime) const;
	bool operator!=(const DateTime & dateTime) const;

	DateTime operator+(const TimeSpan & timeSpan);
	DateTime operator-(const TimeSpan & timeSpan);

	TimeSpan operator-(const DateTime & dateTime);

	void operator+=(const TimeSpan & timeSpan);
	void operator-=(const TimeSpan & timeSpan);

	std::string GetAsString();
	std::string GetShortTimeString();
	std::string GetLongTimeString();
	std::string GetShortDateString();
	std::string GetLongDateString();

private:
	time_t GetTimestamp() const;

	void SetWithTimestamp(time_t timeSpan);

	void Init(const int & day, int month, int year, int hour, int minute, int second, int millisecond);

	void InitMonthNames();

	void InitDayNames();

	bool IsValidWeekday(const int & day);

	bool IsValidDayOfMonth(const int & day, int month, const int & year);

	bool IsValidMonth(const int & month);

	bool IsValidYear(const int & year);

	bool IsValidHour(const int & hour);

	bool IsValidMinute(const int & minute);

	bool IsValidSecond(const int & second);

	bool IsValidMillisecond(const int & millisecond);

	int daysOfMonth[MAX_MONTH];

	std::string monthNames[12];

	std::string dayNames[7];

	int _year;
	int _month;
	int _day;
	int _hour;
	int _minute;
	int _second;
	int _millisecond;
};
