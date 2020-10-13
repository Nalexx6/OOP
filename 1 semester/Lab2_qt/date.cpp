#include "date.h"

int Date::day() const
{
    return _day;
}

void Date::setDay(const int &day)
{
    _day = day;
}

int Date::month() const
{
    return _month;
}

void Date::setMonth(const int &month)
{
    _month = month;
}

int Date::year() const
{
    return _year;
}

void Date::setYear(const int &year)
{
    _year = year;
}

int Date::secs() const
{
    return _secs;
}

void Date::setSecs(const int &secs)
{
    _secs = secs;
}

int Date::mins() const
{
    return _mins;
}

void Date::setMins(const int &mins)
{
    _mins = mins;
}

int Date::hours() const
{
    return _hours;
}

void Date::setHours(const int &hours)
{
    _hours = hours;
}

Date::Date()
{

}
