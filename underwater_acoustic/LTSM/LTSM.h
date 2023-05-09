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

#include"Setting_Panel.h"
#include"../tool/qcustomplot.h"
#include"../tool/Spectral_analyze.h"

class LTSM : public QWidget{
public:
    
    LTSM(QWidget* parent = nullptr);
    void read_file_path();
    void save_file_path();
    void Analyze();
    void open_setting_pannel();
    void save_as_csv(std::vector<double> spectrum, std::string file_path);
    ~LTSM();
    QPushButton* audio_file_read_button;//read the audio file
    QPushButton* save_file_read_button;//read the save_file path
    QPushButton* analyze_button;//start to analysze
    QPushButton* Setting_Button;//Setting Pannel

    QLineEdit* audio_file;//Audio file path 
    QLineEdit* save_file;//Audio file path 
    QLineEdit* wav_processing;//which wav file is processing

    QLabel* Audio_file_label;
    QLabel* Spec_file_label;


    QFont* font;
    QString dir;

    void draw_spectrogram(Spectral_analyze* spec);
    void load_wav_file();
    std::string load_path;
    std::string save_path;
    std::vector<std::string> load_path_list;
    std::vector<std::vector<double>> Long_Spectrogram;

    QCustomPlot* spectrogram;//spectrogram
    QCPColorMap* pcolor;

    Setting_Panel* Acoustic_Setting_Panel_Class;
    //setting variable
    double win;
    double noverlap;
    double sensitivity;

    bool check_total_spectrogram;
    bool check_octave_band;
    std::vector<double> Oc_Center_frequency;
};
