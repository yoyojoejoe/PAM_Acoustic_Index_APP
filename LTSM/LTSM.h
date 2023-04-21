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
class LTSM : public QWidget{
public:
    
    LTSM(QWidget* parent = nullptr);
    void read_file_path();
    void save_file_path();
    void spectral_gnu_plot();
    ~LTSM();
    QPushButton* audio_file_read_button;
    QPushButton* save_file_read_button;
    QPushButton* analyze_button;

    QLineEdit* audio_file;
    QLineEdit* save_file;
    QLineEdit* window;
    QLineEdit* noverlap;
    QLineEdit* wav_processing;

    QLabel* image_label;
    QLabel* Audio_file_label;
    QLabel* Spec_file_label;
    QLabel* window_label;
    QLabel* overlap_label;

    QFont* font;
    QString dir;


    void load_wav_file();
    std::string load_path;
    std::string save_path;
    std::vector<std::string> load_path_list;
};
