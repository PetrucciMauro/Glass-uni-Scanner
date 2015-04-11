#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QMap>
#include "model/lemma.h"
#include <map>
#include <vector>
class DataBase
{
public:
	 DataBase();
	 void load();
	 void save();
	 void texprint();
	 void inserisci(const QString& w, const QString& d);
     void replaceFile(const QString& nomefile, const QString& oldw);
     void applyGlossario(const QString& nomefile);

private:
	 QMap<QString, Lemma*> db;

};

#endif // DATABASE_H
