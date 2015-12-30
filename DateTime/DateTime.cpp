#include "DateTime.h"

DateTime::DateTime()
{
  _day         = 0;
  _month       = 0;
  _year        = 0;

  _hour        = 0;
  _minute      = 0;
  _second      = 0;
  _millisecond = 0;

  InitMonthNames();
  InitDayNames();
}

DateTime::DateTime( int day, int month, int year )
{
	Init(month, day, year, 0, 0, 0, 0);
}

DateTime::DateTime( 
	int day, int month, int year, int hour, int minute, int second )
{
	Init(month, day, year, hour, minute, second, 0);
}

DateTime::DateTime( 
	int day, int month, int year, int hour, int minute, int second, int millisecond )
{
	Init(month, day, year, hour, minute, second, millisecond);
}

void DateTime::Init( 
	const int& day, int month, int year, int hour, int minute, int second, int millisecond)
{
  InitMonthNames();
  InitDayNames();

  if( !IsValidMonth( month ) )
  {
	  throw std::exception(fmt::format("Month {0} is not in range", month ).c_str());
  }

  if( !IsValidDayOfMonth( day, month ,year ) )
  {
	  throw std::exception(fmt::format("Day {0} is not in month {1}'s range", day, month).c_str());
  }

  if( !IsValidHour( hour ) )
  {
	  throw std::exception(fmt::format("Hour {0} is not in valid range ( {1} - {2} )", hour, MIN_HOUR, MAX_HOUR).c_str());
  }

  if( !IsValidMinute( minute ) )
  {
	  throw std::exception(fmt::format("Minute {0} is not in valid range ( {1} - {2} )", minute, MIN_MINUTE, MAX_MINUTE).c_str());
  }

  if( !IsValidSecond( second ) )
  {
	  throw std::exception(fmt::format("Second {0} is not in valid range ( {1} - {2} )", second, MIN_SECOND, MAX_SECOND).c_str());
  }

  if( !IsValidMillisecond( millisecond ) )
  {
	  throw std::exception(fmt::format("Millisecond {0} is not in valid range ( {1} - {2} )", millisecond, MIN_MILLISECOND, MAX_MILLISECOND).c_str());
  }

  _day         = day;
  _month       = month;
  _year        = year;
  _hour        = hour;
  _minute      = minute;
  _second      = second;
  _millisecond = millisecond;
}

void DateTime::InitMonthNames()
{
  monthNames[Months::January]  = "January";
  monthNames[Months::February] = "February";
  monthNames[Months::March]    = "March";
  monthNames[Months::April]    = "April";
  monthNames[Months::May]      = "May";
  monthNames[Months::June]     = "June";
  monthNames[Months::July]     = "July";
  monthNames[Months::August]   = "August";
  monthNames[Months::September]= "September";
  monthNames[Months::October]  = "October";
  monthNames[Months::November] = "November";
  monthNames[Months::December] = "December";
}

void DateTime::InitDayNames()
{
	dayNames[DayOfWeek::Sunday] = "Sunday";
	dayNames[DayOfWeek::Monday]   = "Monday";
	dayNames[DayOfWeek::Thuesday] = "Tuesday";
	dayNames[DayOfWeek::Wednesday]= "Wednesday";
	dayNames[DayOfWeek::Thursday] = "Thursday";
	dayNames[DayOfWeek::Friday]   = "Friday";
	dayNames[DayOfWeek::Saturday] = "Saturday";
}

DateTime::~DateTime() { }

DateTime DateTime::Now()
{
	DateTime dt;
	dt.SetWithTimestamp(time(nullptr));
  return dt;
}

void DateTime::SetWithTimestamp( time_t timeSpan )
{
	tm time;
	localtime_s(&time,&timeSpan);
	Init( time.tm_mday, time.tm_mon + 1, time.tm_year + 
		SINCE_YEAR, time.tm_hour, time.tm_min, time.tm_sec, 0 );
}

time_t DateTime::GetTimestamp() const
{
  time_t rawtime;
  tm tim;
  rawtime = time(nullptr);
  localtime_s(&tim,&rawtime);
  tim.tm_year = _year - SINCE_YEAR;
  tim.tm_mon = _month - 1;
  tim.tm_mday = _day;
  tim.tm_hour = _hour;
  tim.tm_min = _minute;
  tim.tm_sec = _second;
  return mktime( &tim );
}


void DateTime::Add( const TimeSpan& ts )
{
	AddMilliseconds(ts.GetMilliseconds());
	AddSeconds(ts.GetSeconds());
	AddMinutes(ts.GetMinutes());
	AddHours(ts.GetHours());
	AddDays(ts.GetDays());
	AddMonths(ts.GetMonths());
	AddYears(ts.GetYears());
}

