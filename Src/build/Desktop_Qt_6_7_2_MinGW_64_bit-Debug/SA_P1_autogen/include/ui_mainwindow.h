/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *editor;
    QTableWidget *REGtw;
    QTableWidget *RAMtw;
    QLineEdit *clock;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *PClbl;
    QLineEdit *PCle;
    QVBoxLayout *verticalLayout;
    QLabel *Nlbl;
    QLineEdit *Nle;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *MARlbl;
    QLineEdit *MARle;
    QVBoxLayout *verticalLayout_3;
    QLabel *Plbl;
    QLineEdit *Ple;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_7;
    QLabel *MDRlbl;
    QLineEdit *MDRle;
    QVBoxLayout *verticalLayout_5;
    QLabel *Zlbl;
    QLineEdit *Zle;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_6;
    QLabel *IRlbl;
    QLineEdit *IRle;
    QSpacerItem *horizontalSpacer_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *compileButton;
    QPushButton *runButton;
    QPushButton *resetButton;
    QPushButton *nxtButton;
    QLabel *label_3;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_14;
    QLabel *Nlbl_4;
    QLineEdit *DDR_le;
    QVBoxLayout *verticalLayout_15;
    QLabel *Nlbl_5;
    QLineEdit *DSR_le;
    QWidget *widget;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_2;
    QLineEdit *srchle;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *gotoButton;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_10;
    QLabel *Nlbl_2;
    QLineEdit *KBDR_le;
    QVBoxLayout *verticalLayout_11;
    QLabel *Nlbl_3;
    QLineEdit *KBSR_le;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_17;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *inp_le;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *inputButton;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QLineEdit *console;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_5;
    QLineEdit *output_le;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1035, 788);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1035, 788));
        MainWindow->setMaximumSize(QSize(1035, 788));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        editor = new QTextEdit(centralwidget);
        editor->setObjectName("editor");
        editor->setGeometry(QRect(670, 40, 351, 421));
        REGtw = new QTableWidget(centralwidget);
        if (REGtw->columnCount() < 2)
            REGtw->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        REGtw->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        REGtw->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        REGtw->setObjectName("REGtw");
        REGtw->setGeometry(QRect(0, 50, 221, 271));
        REGtw->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);"));
        REGtw->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        REGtw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        REGtw->setRowCount(0);
        REGtw->setColumnCount(2);
        RAMtw = new QTableWidget(centralwidget);
        if (RAMtw->columnCount() < 4)
            RAMtw->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        RAMtw->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        RAMtw->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        RAMtw->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        RAMtw->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        RAMtw->setObjectName("RAMtw");
        RAMtw->setGeometry(QRect(10, 470, 481, 261));
        RAMtw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        RAMtw->setShowGrid(true);
        RAMtw->setRowCount(0);
        RAMtw->setColumnCount(4);
        RAMtw->verticalHeader()->setVisible(false);
        clock = new QLineEdit(centralwidget);
        clock->setObjectName("clock");
        clock->setGeometry(QRect(670, 10, 351, 28));
        clock->setReadOnly(true);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(240, 50, 265, 366));
        verticalLayout_8 = new QVBoxLayout(layoutWidget);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        PClbl = new QLabel(layoutWidget);
        PClbl->setObjectName("PClbl");
        PClbl->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);"));
        PClbl->setAlignment(Qt::AlignCenter);
        PClbl->setMargin(9);
        PClbl->setIndent(-1);

        verticalLayout_2->addWidget(PClbl);

        PCle = new QLineEdit(layoutWidget);
        PCle->setObjectName("PCle");
        PCle->setStyleSheet(QString::fromUtf8("background-color: rgb(54, 54, 54);\n"
"color: white;"));
        PCle->setAlignment(Qt::AlignCenter);
        PCle->setReadOnly(true);

        verticalLayout_2->addWidget(PCle);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        Nlbl = new QLabel(layoutWidget);
        Nlbl->setObjectName("Nlbl");
        Nlbl->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 0, 0);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);"));
        Nlbl->setAlignment(Qt::AlignCenter);
        Nlbl->setMargin(9);
        Nlbl->setIndent(-1);

        verticalLayout->addWidget(Nlbl);

        Nle = new QLineEdit(layoutWidget);
        Nle->setObjectName("Nle");
        Nle->setStyleSheet(QString::fromUtf8("background-color: rgb(157, 16, 16);\n"
"color: rgb(255,255,255);"));
        Nle->setAlignment(Qt::AlignCenter);
        Nle->setReadOnly(true);

        verticalLayout->addWidget(Nle);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_8->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        MARlbl = new QLabel(layoutWidget);
        MARlbl->setObjectName("MARlbl");
        MARlbl->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);"));
        MARlbl->setAlignment(Qt::AlignCenter);
        MARlbl->setMargin(9);
        MARlbl->setIndent(-1);

        verticalLayout_4->addWidget(MARlbl);

        MARle = new QLineEdit(layoutWidget);
        MARle->setObjectName("MARle");
        MARle->setStyleSheet(QString::fromUtf8("background-color: rgb(54, 54, 54);\n"
"color: white;"));
        MARle->setAlignment(Qt::AlignCenter);
        MARle->setReadOnly(true);

        verticalLayout_4->addWidget(MARle);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        Plbl = new QLabel(layoutWidget);
        Plbl->setObjectName("Plbl");
        Plbl->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 0, 0);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);\n"
