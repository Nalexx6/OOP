#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <QString>
#include <QVector>

#include "date.h"

class Note
{
private:

    QString _title;
    QVector<QString> contexts;
    QString _text;
    Date _date;

public:
    Note();
    explicit Note(const QString &title, const QString &text, const Date &date) : _title(title), _text(text), _date(date) {}

    QString title() const;
    void setTitle(const QString &title);
    QString text() const;
    void setText(const QString &text);  
    Date date() const;
    void setDate(const Date &date);

};

#endif // NOTE_H
