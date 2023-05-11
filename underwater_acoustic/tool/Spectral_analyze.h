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
    int fs;
    VectorXd data;//Audiofile_data
    MatrixXd spectrogram;//Spectrogram (linear scale psd)
    VectorXd time;//Time of spectrogram (seconds);
    VectorXd frequency;//frequency of spectrogram (Hz)
    VectorXd frequency_spectrum;//frequency of spectrogram (Hz)
    std::ofstream ofs;
    VectorXd time_wav;//original_wav time;
    VectorXd Spectrum;

    MatrixXd ACI_map;

    
    std::vector<double> Octave_3_1;
    Spectral_analyze(double sens);//clas initialize
    VectorXd hamming(int N);

    double sensitivity;//underwater hydrophone sensitivity
    
};
