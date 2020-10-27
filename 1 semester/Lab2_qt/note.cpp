#include "note.h"


QString Note::text() const
{
    return _text;
}

void Note::setText(const QString &text)
{
    _text = text;
}

QString Note::title() const
{
    return _title;
}

void Note::setTitle(const QString &title)
{
    _title = title;
}

Date Note::date() const
{
    return _date;
}

void Note::setDate(const Date &date)
{
    _date = date;
}



QSet<QString> Note::lists() const
{
    return _lists;
}

void Note::setLists(const QSet<QString> &lists)
{
    _lists = lists;
}

Note::Note()
{
    
}
