#include "TabClass.h"
#include "TabTemplateClass.h"

TabClass::TabClass(QWidget* Parent, const bool P_Debug_option) : QWidget(nullptr), Debug_Option(P_Debug_option)
{
	ParentPTR = Parent;	
	ThisTab = new TabUI(this);	//Tab Object
	Canvas = new CanvasWidget(this);	//Drawing object
	ThisTab->ui.CanvasScrollArea->setWidget(Canvas);

	DebugConstructor();
}

TabClass::~TabClass()
{
	emit Stop();
	WorkerThread.quit(); //Quit through the event loop
	WorkerThread.wait(); //wait for the thread to end
	ThisTab->deleteLater();

	emit CloseTextFiles();
}

void TabClass::DebugConstructor()
{
	if (Debug_Option)
	{
		ThisTab->ui.LowerSplitter->setSizes(QList<int>() << 400 << 100); //4:1 ratio 
	}
	else
	{
		ThisTab->ui.LowerSplitter->setSizes(QList<int>() << 100 << 0); //1:0 ratio
		ThisTab->ui.DebugScrollArea->setVisible(false); //remove Debug Widget
		ThisTab->ui.LowerSplitter->setEnabled(false);	//Make Splitter inactive but visable
	}
}

void TabClass::CallAfterConstructor()
{

	C_CACB();
	SetConnection();
	for (int i = 0; i < NumOfAlgorithms(); i++)
	{
		C_CACL(i);
		Algorithms[i]->moveToThread(&WorkerThread); //move to thread
		connect(this, &TabClass::Cancle, Algorithms[i], &TabTemplateClass::Cancle, Qt::QueuedConnection); //set up deletion signal
	}

	WorkerThread.start(prior); //start thread

	CurrentAlgorithm = Algorithms[0];

	ChangeThreadObj(0); //connect only 1 object to the thread

	update();
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

void TabClass::TextFileBtnClicked()
{
	std::string FilePath = "TextFiles\\"+FileHeader+CurrentAlgorithm->AlgrothimName.toUtf8().constData()+".FFTF";
	std::ifstream TxtFile(FilePath);
	std::vector<std::string>* Lines = new std::vector<std::string>;
	std::string buffer;
	if (TxtFile.is_open())
	{
		while (getline(TxtFile, buffer))
		{
			Lines->push_back(buffer);
		}
		TextWidget* panel = new TextWidget(Lines);
		connect(this, &TabClass::CloseTextFiles, panel, &TextWidget::Delete, Qt::QueuedConnection);
		FileVect.push_back(panel);  //memory leak as the pointer is never removed once the object is deleted 4 bytes per file opened
		panel->show();
	}
	else
	{
		QMessageBox PopupBox(this);
		PopupBox.setIcon(QMessageBox::Critical);
		PopupBox.setText("Algorithm has no text file");
		PopupBox.exec();
	}
}

void TabClass::DebugCheckChanged(int state)
{
	//state 0 == unchecked, 2 == checked, 1 == ???::PartiallyChecked
	switch (state)
	{
	case(0):
		DebugOff();
		break;
	case(2):
		DebugOn();
		break;
	default:
		break;
	}
}

void TabClass::ChangeThreadObj(int index)
{
	emit Stop();
	disconnect(this, &TabClass::Start, CurrentAlgorithm, &TabTemplateClass::Start);
	disconnect(this, &TabClass::Stop, CurrentAlgorithm, &TabTemplateClass::Pause);
	disconnect(this, &TabClass::Restart, CurrentAlgorithm, &TabTemplateClass::Reset);
	disconnect(CurrentAlgorithm, &TabTemplateClass::Finished, this, &TabClass::Finished);
	CustomDisconnect(CurrentAlgorithm);
	//swap algorithm
	CurrentIndex = index;
	CurrentAlgorithm = Algorithms[CurrentIndex];
	//set the new connection
	connect(this, &TabClass::Start, CurrentAlgorithm, &TabTemplateClass::Start, Qt::QueuedConnection);
	connect(this, &TabClass::Stop, CurrentAlgorithm, &TabTemplateClass::Pause, Qt::QueuedConnection);
	connect(this, &TabClass::Restart, CurrentAlgorithm, &TabTemplateClass::Reset, Qt::QueuedConnection);
	connect(CurrentAlgorithm, &TabTemplateClass::Finished, this, &TabClass::Finished, Qt::QueuedConnection);
	CustomConnect(CurrentAlgorithm);
	emit Restart();
}

void TabClass::DebugOff()
{
	ThisTab->ui.LowerSplitter->setSizes(QList<int>() << 100 << 0); 
	ThisTab->ui.DebugScrollArea->setVisible(false);
	ThisTab->ui.LowerSplitter->setEnabled(false);
}

void TabClass::DebugOn()
{
	ThisTab->ui.LowerSplitter->setSizes(QList<int>() << 400 << 100);
	ThisTab->ui.DebugScrollArea->setVisible(true);
	ThisTab->ui.LowerSplitter->setEnabled(true);
}

void TabClass::Finished()
{
	SetEndState();
}

void TabClass::SetStartState()
{
	ThisState = TabState::start;
}

void TabClass::SetRunningState()
{
	ThisState = TabState::running;
}

void TabClass::SetPausedState()
{
	ThisState = TabState::paused;
}

void TabClass::SetEndState()
{
	ThisState = TabState::ended;
}




