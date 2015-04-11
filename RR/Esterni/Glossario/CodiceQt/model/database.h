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

private:
	 QMap<QString, Lemma*> db;
      const QString norme[7]= {  QString::fromStdString("ambientelavoro.tex"),
                                          QString::fromStdString("comunicazioni.tex"),
                                          QString::fromStdString("documenti.tex"),
                                          QString::fromStdString("glossario.tex"),
                                          QString::fromStdString("ingegneriaRequisiti.tex"),
                                          QString::fromStdString("introduzione.tex"),
                                          QString::fromStdString("riunioni.tex")};

     const QString qualifica[6]={QString::fromStdString("gestioneAmministrativa.tex"),
                                                      QString::fromStdString("introduzione.tex"),
                                                      QString::fromStdString("obiettivi.tex"),
                                                      QString::fromStdString("pianoDiQualifica.tex"),
                                                      QString::fromStdString("strategiaVerifica.tex"),
                                                      QString::fromStdString("stumentiTecnicheMetodi.tex")};

     const  QString analisi[13]={QString::fromStdString("UC1.tex"),QString::fromStdString("UC1.1.tex"),QString::fromStdString("UC1.2.tex"),
                                                   QString::fromStdString("UC1.3.tex"),QString::fromStdString("UC1.4.tex"),QString::fromStdString("UC1.5.tex"),
                                                   QString::fromStdString("UC1.6.tex"),QString::fromStdString("UC1.7.tex"),QString::fromStdString("UC1.8.tex"),
                                                   QString::fromStdString("UC1.9.tex"),QString::fromStdString("UC1.10.tex"),QString::fromStdString("UC1.11.tex"),
                                                   QString::fromStdString("UC1.12.tex")};

     const QString filesLatex[7]= {QString::fromStdString("NormeDiProgetto_v.1.0.tex"),
                                                       QString::fromStdString("AnalisiDeiRequisiti_v.1.0.tex"),
                                                       QString::fromStdString("PianoDiProgetto_v.1.0.tex"),
                                                       QString::fromStdString("PianoDiQualifica_v.1.0.tex"),
                                                       QString::fromStdString("StudioDiFattibilita_v.1.0.tex"),
                                                       QString::fromStdString("NormeDiAmministrazione_v.1.0.tex")};

};

#endif // DATABASE_H
