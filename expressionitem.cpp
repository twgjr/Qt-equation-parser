#include "expressionitem.h"

ExpressionItem::ExpressionItem(QObject *parent) : QObject(parent)
{

}

QString ExpressionItem::string() const
{
    return m_string;
}

void ExpressionItem::setString(const QString &string)
{
    m_string = string;
}

int ExpressionItem::matchTypeId() const
{
    return m_matchTypeId;
}

void ExpressionItem::setMatchTypeId(int matchTypeId)
{
    m_matchTypeId = matchTypeId;
}

int ExpressionItem::matchStart() const
{
    return m_matchStart;
}

void ExpressionItem::setMatchStart(int matchStart)
{
    m_matchStart = matchStart;
}

int ExpressionItem::matchEnd() const
{
    return m_matchEnd;
}

void ExpressionItem::setMatchEnd(int matchEnd)
{
    m_matchEnd = matchEnd;
}

int ExpressionItem::matchLength() const
{
    return m_matchLength;
}

void ExpressionItem::setMatchLength(int matchLength)
{
    m_matchLength = matchLength;
}
