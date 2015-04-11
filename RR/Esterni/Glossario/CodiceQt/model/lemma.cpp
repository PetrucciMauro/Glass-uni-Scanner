#include "lemma.h"

Lemma::Lemma(const QString& parola, const QString& definizione, const std::vector<QString>& plur):word(parola),
    desc(definizione), plural(plur){}

bool Lemma::operator==(const Lemma& lem) const{
     return word==lem.word && desc==lem.desc && plural==lem.plural;
}
bool Lemma::operator!=(const Lemma& lem) const{
	 return !(*this==lem);
}
const std::vector<QString>& Lemma::getPlural() const{
    return plural;
}
QString Lemma::getWord()const{return word;}
QString Lemma::getDesc()const{return desc;}
