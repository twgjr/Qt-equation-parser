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
    ExpressionItem * m_parent;
    QVector<ExpressionItem*> m_children;

private:

};

#endif // EXPRESSIONITEM_H
