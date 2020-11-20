#include <QCoreApplication>
#include <QDebug>
//#include <QRegularExpression>
//#include <QRegularExpressionMatchIterator>
#include "regexparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString equationStringInput = "";
    do{
        QTextStream s(stdin);
        equationStringInput = s.readLine();

        RegExParser regexparser;
        regexparser.parseString(equationStringInput);
    }
    while (equationStringInput != "exit");

    return a.exec();
}
