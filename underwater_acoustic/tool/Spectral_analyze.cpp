#include"Spectral_analyze.h"

Spectral_analyze::Spectral_analyze(double sens) {
    sensitivity = sens;
}
void Spectral_analyze::Audio_read(std::string file_name) {
    AudioFile<double> audioFile;
    audioFile.load(file_name);
    fs = audioFile.getSampleRate();
    data = Map<VectorXd, Unaligned>(audioFile.samples[0].data(), audioFile.samples[0].size());
    time_wav =  VectorXd::LinSpaced(data.size(), 0, data.size() / fs);
}
VectorXd Spectral_analyze::hamming(int N) {
    double a = 0.53836;
    VectorXd window = VectorXd::LinSpaced(N, 0, N - 1);
    window = 2.0 * PI * window / (1.0 * (N - 1));
    window.array() = window.array().cos();
    window.array() = a - (1 - a) * window.array();
    return window;
}
void Spectral_analyze::STFT(int window, int noverlap) {
    int win_num = (data.size() - noverlap) / (window - noverlap);
    FFT< double > fft;
    data.array() = data.array() - data.array().mean();
    spectrogram = MatrixXd::Zero(window, win_num);
    MatrixXcd temp;
    VectorXd win = hamming(window);
    for (int i = 0; i < win_num; i++) {
        spectrogram.col(i) = data.block(i * (window - noverlap), 0, window, 1).cwiseProduct(win);
        VectorXcd tmpOut;
        fft.fwd(tmpOut, spectrogram.col(i));
        spectrogram.col(i) = tmpOut.cwiseAbs2();
    }
    time = VectorXd::LinSpaced(win_num, 0, data.size() / fs);
    frequency = VectorXd::LinSpaced(window, 0, fs);
    spectrogram = spectrogram * (1.0 / (1.0 * fs * window));
    VectorXd temp2 = spectrogram.rowwise().mean();
    temp2.array() = 10 * temp2.array().log10() + sensitivity;
    Spectrum = temp2.block(0, 0, spectrogram.rows() / 2 + 1, 1);
    frequency_spectrum = VectorXd::LinSpaced(window / 2 + 1, 0, fs / 2);
    spectrogram.array() = 10 * spectrogram.array().log10() + sensitivity;
}

void Spectral_analyze::LTSM_Time() {
    if (SPL_LTSM.rows() > 1) {
        MatrixXd temp(SPL_LTSM.rows(), SPL_LTSM.cols() + 1);
        temp << SPL_LTSM, Spectrum;
        SPL_LTSM = temp;
    }
    else {
        SPL_LTSM = Spectrum;
    }
    
}
void Spectral_analyze::save(std::string file_path,int mode) {
    if (mode == 1) {
        spectrogram.array() = 10 * spectrogram.array().log10()+sensitivity;
        ofs.open(file_path);
        ofs << 48000*12 << " ";
        for (int j = 0; j < spectrogram.cols(); j++) {
            ofs << time(j) << " ";
        }
        ofs << "\n";
        for (int i = 0; i < spectrogram.rows(); i++) {
            ofs << frequency(i) << " ";
            for (int j = 0; j < spectrogram.cols(); j++) {
                ofs << spectrogram(i,j)<<" ";
            }
            ofs << "\n";
        }
        
        ofs.close();
    }
    if (mode == 2) {
        VectorXd temp = spectrogram.rowwise().mean();
        temp.array() = 10 * temp.array().log10() + sensitivity;
        VectorXd mean_level = temp.block(0, 0, spectrogram.rows() / 2 + 1, 1);
        //ofs.open(file_path, ios::app);
        ofs.open(file_path);

        for (int i = 0; i < mean_level.size(); i++) {
            ofs << frequency(i) << " " << mean_level(i) << '\n';
        }
        ofs << '\n';
        ofs.close();
    }
    if (mode == 3) {
        VectorXd time2 = VectorXd::LinSpaced(data.size(), 0, data.size() / fs);
        ofs.open(file_path);
        for (int i = 0; i < data.size(); i++) {
            ofs << time2[i] << " " << data[i] << '\n';
        }
        ofs.close();
    }
}