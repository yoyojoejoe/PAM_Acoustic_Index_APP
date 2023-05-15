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
    spectrogram_linear = spectrogram;
    Spectrum_linear = temp2.block(0, 0, spectrogram.rows() / 2 + 1, 1);
    temp2.array() = 10 * temp2.array().log10() + sensitivity;
    Spectrum = temp2.block(0, 0, spectrogram.rows() / 2 + 1, 1);
    
    frequency_spectrum = VectorXd::LinSpaced(window / 2 + 1, 0, fs / 2);
    spectrogram.array() = 10 * spectrogram.array().log10() + sensitivity;
}

void Spectral_analyze::Octave_Band(std::vector<double>center_frequency,int window) {
    Octave_3_1 = VectorXd::Zero(center_frequency.size());
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
        VectorXd temp = Spectrum_linear.segment(low_index, high_index-low_index);
        double temp_2 = temp.sum();
        Octave_3_1[i] = (10 * log10(temp_2) + sensitivity);
    }
    
}

void Spectral_analyze::ACI_Calculate() {
    int a = spectrogram_linear.rows();
    int b = spectrogram_linear.cols();
    ACI_map = MatrixXd::Zero(spectrogram_linear.rows(), spectrogram_linear.cols() - 1);
    VectorXd sum_spec = spectrogram_linear.rowwise().sum().array();
    for (int i = 1; i < spectrogram_linear.cols(); i++) {
        ACI_map.col(i-1) = spectrogram_linear.col(i) - spectrogram_linear.col(i - 1);
        ACI_map.col(i - 1).array() = ACI_map.col(i - 1).array().abs() / sum_spec.array();
    }

    VectorXd temp2 = ACI_map.rowwise().sum();
    ACI_spectrum = temp2.block(0, 0, ACI_map.rows() / 2 + 1, 1);
}

void Spectral_analyze::save_as_csv(VectorXd spectrum, std::string file_path) {
    std::ofstream spectrogram_file(file_path, std::ios_base::app);
    for (int i = 0; i < spectrum.size(); i++) {
        spectrogram_file << spectrum[i] << ',';
    }
    spectrogram_file << '\n';
    spectrogram_file.close();
}
void Spectral_analyze::Ambient_Noise_Estimate(double percentile) {
    std::vector<double> sort_array;
    Ambient_Noise_Spectrum = VectorXd::Zero(spectrogram_linear.rows());
    for (int i = 0; i < spectrogram_linear.rows()/2+1; i++) {
        sort_array.clear();
        for (int j = 0; j < spectrogram_linear.cols(); j++) {
            sort_array.push_back(spectrogram_linear(i,j));
        }
        std::sort(sort_array.begin(), sort_array.end());
        Ambient_Noise_Spectrum[i] = -sort_array[sort_array.size()*percentile]/log(1.0-percentile);
        Ambient_Noise_Spectrum[i] = 10 * std::log10(Ambient_Noise_Spectrum[i]) + sensitivity;
    }
}