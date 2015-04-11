#ifndef LEMMA_H
#define LEMMA_H
#include <QString>
#include <vector>
class Lemma
{
public:
    Lemma(const QString& parola, const QString& definizione, const std::vector<QString>& plur=std::vector<QString>());
    QString getWord() const;
    QString getDesc() const;
    bool operator==(const Lemma& lem) const;
    bool operator!=(const Lemma& lem) const;
private:
    QString word, desc;
    std::vector<QString> plural;
};

#endif // LEMMA_H
