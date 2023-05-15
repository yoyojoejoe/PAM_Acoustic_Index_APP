#pragma once
#include "Setting_Panel.h"

Setting_Panel::Setting_Panel(Acousic_Input *input, QWidget* parent) {
	font = new QFont();
	font->setFamily("Verdana");
	font->setPointSize(15); 
	temp_input = input;

	window_Label = new QLabel("Window (s) : ", this);
	window_Label->setGeometry(QRect(QPoint(20, 120), QSize(150, 50)));
	window_Label->setFont(*font);
	noverlap_Label = new QLabel("Noverlap (s) : ", this);
	noverlap_Label->setGeometry(QRect(QPoint(20, 220), QSize(150, 50)));
	noverlap_Label->setFont(*font);
	sensitivity_Label = new QLabel("Sensitivity : ", this);
	sensitivity_Label->setGeometry(QRect(QPoint(20, 320), QSize(200, 50)));
	sensitivity_Label->setFont(*font);
	Oc_Label = new QLabel("Octave Freq : ", this);
	Oc_Label->setGeometry(QRect(QPoint(20, 20), QSize(200, 50)));
	Oc_Label->setFont(*font);


	std::string temp_str;
	window_LineEdit = new QLineEdit(this);
	window_LineEdit->setGeometry(QRect(QPoint(200, 120), QSize(150, 50)));
	window_LineEdit->setFont(*font);
	temp_str = std::to_string(temp_input->win);
	window_LineEdit->setText(QString::fromStdString( temp_str.substr(0,temp_str.find(".")+3 )));
	noverlap_LineEdit = new QLineEdit(this);
	noverlap_LineEdit->setGeometry(QRect(QPoint(200, 220), QSize(150, 50)));
	noverlap_LineEdit->setFont(*font);
	temp_str = std::to_string(temp_input->noverlap);
	noverlap_LineEdit->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") +3)));
	sensitivity_LineEdit = new QLineEdit(this);
	sensitivity_LineEdit->setGeometry(QRect(QPoint(200, 320), QSize(150, 50)));
	sensitivity_LineEdit->setFont(*font);
	temp_str = std::to_string(temp_input->sensitivity);
	sensitivity_LineEdit->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") +2)));
	Oc_LineEdit = new QLineEdit(this);
	Oc_LineEdit->setGeometry(QRect(QPoint(200, 20), QSize(700, 50)));
	Oc_LineEdit->setFont(*font);


	temp_str = "";
	for (int i = 0; i < temp_input->Oc_Center_frequency.size(); i++) {
		std::string temp_float = std::to_string(temp_input->Oc_Center_frequency[i]);
		temp_float = temp_float.substr(0, temp_float.find(".") + 2);
		temp_str += temp_float;
		temp_str += ", ";
	}
	Oc_LineEdit->setText(QString::fromStdString(temp_str));
	

	OC_band_check = new QCheckBox(this);
	OC_band_check->setGeometry(QRect(QPoint(600, 120), QSize(150, 50)));
	OC_band_check->setChecked(temp_input->check_octave_band);
	OC_check_Label = new QLabel("1/3 Octave Band :",this);
	OC_check_Label->setGeometry(QRect(QPoint(400, 120), QSize(200, 50)));
	OC_check_Label->setFont(*font);

	ACI_check = new QCheckBox(this);
	ACI_check->setGeometry(QRect(QPoint(900, 120), QSize(150, 50)));
	ACI_check->setChecked(temp_input->check_ACI_map);
	ACI_check_Label = new QLabel("ACI Calculate :", this);
	ACI_check_Label->setGeometry(QRect(QPoint(740, 120), QSize(160, 50)));
	ACI_check_Label->setFont(*font);

	confirm_button = new QPushButton("Confirm", this);
	confirm_button->setGeometry(QRect(QPoint(800, 400), QSize(150, 50)));
	confirm_button->setFont(*font);
	connect(confirm_button, &QPushButton::clicked, this, &Setting_Panel::Change_value);

}
void Setting_Panel::Change_value() {
	temp_input->win = std::stod(window_LineEdit->text().toUtf8().constData());
	temp_input->noverlap = std::stod(noverlap_LineEdit->text().toUtf8().constData());
	temp_input->sensitivity = std::stod(sensitivity_LineEdit->text().toUtf8().constData());
	std::string a = Oc_LineEdit->text().toUtf8().constData();
	std::vector<double> aa = transfer_string_doble(a);
	temp_input->Oc_Center_frequency = aa;
	this->close();
	temp_input->check_ACI_map = ACI_check->isChecked();
	temp_input->check_octave_band = OC_band_check->isChecked();
}
std::vector<double> Setting_Panel::transfer_string_doble(std::string a) {
	std::vector<double> result;
	std::string temp;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] == ',' ) {
			result.push_back(std::stod(temp));
			temp = "";
		}
		else {
			temp += a[i];
		}
		
	}
	return result;
}
Setting_Panel::~Setting_Panel()
{}