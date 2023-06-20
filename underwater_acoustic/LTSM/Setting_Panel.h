#pragma once

#include <QtWidgets/QMainWindow>
#include<QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include<QtWidgets/QFileDialog>
#include<QtGui/QFont>
#include<QCoreApplication>
#include<QtWidgets/QLabel>
#include<QtWidgets/QCheckBox>

#include<io.h>
#include<string>
#include<vector>
#include<iostream>
#include <fstream> 
#include<stdio.h>
#include<vector>
#include<iomanip>
#include"../tool/Spectral_analyze.h"
#include"Acoustic_Input.h"
class Setting_Panel : public QWidget {
public:

    void Change_value();
    std::vector<double> transfer_string_doble(std::string a);
    Setting_Panel(Acousic_Input *input, QWidget* parent = nullptr);
    ~Setting_Panel();
    QLineEdit* window_LineEdit;//window
    QLineEdit* noverlap_LineEdit;//noverlap
    QLineEdit* sensitivity_LineEdit;//Sensitivity
    QLineEdit* Oc_LineEdit;//Sensitivity
    QLineEdit* percentile_LineEdit;//percentile
    QLabel* window_Label;
    QLabel* noverlap_Label;
    QLabel* sensitivity_Label;
    QLabel* Oc_Label;
    QLabel* percentile_Label;
    QFont* font;

    QCheckBox* OC_band_check;
    QLabel* OC_check_Label;
    QCheckBox* ACI_check;
    QLabel* ACI_check_Label;
    QCheckBox* Ambient_check;
    QLabel* Ambient_check_Label;

    QPushButton* confirm_button;
    
    Acousic_Input* temp_input;
};
