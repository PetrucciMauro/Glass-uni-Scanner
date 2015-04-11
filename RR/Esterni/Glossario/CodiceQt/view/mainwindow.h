#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "control/dbcontroller.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;}

class MainWindow : public QMainWindow
{
	 Q_OBJECT
public:
	 explicit MainWindow(QWidget *parent = 0);
	 ~MainWindow();
public slots:
		void insert();
		void save();
		void latex();
private slots:
        void on_btnPrint_clicked();

private:
	 Ui::MainWindow *ui;
	 DbController mydb;
};

#endif // MAINWINDOW_H
