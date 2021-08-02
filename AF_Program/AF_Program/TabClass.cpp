#include "TabClass.h"

TabClass::TabClass(QWidget* Parent, int i) : QWidget(nullptr)
{
	index = i;
	ParentPTR = Parent;
	ThisTab = new TabUI(this);
	SetConnection();
}

TabClass::~TabClass()
{
	emit Stop();
	WorkerThread.quit(); //Quit through the event loop
	WorkerThread.wait(); //wait for the thread to end
	ThisTab->deleteLater();
}


void TabClass::SetConnection()
{
	connect(ThisTab->ui.PrimaryBtn, &QPushButton::clicked, this, &TabClass::PrimaryBtnClicked);
	connect(ThisTab->ui.SecondaryBtn, &QPushButton::clicked, this, &TabClass::SecondaryBtnClicked);	
	connect(ThisTab->ui.AlgoComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &TabClass::AlgoComboBoxChanged);
	connect(ThisTab->ui.DelaySpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &TabClass::DelaySpinBox);
}

void TabClass::DelaySpinBox(int value)
{
	Delay = value;
}

void TabClass::TabChanged(int i)
{
	if (i == index && !Active)
	{
		Active = true;
		OpenTab();
	}
	else if(i!=index && Active)
	{
		Active = false;
		CloseTab();
	}
}

void TabClass::PrimaryBtnClicked()
{
	switch (ThisState)
	{
	case(TabState::start):
		SetRunningState();
		emit Start();
		break;
	case(TabState::running):
		SetPausedState();
		emit Stop();
		break;
	case(TabState::paused):
		SetRunningState();
		emit Start();
		break;
	case(TabState::ended):
		SetStartState();
		emit Restart();
		break;
	}
}

void TabClass::SecondaryBtnClicked()
{
	SetStartState();
	emit Restart();
}

void TabClass::paintEvent(QPaintEvent* PEvent)
{
	InPaintEvent = true;
	QPainter paint(this);
	QPen Pen(Qt::black);
	QBrush Brush(Qt::white);
	QRect Rect;
	DrawDrawableArea(&paint, &Pen, &Rect);
	CustomPaintEvent(&paint, &Pen, &Brush, &Rect);
	InPaintEvent = false;
}

void TabClass::DrawDrawableArea(QPainter* paint, QPen* Pen, QRect* rect)
{
	Pen->setWidth(3);
	paint->setPen(*Pen);
	QPoint X_Y = ThisTab->ui.MainTabWidget->pos();
	int Width = ThisTab->ui.MainTabWidget->width();
	int Height = ThisTab->ui.MainTabWidget->height();
	*rect = QRect(X_Y.x(), X_Y.y(), Width, Height);
	paint->drawRect(*rect);
	Pen->setWidth(1);
}

void TabClass::Finished()
{
	SetEndState();
}

void TabClass::SetStartState()
{
	ThisState = TabState::start;
	ThisTab->ui.AlgoComboBox->setEnabled(true);
	ThisTab->ui.TimerLab->setText("0");
	ThisTab->ui.PrimaryBtn->setText("Start");
}

void TabClass::SetRunningState()
{
	ThisState = TabState::running;
	ThisTab->ui.AlgoComboBox->setEnabled(false);
	ThisTab->ui.PrimaryBtn->setText("Pause");
}

void TabClass::SetPausedState()
{
	ThisState = TabState::paused;
	ThisTab->ui.PrimaryBtn->setText("Resume");
}

void TabClass::SetEndState()
{
	ThisState = TabState::ended;
	ThisTab->ui.AlgoComboBox->setEnabled(true);
	ThisTab->ui.PrimaryBtn->setText("Restart");
}




