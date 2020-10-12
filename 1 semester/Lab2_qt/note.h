#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <QString>

class Note
{
private:
    QString _text;


public:
    Note();
    explicit Note(const QString &text) : _text(text) {};

    QString text() const;
    void setText(const QString &text);

};

#endif // NOTE_H
