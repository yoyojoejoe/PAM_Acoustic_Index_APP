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
class LTSM : public QWidget{
public:
    
    LTSM(QWidget* parent = nullptr);
    void initialize();
    void read_file_path();//read wav file dir path
    void save_file_path();//read save file dir path
    void Analyze();//Start to analize
    void open_setting_pannel();
    void open_figure_setting_pannel();
    void draw_spectrum(Spectral_analyze* spec);
    void draw_spectrogram(Spectral_analyze* spec);//draw and renew the spetrogram figure
    void draw_Oc_Band(Spectral_analyze* spec);
    void load_wav_file();//load all the wav file in the dir
    void generate_report(double system_time);
    ~LTSM();
    QPushButton* audio_file_read_button;//read the audio file
    QPushButton* save_file_read_button;//read the save_file path
    QPushButton* analyze_button;//start to analysze
    QPushButton* Setting_Button;//Setting Pannel
    QPushButton* Figure_Setting_Button;//Setting Pannel


    QLineEdit* audio_file;//Audio file path 
    QLineEdit* save_file;//Audio file path 
    QLineEdit* wav_processing;//which wav file is processing

    QLabel* Audio_file_label;//Audio file label
    QLabel* Spec_file_label;//Result file label


    QFont* font;// Font variable
    QString dir;//dir variable

    
    std::string load_path;//wave file path string
    std::string save_path;//result file path string
    std::vector<std::string> load_path_list;// all the wave file path
    std::vector<std::vector<double>> Long_Spectrogram;// all the spectrogram

    QCustomPlot* spectrogram;//spectrogram
    QCPColorMap* pcolor;//spectrogram
    QCustomPlot* fig;
    QCPBars* Oc_Band;

    Setting_Panel* Acoustic_Setting_Panel_Class;//Acoustic setting panel
    Figure_Setting_Panel* Figure_Setting_Panel_Class;//Figure setting panel
    Acousic_Input acoustic_input;//Acoustic setting input variable
    Figure_Input figure_input;//Figure setting input variable

};
