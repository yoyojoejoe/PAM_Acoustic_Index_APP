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
#include<time.h>
#include<Windows.h>
#include"Setting_Panel.h"
#include "Figure_Setting_Panel.h"
#include"../tool/qcustomplot.h"
#include"../tool/Spectral_analyze.h"
#include"Acoustic_Input.h"
#include"Figure_Input.h"
#include"Analyze_Item.h"
#include"workThread.h"

class LTSM : public QWidget{
public:
    
    LTSM(QWidget* parent = nullptr);
    void initialize();
    void read_file_path();//read wav file dir path
    void save_file_path();//read save file dir path
    void start();//Start to analyze
    void stop();//stop analyze
    void open_setting_pannel();
    void open_figure_setting_pannel();
    void initial_analyze_input();
    ~LTSM();
    
    QThread* m_workerThread;
    QFont* font;// Font variable
    workThread* thread;
    Setting_Panel* Acoustic_Setting_Panel_Class;//Acoustic setting panel
    Figure_Setting_Panel* Figure_Setting_Panel_Class;//Figure setting panel
    Acousic_Input acoustic_input;//Acoustic setting input variable
    Figure_Input figure_input;//Figure setting input variable
    Analyze_Item analyze_input;
};
