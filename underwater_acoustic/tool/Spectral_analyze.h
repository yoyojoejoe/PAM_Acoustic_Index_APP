#pragma once
#define EIGEN_USE_MKL_ALL //Eigen MKL use
#define EIGEN_VECTORIZE_SSE4_2 //Eigen MKL library use
#define _CRT_SECURE_NO_WARNINGS //fopen remove warning
#include<Eigen/Eigen/core>
#include<Eigen/Eigen/Dense>
#include <Eigen/unsupported/Eigen/FFT>
using namespace Eigen;
#include <string>
#include <fstream>
#include<D:/library/AudioFile/AudioFile.h>
#include <iostream>
#include <math.h>
#include<vector>

#define PI acos(-1)


//Used to analyze the audio spectral;
class Spectral_analyze {
public:
    void STFT(int window, int noverlap);
    void Audio_read(std::string file_name);//read the audio file
    void Octave_Band(std::vector<double>center_frequency,int window);
    void ACI_Calculate();
    void Ambient_Noise_Estimate(double percentile);
    void save_as_csv(VectorXd spectrum, std::string file_path, std::string file_name);
    int fs;
    VectorXd data;//Audiofile_data
    VectorXd time;//Time of spectrogram (seconds);
    VectorXd frequency;//frequency of spectrogram (Hz)
    VectorXd frequency_spectrum;//frequency of spectrogram (Hz)
    std::ofstream ofs;
    VectorXd time_wav;//original_wav time;
    VectorXd Spectrum;//spectrum (dB scale psd)
    VectorXd Spectrum_linear;//Spectrum (linear scale psd)
    VectorXd Ambient_Noise_Spectrum;//Ambient Noise Spectrum (dB scale psd)
    MatrixXd spectrogram;//Spectrogram (dB scale psd)
    MatrixXd spectrogram_linear;//Spectrogram (linear scale psd)
    MatrixXd ACI_map;
    VectorXd ACI_spectrum;
    
    VectorXd Octave_3_1;
    //std::vector<double> Octave_3_1;
    Spectral_analyze(double sens);//clas initialize
    VectorXd hamming(int N);

    double sensitivity;//underwater hydrophone sensitivity
    
};
