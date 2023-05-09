#pragma once
#include "Setting_Panel.h"

Setting_Panel::Setting_Panel(double *win, double *noverlap, QWidget* parent) {
	font = new QFont();
	font->setFamily("Verdana");
	font->setPointSize(15);

	temp_win = win;
	temp_noverlap = noverlap;

	window_Label = new QLabel("Window (s) : ", this);
	window_Label->setGeometry(QRect(QPoint(20, 20), QSize(150, 50)));
	window_Label->setFont(*font);
	noverlap_Label = new QLabel("Noverlap (s) : ", this);
	noverlap_Label->setGeometry(QRect(QPoint(20, 120), QSize(150, 50)));
	noverlap_Label->setFont(*font);


	std::string temp_str;
	window_LineEdit = new QLineEdit(this);
	window_LineEdit->setGeometry(QRect(QPoint(200, 20), QSize(150, 50)));
	window_LineEdit->setFont(*font);
	temp_str = std::to_string(*win);
	window_LineEdit->setText(QString::fromStdString( temp_str.substr(0,temp_str.find(".")+2+1)));
	noverlap_LineEdit = new QLineEdit(this);
	noverlap_LineEdit->setGeometry(QRect(QPoint(200, 120), QSize(150, 50)));
	noverlap_LineEdit->setFont(*font);
	temp_str = std::to_string(*noverlap);
	noverlap_LineEdit->setText(QString::fromStdString(temp_str.substr(0, temp_str.find(".") + 2 + 1)));
	

	confirm_button = new QPushButton("Confirm", this);
	confirm_button->setGeometry(QRect(QPoint(350, 400), QSize(150, 50)));

	connect(confirm_button, &QPushButton::clicked, this, &Setting_Panel::Change_value);

}
void Setting_Panel::Change_value() {
	*temp_win = std::stod(window_LineEdit->text().toUtf8().constData());
	*temp_noverlap = std::stod(noverlap_LineEdit->text().toUtf8().constData());
	this->close();
}
Setting_Panel::~Setting_Panel()
{}