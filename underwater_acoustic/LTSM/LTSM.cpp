#include "LTSM.h"
#include"../tool/Data_split.h"

LTSM::LTSM(QWidget* parent)
{
 
    initialize();
    initial_analyze_input();
    
}
void LTSM::start() {
    
    if (analyze_input.if_start == false) {
        analyze_input.if_start = true;
        thread->moveToThread(m_workerThread);
        thread->acoustic_input = acoustic_input;
        thread->analyze_input = &analyze_input;
        thread->figure_input = figure_input;
        m_workerThread->start();

    }
}
void LTSM::stop() {
    thread->stop();
    m_workerThread->quit();
    m_workerThread->wait();
    m_workerThread = new QThread();
    thread = new workThread();
    connect(m_workerThread, &QThread::started, thread, &workThread::start1);
    connect(thread, &workThread::workFinished, m_workerThread, &QThread::quit);
    connect(m_workerThread, &QThread::finished, m_workerThread, &QThread::deleteLater);
    connect(analyze_input.analyze_button, &QPushButton::clicked, this, &LTSM::start);
}
void LTSM::read_file_path() {
    //read audio file;
    analyze_input.dir = QFileDialog::getExistingDirectory();
    analyze_input.audio_file->setText(analyze_input.dir);
}
void LTSM::save_file_path() {
    //read audio file;
    analyze_input.dir = QFileDialog::getExistingDirectory();
    analyze_input.save_file->setText(analyze_input.dir);
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


void LTSM::initialize() {
    std::string setting_path = "Setting.txt";
    std::fstream fin(setting_path.c_str());
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
void LTSM::initial_analyze_input(){
    font = new QFont();

    font->setFamily("Verdana");
    font->setPointSize(15);

    analyze_input.spectrogram = new QCustomPlot(this);
    analyze_input.spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));;
    analyze_input.fig = new QCustomPlot(this);
    analyze_input.fig->addGraph();
    analyze_input.fig->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));;
    //Button
    //button audio read path
    //set size and location of the button
    analyze_input.audio_file_read_button = new QPushButton("...", this);
    analyze_input.audio_file_read_button->setGeometry(QRect(QPoint(550, 20), QSize(50, 50)));
    analyze_input.save_file_read_button = new QPushButton("...", this);
    analyze_input.save_file_read_button->setGeometry(QRect(QPoint(550, 120), QSize(50, 50)));
    analyze_input.analyze_button = new QPushButton("Start", this);
    analyze_input.analyze_button->setGeometry(QRect(QPoint(20, 190), QSize(70, 50)));
    analyze_input.stop_button = new QPushButton("Stop", this);
    analyze_input.stop_button->setGeometry(QRect(QPoint(95, 190), QSize(70, 50)));
    analyze_input.Setting_Button = new QPushButton("Acoustic Setting Panel", this);
    analyze_input.Setting_Button->setGeometry(QRect(QPoint(600, 20), QSize(250, 50)));
    analyze_input.Figure_Setting_Button = new QPushButton("Figure Setting Panel", this);
    analyze_input.Figure_Setting_Button->setGeometry(QRect(QPoint(600, 120), QSize(250, 50)));



    analyze_input.analyze_button->setFont(*font);
    analyze_input.stop_button->setFont(*font);
    analyze_input.audio_file_read_button->setFont(*font);
    analyze_input.save_file_read_button->setFont(*font);
    analyze_input.Setting_Button->setFont(*font);
    analyze_input.Figure_Setting_Button->setFont(*font);
    //connect to the function
    connect(analyze_input.audio_file_read_button, &QPushButton::clicked, this, &LTSM::read_file_path);
    connect(analyze_input.save_file_read_button, &QPushButton::clicked, this, &LTSM::save_file_path);
    connect(analyze_input.Setting_Button, &QPushButton::clicked, this, &LTSM::open_setting_pannel);
    connect(analyze_input.Figure_Setting_Button, &QPushButton::clicked, this, &LTSM::open_figure_setting_pannel);



    //Line Edit Audio file path
    analyze_input.audio_file = new QLineEdit(this);
    analyze_input.save_file = new QLineEdit(this);


    

    //Line Edit Save File path
    analyze_input.audio_file->setGeometry(QRect(QPoint(150, 20), QSize(400, 50)));
    analyze_input.audio_file->setFont(*font);

    

    analyze_input.save_file->setGeometry(QRect(QPoint(150, 120), QSize(400, 50)));
    analyze_input.save_file->setFont(*font);


    analyze_input.audio_file->setText("D:/test");
    analyze_input.save_file->setText("D:/test");

    //Progress Bar
    font->setPointSize(10);
    analyze_input.wav_processing = new QLabel(this);
    analyze_input.wav_processing->setGeometry(QRect(QPoint(170, 190), QSize(700, 25)));
    analyze_input.wav_processing->setFont(*font);
    analyze_input.wav_processing->setAlignment(Qt::AlignHCenter);
    analyze_input.progressBar = new QProgressBar(this);
    analyze_input.progressBar->setRange(0, 100);
    analyze_input.progressBar->setGeometry(QRect(QPoint(170, 215), QSize(700, 25)));
    //Audio File Label
    font->setPointSize(15);
    analyze_input.Audio_file_label = new QLabel("Audio Path : ", this);
    analyze_input.Audio_file_label->setGeometry(QRect(QPoint(20, 20), QSize(150, 50)));
    analyze_input.Audio_file_label->setFont(*font);
    analyze_input.Spec_file_label = new QLabel("Result Path : ", this);
    analyze_input.Spec_file_label->setGeometry(QRect(QPoint(20, 120), QSize(150, 50)));
    analyze_input.Spec_file_label->setFont(*font);

    //
    analyze_input.Oc_Band = new QCPBars(analyze_input.fig->xAxis, analyze_input.fig->yAxis);
    analyze_input.if_start = true;
    //multi thread

    connect(analyze_input.stop_button, &QPushButton::clicked, this, &LTSM::stop);

    analyze_input.if_start = true;
    m_workerThread = new QThread();
    thread = new workThread();
    thread->moveToThread(m_workerThread);
    thread->acoustic_input = acoustic_input;
    thread->analyze_input = &analyze_input;
    thread->figure_input = figure_input;
    connect(m_workerThread, &QThread::started, thread, &workThread::start1);
    connect(thread, &workThread::workFinished, m_workerThread, &QThread::quit);
    connect(m_workerThread, &QThread::finished, m_workerThread, &QThread::deleteLater);
    connect(analyze_input.analyze_button, &QPushButton::clicked, this, &LTSM::start);
    analyze_input.if_start = false;
}
LTSM::~LTSM()
{}
