#include "workThread.h"

using namespace std;

workThread::workThread(QObject* parent) : QObject(parent)
{

}
workThread::~workThread()
{
}
void workThread::start1()
{
    emit workStart();
    Analyze();
}
void workThread::Analyze()
{   
    DWORD star_time = GetTickCount();//Analyze Function Time Calculate
    font.setFamily("Verdana");
    font.setPointSize(12);
    analyze_input->Long_Spectrogram.clear();
    std::vector<double> temp_spectrum;
    std::string temp;
    analyze_input->load_path = analyze_input->audio_file->text().toUtf8().constData();
    analyze_input->save_path = analyze_input->save_file->text().toUtf8().constData();
    load_wav_file();
    analyze_input->wav_processing->setText(QString::fromStdString("Initialize..."));
    analyze_input->progressBar->setValue(0);
    Spectral_analyze* spec2 = new Spectral_analyze(acoustic_input.sensitivity);
    spec2->Audio_read(analyze_input->load_path_list[0]);
    //spec.Audio_read(load_path_list[0]);
    //int win = std::stod(window->text().toUtf8().constData()) * (1.0 * spec2->fs);
    //int overlap = std::stod(noverlap->text().toUtf8().constData()) * (1.0 * spec2->fs);
    analyze_input->temp_win = acoustic_input.win * spec2->fs;
    analyze_input->temp_noverlap = acoustic_input.noverlap * spec2->fs;
    //save_frequency
    analyze_input->spectrogram_file_path = "";
    analyze_input->Oc_file_path = "";
    analyze_input->ACI_file_path = "";
    analyze_input->Ambient_file_path = "";
    if (acoustic_input.check_total_spectrogram) {
        analyze_input->spectrogram_file_path = analyze_input->save_file->text().toUtf8().constData();
        analyze_input->spectrogram_file_path += "/Total_Spectrogram.csv";
        std::ofstream spectrogram_file(analyze_input->spectrogram_file_path);
        spectrogram_file << " ,";
        for (int i = 0; i < analyze_input->temp_win / 2 + 1; i++) {
            spectrogram_file << i * (spec2->fs) / analyze_input->temp_win << ",";
        }
        spectrogram_file << '\n';
        spectrogram_file.close();
    }
    if (acoustic_input.check_Ambient_estimate) {
        analyze_input->Ambient_file_path = analyze_input->save_file->text().toUtf8().constData();
        analyze_input->Ambient_file_path += "/Ambient_Noise.csv";
        std::ofstream Ambient_file(analyze_input->Ambient_file_path);
        Ambient_file << " ,";
        for (int i = 0; i < analyze_input->temp_win / 2 + 1; i++) {
            Ambient_file << i * (spec2->fs) / analyze_input->temp_win << ",";
        }
        Ambient_file << '\n';
        Ambient_file.close();
    }
    if (acoustic_input.check_ACI_map) {
        analyze_input->ACI_file_path = analyze_input->save_file->text().toUtf8().constData();
        analyze_input->ACI_file_path += "/ACI.csv";
        std::ofstream ACI_file(analyze_input->ACI_file_path);
        ACI_file << " ,";
        for (int i = 0; i < analyze_input->temp_win / 2 + 1; i++) {
            ACI_file << i * (spec2->fs) / analyze_input->temp_win << ",";
        }
        ACI_file << '\n';
        ACI_file.close();
    }
    if (acoustic_input.check_octave_band) {
        analyze_input->Oc_file_path = analyze_input->save_file->text().toUtf8().constData();
        analyze_input->Oc_file_path += "/One_Third_Octave_Band.csv";
        std::ofstream Octave_Band_file(analyze_input->Oc_file_path);
        Octave_Band_file << " ,";
        for (int i = 0; i < acoustic_input.Oc_Center_frequency.size(); i++) {
            Octave_Band_file << acoustic_input.Oc_Center_frequency[i] << ",";
        }
        Octave_Band_file << '\n';
        Octave_Band_file.close();
    }

    delete(spec2);
    //spec.STFT(win, overlap);
    //spec.LTSM_Time();
    if (figure_input.Figure_setting_type == 1.0) {
        analyze_input->fig->setGeometry(QRect(QPoint(50, 250), QSize(1200, 350)));
        analyze_input->spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));
        
        //fig->xAxis->setScaleType(QCPAxis::stLogarithmic);
        // give the axes some labels:
        analyze_input->fig->xAxis->setLabel("Frequency (Hz)");
        analyze_input->fig->yAxis->setLabel("SPL (dB re 1μ Pa)");
        analyze_input->fig->xAxis->setScaleType(QCPAxis::stLogarithmic);
        analyze_input->fig->xAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
        analyze_input->fig->xAxis->setNumberPrecision(0);
        analyze_input->fig->xAxis->setLabelFont(font);
        analyze_input->fig->yAxis->setLabelFont(font);
        analyze_input->fig->xAxis->setTickLabelFont(font);
        analyze_input->fig->yAxis->setTickLabelFont(font);
        QSharedPointer<QCPAxisTickerLog> fixedTicker(new QCPAxisTickerLog);
        fixedTicker->setLogBase(10);
        analyze_input->fig->xAxis->setTicker(fixedTicker);
    }
    for (int i = 0; i < analyze_input->load_path_list.size(); i++) {
        if (analyze_input->if_start==false) {
            break;
        }
        temp_spectrum.clear();
        Spectral_analyze* spec = new Spectral_analyze(acoustic_input.sensitivity);
        std::string temp =analyze_input->load_path_list[i].substr(analyze_input->load_path.length() + 1, analyze_input->load_path_list[i].length() - 1);
        temp += "  is processing.    ";
        temp += std::to_string(i + 1);
        temp += " / ";
        temp += std::to_string(analyze_input->load_path_list.size());
        analyze_input->wav_processing->setText(QString::fromStdString(temp));
        spec->Audio_read(analyze_input->load_path_list[i]);
        spec->STFT(analyze_input->temp_win, analyze_input->temp_noverlap);
        if (figure_input.Figure_setting_type == 1.0) {
            draw_spectrum(spec);
        }
        if (acoustic_input.check_total_spectrogram) {// all spectrogram
            temp_spectrum.resize(spec->Spectrum.size());
            VectorXd::Map(&temp_spectrum[0], spec->Spectrum.size()) = spec->Spectrum;
            spec->save_as_csv(spec->Spectrum, analyze_input->spectrogram_file_path, analyze_input->load_path_list[i].substr(analyze_input->load_path.length() + 1, analyze_input->load_path_list[i].length() - 1));
            if (figure_input.Figure_setting_type == 0) {
                analyze_input->Long_Spectrogram.push_back(temp_spectrum);
                draw_spectrogram(spec);
            }
        }
        if (acoustic_input.check_Ambient_estimate) {
            spec->Ambient_Noise_Estimate(acoustic_input.ambient_estimate_percentile);
            spec->save_as_csv(spec->Ambient_Noise_Spectrum, analyze_input->Ambient_file_path, analyze_input->load_path_list[i].substr(analyze_input->load_path.length() + 1, analyze_input->load_path_list[i].length() - 1));
        }
        if (acoustic_input.check_octave_band) {//1/3 Octave Band
            spec->Octave_Band(acoustic_input.Oc_Center_frequency, analyze_input->temp_win);
            if (figure_input.Figure_setting_type == 2.0) {
                draw_Oc_Band(spec);
            }
            spec->save_as_csv(spec->Octave_3_1, analyze_input->Oc_file_path, analyze_input->load_path_list[i].substr(analyze_input->load_path.length() + 1, analyze_input->load_path_list[i].length() - 1));
        }
        if (acoustic_input.check_ACI_map) {//Calculate ACI
            spec->ACI_Calculate();
            spec->save_as_csv(spec->ACI_spectrum, analyze_input->ACI_file_path, analyze_input->load_path_list[i].substr(analyze_input->load_path.length() + 1, analyze_input->load_path_list[i].length() - 1));
        }

        
        analyze_input->progressBar->setValue((i+1)*100/ analyze_input->load_path_list.size());
    }
    DWORD end_time = GetTickCount();//Analyze Function Time Calculate
    generate_report((end_time - star_time) / 1000);
    analyze_input->wav_processing->setText(QString::fromStdString("Finish"));
    stop();


}




