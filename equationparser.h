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
    int processSyntaxTree(QString equationString,
                           int count,
                           ExpressionItem * thisNode,
                           ExpressionItem * parentNode); //recursion for AST
    int makeLeaf(QString matchString,
                  int count,
                  ExpressionItem * thisNode,
                  ExpressionItem * parentNode);
    int makeNodeBranchOut(QString equationString,
                           QString matchString,
                           int start,
                           int end,
                           int count,
                           ExpressionItem * thisNode,
                           ExpressionItem * parentNode);

    QVector<ExpressionItem*> branchInside(QString equationString,
                                         QString matchString,
                                         int count,
                                         int start,
                                         int end);

    QVector<ExpressionItem*> branchOutside(QString equationString,
                                         QString matchString,
                                         int count,
                                         int start,
                                         int end);

    QVector<ExpressionItem*> branchReplace(QString equationString,
                                         QString matchString,
                                         int count,
                                         int start,
                                         int end);

    void compileZ3Expression();

    ExpressionItem * expressionGraph();

private:
    ExpressionItem * m_expressionGraph;
    RegExList m_regExList;
};

#endif // EQUATIONPARSER_H
