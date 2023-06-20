#include "LTSM.h"
#include"../tool/Data_split.h"

LTSM::LTSM(QWidget* parent)
{
    

    initialize();
    font = new QFont();

    font->setFamily("Verdana");
    font->setPointSize(15);
    
    
    //Button
    //button audio read path
    //set size and location of the button
    audio_file_read_button = new QPushButton("...", this);
    audio_file_read_button->setGeometry(QRect(QPoint(550, 20), QSize(50, 50)));
    save_file_read_button = new QPushButton("...", this);
    save_file_read_button->setGeometry(QRect(QPoint(550, 120), QSize(50, 50)));
    analyze_button = new QPushButton("Analyze", this);
    analyze_button->setGeometry(QRect(QPoint(20, 190), QSize(150, 50)));
    Setting_Button = new QPushButton("Acoustic Setting Panel", this);
    Setting_Button->setGeometry(QRect(QPoint(600, 20), QSize(250, 50)));
    Figure_Setting_Button = new QPushButton("Figure Setting Panel", this);
    Figure_Setting_Button->setGeometry(QRect(QPoint(600, 120), QSize(250, 50)));

    
    
    analyze_button->setFont(*font);
    audio_file_read_button->setFont(*font);
    save_file_read_button->setFont(*font);
    Setting_Button->setFont(*font);
    Figure_Setting_Button->setFont(*font);
    //connect to the function
    connect(audio_file_read_button, &QPushButton::clicked, this, &LTSM::read_file_path);
    connect(save_file_read_button, &QPushButton::clicked, this, &LTSM::save_file_path);
    connect(analyze_button, &QPushButton::clicked, this, &LTSM::Analyze);
    connect(Setting_Button, &QPushButton::clicked, this, &LTSM::open_setting_pannel);
    connect(Figure_Setting_Button, &QPushButton::clicked, this, &LTSM::open_figure_setting_pannel);

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
    DWORD star_time = GetTickCount();//Analyze Function Time Calculate
    spectrogram = new QCustomPlot(this);
    spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));;
    Long_Spectrogram.clear();
    std::vector<double> temp_spectrum;
    std::string temp;
    load_path = audio_file->text().toUtf8().constData();
    save_path = save_file->text().toUtf8().constData();
    load_wav_file();
    wav_processing->setText(QString::fromStdString(load_path_list[0]));
    QCoreApplication::processEvents();
    Spectral_analyze* spec2 = new Spectral_analyze(acoustic_input.sensitivity);
    spec2->Audio_read(load_path_list[0]);
    //spec.Audio_read(load_path_list[0]);
    //int win = std::stod(window->text().toUtf8().constData()) * (1.0 * spec2->fs);
    //int overlap = std::stod(noverlap->text().toUtf8().constData()) * (1.0 * spec2->fs);
    int temp_win = acoustic_input.win * spec2->fs;
    int temp_noverlap = acoustic_input.noverlap * spec2->fs;
    //save_frequency
    std::string spectrogram_file_path = "";
    std::string Oc_file_path = "";
    std::string ACI_file_path = "";
    std::string Ambient_file_path = "";
    if (acoustic_input.check_total_spectrogram) {
        spectrogram_file_path = save_file->text().toUtf8().constData();
        spectrogram_file_path += "/Total_Spectrogram.csv";
        std::ofstream spectrogram_file(spectrogram_file_path);
        for (int i = 0; i < temp_win / 2 + 1; i++) {
            spectrogram_file << i * (spec2->fs) / temp_win << ",";
        }
        spectrogram_file << '\n';
        spectrogram_file.close();
    }
    if (acoustic_input.check_ACI_map) {
        ACI_file_path = save_file->text().toUtf8().constData();
        ACI_file_path += "/ACI.csv";
        std::ofstream ACI_file(ACI_file_path);
        for (int i = 0; i < temp_win / 2 + 1; i++) {
            ACI_file << i * (spec2->fs) / temp_win << ",";
        }
        ACI_file << '\n';
        ACI_file.close();
    }
    if (acoustic_input.check_octave_band) {
        Oc_file_path = save_file->text().toUtf8().constData();
        Oc_file_path += "/One_Third_Octave_Band.csv";
        std::ofstream Octave_Band_file(Oc_file_path);
        for (int i = 0; i < acoustic_input.Oc_Center_frequency.size(); i++) {
            Octave_Band_file << acoustic_input.Oc_Center_frequency[i] << ",";
        }
        Octave_Band_file << '\n';
        Octave_Band_file.close();
    }
    if (acoustic_input.check_Ambient_estimate) {
        Ambient_file_path = save_file->text().toUtf8().constData();
        Ambient_file_path += "/Ambient_Noise.csv";
        std::ofstream Ambient_file(ACI_file_path);
        for (int i = 0; i < temp_win / 2 + 1; i++) {
            Ambient_file << i * (spec2->fs) / temp_win << ",";
        }
        Ambient_file << '\n';
        Ambient_file.close();
    }
    delete(spec2);
    //spec.STFT(win, overlap);
    //spec.LTSM_Time();
    for (int i = 0; i < load_path_list.size(); i++) {
        temp_spectrum.clear();
        Spectral_analyze* spec = new Spectral_analyze(acoustic_input.sensitivity);
        wav_processing->setText(QString::fromStdString(load_path_list[i]));
        QCoreApplication::processEvents();
        spec->Audio_read(load_path_list[i]);
        spec->STFT(temp_win, temp_noverlap);
        
        if (acoustic_input.check_total_spectrogram) {// all spectrogram
            temp_spectrum.resize(spec->Spectrum.size());
            VectorXd::Map(&temp_spectrum[0], spec->Spectrum.size()) = spec->Spectrum;
            Long_Spectrogram.push_back(temp_spectrum);
            spec->save_as_csv(spec->Spectrum, spectrogram_file_path);
            draw_spectrogram(spec);
            
        }

        if (acoustic_input.check_octave_band) {//1/3 Octave Band
            spec->Octave_Band(acoustic_input.Oc_Center_frequency, temp_win);
            spec->save_as_csv(spec->Octave_3_1, Oc_file_path);
        }
        if (acoustic_input.check_ACI_map) {//Calculate ACI
            spec->ACI_Calculate();
            spec->save_as_csv(spec->ACI_spectrum, ACI_file_path);
        }
        if (acoustic_input.check_Ambient_estimate) {
            spec->Ambient_Noise_Estimate(acoustic_input.ambient_estimate_percentile);
            spec->save_as_csv(spec->Ambient_Noise_Spectrum, Ambient_file_path);
        }
        delete(spec);
    }
    DWORD end_time = GetTickCount();//Analyze Function Time Calculate
    generate_report((end_time-star_time)/1000);
    
}
void LTSM::draw_spectrogram(Spectral_analyze* spec) {
    spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(1200, 350)));
    spectrogram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    spectrogram->axisRect()->setupFullAxesBox(true);
    spectrogram->xAxis->setLabel("Time");
    spectrogram->yAxis->setLabel("Frequency (Hz)");
    pcolor = new QCPColorMap(spectrogram->xAxis, spectrogram->yAxis);
    int nx = Long_Spectrogram.size();
    int ny = Long_Spectrogram[0].size();
    pcolor->data()->setSize(nx, ny);
    pcolor->data()->setRange(QCPRange(0, nx), QCPRange(spec->frequency(0), spec->frequency(ny - 1))); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    //pcolor->data()->setRange(QCPRange(spec->time.minCoeff(), spec->time.maxCoeff()), QCPRange(spec->frequency.minCoeff(), spec->frequency.minCoeff()));
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j <= ny; j++)
        {
            pcolor->data()->setCell(i, j, Long_Spectrogram[i][j]);
            
        }
        
    }
    pcolor->data()->setCell(0, 0, 0);
    pcolor->data()->setCell(0, 1, 100);
    QCPColorScale* colorScale = new QCPColorScale(spectrogram);
    QCPColorGradient* colorgradient = new QCPColorGradient();
    spectrogram->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setType(QCPAxis::atRight);
    //colorScale->setDataRange(QCPRange(-100, 150));
    colorScale->axis()->setLabel("SPL");
    pcolor->setColorScale(colorScale);
    pcolor->setGradient(QCPColorGradient::gpJet);
    
    pcolor->rescaleDataRange();
    QCPMarginGroup* marginGroup = new QCPMarginGroup(spectrogram);
    spectrogram->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    spectrogram->rescaleAxes();
    spectrogram->replot();
    spectrogram->show();
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
    
    Acoustic_Setting_Panel_Class = new Setting_Panel(&acoustic_input);
    Acoustic_Setting_Panel_Class->setFixedSize(1000, 500);
    Acoustic_Setting_Panel_Class->show();
    
}
void LTSM::open_figure_setting_pannel() {
    Figure_Setting_Panel_Class = new Figure_Setting_Panel(&figure_input);
    Figure_Setting_Panel_Class->setFixedSize(1000, 500);
    Figure_Setting_Panel_Class->show();
}

