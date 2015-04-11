#include "dbcontroller.h"
#include "model/eccezione.h"

DbController::DbController():database(new DataBase()){	}
void DbController::carica(){
		try{database->load();}
		catch(eccezione e){throw e;}
	}

void DbController::inserisci(const QString& w, const QString& d){
	 try{database->inserisci(w,d);}
	catch(eccezione e){throw e;}
}
void DbController::save(){
	 try{database->save();}
	catch(eccezione e){throw e;}
}
void DbController::texprint(){
	 database->texprint();
}
