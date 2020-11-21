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
        QTextStream s(stdin);
        equationStringInput = s.readLine();

        EquationParser equationParser;
        equationParser.parseEquation(equationStringInput,0);
        QVector<ExpressionItem*>expressionSet = equationParser.expressionSet();
        for (int i = 0; i<expressionSet.size();i++){
            qDebug()<<"     Match String:"<<expressionSet[i]->string();
        }
    }
    while (equationStringInput != "exit");

    return a.exec();
}
