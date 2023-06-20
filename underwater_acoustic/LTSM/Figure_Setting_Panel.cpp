#pragma once
#include "Figure_Setting_Panel.h"

Figure_Setting_Panel::Figure_Setting_Panel(Figure_Input*input, QWidget* parent) {
	font = new QFont();
	font->setFamily("Verdana");
	font->setPointSize(15); 
	temp_input = input;


	std::string temp_str;
	////autoscale
	auto_scale_text = new QLabel("     Auto Scale The Axis : ",this);
	auto_scale_text->setGeometry(QRect(QPoint(20, 20), QSize(300, 50)));
	auto_scale_text->setFont(*font);
	auto_scale = new QCheckBox(this);
	auto_scale->setGeometry(QRect(QPoint(320, 20), QSize(150, 50)));
	auto_scale->setChecked(temp_input->auto_scale);
	//X Limit
	xlim = new QLabel("Xlim : ", this);
	xlim->setGeometry(QRect(QPoint(20, 120), QSize(100, 50)));
	xlim->setFont(*font);
	xlim_low = new QLineEdit(this);
	xlim_low->setGeometry(QRect(QPoint(120, 120), QSize(100, 50)));
	xlim_low->setFont(*font);
	temp_str = std::to_string(temp_input->xlim_low);
	xlim_low->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") + 2)));
	xlim_high = new QLineEdit(this);
	xlim_high->setGeometry(QRect(QPoint(240, 120), QSize(100, 50)));
	xlim_high->setFont(*font);
	temp_str = std::to_string(temp_input->xlim_high);
	xlim_high->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") + 2)));
	//Y Limit
	ylim = new QLabel("Ylim : ", this);
	ylim->setGeometry(QRect(QPoint(20, 220), QSize(100, 50)));
	ylim->setFont(*font);
	ylim_low = new QLineEdit(this);
	ylim_low->setGeometry(QRect(QPoint(120, 220), QSize(100, 50)));
	ylim_low->setFont(*font);
	temp_str = std::to_string(temp_input->ylim_low);
	ylim_low->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") + 2)));
	ylim_high = new QLineEdit(this);
	ylim_high->setGeometry(QRect(QPoint(240, 220), QSize(100, 50)));
	ylim_high->setFont(*font);
	temp_str = std::to_string(temp_input->ylim_high);
	ylim_high->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") + 2)));
	//C Limit
	clim = new QLabel("Clim : ", this);
	clim->setGeometry(QRect(QPoint(20, 320), QSize(100, 50)));
	clim->setFont(*font);
	clim_low = new QLineEdit(this);
	clim_low->setGeometry(QRect(QPoint(120, 320), QSize(100, 50)));
	clim_low->setFont(*font);
	temp_str = std::to_string(temp_input->clim_low);
	clim_low->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") + 2)));
	clim_high = new QLineEdit(this);
	clim_high->setGeometry(QRect(QPoint(240, 320), QSize(100, 50)));
	clim_high->setFont(*font);
	temp_str = std::to_string(temp_input->clim_high);
	clim_high->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") + 2)));
	//figure type

	figure_type = new QComboBox(this);
	figure_type->setGeometry(QRect(QPoint(20, 420), QSize(300, 50)));
	figure_type->addItem("Spectrogram");
	figure_type->addItem("Spectrum");
	figure_type->addItem("1/3 Octave Band");
	figure_type->setFont(*font);
	figure_type->setCurrentIndex(temp_input->Figure_setting_type);
	//Comfrim Button
	confirm_button = new QPushButton("Confirm", this);
	confirm_button->setGeometry(QRect(QPoint(800, 400), QSize(150, 50)));
	confirm_button->setFont(*font);
	connect(confirm_button, &QPushButton::clicked, this, &Figure_Setting_Panel::Change_value);


}
void Figure_Setting_Panel::Change_value() {
	temp_input->xlim_low = std::stod(xlim_low->text().toUtf8().constData());
	temp_input->xlim_high = std::stod(xlim_high->text().toUtf8().constData());
	temp_input->ylim_low = std::stod(xlim_low->text().toUtf8().constData());
	temp_input->ylim_high = std::stod(xlim_high->text().toUtf8().constData());
	temp_input->clim_low = std::stod(xlim_low->text().toUtf8().constData());
	temp_input->clim_high = std::stod(xlim_high->text().toUtf8().constData());
	temp_input->auto_scale = auto_scale->isChecked();
	temp_input->Figure_setting_type = figure_type->currentIndex();
	this->close();
}
Figure_Setting_Panel::~Figure_Setting_Panel()
{}