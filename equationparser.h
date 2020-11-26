#ifndef EQUATIONPARSER_H
#define EQUATIONPARSER_H

#include <QObject>
#include <QDebug>
#include "regexlist.h"
#include "expressionitem.h"
#include "z3++.h"

class EquationParser : public QObject
{
    Q_OBJECT
public:
    explicit EquationParser(QObject *parent = nullptr);

    void parseEquation(QString equationString);//pre and post recursion processing
    bool processSyntaxTree(QString equationString,
                           int depth,
                           ExpressionItem * parentNode); //recursion for AST
    bool makeLeaf(QString matchString,
                  int depth,
                  ExpressionItem * parentNode);
    bool makeNodeBranchOut(QString equationString,
                           QString matchString,
                           int start,
                           int end,
                           int depth,
                           ExpressionItem * parentNode);
    bool makeNodeBranchIn(QString equationString,
                          QString matchString,
                          int start,
                          int end,
                          int depth,
                          ExpressionItem * parentNode);

    void compileZ3Expression();
    ExpressionItem *expressionGraph();

private:
    ExpressionItem * m_expressionGraph;
    RegExList m_regExList;
};

#endif // EQUATIONPARSER_H
