#include "database.h"
#include "lemma.h"
#include <QDomDocument>
#include <QFile>
#include "eccezione.h"
#include <iostream>
#include <QTextStream>
#include <QRegularExpression>
DataBase::DataBase(){

}


void DataBase::load(){
	 QFile file("../glossario.xml");

	 QDomDocument xml;
	 if(!file.open(QIODevice::ReadOnly)){
		  throw Ecc_FileNotFound;
	 }
	 xml.setContent(&file);
	 QDomElement root=xml.documentElement();
	 file.close();

	 //Reading from the file
	 QDomElement lemma=root.firstChild().toElement();
	 bool found=false;
	 // Loop while there is a child
	 while(!lemma.isNull()&&!found)
	 {
		  // Check if the child tag name is utente
		  if (lemma.tagName()=="lemma")
		  {
				// Get the first child of the component
				QDomElement child=lemma.firstChild().toElement();
				QString parola;
				QString descrizione;
				// Read each child of the utente node
				std::vector<QString> p;
				while (!child.isNull())
				{
					 // Read Name and value
					 if (child.tagName()=="word") parola=child.firstChild().toText().data().simplified();
					 if (child.tagName()=="plural") p.push_back(child.firstChild().toText().data().simplified());
					 // Next child
					 if (child.tagName()=="desc"){
						  descrizione=child.firstChild().toText().data().simplified();
					 }
					 Lemma* l = new Lemma(parola, descrizione, p);
					 db[parola]=l;
					 if (parola.contains(QString(" "))){
						  reservedlist[parola]=l;

						  std::vector<QString>::const_iterator tempit=p.begin();
						  for(;tempit!=p.end();++tempit){
								reservedlist[*tempit]=l;
						  }
					 }

					 child = child.nextSibling().toElement();
				}//end while !child.isNull()

		  }//end if tag==lemma
		  // Next lemma
		  lemma = lemma.nextSibling().toElement();
	 }
	 /*QMap<QString, Lemma*>::const_iterator i=db.begin();
		  for(;i!=db.end();++i){
				 std::cout<<i->second->getWord().toStdString()<<std::endl;
				 i.
		  }*/
}

void DataBase::save(){
	 QFile file("../glossario.xml");

	 QDomDocument xml;
	 if(!file.open(QIODevice::ReadWrite))
	 {
		  throw Ecc_FileNotFound;
	 }
	 xml.setContent(&file);
	 QDomElement root = xml.documentElement();

	 QDomElement lemma = root.firstChild().toElement();

	 while(!lemma.firstChild().isNull()){
		  QDomElement templemma=lemma;
		  lemma=templemma.nextSibling().toElement();
		  root.removeChild(templemma);
	 }
	 QMap<QString, Lemma*>::const_iterator it=db.begin();
	 for(;it!=db.end();++it){
		  QDomElement nlemma=xml.createElement("lemma");
		  root.appendChild(nlemma);

		  QDomElement par=xml.createElement("word");
		  nlemma.appendChild(par);

		  QString temp=it.value()->getWord();
		  temp[0]=temp[0].toUpper();
		  std::vector<QString>::const_iterator i=it.value()->getPlural().begin();
		  for(; i!=it.value()->getPlural().end();++i){
				QDomElement plur=xml.createElement("plural");
				nlemma.appendChild(plur);
				QDomText ptxt=xml.createTextNode(*i);
				plur.appendChild(ptxt);
		  }
		  QDomText txt=xml.createTextNode(temp);
		  par.appendChild(txt);
		  QDomElement des=xml.createElement("desc");
		  nlemma.appendChild(des);
		  QDomText dtxt=xml.createTextNode(it.value()->getDesc());
		  des.appendChild(dtxt);
	 }
	 file.resize(0);
	 QTextStream stream(&file);
	 stream.setDevice(&file);
	 xml.save(stream,4);
	 file.close();
}
void DataBase::texprint(){
	 QFile file("../parti/glossario.tex");

	 if(!file.open(QIODevice::WriteOnly))
	 {throw Ecc_FileNotFound;}
	 QTextStream out(&file);
	 out.setCodec("UTF-8");
	 QMap<QString, Lemma*>::const_iterator it=db.begin();

	 out<<"\\section{Glossario}{ \n";
	 QChar temp;
	 bool primo=true;
	 for(;it!=db.end();++it){
		  QString lemma=it.value()->getWord();
		  QString descr=it.value()->getDesc();
		  if(primo || (lemma[0]>'9' && lemma[0]!=temp)){
				QString what;
				if(primo){
					 temp=lemma[0];
					 if(lemma[0].toLatin1()<='9')
						  what="0-9";
					 else
						  what=lemma[0];
				}
				if(lemma[0]>'9' && lemma[0]!=temp){
					 out<<"\\end{longtabu} \n";
					 out<<"\\newpage \n";
					 temp=lemma[0];
					 what=lemma[0];
				}
				out<<"\\subsection{"<<what.toLatin1()<<"} \n";
				out<<"\\hfill\\Huge{\\textbf{"<<what.toLatin1()<<"}} \\\\ \n";
				out<<"\\normalsize \n";
				out<<"\\begin{longtabu} to \\textwidth{p{3cm} p{8cm}}\n";
				out<<"\\toprule \\\\ \n";}
		  out<<"\\textbf{"<<lemma.toLatin1()<<"} & ";
		  out<<descr.toLatin1()<<" \\\\ \n \\\\ \n";
		  if(primo)
				primo=false;
	 }
	 out<<"\\end{longtabu} \n }";
	 file.close();
}

