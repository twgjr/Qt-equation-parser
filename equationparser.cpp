#include "equationparser.h"

EquationParser::EquationParser(QObject *parent) : QObject(parent)
{
    m_expressionGraph = new ExpressionItem(this);
}

void EquationParser::parseEquation(QString equationString)
{
    // clean up and simplify the string format
    equationString.replace( " ", "" ); // remove spaces

    //go down the checklist
    qDebug()<<"Beginning recursion.";
    if(!processSyntaxTree(equationString,0,m_expressionGraph)){
        qDebug()<<"failed to parse!";
    }
}

bool EquationParser::processSyntaxTree(QString equationString,
                                       int depth,
                                       ExpressionItem * parentNode)
{
    for(int index = 1; index < m_regExList.formats().size() ; index++){
        QRegularExpression regex(m_regExList.formats()[index].regExStr);
        QRegularExpressionMatch match = regex.match(equationString);
        if(match.hasMatch()){
            QString matchString = match.captured(0);
            int start = match.capturedStart();
            int end = match.capturedEnd();
            int length = matchString.length();

            //no-match case 0 is skipped, checked in parseEquation() after complete parsing
            switch (index) {

            case 1:{// Parenthesis
                if((length)!=equationString.length()){
                    break;
                } else {
                    makeNodeBranchIn(equationString,matchString,start,end,depth,parentNode);
                    return true;
                }
            }
            case 2:{}// Equals
            case 3:{}// Less than or Equals
            case 4:{}// Greater than or Equals
            case 5:{}// Less than
            case 6:{ // Greater than
            }
            case 7:{ // Power
            }
            case 8:{// Multiply
            }
            case 9:{// Divide
            }
            case 10:{}// Add
            case 11:{ // Subtract
                makeNodeBranchOut(equationString,matchString,start,end,depth,parentNode);
                return true;
            }
            case 12:{}// Variable
            case 13:{// Constant
                makeLeaf(matchString,depth,parentNode);
                return true;
            }
            }
        }
    }
    if(equationString.length()==0){
        return false;
    }
    return false;
}

bool EquationParser::makeLeaf(QString matchString,
                              int depth,
                              ExpressionItem * parentNode)
{
    qDebug()<<"Level: "<<depth<<", adding leaf: "<<matchString;
    ExpressionItem * thisNode = new ExpressionItem(this);
    thisNode->m_string = matchString;
    thisNode->m_parent = parentNode;
    parentNode->m_children.append(thisNode);
    return true;
}

bool EquationParser::makeNodeBranchOut(QString equationString,
                                       QString matchString,
                                       int start,
                                       int end,
                                       int depth,
                                       ExpressionItem * parentNode)
{
    qDebug()<<"Level: "<<depth<<", adding node: "<<matchString<<", branching outside";
    ExpressionItem * thisNode = new ExpressionItem(this);
    thisNode->m_string = matchString;
    thisNode->m_parent = parentNode;
    parentNode->m_children.append(thisNode);
    QString sectionStr0=equationString.section("",0,start);
    processSyntaxTree(sectionStr0,depth+1,thisNode);
    QString sectionStr1=equationString.section("",end+1);
    processSyntaxTree(sectionStr1,depth+1,thisNode);
    return true;
}

bool EquationParser::makeNodeBranchIn(QString equationString,
                                      QString matchString,
                                      int start,
                                      int end,
                                      int depth,
                                      ExpressionItem *parentNode)
{
    qDebug()<<"Level: "<<depth<<", adding node: "<<matchString<<", branching outside";
    ExpressionItem * thisNode = new ExpressionItem(this);
    thisNode->m_string = matchString;
    thisNode->m_parent = parentNode;
    parentNode->m_children.append(thisNode);
    QString sectionStr1=equationString.section("",start,end+1);
    processSyntaxTree(sectionStr1,depth+1,thisNode);
    return true;
}

ExpressionItem *EquationParser::expressionGraph()
{
    return m_expressionGraph;
}
