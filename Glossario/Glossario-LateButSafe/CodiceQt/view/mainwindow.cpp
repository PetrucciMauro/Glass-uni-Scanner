#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model/eccezione.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),ui(new Ui::MainWindow){
		try{mydb.carica();}
		catch(eccezione e){
				QMessageBox box;
				box.setText("Errore col file.");
				box.setWindowTitle("Errore");
				box.exec();
				return;}
		ui->setupUi(this);
		connect(ui->btnInserisci,SIGNAL(clicked()),this,SLOT(insert()));
		connect(ui->btnPrint,SIGNAL(clicked()),this,SLOT(latex()));
		connect(ui->btnSalva,SIGNAL(clicked()),this,SLOT(save()));
	}

MainWindow::~MainWindow(){
		delete ui;
	}

void MainWindow::insert(){
		if(ui->textDesc->toPlainText().isEmpty() || ui->textWord->text().isEmpty()){
				QMessageBox box;
				box.setText("Nessun campo può essere vuoto");
				box.setWindowTitle("Errore");
				box.exec();
				return;}
		try{mydb.inserisci(ui->textWord->text(),ui->textDesc->toPlainText());
			ui->labelInfo->setText("<font color='green'>Inserimento avvenuto</font>");}
		catch(eccezione e){
				QMessageBox box;
				box.setText("Errore nell'inserimento. Probabilmente la parolà è già nel glossario.");
				box.setWindowTitle("Errore");
				ui->labelInfo->clear();
				box.exec();
				return;}
	}
void MainWindow::save(){
		try{mydb.save();
			ui->labelInfo->setText("<font color='green'>Salvataggio avvenuto</font>");}
		catch(eccezione e){
				QMessageBox box;
				box.setText("Errore nel salvataggio. Probabilmente il file non è stato trovato.");
				box.setWindowTitle("Errore");
				ui->labelInfo->clear();
				box.exec();
				return;}
	}
void MainWindow::latex(){
		try{mydb.texprint();
			ui->labelInfo->setText("<font color='green'>Conversione avvenuta</font>");}
		catch(eccezione e){
				QMessageBox box;
				box.setText("Errore nella conversione. Probabilmente il file non è stato trovato.");
				box.setWindowTitle("Errore");
				ui->labelInfo->clear();
				box.exec();
				return;}
	}
