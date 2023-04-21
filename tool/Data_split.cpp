#include"Data_split.h"

void Data_split::Audio_read(std::string file_name) {
    AudioFile<double> audioFile;
    audioFile.load(file_name);
    fs = audioFile.getSampleRate();
    data = Map<VectorXd, Unaligned>(audioFile.samples[0].data(), audioFile.samples[0].size());
}
void Data_split::split_data(long long int second) {

    VectorXd temp = data.tail(data.size() - second * fs);
    output_data = data.block(0, 0, second * fs, 1);
    data = temp;

}