void DateTime::Subtract(const TimeSpan& timeSpan)
{
	SubtractMilliseconds(timeSpan.GetMilliseconds());
	SubtractSeconds(timeSpan.GetSeconds());
	SubtractMinutes(timeSpan.GetMinutes());
	SubtractHours(timeSpan.GetHours());
	SubtractDays(timeSpan.GetDays());
	SubtractMonths(timeSpan.GetMonths());
	SubtractYears(timeSpan.GetYears());
}

void DateTime::AddYears(const int& years)
{
	years > 0 ? _year += years : SubtractYears(years * -1);
}

void DateTime::SubtractYears(const int& years)
{
	_year -= years;
}

void DateTime::AddMonths(const int& months)
{
	auto totalMonths = _month + months;

	if (totalMonths > MAX_MONTH)
	{
		auto yearsToIncrease = totalMonths / MAX_MONTH;
		auto monthsToSubstract = yearsToIncrease * MAX_MONTH;

		AddYears(yearsToIncrease);
		_month = totalMonths - monthsToSubstract;
	}
	else
		_month += months;
}

void DateTime::SubtractMonths(const int& months)
{
	for (auto&& i = 0; i < months; i++)
	{
		_month--;

		if (_month < 1)
		{
			SubtractYears(1);
			_month = 12;
		}
	}
}

void DateTime::AddDays(const int& days)
{

	if (days < 0)
		SubtractDays(days);
	
	if (GetDaysOfMonth(_month, _year) >= _day + days)
	{
		_day += days;
		return;
	}

	auto totalDays = _day + days;
	auto month = _month;
	auto year = _year;

	for (;;)
	{
		auto daysInCurrentMonth = GetDaysOfMonth(month, year);

		if (totalDays > daysInCurrentMonth)
		{
			AddMonths(1);
			totalDays -= daysInCurrentMonth;
			if (month < 12)
			{
				month++;
			}
			else
			{
				month = 1;
				year++;
			}
		}
		else
		{
			break;
		}
	}
	_day = totalDays;
}

void DateTime::SubtractDays(const int& days)
{
	for (auto&& i = 0; i < days; i++)
	{
		_day--;

		if (_day < 1)
		{
			SubtractMonths(1);
			_day = GetDaysOfMonth(_month, _year);
		}
	}
}

void DateTime::AddHours(const int& hours)
{
	auto totalHours = _hour + hours;

	if (totalHours >= MAX_HOUR)
	{
		auto daysToIncrease = totalHours / MAX_HOUR;
		auto hoursToSubstract = daysToIncrease * MAX_HOUR;

		AddDays(daysToIncrease);
		_hour = totalHours - hoursToSubstract;
	}
	else
		_hour += hours;
}

void DateTime::SubtractHours(const int& hours)
{
	for (auto&& i = 0; i < hours; i++)
	{
		_hour--;

		if (_hour < 1)
		{
			SubtractDays(1);
			_hour = MAX_HOUR;
		}
	}
}

void DateTime::AddMinutes(const int& minutes)
{
	auto totalMinutes = _minute + minutes;

	if (totalMinutes >= MAX_MINUTE)
	{
		auto hoursToIncrease = totalMinutes / MAX_MINUTE;
		auto minutesToSubstract = hoursToIncrease * MAX_MINUTE;

		AddHours(hoursToIncrease);
		_minute = totalMinutes - minutesToSubstract;
	}
	else
		_minute += minutes;
}

void DateTime::SubtractMinutes(const int& minutes)
{
	for (auto&& i = 0; i < minutes; i++)
	{
		_minute--;

		if (_minute < 1)
		{
			SubtractHours(1);
			_minute = MAX_MINUTE;
		}
	}
}

void DateTime::AddSeconds(const int& seconds)
{
	auto totalSeconds = _second + seconds;

	if (totalSeconds >= MAX_SECOND)
	{
		auto minutesToIncrease = totalSeconds / MAX_SECOND;
		auto secondsToSubtract = minutesToIncrease * MAX_SECOND;
		AddMinutes(minutesToIncrease);
		_second = totalSeconds - secondsToSubtract;
	}
	else
		_second += seconds;
}

void DateTime::SubtractSeconds(const int& seconds)
{
	for (auto&& i = 0; i < seconds; i++)
	{
		_second--;

		if (_second < 1)
		{
			SubtractMinutes(1);
			_second = MAX_SECOND;
		}
	}
}

