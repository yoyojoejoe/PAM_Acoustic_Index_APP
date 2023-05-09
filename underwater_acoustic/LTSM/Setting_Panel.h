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
    std::vector<double> transfer_string_doble(std::string a);
    Setting_Panel(double *win,double *noverlap,double *sensitivity, std::vector<double> &oc_center_freq,QWidget* parent = nullptr);
    ~Setting_Panel();
    QLineEdit* window_LineEdit;//window
    QLineEdit* noverlap_LineEdit;//noverlap
    QLineEdit* sensitivity_LineEdit;//Sensitivity
    QLineEdit* Oc_LineEdit;//Sensitivity
    QLabel* window_Label;
    QLabel* noverlap_Label;
    QLabel* sensitivity_Label;
    QLabel* Oc_Label;
    QFont* font;

    QPushButton* confirm_button;
    
    double *temp_win;
    double *temp_noverlap;
    double *temp_sensitivity;
    std::vector<double> *temp_oc_center_freq;
};
