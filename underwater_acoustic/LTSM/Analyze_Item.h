#pragma once
#include <QtWidgets/QMainWindow>
#include<QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include<QtWidgets/QFileDialog>
#include<QtGui/QFont>
#include<QCoreApplication>
#include<QtWidgets/QLabel>
#include <QProgressBar>
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
#ifndef ANAlYZE_ITEM_H
#define ANAlYZE_ITEM_H

struct Analyze_Item {

    int temp_win;
    int temp_noverlap;
    std::string spectrogram_file_path ;
    std::string Oc_file_path;
    std::string ACI_file_path;
    std::string Ambient_file_path;
    QPushButton* audio_file_read_button;//read the audio file
    QPushButton* save_file_read_button;//read the save_file path
    QPushButton* analyze_button;//start to analysze
    QPushButton* Setting_Button;//Setting Pannel
    QPushButton* Figure_Setting_Button;//Setting Pannel
    QPushButton* stop_button;

    QProgressBar* progressBar;//Progress bar

    QLineEdit* audio_file;//Audio file path 
    QLineEdit* save_file;//Audio file path 
    QLabel* wav_processing;//which wav file is processing

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

    bool if_start;
};
#endif