#ifndef LEMMA_H
#define LEMMA_H
#include <QString>

class Lemma
{
public:
    Lemma(const QString& parola, const QString& definizione);
    QString getWord() const;
    QString getDesc() const;
    bool operator==(const Lemma& lem) const;
    bool operator!=(const Lemma& lem) const;
private:
    QString word, desc;
};

#endif // LEMMA_H
