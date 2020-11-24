#include <QCoreApplication>
#include <QDebug>
//#include <QRegularExpression>
//#include <QRegularExpressionMatchIterator>
//#include "regexmatcher.h"
#include "equationparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString equationStringInput = "";
    do{
        qDebug()<<"Enter an equation: ";
        QTextStream s(stdin);
        equationStringInput = s.readLine();

        EquationParser equationParser;
        equationParser.parseEquation(equationStringInput);
        QVector<ExpressionItem*> expressionSet = equationParser.expressionSet();
        //if(expressionSet.size()!=0){
        qDebug()<<"Match...";
        for (int i = 0; i<expressionSet.size();i++){
            qDebug()<<"     "<<expressionSet[i]->string();
            qDebug()<<"     Type: "<<expressionSet[i]->matchTypeId();
            qDebug()<<"     Start/Length/End:"<<expressionSet[i]->matchStart()<<"/"<<
                                                          expressionSet[i]->matchLength()<<"/"<<
                                                          expressionSet[i]->matchEnd();
       // }
        //} else {
        //    qDebug()<<"parsing error!";
        }
    }
    while (equationStringInput != "exit");

    return a.exec();
}
