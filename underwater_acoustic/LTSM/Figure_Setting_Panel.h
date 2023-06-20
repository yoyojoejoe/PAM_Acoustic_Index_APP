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
#include <QComboBox>
#include<io.h>
#include<string>
#include<vector>
#include<iostream>
#include <fstream> 
#include<stdio.h>
#include<vector>
#include<iomanip>
#include"../tool/Spectral_analyze.h"
#include"Figure_Input.h"
class Figure_Setting_Panel : public QWidget {
public:

    Figure_Setting_Panel(Figure_Input*input, QWidget* parent = nullptr);
    ~Figure_Setting_Panel();
    void Change_value();
    QLineEdit* xlim_low;
    QLineEdit* xlim_high;
    QLineEdit* ylim_low;
    QLineEdit* ylim_high;
    QLineEdit* clim_low;
    QLineEdit* clim_high;

    QLabel* xlim;
    QLabel* ylim;
    QLabel* clim;
    QLabel* auto_scale_text;
    QCheckBox* auto_scale;

    QComboBox* figure_type;
    QFont* font;



    QPushButton* confirm_button;
    
    Figure_Input* temp_input;
};
