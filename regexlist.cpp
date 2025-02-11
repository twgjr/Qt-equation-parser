#include "regexlist.h"

RegExList::RegExList(QObject *parent) : QObject(parent)
{
    initRegExList();
    //qDebug()<<"RegExList created with "<<m_formats.size()<<"items";
}

void RegExList::initRegExList()
{
    // 0
    m_formats.append(setRegExpr("NO_MATCH",""));
    // 1
    m_formats.append(setRegExpr("Parenthesis","\\(([^)]+)\\)"));
    // 2
    m_formats.append(setRegExpr("Equals","\\=="));
    // 3
    m_formats.append(setRegExpr("Less Than Or Equals","\\<="));
    // 4
    m_formats.append(setRegExpr("Greater Than Or Equals","\\>="));
    // 5
    m_formats.append(setRegExpr("Less Than","\\<"));
    // 6
    m_formats.append(setRegExpr("Greater Than","\\>"));
    // 7
    m_formats.append(setRegExpr("Power","\\^"));
    // 8
    m_formats.append(setRegExpr("Multiply","\\*"));
    // 9
    m_formats.append(setRegExpr("Divide","\\/"));
    // 10
    m_formats.append(setRegExpr("Add","\\+"));
    // 11
    m_formats.append(setRegExpr("Subtract","\\-"));
    // 12
    m_formats.append(setRegExpr("Variable","((?=[^\\d])\\w+)")); // variable alphanumeric, not numberic alone
    // 13
    m_formats.append(setRegExpr("Constant","\\d+"));   // just numeric
}

RegExList::RegExpr RegExList::setRegExpr(QString exprCase, QString regExStr)
{
    RegExpr regExpr;
    regExpr.exprCase = exprCase;
    regExpr.regExStr = regExStr;
    return regExpr;
}

QVector<RegExList::RegExpr> RegExList::formats() const
{
    return m_formats;
}
