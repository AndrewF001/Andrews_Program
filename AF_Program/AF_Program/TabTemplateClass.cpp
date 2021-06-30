#include "TabTemplateClass.h"



TabTemplateClass::TabTemplateClass(QObject *parent)
	: QObject(parent)
{


}

TabTemplateClass::~TabTemplateClass()
{


}

//void TabClass::ChangeRunningState(bool State)
//{
//	Running = State;
//	if (State)
//		ThisTab->ui.PrimaryBtn->setText("Start");
//	else
//		ThisTab->ui.PrimaryBtn->setText("Pause");
//}
//
//bool TabClass::FlipRunningState()
//{
//	ChangeRunningState(!Running);
//	return Running;
//}
//
//bool TabClass::GetRunningState()
//{
//	return Running;
//}