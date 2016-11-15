#include "MainWindow.h"
#include "Liczby.h"
#include <iomanip>      // std::setprecision

MainWindow::MainWindow()
{
	bPoint = true;
	bSigns = true;
	QWidget * pMainWidget = new QWidget(this);

	QVBoxLayout *pVBoxLayout = new QVBoxLayout(pMainWidget);
		QHBoxLayout *pHBoxLayout = new QHBoxLayout();
		QHBoxLayout *pHBoxLayout2 = new QHBoxLayout();
		QHBoxLayout *pHBoxLayout3 = new QHBoxLayout();
		QHBoxLayout *pHBoxLayout4 = new QHBoxLayout();
		QHBoxLayout *pHBoxLayout5 = new QHBoxLayout();
		QHBoxLayout *pHBoxLayout6 = new QHBoxLayout();
		QHBoxLayout *pHBoxLayout7 = new QHBoxLayout();

		m_pTextEdit = new QTextEdit();
		pHBoxLayout->addWidget(m_pTextEdit);

		m_pButtonStrong = new QPushButton("!");
		pHBoxLayout2->addWidget(m_pButtonStrong);

		m_pButtonPower2 = new QPushButton("x^2");
		pHBoxLayout2->addWidget(m_pButtonPower2);

		m_pButtonPowerY = new QPushButton("x^y");
		pHBoxLayout2->addWidget(m_pButtonPowerY);

		m_pButtonCE = new QPushButton("CE");
		pHBoxLayout3->addWidget(m_pButtonCE);

		m_pButtonC = new QPushButton("C");
		pHBoxLayout3->addWidget(m_pButtonC);

		m_pButtonDelete = new QPushButton("del");
		pHBoxLayout3->addWidget(m_pButtonDelete);

		m_pButtonDivision = new QPushButton("/");
		pHBoxLayout3->addWidget(m_pButtonDivision);

		m_pButton7 = new QPushButton("7");
		pHBoxLayout4->addWidget(m_pButton7);

		m_pButton8 = new QPushButton("8");
		pHBoxLayout4->addWidget(m_pButton8);

		m_pButton9 = new QPushButton("9");
		pHBoxLayout4->addWidget(m_pButton9);

		m_pButtonMultiplication = new QPushButton("x");
		pHBoxLayout4->addWidget(m_pButtonMultiplication);

		m_pButton4 = new QPushButton("4");
		pHBoxLayout5->addWidget(m_pButton4);

		m_pButton5 = new QPushButton("5");
		pHBoxLayout5->addWidget(m_pButton5);

		m_pButton6 = new QPushButton("6");
		pHBoxLayout5->addWidget(m_pButton6);

		m_pButtonSub = new QPushButton("-");
		pHBoxLayout5->addWidget(m_pButtonSub);

		m_pButton1 = new QPushButton("1");
		pHBoxLayout6->addWidget(m_pButton1);

		m_pButton2 = new QPushButton("2");
		pHBoxLayout6->addWidget(m_pButton2);

		m_pButton3 = new QPushButton("3");
		pHBoxLayout6->addWidget(m_pButton3);

		m_pButtonAdd = new QPushButton("+");
		pHBoxLayout6->addWidget(m_pButtonAdd);

		m_pButton0 = new QPushButton("0");
		pHBoxLayout7->addWidget(m_pButton0);

		m_pButtonPoint = new QPushButton(",");
		pHBoxLayout7->addWidget(m_pButtonPoint);

		m_pButtonEqual = new QPushButton("=");
		pHBoxLayout7->addWidget(m_pButtonEqual);

		pVBoxLayout->addLayout(pHBoxLayout);
		pVBoxLayout->addLayout(pHBoxLayout2);
		pVBoxLayout->addLayout(pHBoxLayout3);
		pVBoxLayout->addLayout(pHBoxLayout4);
		pVBoxLayout->addLayout(pHBoxLayout5);
		pVBoxLayout->addLayout(pHBoxLayout6);
		pVBoxLayout->addLayout(pHBoxLayout7);

		connect(m_pButton1, SIGNAL(clicked()), this, SLOT(Button1Slot()));
		connect(m_pButton2, SIGNAL(clicked()), this, SLOT(Button2Slot()));
		connect(m_pButton3, SIGNAL(clicked()), this, SLOT(Button3Slot()));
		connect(m_pButton4, SIGNAL(clicked()), this, SLOT(Button4Slot()));
		connect(m_pButton5, SIGNAL(clicked()), this, SLOT(Button5Slot()));
		connect(m_pButton6, SIGNAL(clicked()), this, SLOT(Button6Slot()));
		connect(m_pButton7, SIGNAL(clicked()), this, SLOT(Button7Slot()));
		connect(m_pButton8, SIGNAL(clicked()), this, SLOT(Button8Slot()));
		connect(m_pButton9, SIGNAL(clicked()), this, SLOT(Button9Slot()));
		connect(m_pButton0, SIGNAL(clicked()), this, SLOT(Button0Slot()));
		connect(m_pButtonC, SIGNAL(clicked()), this, SLOT(ButtonCSlot()));
		connect(m_pButtonCE, SIGNAL(clicked()), this, SLOT(ButtonCESlot()));
		connect(m_pButtonPoint, SIGNAL(clicked()), this, SLOT(ButtonPointSlot()));
		connect(m_pButtonDelete, SIGNAL(clicked()), this, SLOT(ButtonDeleteSlot()));
		connect(m_pButtonAdd, SIGNAL(clicked()), this, SLOT(ButtonAddSlot()));
		connect(m_pButtonSub, SIGNAL(clicked()), this, SLOT(ButtonSubSlot()));
		connect(m_pButtonMultiplication, SIGNAL(clicked()), this, SLOT(ButtonMultiplicationSlot()));
		connect(m_pButtonDivision, SIGNAL(clicked()), this, SLOT(ButtonDivisionSlot()));
		connect(m_pButtonEqual, SIGNAL(clicked()), this, SLOT(ButtonEqualSlot()));
		connect(m_pButtonPower2, SIGNAL(clicked()), this, SLOT(ButtonPower2Slot()));
		connect(m_pButtonPowerY, SIGNAL(clicked()), this, SLOT(ButtonPowerYSlot()));
		connect(m_pButtonStrong, SIGNAL(clicked()), this, SLOT(ButtonStrongSlot()));

		setCentralWidget(pMainWidget);
}

