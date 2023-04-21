#define EIGEN_USE_MKL_ALL //Eigen MKL use
#define EIGEN_VECTORIZE_SSE4_2 //Eigen MKL library use
#define _CRT_SECURE_NO_WARNINGS //fopen remove warning
#include<Eigen/core>
#include<Eigen/Dense>
#include <unsupported/Eigen/FFT>
using namespace Eigen;

#include <iostream>
#include <math.h>
#define PI acos(-1)
#include <string>
#include <fstream>
#include<D:/library/AudioFile/AudioFile.h>

//Used to analyze the audio spectral;
class Spectral_analyze {
public:
    int fs;
    VectorXd data;//Audiofile_data
    MatrixXd spectrogram;//Spectrogram (linear scale psd)
    VectorXd time;//Time of spectrogram (seconds);
    VectorXd frequency;//frequency of spectrogram (Hz)
    VectorXd frequency_spectrum;//frequency of spectrogram (Hz)
    MatrixXd SPL_LTSM;//Long Time Spectrogram (Real Sound Pressure Level);
    MatrixXd Long_Time;//Time array
    std::ofstream ofs;
    VectorXd time_wav;//original_wav time;
    VectorXd Spectrum;
    double sensitivity;//underwater hydrophone sensitivity
    Spectral_analyze(double sens);//clas initialize
    void Audio_read(std::string file_name);//read the audio file
    VectorXd hamming(int N);
    void STFT(int window, int noverlap);
    void LTSM_Time();
    void save(std::string file_path,int mode);
};
