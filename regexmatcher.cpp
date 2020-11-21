#include "regexmatcher.h"

RegExMatcher::RegExMatcher(QObject *parent) : QObject(parent)
{

}

void RegExMatcher::matchString(QString string, ExpressionItem* expressionItem)
{
    // clean up and simplify the string format
    string.replace( " ", "" ); // remove spaces

    int openingParenthTotal=0;
    int closingParenthTotal=0;
    int numComparisons=0;
    int numVariables=0;
    int numConstants=0;
    int totalMatchLength=0;

    for(int intIter = 0 ; intIter < regexStrings.size() ; intIter++){
        QRegularExpression regex(regexStrings[intIter]);
        QRegularExpressionMatch match = regex.match(string);
        if(match.hasMatch()){
            switch (intIter) {
            case OPEN_PAR:openingParenthTotal++; expressionItem->setMatchTypeId(OPEN_PAR); break;
            case CLOSE_PAR:closingParenthTotal++; expressionItem->setMatchTypeId(CLOSE_PAR); break;
            case EQ: numComparisons++;expressionItem->setMatchTypeId(EQ); break;
            case LTOE: numComparisons++;expressionItem->setMatchTypeId(LTOE); break;
            case GTOE: numComparisons++;expressionItem->setMatchTypeId(GTOE); break;
            case LT: numComparisons++;expressionItem->setMatchTypeId(LT); break;
            case GT: numComparisons++;expressionItem->setMatchTypeId(GT); break;
            case POW: expressionItem->setMatchTypeId(MULT); break;
            case MULT: expressionItem->setMatchTypeId(DIV); break;
            case DIV: expressionItem->setMatchTypeId(POW); break;
            case ADD: numComparisons++;expressionItem->setMatchTypeId(GT); break;
            case SUBT: expressionItem->setMatchTypeId(MULT); break;
            case VARIABLE: numVariables++; expressionItem->setMatchTypeId(VARIABLE); break;
            case CONSTANT: numConstants++; expressionItem->setMatchTypeId(CONSTANT); break;
            default: break;
            }
            expressionItem->setString(match.captured(0));
            expressionItem->setMatchStart(match.capturedStart());
            expressionItem->setMatchEnd(match.capturedEnd());
            totalMatchLength += abs(match.capturedEnd()-match.capturedStart());
        }
    }
}
//    /*
//     Need more checks for:
//     1. parenthesis in the wrong place
//        a. same number of open/close on either side of comparison
//        b. outside of parenthesis must touch an operator.  inside must touch value or variable.
//     2. operators have the required operands. a*b requires two, not(a) requires one
//     */


//    // Check for errors, if no errors then convert to z3 expression
//    bool parseError=false;
//    QString parseErrorMessage = "";
//    if(numVariables==0){parseError=true;parseErrorMessage+="Error: Must have at least one variable!\n";}
//    if(numComparisons!=1){parseError=true;parseErrorMessage+="Error: One comparison operator is required/allowed!\n";}
//    if(openingParenthTotal!=closingParenthTotal){parseError=true;parseErrorMessage+="Error: Parenthesis not balanced!\n";}
//    if(totalMatchLength!=string.length()){parseError=true;parseErrorMessage+="Error: Match length does not match string!\n";}
//    for (int i = 0 ; i < m_wordSet.size();i++){
//        for( int j = 0 ; j < m_wordSet.size();j++){
//            if(i>=j){
//                continue;
//            }else if (m_wordSet[i]->m_matchStart < m_wordSet[j]->m_matchStart &&
//                      m_wordSet[j]->m_matchStart < m_wordSet[i]->m_matchEnd){
//                parseError=true;
//                parseErrorMessage+="Error: Overlapping matches!\n";
//            }
//        }
//    }

//    if(parseError){
//        qDebug().noquote()<<"Parse error:\n"<<parseErrorMessage;
//    }else{
//        // finally, order the word set like the original string
//        for (int i = 0 ; i < m_wordSet.size();i++){
//            for( int j = 0 ; j < m_wordSet.size();j++){
//                if(i>=j){
//                    continue;
//                }else if (m_wordSet[i]->m_matchStart > m_wordSet[j]->m_matchStart){
//                    m_wordSet.swapItemsAt(i,j);
//                }
//            }
//        }
//        // convert each item in stringlist to an item in QVector<z3 expr>
//        // solver will later concatenate the vector into one expression
//        // solver will need to generate multiple versions at runtime of differential equations
//        // differential equaitons will have to have distinct variables dx_(n)/dt_(n) = [x_(n-1)-x(n)]/[t_(n-1)-t(n)]
//        // dx_(n+1)/dt_(n+1) = [x_(n)-x(n+1)]/[t_(n)-t(n+1)]
//        qDebug()<<"final match set: ";
//        //print set to check if sorted
//        for (int i = 0; i<m_wordSet.size();i++){
//            qDebug()<<"     Match Start:"<<m_wordSet[i]->m_matchStart;
//            qDebug()<<"     Matches:"<<m_wordSet[i]->m_matches;
//        }
//    }
//}
