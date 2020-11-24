#ifndef EXPRESSIONITEM_H
#define EXPRESSIONITEM_H

#include <QObject>
#include "regexlist.h"

class ExpressionItem : public QObject
{
    Q_OBJECT
public:
    explicit ExpressionItem(QObject *parent = nullptr);

    QString string() const;
    void setString(const QString &string);
    int matchTypeId() const;
    void setMatchTypeId(int matchTypeId);
    int matchStart() const;
    void setMatchStart(int matchStart);
    int matchEnd() const;
    void setMatchEnd(int matchEnd);
    int matchLength() const;
    void setMatchLength(int matchLength);

private:
    QString m_string="";
    int m_matchTypeId = 0; // NO MATCH by default
    int m_matchStart = 0;
    int m_matchEnd = 0;
    int m_matchLength = 0;
};

#endif // EXPRESSIONITEM_H
