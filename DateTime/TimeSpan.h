#pragma once
#include "format.h"

const int MAX_MILLISECONDS = 1000;
const int MAX_SECONDS = 60;
const int MAX_MINUTES = 60;
const int MAX_HOURS = 24;
const int MAX_DAYS_IN_MONTH = 31;
const int MONTHS_IN_YEAR = 12;
const int DAYS_IN_A_YEAR = 365;

class TimeSpan
{
  public:
	TimeSpan();
	TimeSpan(const int& milliseconds);
	TimeSpan(const int& seconds, const int& milliseconds);
	TimeSpan(const int& minutes, const int& seconds, const int& milliseconds);
	TimeSpan(const int& hours,const int& minutes, const int& seconds, const int& milliseconds);
    TimeSpan(const int& days, const int& hours, const int& minutes, const int& seconds, const int& milliseconds );
	TimeSpan(const int& months,const int& days, const int& hours, const int& minutes, const int& seconds, const int& milliseconds);
	TimeSpan(const int& years, const int& months, const int& days, const int& hours, const int& minutes, const int& seconds, const int& milliseconds);
    virtual ~TimeSpan();

    static TimeSpan FromMilliseconds( const int& milliseconds );
    static TimeSpan FromSeconds( const int& seconds );
    static TimeSpan FromMinutes( const int& minutes );
    static TimeSpan FromHours( const int& hours );
    static TimeSpan FromDays( const int& days );

	int GetMilliseconds() const;
    int GetSeconds() const;
	int GetMinutes() const;
	int GetHours() const;
	int GetDays() const;
	int GetMonths() const;
	int GetYears() const;

	void AddMilliseconds(const int& milliSeconds);
	void AddSeconds(const int& seconds);
	void AddMinutes(const int& minutes);
	void AddHours(const int& hours);
	void AddDays(const int& days);
	void AddMonths(const int& months);
	void AddYears(const int& years);

    bool operator<( const TimeSpan &ts ) const;
    bool operator>( const TimeSpan &ts ) const;
    bool operator<=( const TimeSpan &ts ) const;
    bool operator>=( const TimeSpan &ts ) const;
    bool operator==( const TimeSpan &ts ) const;
	bool operator!=(const TimeSpan &ts) const;

	std::string ToString();

  protected:
	  void Init(const int& years, const int& months, const int& days, const int& hours, const int& minutes, const int& seconds, const int& milliseconds);

	int _years;
	int _months;
	int _days;
	int _hours;
	int _minutes;
	int _seconds;
	int _milliseconds;
};
