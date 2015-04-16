#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T15:26:52
#
#-------------------------------------------------

QT       += core gui
QT      += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LatexGlossario
TEMPLATE = app


SOURCES += main.cpp\
	model/lemma.cpp \
	model/database.cpp \
	view/mainwindow.cpp \
	control/dbcontroller.cpp

HEADERS  += mainwindow.h \
	ui_mainwindow.h \
	model/database.h \
	model/eccezione.h \
	model/lemma.h \
	view/mainwindow.h \
	control/dbcontroller.h

FORMS    += view/mainwindow.ui
