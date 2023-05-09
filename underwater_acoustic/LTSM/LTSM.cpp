#include "LTSM.h"
#include"../tool/Data_split.h"

LTSM::LTSM(QWidget* parent)
{
    win = 1.0;
    noverlap = 0.0;

    font = new QFont();

    font->setFamily("Verdana");
    font->setPointSize(15);
    
    spectrogram = new QCustomPlot(this);
    spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));;
    //Button
    //button audio read path
    //set size and location of the button
    audio_file_read_button = new QPushButton("...", this);
    audio_file_read_button->setGeometry(QRect(QPoint(550, 20), QSize(50, 50)));
    save_file_read_button = new QPushButton("...", this);
    save_file_read_button->setGeometry(QRect(QPoint(550, 120), QSize(50, 50)));
    analyze_button = new QPushButton("Analyze", this);
    analyze_button->setGeometry(QRect(QPoint(20, 190), QSize(150, 50)));
    Setting_Button = new QPushButton("Setting Panel", this);
    Setting_Button->setGeometry(QRect(QPoint(600, 20), QSize(200, 50)));

    
    
    analyze_button->setFont(*font);
    audio_file_read_button->setFont(*font);
    save_file_read_button->setFont(*font);
    Setting_Button->setFont(*font);
    //connect to the function
    connect(audio_file_read_button, &QPushButton::clicked, this, &LTSM::read_file_path);
    connect(save_file_read_button, &QPushButton::clicked, this, &LTSM::save_file_path);
    connect(analyze_button, &QPushButton::clicked, this, &LTSM::Analyze);
    connect(Setting_Button, &QPushButton::clicked, this, &LTSM::open_setting_pannel);
    //Line Edit Audio file path
    audio_file = new QLineEdit(this);
    save_file = new QLineEdit(this);


    wav_processing = new QLineEdit(this);

    //Line Edit Save File path
    audio_file->setGeometry(QRect(QPoint(150, 20), QSize(400, 50)));
    audio_file->setFont(*font);

    wav_processing->setGeometry(QRect(QPoint(170, 190), QSize(700, 50)));
    wav_processing->setFont(*font);

    save_file->setGeometry(QRect(QPoint(150, 120), QSize(400, 50)));
    save_file->setFont(*font);


    audio_file->setText("D:/test");
    save_file->setText("D:/test");

    //Label

    //Audio File Label
    Audio_file_label = new QLabel("Audio Path : ", this);
    Audio_file_label->setGeometry(QRect(QPoint(20, 20), QSize(150, 50)));
    Audio_file_label->setFont(*font);
    Spec_file_label = new QLabel("Result Path : ", this);
    Spec_file_label->setGeometry(QRect(QPoint(20, 120), QSize(150, 50)));
    Spec_file_label->setFont(*font);


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
void LTSM::Analyze() {

    std::vector<double> temp_spectrum;
    std::string temp;
    load_path = audio_file->text().toUtf8().constData();
    save_path = save_file->text().toUtf8().constData();
    load_wav_file();
    wav_processing->setText(QString::fromStdString(load_path_list[0]));
    QCoreApplication::processEvents();
    Spectral_analyze* spec2 = new Spectral_analyze(176.3);
    spec2->Audio_read(load_path_list[0]);
    //spec.Audio_read(load_path_list[0]);
    //int win = std::stod(window->text().toUtf8().constData()) * (1.0 * spec2->fs);
    //int overlap = std::stod(noverlap->text().toUtf8().constData()) * (1.0 * spec2->fs);
    int temp_win = win * spec2->fs;
    int temp_noverlap = noverlap * spec2->fs;
    delete(spec2);
    //spec.STFT(win, overlap);
    //spec.LTSM_Time();
    for (int i = 0; i < load_path_list.size(); i++) {
        temp_spectrum.clear();
        Spectral_analyze* spec = new Spectral_analyze(176.3);
        wav_processing->setText(QString::fromStdString(load_path_list[i]));
        QCoreApplication::processEvents();
        spec->Audio_read(load_path_list[i]);
        //spec.Audio_read(load_path_list[i]);
        spec->STFT(temp_win, temp_noverlap);
        //spec.LTSM_Time();
        for (int j = 0; j < temp_win /2+1; j++) {
            temp_spectrum.push_back(spec->Spectrum[j]);
        }
        Long_Spectrogram.push_back(temp_spectrum);
        draw_spectrogram(spec);
        delete(spec);
    }
    //
    //spec.STFT(win, overlap);
    //spec.LTSM_Time(save_path);
    
}
void LTSM::draw_spectrogram(Spectral_analyze* spec) {
    spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(1200, 350)));;
    spectrogram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    spectrogram->axisRect()->setupFullAxesBox(true);
    spectrogram->xAxis->setLabel("Time (s)");
    spectrogram->yAxis->setLabel("Frequency (Hz)");
    pcolor = new QCPColorMap(spectrogram->xAxis, spectrogram->yAxis);
    int nx = Long_Spectrogram.size();
    int ny = Long_Spectrogram[0].size();
    pcolor->data()->setSize(nx, ny);
    pcolor->data()->setRange(QCPRange(spec->time(0), spec->time(nx - 1)), QCPRange(spec->frequency(0), spec->frequency(ny - 1))); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    //pcolor->data()->setRange(QCPRange(spec->time.minCoeff(), spec->time.maxCoeff()), QCPRange(spec->frequency.minCoeff(), spec->frequency.minCoeff()));
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            pcolor->data()->setCell(i, j, Long_Spectrogram[i][j]);
        }
    }
    QCPColorScale* colorScale = new QCPColorScale(spectrogram);
    spectrogram->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setType(QCPAxis::atRight);
    colorScale->setDataRange(QCPRange(0, 150));
    pcolor->setColorScale(colorScale);
    colorScale->axis()->setLabel("SPL");
    pcolor->setGradient(QCPColorGradient::gpJet);
    pcolor->rescaleDataRange();
    QCPMarginGroup* marginGroup = new QCPMarginGroup(spectrogram);
    spectrogram->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    spectrogram->rescaleAxes();
    spectrogram->replot();
    spectrogram->show();
}

void LTSM::save_as_csv() {

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
void LTSM::open_setting_pannel() {
    
    Setting_Panel_Class = new Setting_Panel(&win,&noverlap);
    Setting_Panel_Class->setFixedSize(500, 500);
    Setting_Panel_Class->show();
    
}

LTSM::~LTSM()
{}