void DateTime::AddMilliseconds(const int& milliseconds)
{
	auto totalMilliseconds = _millisecond + milliseconds;

	if (totalMilliseconds >= MAX_MILLISECOND)
	{
		auto secondsToIncrease = totalMilliseconds / MAX_MILLISECOND;
		auto milliSecondsToSubstract = secondsToIncrease * MAX_MILLISECOND;
		AddSeconds(secondsToIncrease);
		_millisecond = totalMilliseconds - milliSecondsToSubstract;
	}
	else
		_millisecond += milliseconds;
}

void DateTime::SubtractMilliseconds(const int& milliseconds)
{
	for (auto&& i = 0; i < milliseconds; i++)
	{
		_millisecond--;

		if (_millisecond < 1)
		{
			SubtractSeconds(1);
			_millisecond = MAX_MILLISECOND;
		}
	}
}

TimeSpan DateTime::CalculateTimeSpan(DateTime& from, DateTime& to)
{
	return to - from;
}

bool DateTime::IsLeapYear()
{
	return IsLeapYear(_year);
}

bool DateTime::IsLeapYear(const int& year)
{
  return (( year % 4 == 0 ) && ( year % 100 != 0 )) || ( year % 400 == 0 );
}

DayOfWeek::Day DateTime::GetDayOfWeek()
{
	return GetDayOfWeek(_year, _month, _day);
}