""));
        Plbl->setAlignment(Qt::AlignCenter);
        Plbl->setMargin(9);
        Plbl->setIndent(-1);

        verticalLayout_3->addWidget(Plbl);

        Ple = new QLineEdit(layoutWidget);
        Ple->setObjectName("Ple");
        Ple->setStyleSheet(QString::fromUtf8("background-color: rgb(157, 16, 16);\n"
"color: rgb(255,255,255);"));
        Ple->setAlignment(Qt::AlignCenter);
        Ple->setReadOnly(true);

        verticalLayout_3->addWidget(Ple);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_8->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        MDRlbl = new QLabel(layoutWidget);
        MDRlbl->setObjectName("MDRlbl");
        MDRlbl->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);"));
        MDRlbl->setAlignment(Qt::AlignCenter);
        MDRlbl->setMargin(9);
        MDRlbl->setIndent(-1);

        verticalLayout_7->addWidget(MDRlbl);

        MDRle = new QLineEdit(layoutWidget);
        MDRle->setObjectName("MDRle");
        MDRle->setStyleSheet(QString::fromUtf8("background-color: rgb(54, 54, 54);\n"
"color: white;"));
        MDRle->setAlignment(Qt::AlignCenter);
        MDRle->setReadOnly(true);

        verticalLayout_7->addWidget(MDRle);


        horizontalLayout_3->addLayout(verticalLayout_7);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        Zlbl = new QLabel(layoutWidget);
        Zlbl->setObjectName("Zlbl");
        Zlbl->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 0, 0);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);"));
        Zlbl->setAlignment(Qt::AlignCenter);
        Zlbl->setMargin(9);
        Zlbl->setIndent(-1);

        verticalLayout_5->addWidget(Zlbl);

        Zle = new QLineEdit(layoutWidget);
        Zle->setObjectName("Zle");
        Zle->setStyleSheet(QString::fromUtf8("background-color: rgb(157, 16, 16);\n"
"color: rgb(255,255,255);"));
        Zle->setAlignment(Qt::AlignCenter);
        Zle->setReadOnly(true);

        verticalLayout_5->addWidget(Zle);


        horizontalLayout_3->addLayout(verticalLayout_5);


        verticalLayout_8->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        IRlbl = new QLabel(layoutWidget);
        IRlbl->setObjectName("IRlbl");
        IRlbl->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);"));
        IRlbl->setAlignment(Qt::AlignCenter);
        IRlbl->setMargin(9);
        IRlbl->setIndent(-1);

        verticalLayout_6->addWidget(IRlbl);

        IRle = new QLineEdit(layoutWidget);
        IRle->setObjectName("IRle");
        IRle->setStyleSheet(QString::fromUtf8("background-color: rgb(54, 54, 54);\n"
"color: white;"));
        IRle->setAlignment(Qt::AlignCenter);
        IRle->setReadOnly(true);

        verticalLayout_6->addWidget(IRle);


        horizontalLayout_4->addLayout(verticalLayout_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_8->addLayout(horizontalLayout_4);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(270, 10, 343, 31));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        compileButton = new QPushButton(layoutWidget1);
        compileButton->setObjectName("compileButton");

        horizontalLayout_5->addWidget(compileButton);

        runButton = new QPushButton(layoutWidget1);
        runButton->setObjectName("runButton");

        horizontalLayout_5->addWidget(runButton);

        resetButton = new QPushButton(layoutWidget1);
        resetButton->setObjectName("resetButton");

        horizontalLayout_5->addWidget(resetButton);

        nxtButton = new QPushButton(layoutWidget1);
        nxtButton->setObjectName("nxtButton");

        horizontalLayout_5->addWidget(nxtButton);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(630, 10, 41, 21));
        layoutWidget_4 = new QWidget(centralwidget);
        layoutWidget_4->setObjectName("layoutWidget_4");
        layoutWidget_4->setGeometry(QRect(520, 240, 141, 181));
        verticalLayout_13 = new QVBoxLayout(layoutWidget_4);
        verticalLayout_13->setObjectName("verticalLayout_13");
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName("verticalLayout_14");
        Nlbl_4 = new QLabel(layoutWidget_4);
        Nlbl_4->setObjectName("Nlbl_4");
        Nlbl_4->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 51, 255);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);"));
        Nlbl_4->setAlignment(Qt::AlignCenter);
        Nlbl_4->setMargin(9);
        Nlbl_4->setIndent(-1);

        verticalLayout_14->addWidget(Nlbl_4);

        DDR_le = new QLineEdit(layoutWidget_4);
        DDR_le->setObjectName("DDR_le");
        DDR_le->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:repeat, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(255,255,255);"));
        DDR_le->setAlignment(Qt::AlignCenter);
        DDR_le->setReadOnly(true);

        verticalLayout_14->addWidget(DDR_le);


        verticalLayout_13->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName("verticalLayout_15");
        Nlbl_5 = new QLabel(layoutWidget_4);
        Nlbl_5->setObjectName("Nlbl_5");
        Nlbl_5->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 51, 255);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);"));
        Nlbl_5->setAlignment(Qt::AlignCenter);
        Nlbl_5->setMargin(9);
        Nlbl_5->setIndent(-1);

        verticalLayout_15->addWidget(Nlbl_5);

        DSR_le = new QLineEdit(layoutWidget_4);
        DSR_le->setObjectName("DSR_le");
        DSR_le->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:repeat, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(255,255,255);"));
        DSR_le->setAlignment(Qt::AlignCenter);
        DSR_le->setReadOnly(true);

        verticalLayout_15->addWidget(DSR_le);


        verticalLayout_13->addLayout(verticalLayout_15);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 360, 127, 95));
        verticalLayout_9 = new QVBoxLayout(widget);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: white;"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_2);

        srchle = new QLineEdit(widget);
        srchle->setObjectName("srchle");

        verticalLayout_9->addWidget(srchle);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        gotoButton = new QPushButton(widget);
        gotoButton->setObjectName("gotoButton");

        horizontalLayout_6->addWidget(gotoButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_9->addLayout(horizontalLayout_6);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(520, 50, 141, 181));
        verticalLayout_12 = new QVBoxLayout(widget1);
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        Nlbl_2 = new QLabel(widget1);
        Nlbl_2->setObjectName("Nlbl_2");
        Nlbl_2->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 51, 255);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);"));
        Nlbl_2->setAlignment(Qt::AlignCenter);
        Nlbl_2->setMargin(9);
        Nlbl_2->setIndent(-1);

        verticalLayout_10->addWidget(Nlbl_2);

        KBDR_le = new QLineEdit(widget1);
        KBDR_le->setObjectName("KBDR_le");
        KBDR_le->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:repeat, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(255,255,255);"));
        KBDR_le->setAlignment(Qt::AlignCenter);
        KBDR_le->setReadOnly(true);

        verticalLayout_10->addWidget(KBDR_le);


        verticalLayout_12->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName("verticalLayout_11");
        Nlbl_3 = new QLabel(widget1);
        Nlbl_3->setObjectName("Nlbl_3");
        Nlbl_3->setStyleSheet(QString::fromUtf8("background-color: rgb(15, 51, 255);\n"
"border-top-left-radius: 15px;\n"
"border-top-right-radius: 15px;\n"
"color: rgb(255,255,255);"));
        Nlbl_3->setAlignment(Qt::AlignCenter);
        Nlbl_3->setMargin(9);
        Nlbl_3->setIndent(-1);

        verticalLayout_11->addWidget(Nlbl_3);

        KBSR_le = new QLineEdit(widget1);
        KBSR_le->setObjectName("KBSR_le");
        KBSR_le->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:repeat, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(255,255,255);"));
        KBSR_le->setAlignment(Qt::AlignCenter);
        KBSR_le->setReadOnly(true);

        verticalLayout_11->addWidget(KBSR_le);


        verticalLayout_12->addLayout(verticalLayout_11);

        widget2 = new QWidget(centralwidget);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(600, 500, 424, 231));
        verticalLayout_17 = new QVBoxLayout(widget2);
        verticalLayout_17->setObjectName("verticalLayout_17");
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName("verticalLayout_16");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);

        inp_le = new QLineEdit(widget2);
        inp_le->setObjectName("inp_le");
        sizePolicy.setHeightForWidth(inp_le->sizePolicy().hasHeightForWidth());
        inp_le->setSizePolicy(sizePolicy);
        inp_le->setMinimumSize(QSize(191, 28));
        inp_le->setMaximumSize(QSize(191, 28));

        horizontalLayout_9->addWidget(inp_le);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);


        verticalLayout_16->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);

        inputButton = new QPushButton(widget2);
        inputButton->setObjectName("inputButton");
        sizePolicy.setHeightForWidth(inputButton->sizePolicy().hasHeightForWidth());
        inputButton->setSizePolicy(sizePolicy);
        inputButton->setMinimumSize(QSize(80, 29));
        inputButton->setMaximumSize(QSize(80, 29));
        inputButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        inputButton->setStyleSheet(QString::fromUtf8("border-top-left-radius: 15px;\n"
"border-bottom-right-radius: 15px;\n"
"background-color: rgb(0, 0, 0);\n"
"color: rgb(255,255,255);"));
        inputButton->setFlat(true);

        horizontalLayout_10->addWidget(inputButton);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);


        verticalLayout_16->addLayout(horizontalLayout_10);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label = new QLabel(widget2);
        label->setObjectName("label");

        horizontalLayout_7->addWidget(label);

        console = new QLineEdit(widget2);
        console->setObjectName("console");
        sizePolicy.setHeightForWidth(console->sizePolicy().hasHeightForWidth());
        console->setSizePolicy(sizePolicy);
        console->setMinimumSize(QSize(351, 111));
        console->setMaximumSize(QSize(351, 111));
        console->setReadOnly(true);

        horizontalLayout_7->addWidget(console);

        horizontalSpacer_5 = new QSpacerItem(278, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        verticalLayout_16->addLayout(horizontalLayout_7);


        verticalLayout_17->addLayout(verticalLayout_16);

        widget3 = new QWidget(centralwidget);
        widget3->setObjectName("widget3");
        widget3->setGeometry(QRect(680, 470, 331, 30));
        horizontalLayout_11 = new QHBoxLayout(widget3);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget3);
        label_5->setObjectName("label_5");

        horizontalLayout_11->addWidget(label_5);

        output_le = new QLineEdit(widget3);
        output_le->setObjectName("output_le");

        horizontalLayout_11->addWidget(output_le);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1035, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        QTableWidgetItem *___qtablewidgetitem = REGtw->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = REGtw->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = RAMtw->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Label", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = RAMtw->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Add.", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = RAMtw->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = RAMtw->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Command", nullptr));
        PClbl->setText(QCoreApplication::translate("MainWindow", "PC", nullptr));
        PCle->setText(QString());
        Nlbl->setText(QCoreApplication::translate("MainWindow", "N", nullptr));
        MARlbl->setText(QCoreApplication::translate("MainWindow", "MAR", nullptr));
        Plbl->setText(QCoreApplication::translate("MainWindow", "P", nullptr));
        MDRlbl->setText(QCoreApplication::translate("MainWindow", "MDR", nullptr));
        Zlbl->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        IRlbl->setText(QCoreApplication::translate("MainWindow", "IR", nullptr));
        compileButton->setText(QCoreApplication::translate("MainWindow", "Compile", nullptr));
        runButton->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        nxtButton->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "RTL :", nullptr));
        Nlbl_4->setText(QCoreApplication::translate("MainWindow", "DDR", nullptr));
        Nlbl_5->setText(QCoreApplication::translate("MainWindow", "DSR", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Search in Memory", nullptr));
        gotoButton->setText(QCoreApplication::translate("MainWindow", "Goto ", nullptr));
        Nlbl_2->setText(QCoreApplication::translate("MainWindow", "KBDR", nullptr));
        Nlbl_3->setText(QCoreApplication::translate("MainWindow", "KBSR", nullptr));
        inputButton->setText(QCoreApplication::translate("MainWindow", "Input", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Console", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
