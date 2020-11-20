#ifndef REGEXPARSER_H
#define REGEXPARSER_H

#include <QObject>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include "matching.h"

class RegExParser : public QObject
{
    Q_OBJECT
public:
    explicit RegExParser(QObject *parent = nullptr);

    enum RegExprId{
        VARIABLE,
        CONSTANT,
        MATH_OPERATOR,
        POWER_OPERATOR,
        COMPARISON_OPERATOR,
        OPENING_PARENTHESIS,
        CLOSING_PARENTHESIS,
    };

    // regex and strings for matching
    QStringList regexStrings = {
        "((?=[^\\d])\\w+)",         // 0: is a word(alphanumeric), but not purely numeric
        "\\d",                      // 1: numeric constants
        "\\+|\\-|\\*|\\/",          // 2: generic math operators (same as z3)
        "\\^",                      // 3: replace "x^n" with x_0*x_1*x_2*...*x_n
        "\\==|\\<=|\\>=|\\>|\\<",   // 4: generic comparison operators (same as z3)
        "\\(",                      // 5: opening bracket
        "\\)",                      // 6: closing bracket
    };

    void parseString(QString string);

    void appendMatchingItem();
    void appendMatchingItem(Matching * matchingItem);

private:
    QVector<Matching*> m_wordSet;
};

#endif // REGEXPARSER_H
