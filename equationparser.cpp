#include "equationparser.h"

EquationParser::EquationParser(QObject *parent) : QObject(parent)
{

}

void EquationParser::parseEquation(QString equationString)
{
    // clean up and simplify the string format
    equationString.replace( " ", "" ); // remove spaces

    //go down the checklist
    //m_expressionGraph->m_string = equationString;
    ExpressionItem * childNode = new ExpressionItem(this);
    qDebug()<<"Beginning recursion.";
    processSyntaxTree(equationString,0,childNode,m_expressionGraph);
}

int EquationParser::processSyntaxTree(QString equationString,
                                       int count,
                                       ExpressionItem * thisNode,
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
                    return count;
                }
            }
            case 2:{}// Equals
            case 3:{}// Less than or Equals
            case 4:{}// Greater than or Equals
            case 5:{}// Less than
            case 6:{ // Greater than
            }                // Addition
            case 7:{ // Power
            }
            case 8:{// Multiply
            }
            case 9:{// Divide
            }
            case 10:{}// Add
            case 11:{ // Subtract
                makeNodeBranchOut(equationString,matchString,start,end,count,thisNode,parentNode);
                return count;
            }
            case 12:{}// Variable
            case 13:{// Constant
                makeLeaf(matchString,count,thisNode,parentNode);
                return count;
            }
            }
        }
    }
    if(equationString.length()==0){
        return count; // empty expression vector
    }
    return count;
}

int EquationParser::makeLeaf(QString matchString,
                              int count,
                              ExpressionItem * thisNode,
                              ExpressionItem * parentNode)
{
    qDebug()<<"Level: "<<count<<", adding leaf: "<<matchString;
    thisNode->m_string = matchString;
    thisNode->m_parent = parentNode;
    return count;
}

int EquationParser::makeNodeBranchOut(QString equationString,
                                       QString matchString,
                                       int start,
                                       int end,
                                       int count,
                                       ExpressionItem * thisNode, //the parents child
                                       ExpressionItem * parentNode)
{
    qDebug()<<"Level: "<<count<<", adding node: "<<matchString<<", branching outside";
    thisNode->m_string = matchString;
    thisNode->m_parent = parentNode;
    QString sectionStr0=equationString.section("",0,start);
    ExpressionItem * childNode0 = new ExpressionItem(this);
    processSyntaxTree(sectionStr0,count+1,childNode0,thisNode);
    thisNode->m_children.append(childNode0);
    QString sectionStr1=equationString.section("",end+1);
    ExpressionItem * childNode1 = new ExpressionItem(this);
    thisNode->m_children.append(childNode1);
    processSyntaxTree(sectionStr1,count+1,childNode1,thisNode);
    return count;
}

ExpressionItem *EquationParser::expressionGraph()
{
    return m_expressionGraph;
}

//QVector<ExpressionItem *> EquationParser::branchInside(QString equationString,
//                                                       QString matchString,
//                                                       int level,
//                                                       int start,
//                                                       int end)
//{
//    QVector<ExpressionItem *> expressionVector;
//    qDebug()<<"Level: "<<level<<", branching inside: "<<matchString<<" from: "<<equationString;
//    QString sectionStr=equationString.section("",start+2,end-1);
//    expressionVector.append(makeLeaf("(",level+1));
//    expressionVector.append(processSyntaxTree(sectionStr,level+1));
//    expressionVector.append(makeLeaf(")",level+1));
//    return expressionVector;
//}

//QVector<ExpressionItem *> EquationParser::branchOutside(QString equationString,
//                                                        QString matchString,
//                                                        int level,
//                                                        int start,
//                                                        int end)
//{
//    QVector<ExpressionItem *> expressionVector;
//    qDebug()<<"Level: "<<level<<", branching outside: "<<matchString<<" from: "<<equationString;
//    QString sectionStr0=equationString.section("",0,start);
//    expressionVector.append(processSyntaxTree(sectionStr0,level+1));
//    expressionVector.append(makeLeaf(matchString,level+1));
//    QString sectionStr1=equationString.section("",end+1);
//    expressionVector.append(processSyntaxTree(sectionStr1,level+1));

//    return expressionVector;
//}

//QVector<ExpressionItem *> EquationParser::branchReplace(QString equationString,
//                                                        QString matchString,
//                                                        int level,
//                                                        int start,
//                                                        int end)
//{
//    QVector<ExpressionItem *> expressionVector;
//    qDebug()<<"Level: "<<level<<", branching outside: "<<matchString<<" from: "<<equationString;
//    QString sectionStr0=equationString.section("",0,start);
//    expressionVector.append(processSyntaxTree(sectionStr0,level+1));
//    expressionVector.append(makeLeaf(matchString,level+1));
//    QString sectionStr1=equationString.section("",end+1);
//    expressionVector.append(processSyntaxTree(sectionStr1,level+1));

//    return expressionVector;
//}
