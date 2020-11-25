#include <QCoreApplication>
#include <QDebug>
#include "equationparser.h"

//visit all children to reassemble the string
QString concatGraph(ExpressionItem * expressionItem){
    QString string;
    for (int i = 0; i < expressionItem->m_children.size();i++){
        string += concatGraph(expressionItem->m_children[i]);
        if(expressionItem->m_children.isEmpty()){
            return expressionItem->m_string;
        }
    }
    return string;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QString equationStringInput = "";
    do{
        qDebug()<<"Enter an equation: ";
        QTextStream s(stdin);
        equationStringInput = s.readLine();
        if(equationStringInput.isEmpty()){
            qDebug()<<"Empty equation attemped!";
            continue;
        }

        EquationParser equationParser;
        qDebug()<<"calling parse equation.";
        equationParser.parseEquation(equationStringInput);
        ExpressionItem * expressionGraph = equationParser.expressionGraph();
        qDebug()<<"Match...";
        QString concatString = concatGraph(expressionGraph);

        if(QString::compare(concatString,equationStringInput)==0){
            // concat into a z3 expression

            // load into z3 expression vector

        } else {
            //error
            qDebug()<<"Invalid equation";
        }
        qDebug()<<"Concatenated"<<concatString;
    }
    while (equationStringInput != "exit");


    // solve the set of equations

    return a.exec();
}
