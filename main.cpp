#include <QCoreApplication>
#include <QDebug>
#include "equationparser.h"

//visit all children to reassemble the string
QString concatGraph(ExpressionItem * expressionItem){
    QString string="";
    if(expressionItem->m_children.size() == 0){
        return expressionItem->m_string;
    }
    if(expressionItem->m_children.size() == 1){
        string += expressionItem->m_string;
        string += concatGraph(expressionItem->m_children[0]);
    }
    if(expressionItem->m_children.size() == 2){
        string += concatGraph(expressionItem->m_children[0]);
        string += expressionItem->m_string;
        string += concatGraph(expressionItem->m_children[1]);
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
        ExpressionItem * exprGraph = equationParser.expressionGraph();
        qDebug()<<"Match...";
        QString concatString = concatGraph(exprGraph);

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
