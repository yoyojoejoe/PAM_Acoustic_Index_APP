#include "single_wav_spectrogram.h"
#include"../tool/Spectral_analyze.h"

single_wav_spectrogram::single_wav_spectrogram(QWidget* parent)
{
    font = new QFont();

    font->setFamily("Verdana");
    font->setPointSize(15);

    
    fig = new QCustomPlot(this);
    fig->addGraph();
    spectrogram = new QCustomPlot(this);
    fig->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));;
    spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));;

    //Button
    //button audio read path
    audio_file_read_button = new QPushButton("...", this);
    save_file_read_button = new QPushButton("...", this);
    spectrogram_button = new QPushButton("Spectrogram", this);
    spectrum_button = new QPushButton("Spectrum", this);
    raw_data_button = new QPushButton("Wave Form", this);
    //set size and location of the button
    audio_file_read_button->setGeometry(QRect(QPoint(550, 20), QSize(50, 50)));
    save_file_read_button->setGeometry(QRect(QPoint(550, 120), QSize(50, 50)));
    spectrogram_button->setGeometry(QRect(QPoint(20, 190), QSize(150, 50)));
    spectrum_button->setGeometry(QRect(QPoint(190, 190), QSize(150, 50)));
    raw_data_button->setGeometry(QRect(QPoint(360, 190), QSize(150, 50)));

    spectrogram_button->setFont(*font);
    spectrum_button->setFont(*font);
    audio_file_read_button->setFont(*font);
    save_file_read_button->setFont(*font);
    raw_data_button->setFont(*font);
    //connect to the function
    connect(audio_file_read_button, &QPushButton::clicked, this, &single_wav_spectrogram::read_file_path);
    connect(save_file_read_button, &QPushButton::clicked, this, &single_wav_spectrogram::save_file_path);
    connect(spectrogram_button, &QPushButton::clicked, this, &single_wav_spectrogram::spectrogram_plot);
    connect(spectrum_button, &QPushButton::clicked, this, &single_wav_spectrogram::spectrum_plot);
    connect(raw_data_button, &QPushButton::clicked, this, &single_wav_spectrogram::wave_plot);
    //Line Edit Audio file path
    audio_file = new QLineEdit(this);
    save_file = new QLineEdit(this);
    window = new QLineEdit(this);
    noverlap = new QLineEdit(this);
    //Line Edit Save File path
    audio_file->setGeometry(QRect(QPoint(150, 20), QSize(400, 50)));
    audio_file->setFont(*font);
    save_file->setGeometry(QRect(QPoint(150, 120), QSize(400, 50)));
    save_file->setFont(*font);
    window->setGeometry(QRect(QPoint(750, 20), QSize(100, 50)));
    window->setFont(*font);
    noverlap->setGeometry(QRect(QPoint(750, 120), QSize(100, 50)));
    noverlap->setFont(*font);
    audio_file->setText("D:/test.wav");
    save_file->setText("D:/spectrogram.txt");
    window->setText("0.01");
    noverlap->setText("0");
    //Label
    image_label = new QLabel(this);
    //image_label->setGeometry(QRect(QPoint(50, 250), QSize(1200, 350)));
    image_pix = new QPixmap();
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
void single_wav_spectrogram::read_file_path() {
    //read audio file;
    dir = QFileDialog::getOpenFileName(this, "Select source file",".","Wav files (*.wav)");
    audio_file->setText(dir);
}
void single_wav_spectrogram::save_file_path() {
    //read audio file;
    dir = QFileDialog::getExistingDirectory();
    save_file->setText(dir);
}
void single_wav_spectrogram::spectrogram_plot() {

    spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(1200, 350)));;
    fig->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));;
    spectrogram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    spectrogram->axisRect()->setupFullAxesBox(true);
    spectrogram->xAxis->setLabel("Time (s)");
    spectrogram->yAxis->setLabel("Frequency (Hz)");
    std::string path = audio_file->text().toUtf8().constData();
    std::string path2 = save_file->text().toUtf8().constData();
    Spectral_analyze* spec = new Spectral_analyze(176.3);
    spec->Audio_read(path);
    int win = std::stod(window->text().toUtf8().constData()) * (1.0 * spec->fs);
    int overlap = std::stod(noverlap->text().toUtf8().constData()) * (1.0 * spec->fs);
    spec->STFT(win, overlap);

    
    pcolor = new QCPColorMap(spectrogram->xAxis, spectrogram->yAxis);
    int nx = spec->time.size();
    int ny = spec->frequency.size()/2+1;
    pcolor->data()->setSize(nx, ny);
    pcolor->data()->setRange(QCPRange(spec->time(0), spec->time(nx-1)), QCPRange(spec->frequency(0), spec->frequency(ny-1))); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    //pcolor->data()->setRange(QCPRange(spec->time.minCoeff(), spec->time.maxCoeff()), QCPRange(spec->frequency.minCoeff(), spec->frequency.minCoeff()));
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {   
            pcolor->data()->setCell(i, j, spec->spectrogram(j,i));
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
void single_wav_spectrogram::spectrum_plot() {
    fig->setGeometry(QRect(QPoint(50, 250), QSize(1200, 350)));;
    spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));;
    std::string path = audio_file->text().toUtf8().constData();
    std::string path2 = save_file->text().toUtf8().constData();
    Spectral_analyze* spec = new Spectral_analyze(176.3);
    spec->Audio_read(path);
    int win = std::stod(window->text().toUtf8().constData()) * (1.0 * spec->fs);
    int overlap = std::stod(noverlap->text().toUtf8().constData()) * (1.0 * spec->fs);
    spec->STFT(win, overlap);
    
    QVector<double> x(spec->frequency_spectrum.size()), y(spec->frequency_spectrum.size()); // initialize with entries 0..100
    for (int i = 0; i < spec->frequency_spectrum.size(); i++)
    {
        x[i] = spec->frequency_spectrum(i); // x goes from -1 to 1
        y[i] = spec->Spectrum(i); // let's plot a quadratic function
    }
    // create graph and assign data to it:
    
    fig->graph(0)->setData(x, y);
    fig->xAxis->setRange(spec->frequency_spectrum.minCoeff(), spec->frequency_spectrum.maxCoeff());
    fig->yAxis->setRange(spec->Spectrum.minCoeff(), spec->Spectrum.array().maxCoeff());
    // give the axes some labels:
    fig->xAxis->setLabel("Frequency (Hz)");
    fig->yAxis->setLabel("SPL (dB)");
    // set axes ranges, so we see all data:
    fig->replot();
    fig->show();
    delete spec;
}
void single_wav_spectrogram::wave_plot() {
    fig->setGeometry(QRect(QPoint(50, 250), QSize(1200, 350)));;
    spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));;
    std::string path = audio_file->text().toUtf8().constData();
    std::string path2 = save_file->text().toUtf8().constData();
    Spectral_analyze* spec = new Spectral_analyze(176.3);
    spec->Audio_read(path);
    QVector<double> x(spec->time_wav.size()), y(spec->time_wav.size());
    for (int i = 0; i < spec->time_wav.size(); i++)
    {
        x[i] = spec->time_wav(i); // x goes from -1 to 1
        y[i] = spec->data(i); // let's plot a quadratic function
    }
    // create graph and assign data to it:
    fig->graph(0)->setData(x, y);
    fig->xAxis->setRange(spec->time_wav.minCoeff(), spec->time_wav.maxCoeff());
    fig->yAxis->setRange(spec->data.minCoeff(), spec->data.array().maxCoeff());
    // give the axes some labels:
    fig->xAxis->setLabel("Frequency (Hz)");
    fig->yAxis->setLabel("SPL (dB)");
    // set axes ranges, so we see all data:
    fig->replot();
    fig->show();
    delete spec;
}
single_wav_spectrogram::~single_wav_spectrogram()
{}
