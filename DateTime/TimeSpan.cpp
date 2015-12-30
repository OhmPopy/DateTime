#include "TimeSpan.h"

TimeSpan::TimeSpan()
{
	Init(0, 0, 0, 0, 0, 0, 0);
}

TimeSpan::TimeSpan(const int& milliseconds)
{
	Init(0, 0, 0, 0, 0, 0, milliseconds);
}

TimeSpan::TimeSpan(const int& seconds, const int& milliseconds)
{
  Init(0,0, 0, 0, 0, seconds, milliseconds );
}

TimeSpan::TimeSpan(const int& minutes, const int& seconds, const int& milliseconds)
{
	Init(0, 0, 0, 0, minutes, seconds, milliseconds);
}

TimeSpan::TimeSpan(const int& hours, const int& minutes, const int& seconds, const int& milliseconds)
{
	Init(0, 0, 0, hours, minutes, seconds, milliseconds);
}

TimeSpan::TimeSpan( const int& days, const int& hours, const int& minutes, const int& seconds, const int& milliseconds )
{
  Init(0,0, days, hours, minutes, seconds, milliseconds );
}

TimeSpan::TimeSpan(const int& months, const int& days, const int& hours, const int& minutes, const int& seconds, const int& milliseconds)
{
	Init(0, months, days, hours, minutes, seconds, milliseconds);
}

TimeSpan::TimeSpan(const int& years, const int& months, const int& days, const int& hours, const int& minutes, const int& seconds, const int& milliseconds)
{
	Init(years, months, days, hours, minutes, seconds, milliseconds);
}

void TimeSpan::Init(const int& years, const int& months, const int& days, const int& hours, const int& minutes, const int& seconds, const int& milliseconds)
{
	_months       = months;
	_years        = years;
	_days         = days;
	_hours        = hours;
	_minutes      = minutes;
	_seconds      = seconds;
	_milliseconds = milliseconds;
}

TimeSpan TimeSpan::FromMilliseconds( const int& milliseconds )
{
  return TimeSpan( 0, 0, 0, 0, milliseconds );
}

TimeSpan TimeSpan::FromSeconds( const int& seconds )
{
  return TimeSpan( 0, 0, 0, seconds, 0 );
}

TimeSpan TimeSpan::FromMinutes( const int& minutes )
{
  return TimeSpan( 0, 0, minutes, 0, 0 );
}

TimeSpan TimeSpan::FromHours( const int& hours )
{
  return TimeSpan( 0, hours, 0, 0, 0 );
}

TimeSpan TimeSpan::FromDays( const int& days )
{
  return TimeSpan( days, 0, 0, 0, 0 );
}

int TimeSpan::GetMilliseconds() const
{
	return _milliseconds;
}

int TimeSpan::GetSeconds() const
{
	return _seconds;
}

int TimeSpan::GetMinutes() const
{
	return _minutes;
}

int TimeSpan::GetHours() const
{
	return _hours;
}

int TimeSpan::GetDays() const
{
	return _days;
}

int TimeSpan::GetMonths() const
{
	return _months;
}

int TimeSpan::GetYears() const
{
	return _years;
}

void TimeSpan::AddMilliseconds(const int& milliSeconds)
{
	_milliseconds += milliSeconds;
}

void TimeSpan::AddSeconds(const int& seconds)
{
	_seconds += seconds;
}

void TimeSpan::AddMinutes(const int& minutes)
{
	_minutes += minutes;
}

void TimeSpan::AddHours(const int& hours)
{
	_hours += hours;
}

void TimeSpan::AddDays(const int& days)
{
	_days += days;
}

void TimeSpan::AddMonths(const int& months)
{
	_months += months;
}

void TimeSpan::AddYears(const int& years)
{
	_years += years;
}

bool TimeSpan::operator<(const TimeSpan &ts) const
{
	return 
		_years        < ts.GetYears()   ||
		_months       < ts.GetMonths()  ||
		_days         < ts.GetDays()    ||
		_minutes      < ts.GetMinutes() ||
		_seconds      < ts.GetSeconds() ||
		_milliseconds < ts.GetMilliseconds();
}

bool TimeSpan::operator>( const TimeSpan &ts ) const
{
	return
		_years        > ts.GetYears() ||
		_months       > ts.GetMonths() ||
		_days         > ts.GetDays() ||
		_minutes      > ts.GetMinutes() ||
		_seconds      > ts.GetSeconds() ||
		_milliseconds > ts.GetMilliseconds();
}

bool TimeSpan::operator<=( const TimeSpan &ts ) const
{
	return
		_years        <= ts.GetYears() ||
		_months       <= ts.GetMonths() ||
		_days         <= ts.GetDays() ||
		_minutes      <= ts.GetMinutes() ||
		_seconds      <= ts.GetSeconds() ||
		_milliseconds <= ts.GetMilliseconds();
}

bool TimeSpan::operator>=( const TimeSpan &ts ) const
{
	return
		_years        >= ts.GetYears() ||
		_months       >= ts.GetMonths() ||
		_days         >= ts.GetDays() ||
		_minutes      >= ts.GetMinutes() ||
		_seconds      >= ts.GetSeconds() ||
		_milliseconds >= ts.GetMilliseconds();
}

bool TimeSpan::operator==( const TimeSpan &ts ) const
{
	return
		_years        == ts.GetYears() ||
		_months       == ts.GetMonths() ||
		_days         == ts.GetDays() ||
		_minutes      == ts.GetMinutes() ||
		_seconds      == ts.GetSeconds() ||
		_milliseconds == ts.GetMilliseconds();
}

bool TimeSpan::operator!=(const TimeSpan& ts) const
{
	return
		_years != ts.GetYears() ||
		_months != ts.GetMonths() ||
		_days != ts.GetDays() ||
		_minutes != ts.GetMinutes() ||
		_seconds != ts.GetSeconds() ||
		_milliseconds != ts.GetMilliseconds();
}

std::string TimeSpan::ToString()
{
	return fmt::format(
		"{0} Years, "
		"{1} Months, "
		"{2} Days, "
		"{3} Hours, "
		"{4} Minutes, "
		"{5} Seconds, "
		"{6} Milliseconds",
		_years,
		_months,
		_days,
		_hours,
		_minutes,
		_seconds,
		_milliseconds);
}

TimeSpan::~TimeSpan() { }