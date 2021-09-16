#pragma once
#include "TabTemplateClass.h"
#include "Static_SGF.h"
Q_DECLARE_METATYPE(std::vector<unsigned int>);   //serilized data for graphics
Q_DECLARE_METATYPE(FPTR);	//custom function pointer

/*
	This will hold all the signal and slots that are required to communicate with SortingBaseClass
	This is inherited by the actual sorting class that does the work.
*/
class SortingTemplateClass : public TabTemplateClass
{
	Q_OBJECT;

public slots:
	void Shuffle(int);
	void FrameRate1();	//Array graphics
	void FrameRate2();	//details graphics

signals:
	void TitlePing(long long Timer, int Comparison, int Swaps);
	void ArrayPing(QVariant arr, QVariant ptr);

public:
	SortingTemplateClass(Menu1*, unsigned int arrsize);
	~SortingTemplateClass();
	int ArrSize();

protected:
	std::vector<unsigned int> Arr;	//actual arr to work on
	std::vector<unsigned int> IntialArr;	//needed for reset button
	int Comparisons = 0, Swaps = 0;	//details about performance
	int Index1=-1, Index2=-1;	//GUI variables
	FPTR GFPTR = &Static_SGF::GraphicsMethod1;	//what graphical function the painting needs to use
	void SwapPos(int, int);
	void RenderMethod();	//Shortcut for sending the signals for GUI
	void TemplateStart();	//tab type specific execution
	void TemplatePause();
	void TemplateReset();
	void TemplateCancle();
	bool ProcessEventLoop();	//Visit parent class
	virtual void AlgorithmMethod()=0;	//the actual method that gets run
	virtual std::vector<unsigned int> SerilizedData();	//this method needs to match up with FPTR


private:
	void Randomize();	//shuffle method
	void ResetArr();	//for the reset button
	void ChangeSize(int);	//can be called at any time so checks need to be made that it's a valid request
	void SendArrayPing();	//Shortcut for sending the signals for GUI
};