void MainWindow::AddItemToStringList()
{
	vTab.clear();
	QString sTmp = m_pTextEdit->toPlainText();
	QString sTmpLiczba;
	for (int i = 0; i < sTmp.length(); i++)
	{
		if (sTmp[i] >= '0' && sTmp[i] <= '9')
		{
			sTmpLiczba += sTmp[i];
		}
		if (sTmp[i] == '.')
		{
			sTmpLiczba+= sTmp[i];
		}
		if (sTmp[i] == '^')
		{
			vTab.push_back(sTmpLiczba);
			vTab.push_back("^");
			sTmpLiczba.clear();
		}
		if (sTmp[i] == '*')
		{
			vTab.push_back(sTmpLiczba);
			vTab.push_back("*");
			sTmpLiczba.clear();
		}
		if (sTmp[i] == '/')
		{
			vTab.push_back(sTmpLiczba);
			vTab.push_back("/");
			sTmpLiczba.clear();
		}
		if (sTmp[i] == '+')
		{
			vTab.push_back(sTmpLiczba);
			vTab.push_back("+");
			sTmpLiczba.clear();
		}
		if (sTmp[i] == '-')
		{
			vTab.push_back(sTmpLiczba);
			vTab.push_back("-");
			sTmpLiczba.clear();
		}
	}
	vTab.push_back(sTmpLiczba);
}
void MainWindow::Button1Slot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "1");
	bSigns = true;
}

void MainWindow::Button2Slot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "2");
	bSigns = true;
}

void MainWindow::Button3Slot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "3");
	bSigns = true;
}

void MainWindow::Button4Slot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "4");
	bSigns = true;
}

void MainWindow::Button5Slot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "5");
	bSigns = true;
}

void MainWindow::Button6Slot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "6");
	bSigns = true;
}

void MainWindow::Button7Slot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "7");
	bSigns = true;
}

void MainWindow::Button8Slot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "8");
	bSigns = true;
}

void MainWindow::Button9Slot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "9");
	bSigns = true;
}

void MainWindow::Button0Slot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "0");
	bSigns = true;
}

void MainWindow::ButtonCSlot()
{
	m_pTextEdit->clear();
	vTab.clear();
	bPoint = true;
	bSigns = false;
}

void MainWindow::ButtonPointSlot()
{
	if (bPoint)
	{
		m_pTextEdit->setText(m_pTextEdit->toPlainText() + ".");
		bPoint = false;
	}
}

void MainWindow::ButtonAddSlot()
{
	if(bSigns)
	{
		m_pTextEdit->setText(m_pTextEdit->toPlainText() + "+");
		bSigns = false;
	}
	bPoint = true;
}

