#pragma once

#include <QtWidgets/QMainWindow>
#include<QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include<QtWidgets/QFileDialog>
#include<QtGui/QFont>
#include<QCoreApplication>
#include<QtWidgets/QLabel>
#include<io.h>
#include<string>
#include<vector>
#include<iostream>
#include <fstream> 
#include<stdio.h>
#include<vector>
#include<iomanip>

class Setting_Panel : public QWidget {
public:

    void Change_value();

    Setting_Panel(double *win,double *noverlap,QWidget* parent = nullptr);
    ~Setting_Panel();
    QLineEdit* window_LineEdit;//window
    QLineEdit* noverlap_LineEdit;//noverlap
    QLabel* window_Label;
    QLabel* noverlap_Label;

    QFont* font;

    QPushButton* confirm_button;
    
    double *temp_win;
    double *temp_noverlap;
};
