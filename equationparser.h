#ifndef EQUATIONPARSER_H
#define EQUATIONPARSER_H

#include <QObject>
#include <QDebug>
#include "regexlist.h"
#include "expressionitem.h"

class EquationParser : public QObject
{
    Q_OBJECT
public:
    explicit EquationParser(QObject *parent = nullptr);

    void appendExpressionItem(ExpressionItem *expressionItem);
    void appendExpressionItem();
    void appendExpressionItem(QString string,
                              int matchTypeId,
                              int matchStart,
                              int matchEnd,
                              int matchLength);

    void parseEquation(QString equationString);//pre and post recursion processing
    QVector<ExpressionItem*> processSyntaxTree(QString equationString, int count); //recursion for AST
    ExpressionItem * makeLeaf(QString matchString,
                            int id,
                            int start,
                            int end,
                            int length,
                            int count);
    QVector<ExpressionItem*> branchInside(QString equationString,
                                         QString matchString,
                                         int count,
                                         int id,
                                         int start,
                                         int end,
                                         int length);
    QVector<ExpressionItem*> branchOutside(QString equationString,
                                         QString matchString,
                                         int count,
                                         int id,
                                         int start,
                                         int end,
                                         int length);

    QVector<ExpressionItem *> expressionSet() const;

    enum RecurseType{
        ONE_OPERAND,
        TWO_OPERAND
    };

private:
    QVector<ExpressionItem*> m_expressionSet;
    RegExList m_regExList;
};

#endif // EQUATIONPARSER_H
