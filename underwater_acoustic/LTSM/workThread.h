#pragma once
#include <QtWidgets/QMainWindow>
#include<QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include<QtWidgets/QFileDialog>
#include<QtGui/QFont>
#include<QCoreApplication>
#include<QtWidgets/QLabel>
#include <qthread.h>
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
#include"Analyze_Item.h"
#include"Figure_Input.h"
#include"Acoustic_Input.h"
class workThread : public QObject
{
    Q_OBJECT
public:
    workThread(QObject* parent = nullptr);
    ~workThread();
    void draw_spectrum(Spectral_analyze* spec);
    void draw_spectrogram(Spectral_analyze* spec);//draw and renew the spetrogram figure
    void draw_Oc_Band(Spectral_analyze* spec);
    void load_wav_file();//load all the wav file in the dir
    void generate_report(double system_time);
    void stop();
    QFont font;
    Analyze_Item* analyze_input;
    Acousic_Input acoustic_input;//Acoustic setting input variable
    Figure_Input figure_input;//Figure setting input variable
    DWORD star_time;
public slots:
    void start1();
    void Analyze();
    
    
signals:
    void workFinished();
    void workStart();
};