void LTSM::generate_report(double system_time) {

    SYSTEMTIME sys;
    GetLocalTime(&sys);
    char tmp[64]{ NULL };
    sprintf(tmp, "%4d-%02d-%02d %02d:%02d:%02d",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);

    std::string report_file_path = "";
    report_file_path = save_file->text().toUtf8().constData() ;
    report_file_path += "/report.txt";
    std::ofstream report_file(report_file_path);
    report_file << "Report Generating Time : " << tmp << std::endl;
    report_file << std::endl << "===========================================Acoustic Settings===============================================" << std::endl;
    report_file << "Sensitivity : "<< acoustic_input.sensitivity<<std::endl;
    report_file << "Window Length (s) : " << acoustic_input.win << std::endl;
    report_file << "Noverlap Length (s) : " << acoustic_input.noverlap << std::endl;
    report_file << "Calculate Variable : ";
    if (acoustic_input.check_total_spectrogram) {
        report_file << "Total Spectrogram, ";
    }
    
    if (acoustic_input.check_ACI_map) {
        report_file << "Acoustic Complexity Index(ACI), ";
    }
    if (acoustic_input.check_Ambient_estimate) {
        report_file << "Ambient Noise Estimate, ";
    }
    if (acoustic_input.check_octave_band) {
        report_file << "1/3 Octave Band, " << std::endl;
        report_file << "1/3 Octave Band Center Frequency : ";
        for (int i = 0; i < acoustic_input.Oc_Center_frequency.size(); i++) {
            report_file << acoustic_input.Oc_Center_frequency[i] << " ";
        }
    }
    report_file <<std::endl<< "=============================================System Settings============================================="<<std::endl;
    report_file << std::endl << "Input File Path : " << audio_file->text().toUtf8().constData() << std::endl;
    report_file << "Output File Path : " << save_file->text().toUtf8().constData() << std::endl;
    report_file << "File Numbers : " << load_path_list.size() << std::endl;
    report_file << "File Process Time(s) : " << system_time << std::endl;
    report_file.close();

}
void LTSM::initialize() {
    //Initialize the input_number
    acoustic_input.check_total_spectrogram = true;
    acoustic_input.check_octave_band = true;
    acoustic_input.check_ACI_map = true;
    acoustic_input.check_Ambient_estimate = true;
    acoustic_input.win = 1;
    acoustic_input.noverlap = 0.0;
    acoustic_input.sensitivity = 176.3;
    acoustic_input.ambient_estimate_percentile = 0.2;
    acoustic_input.Oc_Center_frequency.push_back(63);
    acoustic_input.Oc_Center_frequency.push_back(125);
    acoustic_input.Oc_Center_frequency.push_back(400);
    acoustic_input.Oc_Center_frequency.push_back(1000);
    acoustic_input.Oc_Center_frequency.push_back(2000);
    acoustic_input.Oc_Center_frequency.push_back(4000);
    acoustic_input.Oc_Center_frequency.push_back(8000);
    acoustic_input.Oc_Center_frequency.push_back(16000);

    //figure_input_initialize
    figure_input.xlim_low = 0;
    figure_input.xlim_high = 0;
    figure_input.ylim_low = 0;
    figure_input.ylim_high = 0;
    figure_input.clim_low = 0;
    figure_input.clim_high = 0;
    figure_input.Figure_setting_type = 1;
    figure_input.auto_scale = true;

}
LTSM::~LTSM()
{}
