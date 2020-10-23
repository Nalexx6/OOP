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


bool operator >(Date a, Date b)
{

    if(a.year() > b.year())
        return true;
    if(a.year() < b.year())
        return false;
    if(a.month() > b.month())
        return true;
    if(a.month() < b.month())
        return false;
    if(a.day() > b.day())
        return true;
    if(a.day() < b.day())
        return false;
    if(a.hours() > b.hours())
        return true;
    if(a.hours() < b.hours())
        return false;
    if(a.mins() > b.mins())
        return true;
    if(a.mins() < b.mins())
        return false;
    if(a.secs() > b.secs())
        return true;
    if(a.secs() < b.secs())
        return false;

    return false;

}

bool operator <(Date a, Date b)
{

    if(a.year() < b.year())
        return true;
    if(a.year() > b.year())
        return false;
    if(a.month() < b.month())
        return true;
    if(a.month() > b.month())
        return false;
    if(a.day() < b.day())
        return true;
    if(a.day() > b.day())
        return false;
    if(a.hours() < b.hours())
        return true;
    if(a.hours() > b.hours())
        return false;
    if(a.mins() < b.mins())
        return true;
    if(a.mins() > b.mins())
        return false;
    if(a.secs() < b.secs())
        return true;
    if(a.secs() > b.secs())
        return false;

    return false;

}

bool operator >=(Date a, Date b)
{

    if(a.year() > b.year())
        return true;
    if(a.year() < b.year())
        return false;
    if(a.month() > b.month())
        return true;
    if(a.month() < b.month())
        return false;
    if(a.day() > b.day())
        return true;
    if(a.day() < b.day())
        return false;
    if(a.hours() > b.hours())
        return true;
    if(a.hours() < b.hours())
        return false;
    if(a.mins() > b.mins())
        return true;
    if(a.mins() < b.mins())
        return false;
    if(a.secs() > b.secs())
        return true;
    if(a.secs() < b.secs())
        return false;

    return true;

}

bool operator <=(Date a, Date b)
{

    if(a.year() < b.year())
        return true;
    if(a.year() > b.year())
        return false;
    if(a.month() < b.month())
        return true;
    if(a.month() > b.month())
        return false;
    if(a.day() < b.day())
        return true;
    if(a.day() > b.day())
        return false;
    if(a.hours() < b.hours())
        return true;
    if(a.hours() > b.hours())
        return false;
    if(a.mins() < b.mins())
        return true;
    if(a.mins() > b.mins())
        return false;
    if(a.secs() < b.secs())
        return true;
    if(a.secs() > b.secs())
        return false;

    return true;

}

bool operator ==(Date a, Date b)
{



}

bool operator !=(Date a, Date b)
{

}
