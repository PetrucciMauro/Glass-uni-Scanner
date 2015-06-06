/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QPushButton *btnInserisci;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *textWord;
    QTextEdit *textDesc;
    QLabel *labelInfo;
    QPushButton *btnPrint;
    QPushButton *btnSalva;
    QPushButton *Pedicizza;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnInserisci = new QPushButton(frame);
        btnInserisci->setObjectName(QStringLiteral("btnInserisci"));

        gridLayout->addWidget(btnInserisci, 3, 0, 1, 2, Qt::AlignHCenter);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 2);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        textWord = new QLineEdit(frame);
        textWord->setObjectName(QStringLiteral("textWord"));

        gridLayout->addWidget(textWord, 1, 1, 1, 1);

        textDesc = new QTextEdit(frame);
        textDesc->setObjectName(QStringLiteral("textDesc"));

        gridLayout->addWidget(textDesc, 2, 1, 1, 1);

        labelInfo = new QLabel(frame);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelInfo, 4, 0, 1, 2);


        gridLayout_2->addWidget(frame, 0, 1, 1, 2);

        btnPrint = new QPushButton(centralWidget);
        btnPrint->setObjectName(QStringLiteral("btnPrint"));

        gridLayout_2->addWidget(btnPrint, 1, 2, 1, 1);

        btnSalva = new QPushButton(centralWidget);
        btnSalva->setObjectName(QStringLiteral("btnSalva"));

        gridLayout_2->addWidget(btnSalva, 1, 1, 1, 1);

        Pedicizza = new QPushButton(centralWidget);
        Pedicizza->setObjectName(QStringLiteral("Pedicizza"));

        gridLayout_2->addWidget(Pedicizza, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(textWord, textDesc);
        QWidget::setTabOrder(textDesc, btnInserisci);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        btnInserisci->setText(QApplication::translate("MainWindow", "Inserisci", 0));
        label_3->setText(QApplication::translate("MainWindow", "Inserimento nuovo lemma", 0));
        label->setText(QApplication::translate("MainWindow", "Nome", 0));
        label_2->setText(QApplication::translate("MainWindow", "Descrizione", 0));
        labelInfo->setText(QString());
        btnPrint->setText(QApplication::translate("MainWindow", "Stampa Latex", 0));
        btnSalva->setText(QApplication::translate("MainWindow", "Salva", 0));
        Pedicizza->setText(QApplication::translate("MainWindow", "Pedicizza", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
