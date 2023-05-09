#pragma once
#include "Setting_Panel.h"

Setting_Panel::Setting_Panel(double *win, double *noverlap, double* sensitivity, std::vector<double>&oc_center_freq, QWidget* parent) {
	font = new QFont();
	font->setFamily("Verdana");
	font->setPointSize(15); 

	temp_win = win;
	temp_noverlap = noverlap;
	temp_sensitivity = sensitivity;
	temp_oc_center_freq = &oc_center_freq;

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
	temp_str = std::to_string(*win);
	window_LineEdit->setText(QString::fromStdString( temp_str.substr(0,temp_str.find(".")+3 )));
	noverlap_LineEdit = new QLineEdit(this);
	noverlap_LineEdit->setGeometry(QRect(QPoint(200, 220), QSize(150, 50)));
	noverlap_LineEdit->setFont(*font);
	temp_str = std::to_string(*noverlap);
	noverlap_LineEdit->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") +3)));
	sensitivity_LineEdit = new QLineEdit(this);
	sensitivity_LineEdit->setGeometry(QRect(QPoint(200, 320), QSize(150, 50)));
	sensitivity_LineEdit->setFont(*font);
	temp_str = std::to_string(*sensitivity);
	sensitivity_LineEdit->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") +2)));
	Oc_LineEdit = new QLineEdit(this);
	Oc_LineEdit->setGeometry(QRect(QPoint(200, 20), QSize(700, 50)));
	Oc_LineEdit->setFont(*font);

	temp_str = "";
	for (int i = 0; i < oc_center_freq.size(); i++) {
		std::string temp_float = std::to_string(oc_center_freq[i]);
		temp_float = temp_float.substr(0, temp_float.find(".") + 2);
		temp_str += temp_float;
		temp_str += ", ";
	}
	Oc_LineEdit->setText(QString::fromStdString(temp_str));
	

	confirm_button = new QPushButton("Confirm", this);
	confirm_button->setGeometry(QRect(QPoint(800, 400), QSize(150, 50)));
	confirm_button->setFont(*font);
	connect(confirm_button, &QPushButton::clicked, this, &Setting_Panel::Change_value);

}
void Setting_Panel::Change_value() {
	*temp_win = std::stod(window_LineEdit->text().toUtf8().constData());
	*temp_noverlap = std::stod(noverlap_LineEdit->text().toUtf8().constData());
	*temp_sensitivity = std::stod(sensitivity_LineEdit->text().toUtf8().constData());
	std::string a = Oc_LineEdit->text().toUtf8().constData();
	std::vector<double> aa = transfer_string_doble(a);
	*temp_oc_center_freq = aa;
	this->close();
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