#include "TabTemplateClass.h"



TabTemplateClass::TabTemplateClass(QObject *parent)
	: QObject(parent)
{
	Timer1 = new QTimer(this);
	Timer2 = new QTimer(this);
}

TabTemplateClass::~TabTemplateClass()
{
	delete Timer1;
	delete Timer2;
}