void workThread::draw_Oc_Band(Spectral_analyze* spec) {
    analyze_input->fig->removeGraph(0);
    analyze_input->fig->removeItem(0);

    analyze_input->fig->setGeometry(QRect(QPoint(50, 250), QSize(1200, 350)));
    analyze_input->spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));
    QVector<double> x(spec->Octave_3_1.size()), y(spec->Octave_3_1.size());
    QVector<QString> labels(spec->Octave_3_1.size());
    for (int i = 0; i < spec->Octave_3_1.size(); i++) {
        x[i] = i;
        y[i] = spec->Octave_3_1(i);
        labels[i] = QString::fromStdString(std::to_string(acoustic_input.Oc_Center_frequency[i]));
    }
    analyze_input->Oc_Band->setData(x, y);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(x, labels);
    analyze_input->fig->xAxis->setTicker(textTicker);
    analyze_input->fig->yAxis->setRange(spec->Octave_3_1.minCoeff() - 10, spec->Octave_3_1.maxCoeff() + 10);
    analyze_input->fig->xAxis->setRange(-1, spec->Octave_3_1.size());
    analyze_input->fig->xAxis->setLabel("Frequency (Hz)");
    analyze_input->fig->yAxis->setLabel("SPL (dB re 1μ Pa)");
    
    
    analyze_input->fig->xAxis->setLabelFont(font);
    analyze_input->fig->yAxis->setLabelFont(font);
    analyze_input->fig->xAxis->setTickLabelFont(font);
    analyze_input->fig->yAxis->setTickLabelFont(font);

    analyze_input->fig->xAxis->setNumberPrecision(0);
    analyze_input->fig->replot();
    analyze_input->fig->show();
}
void workThread::draw_spectrum(Spectral_analyze* spec) {
   
    QVector<double> x(spec->frequency_spectrum.size()), y(spec->frequency_spectrum.size()); // initialize with entries 0..100
    int x_initial, x_last;
    if (figure_input.auto_scale) {
        x_initial = 0;
        x_last = spec->frequency_spectrum.maxCoeff();
    }
    else {
        x_initial = figure_input.xlim_low;
        x_last = figure_input.xlim_high;
    }
    for (int i = x_initial; i < x_last; i++)
    {
        x[i] = spec->frequency_spectrum(i); // x goes from -1 to 1
        y[i] = spec->Spectrum(i); // let's plot a quadratic function
    }
    // create graph and assign data to it:

    analyze_input->fig->graph(0)->setData(x, y);
   
    analyze_input->fig->xAxis->setRange(x_initial, x_last);
    analyze_input->fig->yAxis->setRange(spec->Spectrum.minCoeff() - 10, spec->Spectrum.maxCoeff() + 10);
    // set axes ranges, so we see all data:
    analyze_input->fig->replot();
    analyze_input->fig->show();
}
void workThread::draw_spectrogram(Spectral_analyze* spec) {
    analyze_input->spectrogram->setGeometry(QRect(QPoint(50, 250), QSize(1200, 350)));
    analyze_input->fig->setGeometry(QRect(QPoint(50, 250), QSize(0, 0)));;
    analyze_input->spectrogram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    analyze_input->spectrogram->axisRect()->setupFullAxesBox(true);
    analyze_input->spectrogram->xAxis->setLabel("Time");
    analyze_input->spectrogram->yAxis->setLabel("Frequency (Hz)");
    analyze_input->pcolor = new QCPColorMap(analyze_input->spectrogram->xAxis, analyze_input->spectrogram->yAxis);
    int nx = analyze_input->Long_Spectrogram.size();
    int ny = analyze_input->Long_Spectrogram[0].size();
    analyze_input->pcolor->data()->setSize(nx, ny);
    analyze_input->pcolor->data()->setRange(QCPRange(0, nx), QCPRange(spec->frequency(0), spec->frequency(ny - 1))); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    //pcolor->data()->setRange(QCPRange(spec->time.minCoeff(), spec->time.maxCoeff()), QCPRange(spec->frequency.minCoeff(), spec->frequency.minCoeff()));
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j <= ny; j++)
        {
            analyze_input->pcolor->data()->setCell(i, j, analyze_input->Long_Spectrogram[i][j]);

        }

    }
    analyze_input->pcolor->data()->setCell(0, 0, 0);
    analyze_input->pcolor->data()->setCell(0, 1, 100);
    QCPColorScale* colorScale = new QCPColorScale(analyze_input->spectrogram);
    QCPColorGradient* colorgradient = new QCPColorGradient();
    analyze_input->spectrogram->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setType(QCPAxis::atRight);
    //colorScale->setDataRange(QCPRange(-100, 150));
    colorScale->axis()->setLabel("SPL");
    analyze_input->pcolor->setColorScale(colorScale);
    analyze_input->pcolor->setGradient(QCPColorGradient::gpJet);

    analyze_input->pcolor->rescaleDataRange();
    QCPMarginGroup* marginGroup = new QCPMarginGroup(analyze_input->spectrogram);
    analyze_input->spectrogram->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    analyze_input->spectrogram->rescaleAxes();
    analyze_input->spectrogram->replot();
    analyze_input->spectrogram->show();
}