DayOfWeek::Day DateTime::GetDayOfWeek(int year, const int& month, const int& day)
{
	const int monthTable[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	year -= month < 3;

	return static_cast<DayOfWeek::Day>
		((year + year / 4 - year / 100 + year / 400 + monthTable[month - 1] + day) % 7);
}

int DateTime::GetDayOfYear()
{
	return GetDayOfYear(_year, _month, _day);
}

int DateTime::GetDayOfYear(const int& year, const int& month, const int& day)
{
	int daysToMonth[2][13] =
	{
		{ 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
		{ 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 },
	};

	return daysToMonth[IsLeapYear(year) ? 1 : 0][month] + day;
}

int DateTime::GetDaysOfMonth()
{
	return GetDaysOfMonth(_month, _year);
}

int DateTime::GetDaysOfMonth(const int& month, const int& year)
{
	const int MonthDays[2][13] = {
		{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
		{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
	};
	if (month < 1 || month > 12) {
		return 0;
	}
	return MonthDays[IsLeapYear(year)][month - 1];
}

std::string DateTime::GetNameOfDay()
{
	return GetNameOfDay(GetDayOfWeek());
}

bool DateTime::operator<(const DateTime &dateTime) const
{
	return GetTimestamp() < dateTime.GetTimestamp();
}

bool DateTime::operator>(const DateTime &dateTime) const
{
	return GetTimestamp() > dateTime.GetTimestamp();
}

bool DateTime::operator<=(const DateTime &dateTime) const
{
	return GetTimestamp() <= dateTime.GetTimestamp();
}

bool DateTime::operator>=(const DateTime &dateTime) const
{
	return GetTimestamp() >= dateTime.GetTimestamp();
}

bool DateTime::operator==(const DateTime &dateTime) const
{
	return GetTimestamp() == dateTime.GetTimestamp();
}

bool DateTime::operator!=(const DateTime& dateTime) const
{
	return GetTimestamp() != dateTime.GetTimestamp();
}

DateTime DateTime::operator+(const TimeSpan &timeSpan)
{
	auto timeStmp = this;
	timeStmp->Add(timeSpan);
	return *timeStmp;
}

DateTime DateTime::operator-(const TimeSpan& timeSpan)
{
	auto timeStmp = this;
	timeStmp->Subtract(timeSpan);
	return *timeStmp;
}

TimeSpan DateTime::operator-(const DateTime& dateTime)
{
	auto milliSeconds = dateTime.GetMillisecond();
	auto seconds = dateTime.GetSecond();
	auto minutes = dateTime.GetMinute();
	auto hours = dateTime.GetHour();
	auto days = dateTime.GetDay();
	auto months = dateTime.GetMonth();
	auto years = dateTime.GetYear();

	auto totalMilliseconds = 0,
		totalSeconds = 0,
		totalMinutes = 0,
		totalHours = 0,
		totalDays = 0,
		totalMonths = 0,
		totalYears = 0,
		leapYears = 0;

	const int DaysInYear[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

	for (auto i = years; i < _year; i++)
	{
		if (IsLeapYear(i))
			leapYears++;
	}

	auto difference = 
		((_year - 1000) * 365 + DaysInYear[_month - 1] + _day) 
		- 
		((years - 1000) * 365 + DaysInYear[months - 1] + days);

	difference += leapYears;

	auto monthCounter = months;
	auto yearCounter = years;

	for (;;)
	{
		auto daysInCurrentMonth = GetDaysOfMonth(monthCounter, yearCounter);

		if (difference > daysInCurrentMonth)
		{
			totalMonths++;

			difference -= daysInCurrentMonth;

			if (monthCounter < 12)
			{
				monthCounter++;
			}
			else
			{
				monthCounter = 1;

				yearCounter++;
			}
		}
		else
		{
			break;
		}
	}

	totalYears = totalMonths / MAX_MONTH;
	totalDays = difference;
	totalMonths = totalMonths - (MAX_MONTH * totalYears);

	 totalHours = _hour - hours;
	 totalMinutes = _minute - minutes;
	 totalSeconds = _second - seconds;
	 totalMilliseconds = _millisecond - milliSeconds;


	if (totalMilliseconds < 0)
	{
		totalSeconds--;
		totalMilliseconds += 1000;
	}

	if (totalSeconds < 0)
	{
		totalMinutes--;
		totalSeconds += 60;
	}

	if (totalMinutes < 0 && totalHours > 0 && totalDays > 0)
	{
		totalHours--;
		totalMinutes += 60;
	}

	if (totalHours < 0 && totalDays > 0)
	{
		totalDays--;
		totalHours += 24;
	}

	return TimeSpan(totalYears, totalMonths, totalDays, totalHours, totalMinutes, totalSeconds, totalMilliseconds);
}

void DateTime::operator+=( const TimeSpan &timeSpan )
{
	Add(timeSpan);
}

void DateTime::operator-=(const TimeSpan& timeSpan)
{
	Subtract(timeSpan);
}

std::string DateTime::GetNameOfDay(const int& day)
{
  if( IsValidWeekday( day ) )
  {
    return dayNames[day];
  }
  else
  {
	  throw std::exception(fmt::format("Day {0} is not in valid weekday range ( {1} - {2} )", 
		  day, MIN_WEEKDAY, MAX_WEEKDAY).c_str());
  }
}

std::string DateTime::GetNameOfMonth(const int& month)
{
  if( IsValidMonth( month ) )
  {
    return monthNames[month - 1];
  }
  else
  {
	  throw std::exception(fmt::format("Month {0} is not in valid range ( {1} - {2} )", 
		  month, MIN_MONTH, MAX_MONTH).c_str());
  }
}

std::string DateTime::GetNameOfMonth()
{
	return monthNames[_month - 1];
}

std::string DateTime::GetAsString()
{
	return fmt::format("{0} - {1}", GetShortDateString(), GetShortTimeString());
}

std::string DateTime::GetShortTimeString()
{
	return fmt::format("{0}:{1}:{2}",_hour,_minute,_second);
}

std::string DateTime::GetLongTimeString()
{
	return fmt::format("{0}:{1}:{2}:{3}",_hour,_minute,_second,_millisecond);
}

std::string DateTime::GetShortDateString()
{
	return fmt::format("{0}/{1}/{2}",_month,_day,_year);
}

std::string DateTime::GetLongDateString()
{
	return fmt::format("{0}, {1} {2}, {3}",GetNameOfDay(GetDayOfWeek()),GetNameOfMonth(_month),_day,_year);
}

bool DateTime::IsValidWeekday(const int& day)
{
  return day >= MIN_WEEKDAY && day <= MAX_WEEKDAY;
}

bool DateTime::IsValidDayOfMonth(const int& day, int month, const int& year)
{
  if( IsValidMonth( month ) )
  {
    return day >= 1 && day <= GetDaysOfMonth( month, year );
  }
  
  return false;
}

bool DateTime::IsValidMonth(const int& month)
{
  return month >= MIN_MONTH && month <= MAX_MONTH;
}

bool DateTime::IsValidYear(const int& year)
{
  return year >= 0;
}

bool DateTime::IsValidHour(const int& hour)
{
  return hour >= MIN_HOUR && hour <= MAX_HOUR;
}

bool DateTime::IsValidMinute(const int& minute)
{
  return minute >= MIN_MINUTE && minute <= MAX_MINUTE;
}

bool DateTime::IsValidSecond(const int& second)
{
  return second >= MIN_SECOND && second <= MAX_SECOND;
}

bool DateTime::IsValidMillisecond(const int& millisecond)
{
  return millisecond >= MIN_MILLISECOND && millisecond <= MAX_MILLISECOND;
}
