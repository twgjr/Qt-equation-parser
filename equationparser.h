#ifndef EQUATIONPARSER_H
#define EQUATIONPARSER_H

#include <QObject>
#include <QDebug>
//#include "regexmatcher.h"
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

    QVector<ExpressionItem*> parseEquation(QString equationString, int count);

    QVector<ExpressionItem *> expressionSet() const;

private:
    QVector<ExpressionItem*> m_expressionSet;
};

#endif // EQUATIONPARSER_H
