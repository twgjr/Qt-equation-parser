#include "regexparser.h"

RegExParser::RegExParser(QObject *parent) : QObject(parent)
{

}

void RegExParser::parseString(QString string)
{
    qDebug()<<"String input: "<<string;

    // clean up and simplify the string format
    string.replace( " ", "" ); // remove spaces
    qDebug()<<"Simplified input string: "<<string;

    int openingParenthesis=0;
    int closingParenthesis=0;
    int numComparisons=0;
    int numVariables=0;
    int numConstants=0;

    for(int intIter = 0 ; intIter < regexStrings.size() ; intIter++){
        QRegularExpression regex(regexStrings[intIter]);
        //Matching words;

        QRegularExpressionMatchIterator regExIterator = regex.globalMatch(string);
        while (regExIterator.hasNext()) {
            QRegularExpressionMatch match = regExIterator.next();
            if(match.hasMatch()){
                Matching * words = new Matching(this);
                switch (intIter) {
                case VARIABLE: numVariables++; words->m_matchTypeId = words->VARIABLE; break;
                case CONSTANT: numConstants++; words->m_matchTypeId = words->CONSTANT; break;
                case MATH_OPERATOR: words->m_matchTypeId = words->OPERATOR; break;
                case POWER_OPERATOR: words->m_matchTypeId = words->OPERATOR; break;
                case COMPARISON_OPERATOR:numComparisons++; words->m_matchTypeId = words->OPERATOR; break;
                case OPENING_PARENTHESIS:openingParenthesis++; words->m_matchTypeId = words->OTHER; break;
                case CLOSING_PARENTHESIS:closingParenthesis++; words->m_matchTypeId = words->OTHER; break;
                default: break;
                }
                words->m_matches << match.captured(0);
                words->m_matchStart = match.capturedStart();
                words->m_matchEnd = match.capturedEnd();

                qDebug()<<"Matched regex: #"<<intIter<<" ( "<< regexStrings[intIter]<<" ) "<<words->m_matches;
                appendMatchingItem(words);
            }
        }

    }
    qDebug()<<"final match set: ";
    for (int i = 0; i<m_wordSet.size();i++){
        qDebug()<<"     Match Type ID:"<<m_wordSet[i]->m_matchTypeId;
        qDebug()<<"     Matches:"<<m_wordSet[i]->m_matches;
        qDebug()<<"     Match Start:"<<m_wordSet[i]->m_matchStart;
        qDebug()<<"     Match End:"<<m_wordSet[i]->m_matchEnd;
    }
    qDebug()<<"Number of Variables: "<<numVariables;
    qDebug()<<"Number of Constants: "<<numConstants;
    qDebug()<<"Number of Comparison Operators: "<<numComparisons;
    qDebug()<<"Difference in parenthesis: "<<abs(openingParenthesis-closingParenthesis);
    qDebug()<<"Length of Input String = "<<string.length();

    // Check for errors, if no errors then convert to z3 expression

    //check if there was any mismatches or unmatched parts of string
    for (int i =0 ; i < m_wordSet.size();i++){
        //
    }

    //sort the word set in the original order

    bool parseError=false;
    QString parseErrorMessage = "No errors";
    if(numVariables==0){parseError=true;parseErrorMessage="Must have at least one variable!";}
    if(numComparisons!=1){parseError=true;parseErrorMessage="One comparison operator is required/allowed!";}
    if(openingParenthesis!=closingParenthesis){parseError=true;parseErrorMessage="Parenthesis not balanced!";}

    if(parseError){
        qDebug()<<"Parse error: "<<parseErrorMessage;
    }else{
        // convert each item in stringlist to an item in QVector<z3 expr>
        // solver will later concatenate the vector into one expression
        // solver will need to generate multiple versions at runtime of differential equations
        // differential equaitons will have to have distinct variables dx_(n)/dt_(n) = [x_(n-1)-x(n)]/[t_(n-1)-t(n)]
        // dx_(n+1)/dt_(n+1) = [x_(n)-x(n+1)]/[t_(n)-t(n+1)]
        qDebug()<<"Parsing okay.  This is where would convert to z3";
    }
}

void RegExParser::appendMatchingItem()
{
    Matching * matchingItem = new Matching(this);
    appendMatchingItem(matchingItem);
}

void RegExParser::appendMatchingItem(Matching *matchingItem)
{
    m_wordSet.append(matchingItem);
}
