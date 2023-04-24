#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_underwater_acoustic.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include<QtGui/QFont>
#include<QtWidgets/QStackedWidget>

#include"LTSM/LTSM.h";
#include"Single_wav_spectrogram/single_wav_spectrogram.h";
#include<iostream>
#include<stdio.h>
class underwater_acoustic : public QMainWindow
{
    Q_OBJECT

public:
    underwater_acoustic(QWidget *parent = nullptr);
    int mode = 1;
    void LTSM_change();
    void spectrogram_change();
    void set_single_spectrogram();
    void set_LTSM();
    ~underwater_acoustic();
    QPushButton* LTSM_button;
    QPushButton* Spectrogram_button;
    single_wav_spectrogram* single_spectrogram_class;
    LTSM* LTSM_class;
    QStackedWidget* stack;
private:
    Ui::underwater_acousticClass ui;
};
