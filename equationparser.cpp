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

void EquationParser::parseEquation(QString equationString)
{
    QVector<ExpressionItem *> expressionVector;
    // clean up and simplify the string format
    equationString.replace( " ", "" ); // remove spaces

    //go down the checklist
    m_expressionSet = processSyntaxTree(equationString,0);
}

QVector<ExpressionItem *> EquationParser::processSyntaxTree(QString equationString, int count)
{
    QVector<ExpressionItem *> expressionVector;
    for(int index = 1; index < m_regExList.formats().size() ; index++){
        QRegularExpression regex(m_regExList.formats()[index].regExStr);
        QRegularExpressionMatch match = regex.match(equationString);
        if(match.hasMatch()){
            QString matchString = match.captured(0);
            int start = match.capturedStart();
            int end = match.capturedEnd();
            int id = index;
            int length = matchString.length();

            //no-match case 0 is skipped, checked in parseEquation() after complete parsing
            switch (index) {
            // Parenthesis
            case 1:{
                if((length+2)!=equationString.length()){
                    break;
                } else {
                    expressionVector = branchInside(equationString,matchString,count,id,start,end,length);
                    return expressionVector;
                }
            }
                // Equality
            case 2:{
                expressionVector = branchOutside(equationString,matchString,count,id,start,end,length);
                return expressionVector;
            }
                // Addition
            case 10:{
                expressionVector = branchOutside(equationString,matchString,count,id,start,end,length);
                return expressionVector;
            }
                // Variable
            case 12:{
                expressionVector.append(makeLeaf(matchString,id,start,end,length,count));
                return expressionVector;
            }
                // Constant
            case 13:{
                expressionVector.append(makeLeaf(matchString,id,start,end,length,count));
                return expressionVector;
            }
            }
        }
    }
    if(equationString.length()==0){
        return expressionVector; // empty expression vector
    }

    return expressionVector;
}

ExpressionItem * EquationParser::makeLeaf(QString matchString,
                            int id,
                            int start,
                            int end,
                            int length,
                            int count)
{

    qDebug()<<"Level: "<<count<<", adding leaf: "<<matchString;
    //appendExpressionItem(matchString,id,start,end,length);
    ExpressionItem * expressionItem = new ExpressionItem;
    expressionItem->setString(matchString);
    expressionItem->setMatchTypeId(id);
    expressionItem->setMatchStart(start);
    expressionItem->setMatchEnd(end);
    expressionItem->setMatchLength(length);
    return expressionItem;
}

QVector<ExpressionItem *> EquationParser::branchInside(QString equationString,
                                                      QString matchString,
                                                      int level,
                                                      int id,
                                                      int start,
                                                      int end,
                                                      int length)
{
    QVector<ExpressionItem *> expressionVector;
    qDebug()<<"Level: "<<level<<", branching inside: "<<matchString<<" from: "<<equationString;
    QString sectionStr=equationString.section("",start+1,end+1);
    expressionVector.append(makeLeaf("(",id,start,end,length,level+1));
    expressionVector.append(processSyntaxTree(sectionStr,level+1));
    expressionVector.append(makeLeaf(")",id,start,end,length,level+1));
    return expressionVector;
}

QVector<ExpressionItem *> EquationParser::branchOutside(QString equationString,
                                                      QString matchString,
                                                      int level,
                                                      int id,
                                                      int start,
                                                      int end,
                                                      int length)
{
    QVector<ExpressionItem *> expressionVector;
    qDebug()<<"Level: "<<level<<", branching outside: "<<matchString<<" from: "<<equationString;

    //branch left
    QString sectionStr0=equationString.section("",0,start);
    expressionVector.append(processSyntaxTree(sectionStr0,level+1));

    //add match (leaf)
    expressionVector.append(makeLeaf(matchString,id,start,end,length,level+1));

    //branch right
    QString sectionStr1=equationString.section("",end+1);
    expressionVector.append(processSyntaxTree(sectionStr1,level+1));

    return expressionVector;
}


QVector<ExpressionItem *> EquationParser::expressionSet() const
{
    return m_expressionSet;
}