void DataBase::inserisci(const QString& w, const QString& d){
	 QString temp(w);
	 temp[0]=temp[0].toUpper();
	 if(db.count(temp)>0)
		  throw Ecc_ParolaPresente;
	 else{
		  db[temp]=new Lemma(temp,d);
	 }
}

void DataBase::replaceFile(const QString& nomefile,const QString& oldw){
	 QFile file(nomefile);
	 if(!file.open(QIODevice::ReadWrite))
	 {return;	throw Ecc_FileNotFound;}
	 QString temp=oldw;
	 temp[0]=oldw[0].toUpper();
	 QString q("");
	 if(temp.contains(" ")){
		  QStringList p=temp.split(QRegularExpression(" "));

		  QStringList::iterator strit=p.begin();
		  for(; strit!=p.end();++strit){
				if (q!=""){
					 q=q+QString(" ");
				}
				(*strit)[0]=(*strit)[0].toUpper();
				q=q+(*strit);
		  }
	 }

	 QString perreg=QString("((^)|([\\s])|[^:a-z])")+temp+QString("(\\.|,|;|:|$|\\s|[)])");
	 QRegExp exp(perreg);

	 QString nuova=oldw+QString("\\ped{g}");
	 QString oldwl=oldw.toLower();

	 QString nuoval=oldwl+QString("\\ped{g}");
	 if(reservedlist.contains(oldw)||reservedlist.contains(q)||reservedlist.contains(temp.toLower())){

		  QString text(file.readAll());
		  for (int i=0; i<text.length(); ++i){
				int x=text.indexOf(exp, i);
				if (x!=-1){
					 int y;
					 if (text[x]==temp[0])
						  y=x;
					 else
						  y=x+1;
					 text.remove(y,temp.length());
					 text.insert(y,nuova);
					 i+=temp.length();
					 std::cout<<temp.toStdString()<<std::endl;
				}
				else
					 i=text.length();
		  }
		  QString perregl=QString("((^)|([\\s])|[^:a-z\\/]|)")+oldwl+QString("(\\.|,|;|:|$|\\s|[)])");
		  QRegExp expl(perregl);
		  for (int i=0; i<text.length(); ++i){
				int x=text.indexOf(expl, i);
				if (x!=-1){
					 int y;
					 if (text[x]==oldwl[0])
						  y=x;
					 else
						  y=x+1;

					 text.remove(y,oldwl.length());
					 text.insert(y,nuoval);
					 i+=oldwl.length();
					 std::cout<<oldwl.toStdString()<<std::endl;
				}
				else i=text.length();
		  }

		  file.resize(0); // go to the beginning of the file
		  file.write(text.toUtf8()); // write the new text back to the file
	 }/*if(reservedlist.contains(oldw)||reservedlist.contains(q)||reservedlist.contains(temp.toLower()))*/
	 else{
		  QString text(file.readAll());
		  bool trovato=false;
		  bool parz=false;
		  for (int i=0; i<text.length(); ++i){
				trovato=false;

				int x=text.indexOf(exp, i);
				if (x!=-1){
					 int y;
					 if (text[x]==temp[0]||text[x]==oldw[0])
						  y=x;
					 else
						  y=x+1;

					 QMap<QString, Lemma*>::const_iterator mit=reservedlist.begin();
					 for(;mit!=reservedlist.end()&&!trovato;++mit){
						  if(mit.value()->contains(temp) || (mit.value()->contains(q) && q!="" || (mit.value()->contains(oldwl)))){
								parz=true;
								QString t=text.mid(y, mit.value()->getWord().length());
								if(!mit.value()->contains(t)){
									 trovato=true;
								}
						  }
					 }
					 if((trovato)||(!parz)){
						  text.remove(y,temp.length());
						  text.insert(y,nuova);
						  i+=temp.length();
						  std::cout<<temp.toStdString()<<std::endl;
					 }

				}/*if (x!=-1)*/
				else
					 i=text.length();
		  }
		  if(!trovato){
				QString perregl=QString("((^)|([\\s])|[^:a-z\\/])")+oldwl+QString("(\\.|,|;|:|$|\\s|/|[)])");
				QRegExp expl(perregl);
				bool parzl=false;
				for (int i=0; i<text.length(); ++i){
					 int x=text.indexOf(expl, i);
					 if (x!=-1){
						  int y;
						  if (text[x]==oldwl[0])
								y=x;
						  else
								y=x+1;
						  QMap<QString, Lemma*>::const_iterator mit=reservedlist.begin();
						  for(;mit!=reservedlist.end()&&!trovato;++mit){

								if (mit.value()->contains(oldw)){
									 parzl=true;
									 QString t=text.mid(y, mit.value()->getWord().length());

									QString qt("");
									 QStringList tt=t.split(QRegularExpression(" "));

									 QStringList::iterator strit=tt.begin();
									 for(; strit!=tt.end();++strit){
										  if (qt!=""){
											  qt=qt+QString(" ");
										  }
										  (*strit)[0]=(*strit)[0].toUpper();
										  qt=qt+(*strit);
									 }
									 if(!mit.value()->contains(qt)&&!mit.value()->contains(t)){
										  trovato=true;
									 }
								}/*if (mit.value()->contains(oldwl))*/

						  }
						  if(trovato||!parzl){
								text.remove(y,oldwl.length());
								text.insert(y,nuova);
								i+=oldwl.length();
								std::cout<<oldwl.toStdString()<<std::endl;
						  }


					 }
					 else i=text.length();
				}
		  }

		  file.resize(0); // go to the beginning of the file
		  file.write(text.toUtf8()); // write the new text back to the file
	 }

	 file.close();

}

void DataBase::applyGlossario(const QString& nomefile){

	 QFile file(nomefile);
	 if(!file.open(QIODevice::ReadWrite))
	 {return;	throw Ecc_FileNotFound;}
	 QString text(file.readAll());
	 text.replace(QString("\\ped{g}"),QString(""));

	 file.resize(0); // go to the beginning of the file
	 file.write(text.toUtf8()); // write the new text back to the file

	 file.close();

	 QMap<QString, Lemma*>::const_iterator it=db.begin();
	 for (;it!=db.end();++it){
		  replaceFile(nomefile, it.value()->getWord());
		  std::vector<QString>::const_iterator i=it.value()->getPlural().begin();
		  for(; i!=it.value()->getPlural().end();++i){
				replaceFile(nomefile, *i);
		  }
	 }
}
