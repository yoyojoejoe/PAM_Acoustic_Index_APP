#pragma once
#include"../tool/qcustomplot.h"
#include <QtWidgets/QMainWindow>
#include<QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include<QtWidgets/QFileDialog>
#include<QtGui/QFont>
#include<QtWidgets/QLabel>
#include<QtGui/QImage>
#include<QtGui/QPixmap>

//#include<QtCharts/qcustomplot.cpp>

//#include"Data_split.h"
//#include"plot_data.h"
#include<iostream>
#include<stdio.h>



class single_wav_spectrogram : public QWidget{
public:
    
    single_wav_spectrogram(QWidget* parent = nullptr);
    void read_file_path();
    void save_file_path();
    void spectral_gnu_plot();
    void spectrum_plot();
    void wave_plot();
    ~single_wav_spectrogram();
    QPushButton* audio_file_read_button;
    QPushButton* save_file_read_button;
    QPushButton* spectrogram_button;
    QPushButton* spectrum_button;
    QPushButton* raw_data_button;
    QLineEdit* audio_file;
    QLineEdit* save_file;
    QLineEdit* window;
    QLineEdit* noverlap;

    QLabel* image_label;
    QLabel* Audio_file_label;
    QLabel* Spec_file_label;
    QLabel* window_label;
    QLabel* overlap_label;
    QPixmap* image_pix;

    QFont* font;
    QString dir;

    QCustomPlot* fig;
    QCustomPlot* spectrogram;//spectrogram
    QCPColorMap* pcolor;


};