void workThread::load_wav_file() {
    struct _finddata_t fileinfo;
    std::string curr = analyze_input->load_path + "/*.wav";
    analyze_input->load_path_list.clear();
    std::string file_name;
    long long handle;
    if ((handle = _findfirst(curr.c_str(), &fileinfo)) == -1L)
    {
        return;
    }
    else
    {
        file_name = analyze_input->load_path + "/" + fileinfo.name;
        analyze_input->load_path_list.push_back(file_name);
        while (!(_findnext(handle, &fileinfo)))
        {
            file_name = analyze_input->load_path + "/" + fileinfo.name;
            analyze_input->load_path_list.push_back(file_name);
        }
        _findclose(handle);
    }
}
void workThread::generate_report(double system_time) {

    SYSTEMTIME sys;
    GetLocalTime(&sys);
    char tmp[64]{ NULL };
    sprintf(tmp, "%4d-%02d-%02d %02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);

    std::string report_file_path = "";
    report_file_path = analyze_input->save_file->text().toUtf8().constData();
    report_file_path += "/report.txt";
    std::ofstream report_file(report_file_path);
    report_file << "Report Generating Time : " << tmp << std::endl;
    report_file << std::endl << "===========================================Acoustic Settings===============================================" << std::endl;
    report_file << "Sensitivity : " << acoustic_input.sensitivity << std::endl;
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
    report_file <<std::endl<< std::endl << "=============================================System Settings=============================================" << std::endl;
    report_file << "Input File Path : " << analyze_input->audio_file->text().toUtf8().constData() << std::endl;
    report_file << "Output File Path : " << analyze_input->save_file->text().toUtf8().constData() << std::endl;
    report_file << "File Numbers : " << analyze_input->load_path_list.size() << std::endl;
    report_file << "File Process Time(s) : " << system_time << std::endl;
    report_file.close();

}
void workThread::stop() {
    analyze_input->if_start = false;
}