void MainWindow::ButtonSubSlot()
{
	if(bSigns)
	{
		m_pTextEdit->setText(m_pTextEdit->toPlainText() + "-");
		bSigns = false;
	}
	bPoint = true;
}

void MainWindow::ButtonMultiplicationSlot()
{
	if(bSigns)
	{
		m_pTextEdit->setText(m_pTextEdit->toPlainText() + "*");
		bSigns = false;
	}
	bPoint = true;
}

void MainWindow::ButtonDivisionSlot()
{
	if(bSigns)
	{
		m_pTextEdit->setText(m_pTextEdit->toPlainText() + "/");
		bSigns = false;
	}
	bPoint = true;
}

void MainWindow::ButtonDeleteSlot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText().mid(0, m_pTextEdit->toPlainText().size() - 1));
	bSigns = true;
}

void MainWindow::ButtonCESlot()
{
	AddItemToStringList();
	QString sTmp;
	if(vTab.size() > 1)
	{
		if( vTab[vTab.size()-1] >= "0" &&  vTab[vTab.size()-1] <= "9")
		{
			vTab.removeAt(vTab.size()-1);
			vTab.removeAt(vTab.size()-1);
		}
		for(int i=0; i<vTab.size(); i++)
		{
			sTmp += vTab[i];
		}
	}
	m_pTextEdit->setText(sTmp);
	bSigns = false;
}

void MainWindow::ButtonEqualSlot()
{
	AddItemToStringList();
	QString sWyr;

	wynik = 0;
	while (vTab.size() != 1)
	{
		bool bFound = false;
		for (int i = 0; i < vTab.size(); i++)
		{
			sWyr = vTab[i];
			if (sWyr.contains("^"))
			{
				Liczby l1(vTab[i - 1]);
				l1.DebugToConsole();
				int nLiczba1 = vTab[i - 1].toInt();

				Liczby l2(1);
				l2.DebugToConsole();
				int tmp = vTab[i + 1].toInt();

				while (tmp--)
				{
					l2 = l2 * l1;
				}

				vTab[i] = l2.ToString();
				vTab.removeAt(i + 1);
				vTab.removeAt(i - 1);
				bFound = true;
				break;
			}
			if ( sWyr.contains("*") )
			{
				Liczby l1(vTab[i-1]);
				l1.DebugToConsole();

				Liczby l2(vTab[i+1]);
				l2.DebugToConsole();

				l1 = l1 * l2;
				l1.DebugToConsole();

				vTab[i] = l1.ToString();
				vTab.removeAt(i+1);
				vTab.removeAt(i-1);
				bFound = true;
				break;
			}
			else if (sWyr.contains("/"))
			{
				Liczby l1(vTab[i - 1]);
				l1.DebugToConsole();

				Liczby l2(vTab[i + 1]);
				l2.DebugToConsole();

				l1 = l1 / l2;
				l1.DebugToConsole();

				vTab[i] = l1.ToString();
				vTab.removeAt(i+1);
				vTab.removeAt(i-1);
				bFound = true;
				break;
			}
		}
		if( bFound )
			continue;

		for (int i = 0; i < vTab.size(); i++)
		{
			sWyr = vTab[i];
			if (sWyr.contains("+"))
			{
				Liczby l1(vTab[i - 1]);
				l1.DebugToConsole();

				Liczby l2(vTab[i + 1]);
				l2.DebugToConsole();

				l1 = l1 + l2;
				l1.DebugToConsole();

				vTab[i] = l1.ToString();
				vTab.removeAt(i+1);
				vTab.removeAt(i-1);
				break;
			}
			else if (sWyr.contains("-"))
			{
				Liczby l1(vTab[i - 1]);
				l1.DebugToConsole();

				Liczby l2(vTab[i + 1]);
				l2.DebugToConsole();

				l1 = l1 - l2;
				l1.DebugToConsole();

				vTab[i] = l1.ToString();
				vTab.removeAt(i+1);
				vTab.removeAt(i-1);
				break;
			}
		}
	}

	Liczby wyn(vTab[0]);
	m_pTextEdit->setText( wyn.ToString() );
	bSigns = true;
}

void MainWindow::ButtonPower2Slot()
{
	Liczby l(QString::number(m_pTextEdit->toPlainText().toInt()));
	m_pTextEdit->setText(l.Potega().ToString());
}

void MainWindow::ButtonPowerYSlot()
{
	m_pTextEdit->setText(m_pTextEdit->toPlainText() + "^");
	bSigns = true;
}

void MainWindow::ButtonStrongSlot()
{
	Liczby l(m_pTextEdit->toPlainText().toInt());
	m_pTextEdit->setText(l.Silnia().ToString());
}
