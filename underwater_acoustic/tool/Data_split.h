#define EIGEN_USE_MKL_ALL //Eigen MKL use
#define EIGEN_VECTORIZE_SSE4_2 //Eigen MKL library use
#define _CRT_SECURE_NO_WARNINGS //fopen remove warning
#include<Eigen/Eigen/core>
#include<Eigen/Eigen/Dense>
#include <Eigen/unsupported/Eigen/FFT>
using namespace Eigen;

#include <iostream>
#include <math.h>
#define PI acos(-1)
#include <string>
#include <fstream>
#include<D:/library/AudioFile/AudioFile.h>

class Data_split {
public:
    long long int fs;
    VectorXd data;
    VectorXd output_data;

    void Audio_read(std::string file_name);//read the audio file
    void split_data(long long int second);
};