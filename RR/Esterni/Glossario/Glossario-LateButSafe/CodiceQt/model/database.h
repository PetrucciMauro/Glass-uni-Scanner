#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QMap>
#include "model/lemma.h"
#include <map>

class DataBase
{
public:
	 DataBase();
	 void load();
	 void save();
	 void texprint();
	 void inserisci(const QString& w, const QString& d);
private:
	 QMap<QString, Lemma*> db;
};

#endif // DATABASE_H
