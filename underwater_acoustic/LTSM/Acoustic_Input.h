#include<vector>
#ifndef ACOUSIC_Input_H
#define ACOUSIC_Input_H

struct Acousic_Input {
    double win;
    double noverlap;
    double sensitivity;
    bool check_total_spectrogram;
    bool check_octave_band;
    bool check_ACI_map;
    bool check_Ambient_estimate;
    std::vector<double> Oc_Center_frequency;
};
#endif