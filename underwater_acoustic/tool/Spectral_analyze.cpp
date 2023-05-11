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

void Spectral_analyze::Octave_Band(std::vector<double>center_frequency,int window) {
    for (int i = 0; i < center_frequency.size(); i++) {
        
        double low_freq = center_frequency[i] / std::pow(2 , (1.0/6.0));
        double high_freq = center_frequency[i] * std::pow(2, (1.0/6.0));
        int low_index = std::round(low_freq * window / fs);
        int high_index = std::round(high_freq * window / fs);
        if (low_index <= 0) {
            low_index += 1;
        }
        if (high_index >= Spectrum.size()) {
            high_index = Spectrum.size() - 1;
        }
        VectorXd temp = Spectrum.segment(low_index, high_index);
        Octave_3_1.push_back(temp.mean());
    }
    
}

void Spectral_analyze::ACI_Calculate() {
    for (int i = 0; i < spectrogram.cols(); i++) {

    }
}