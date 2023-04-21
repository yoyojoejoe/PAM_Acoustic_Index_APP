#include "LTSM.h"
#include"Spectral_analyze.h"
#include"Data_split.h"

LTSM::LTSM(QWidget* parent)
{

    font = new QFont();

    font->setFamily("Verdana");
    font->setPointSize(15);
    

    //Button
    //button audio read path
    audio_file_read_button = new QPushButton("...", this);
    save_file_read_button = new QPushButton("...", this);
    analyze_button = new QPushButton("Analyze", this);
    
    //set size and location of the button
    audio_file_read_button->setGeometry(QRect(QPoint(550, 20), QSize(50, 50)));
    save_file_read_button->setGeometry(QRect(QPoint(550, 120), QSize(50, 50)));
    analyze_button->setGeometry(QRect(QPoint(20, 190), QSize(150, 50)));

    analyze_button->setFont(*font);
    audio_file_read_button->setFont(*font);
    save_file_read_button->setFont(*font);
    //connect to the function
    connect(audio_file_read_button, &QPushButton::clicked, this, &LTSM::read_file_path);
    connect(save_file_read_button, &QPushButton::clicked, this, &LTSM::save_file_path);
    connect(analyze_button, &QPushButton::clicked, this, &LTSM::spectral_gnu_plot);
    //Line Edit Audio file path
    audio_file = new QLineEdit(this);
    save_file = new QLineEdit(this);
    window = new QLineEdit(this);
    noverlap = new QLineEdit(this);

    wav_processing = new QLineEdit(this);

    //Line Edit Save File path
    audio_file->setGeometry(QRect(QPoint(150, 20), QSize(400, 50)));
    audio_file->setFont(*font);

    wav_processing->setGeometry(QRect(QPoint(150, 320), QSize(400, 50)));
    wav_processing->setFont(*font);

    save_file->setGeometry(QRect(QPoint(150, 120), QSize(400, 50)));
    save_file->setFont(*font);
    window->setGeometry(QRect(QPoint(750, 20), QSize(100, 50)));
    window->setFont(*font);
    noverlap->setGeometry(QRect(QPoint(750, 120), QSize(100, 50)));
    noverlap->setFont(*font);
    audio_file->setText("D:/test");
    save_file->setText("D:/spectrogram.txt");
    window->setText("1");
    noverlap->setText("0");
    //Label

    //Audio File Label
    Audio_file_label = new QLabel("Audio Path : ", this);
    Audio_file_label->setGeometry(QRect(QPoint(20, 20), QSize(150, 50)));
    Audio_file_label->setFont(*font);
    Spec_file_label = new QLabel("Result Path : ", this);
    Spec_file_label->setGeometry(QRect(QPoint(20, 120), QSize(150, 50)));
    Spec_file_label->setFont(*font);
    window_label = new QLabel("Window (s): ", this);
    window_label->setGeometry(QRect(QPoint(620, 20), QSize(150, 50)));
    window_label->setFont(*font);
    overlap_label = new QLabel("Overlap (s): ", this);
    overlap_label->setGeometry(QRect(QPoint(620, 120), QSize(150, 50)));
    overlap_label->setFont(*font);

}
void LTSM::read_file_path() {
    //read audio file;
    dir = QFileDialog::getExistingDirectory();
    audio_file->setText(dir);
}
void LTSM::save_file_path() {
    //read audio file;
    dir = QFileDialog::getExistingDirectory();
    save_file->setText(dir);
}
void LTSM::spectral_gnu_plot() {

    std::string temp;
    load_path = audio_file->text().toUtf8().constData();
    save_path = save_file->text().toUtf8().constData();
    load_wav_file();
    wav_processing->setText(QString::fromStdString(load_path_list[0]));
    QCoreApplication::processEvents();
    Spectral_analyze spec = Spectral_analyze(176.3);
    //spec.Audio_read(load_path_list[0]);
    int win = std::stod(window->text().toUtf8().constData()) * (1.0 * spec.fs);
    int overlap = std::stod(noverlap->text().toUtf8().constData()) * (1.0 * spec.fs);
    //spec.STFT(win, overlap);
    //spec.LTSM_Time();
    for (int i = 0; i < load_path_list.size(); i++) {
        wav_processing->setText(QString::fromStdString(load_path_list[i]));
        
        QCoreApplication::processEvents();
        spec.Audio_read(load_path_list[i]);
        //spec.Audio_read(load_path_list[i]);
        //spec.STFT(win, overlap);
        //spec.LTSM_Time();
    }
    //
    //spec.STFT(win, overlap);
    //spec.LTSM_Time(save_path);

}

void LTSM::load_wav_file() {
    struct _finddata_t fileinfo;
    std::string curr = load_path + "/*.wav";
    load_path_list.clear();
    std::string file_name;
    long long handle;
    if ((handle = _findfirst(curr.c_str(), &fileinfo)) == -1L)
    {
        return;
    }
    else
    {
        file_name = load_path + "/" + fileinfo.name;
        load_path_list.push_back(file_name);
        while (!(_findnext(handle, &fileinfo)))
        {
            file_name = load_path + "/" + fileinfo.name;
            load_path_list.push_back(file_name);
        }
        _findclose(handle);
    }
}


LTSM::~LTSM()
{}
