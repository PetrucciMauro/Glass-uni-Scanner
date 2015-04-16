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

int Lemma::contains(const QString& par) const{
    int lunghezza=0;
    if (word.contains(par)){
        lunghezza=word.length();
    }
    else
    {
        std::vector<QString>::const_iterator it=plural.begin();
        for(; it!=plural.end() && !lunghezza;++it){
            if ((*it).contains(par))
               lunghezza=(*it).length();
        }
    }
    return lunghezza;
}
