#include "note.h"


QString Note::text() const
{
    return _text;
}

void Note::setText(const QString &text)
{
    _text = text;
}

Note::Note()
{

}
