#ifndef REGEXPARSER_H
#define REGEXPARSER_H

#include <QObject>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include "expressionitem.h"

class RegExMatcher : public QObject
{
    Q_OBJECT
public:
    explicit RegExMatcher(QObject *parent = nullptr);

    enum RegExprId{
        OPEN_PAR,
        CLOSE_PAR,
        EQ,
        LTOE,
        GTOE,
        LT,
        GT,
        POW,
        MULT,
        DIV,
        ADD,
        SUBT,
        VARIABLE,
        CONSTANT
    };

    // regex and strings for matching
    QStringList regexStrings = {
        "\\(",  // 0
        "\\)",  // 1
        "\\==", // 2
        "\\<=", // 3
        "\\>=", // 4
        "\\<",  // 5
        "\\>",  // 6
        "\\^",  // 7
        "\\*",  // 8
        "\\/",  // 9
        "\\+",  // 10
        "\\-",  // 11
        "((?=[^\\d])\\w+)", // 12 variable alphanumeric, not numberic alone
        "\\d"   // 13 just numeric
    };

    void matchString(QString string, ExpressionItem* expressionItem);

private:
};

#endif // REGEXPARSER_H
