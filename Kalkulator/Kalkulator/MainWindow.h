#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QtWidgets>
#include <QtCore/QtCore>
#include <iostream>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTextEdit * m_pTextEdit;
	QPushButton * m_pButton1;
	QPushButton * m_pButton2;
	QPushButton * m_pButton3;
	QPushButton * m_pButton4;
	QPushButton * m_pButton5;
	QPushButton * m_pButton6;
	QPushButton * m_pButton7;
	QPushButton * m_pButton8;
	QPushButton * m_pButton9;
	QPushButton * m_pButton0;
	QPushButton * m_pButtonC;
	QPushButton * m_pButtonCE;
	QPushButton * m_pButtonDelete;
	QPushButton * m_pButtonPoint;
	QPushButton * m_pButtonAdd;
	QPushButton * m_pButtonSub;
	QPushButton * m_pButtonMultiplication;
	QPushButton * m_pButtonDivision;
	QPushButton * m_pButtonEqual;
	QPushButton * m_pButtonStrong;
	QPushButton * m_pButtonPower2;
	QPushButton * m_pButtonPowerY;

public:
	MainWindow();
	
	void AddItemToStringList();
	QStringList vTab;
	bool bPoint;
	bool bSigns;
	long double tmpWynik;
	QString wynikString;
	double wynik;

	public slots:

	void Button1Slot();
	void Button2Slot();
	void Button3Slot();
	void Button4Slot();
	void Button5Slot();
	void Button6Slot();
	void Button7Slot();
	void Button8Slot();
	void Button9Slot();
	void Button0Slot();
	void ButtonCSlot();
	void ButtonCESlot();
	void ButtonPointSlot();
	void ButtonDeleteSlot();
	void ButtonAddSlot();
	void ButtonSubSlot();
	void ButtonMultiplicationSlot();
	void ButtonDivisionSlot();
	void ButtonEqualSlot();
	void ButtonStrongSlot();
	void ButtonPower2Slot();
	void ButtonPowerYSlot();
};

#endif // MAINWINDOW_H
