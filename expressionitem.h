#ifndef EXPRESSIONITEM_H
#define EXPRESSIONITEM_H

#include <QObject>
#include "regexlist.h"
#include "z3++.h"

class ExpressionItem : public QObject
{
    Q_OBJECT
public:
    explicit ExpressionItem(QObject *parent = nullptr);

    QString m_string="";
    QVector<ExpressionItem *> m_children;
    ExpressionItem * m_parent;

private:

};

#endif // EXPRESSIONITEM_H
