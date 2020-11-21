#include "equationparser.h"

EquationParser::EquationParser(QObject *parent) : QObject(parent)
{

}

void EquationParser::appendExpressionItem()
{
    ExpressionItem * expressionItem = new ExpressionItem(this);
    appendExpressionItem(expressionItem);
}

void EquationParser::appendExpressionItem(QString string,
                                          int matchTypeId,
                                          int matchStart,
                                          int matchEnd,
                                          int matchLength)
{
    ExpressionItem * expressionItem = new ExpressionItem(this);
    expressionItem->setString(string);
    expressionItem->setMatchTypeId(matchTypeId);
    expressionItem->setMatchStart(matchStart);
    expressionItem->setMatchEnd(matchEnd);
    expressionItem->setMatchLength(matchLength);
    appendExpressionItem(expressionItem);
}

void EquationParser::appendExpressionItem(ExpressionItem *expressionItem)
{
    m_expressionSet.append(expressionItem);
}

QVector<ExpressionItem *> EquationParser::parseEquation(QString equationString, int count)
{
    QVector<ExpressionItem *> expressionVector;
    if(equationString.contains("==")){
        qDebug()<<"Level: "<<count<<"String: "<<equationString;
        int matchStart = equationString.indexOf("==");
        int matchLength = QString("==").length()-1;
        int matchEnd = matchStart+matchLength;
        QString partialString0 = equationString.section("",0,matchStart);
        QString match=equationString.section("",matchStart+1,matchEnd+1);
        QString partialString1 = equationString.section("",matchEnd+matchLength+1);
        expressionVector.append(parseEquation(partialString0,count++));
        appendExpressionItem(match,0,matchStart,matchEnd,matchLength);
        expressionVector.append(parseEquation(partialString1,count++));
        return expressionVector;
    }
    if(equationString.contains("+")){
        qDebug()<<"Level: "<<count<<"String: "<<equationString;
        int matchStart = equationString.indexOf("+");
        int matchLength = QString("+").length();
        int matchEnd = equationString.indexOf("+")+matchLength-1;
        QString partialString0 = equationString.section("",0,matchStart);
        QString match=equationString.section("",matchStart+1,matchEnd+1);
        QString partialString1 = equationString.section("",matchEnd+matchLength+1);
        expressionVector.append(parseEquation(partialString0,count++));
        appendExpressionItem(match,0,matchStart,matchEnd,matchLength);
        expressionVector.append(parseEquation(partialString1,count++));
        return expressionVector;
    }
    //constant
    if(equationString.contains("1")){
        qDebug()<<"Level: "<<count<<"String: "<<equationString;
        int matchStart = equationString.indexOf("1");
        int matchLength = QString("1").length();
        int matchEnd = equationString.indexOf("1")+matchLength-1;
        QString match=equationString.section("",matchStart+1,matchEnd+1);
        appendExpressionItem(match,0,matchStart,matchEnd,matchLength);
        return expressionVector;
    }
    //variable
    if(equationString.contains("x")){
        qDebug()<<"Level: "<<count<<"String: "<<equationString;
        int matchStart = equationString.indexOf("x");
        int matchLength = QString("x").length();
        int matchEnd = equationString.indexOf("x")+matchLength-1;
        QString match=equationString.section("",matchStart+1,matchEnd+1);
        appendExpressionItem(match,0,matchStart,matchEnd,matchLength);
        return expressionVector;
    }
    //variable
    if(equationString.contains("y")){
        qDebug()<<"Level: "<<count<<"String: "<<equationString;
        int matchStart = equationString.indexOf("y");
        int matchLength = QString("y").length();
        int matchEnd = equationString.indexOf("y")+matchLength-1;
        QString match=equationString.section("",matchStart+1,matchEnd+1);
        appendExpressionItem(match,0,matchStart,matchEnd,matchLength);
        return expressionVector;
    }
    if(equationString.length()==0){
        return expressionVector;
    }
    qDebug()<<"Something went wrong with parsing: ";
    appendExpressionItem("parse failure",0,0,0,0);
    return expressionVector;
}

QVector<ExpressionItem *> EquationParser::expressionSet() const
{
    return m_expressionSet;
}
