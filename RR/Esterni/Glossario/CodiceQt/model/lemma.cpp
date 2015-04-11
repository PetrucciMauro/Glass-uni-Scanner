#include "lemma.h"

Lemma::Lemma(const QString& parola, const QString& definizione):word(parola), desc(definizione){}

bool Lemma::operator==(const Lemma& lem) const{
	 return word==lem.word && desc==lem.desc;
}
bool Lemma::operator!=(const Lemma& lem) const{
	 return !(*this==lem);
}

QString Lemma::getWord()const{return word;}
QString Lemma::getDesc()const{return desc;}
