#ifndef MATCHING_H
#define MATCHING_H

#include <QObject>

class Matching : public QObject
{
    Q_OBJECT
public:
    explicit Matching(QObject *parent = nullptr);

    enum MatchTypes{
        NO_MATCH,
        VARIABLE,
        CONSTANT,
        OPERATOR,
        OTHER
    };

    QStringList m_matches;
    int m_matchTypeId = NO_MATCH;
    int m_matchStart = 0;
    int m_matchEnd = 0;
};

#endif // MATCHING_H
