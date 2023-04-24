#include "underwater_acoustic.h"

underwater_acoustic::underwater_acoustic(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    stack = new QStackedWidget(this);
    stack->setFrameStyle(QFrame::Panel | QFrame::Raised);
    single_spectrogram_class = new single_wav_spectrogram();
    LTSM_class = new LTSM();
    stack->addWidget(single_spectrogram_class);
    stack->addWidget(LTSM_class);
    this->setCentralWidget(stack);
    Spectrogram_button = new QPushButton("Wave Spectrogram", this);
    Spectrogram_button->setGeometry(QRect(QPoint(1000, 20), QSize(250, 50)));
    Spectrogram_button->setFont(*LTSM_class->font);
    connect(Spectrogram_button, &QPushButton::clicked, this, &underwater_acoustic::spectrogram_change);

    LTSM_button = new QPushButton("LTSM", this);
    LTSM_button->setGeometry(QRect(QPoint(1000, 70), QSize(250, 50)));
    LTSM_button->setFont(*LTSM_class->font);
    connect(LTSM_button, &QPushButton::clicked, this, &underwater_acoustic::LTSM_change);
    //set_single_spectrogram();
}
void underwater_acoustic::LTSM_change() {
    this->stack->setCurrentIndex(1);
}
void underwater_acoustic::spectrogram_change() {
    this->stack->setCurrentIndex(0);
}
underwater_acoustic::~underwater_acoustic()
{}
