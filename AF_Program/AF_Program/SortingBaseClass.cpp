#include "SortingBaseClass.h"

SortingBaseClass::SortingBaseClass(QWidget *Parent) : TabClass(Parent)
{
	Name = "Sorting";
	LeftWidget = new SortingLeftTitleUi(ThisTab->ui.LeftTitleWidget);
	RightWidget = new SortingRightTitleUi(ThisTab->ui.RightTitleWidget);

	ThisTab->ui.LeftTitleWidget->setLayout(LeftWidget->ui.horizontalLayout);
	ThisTab->ui.RightTitleWidget->setLayout(RightWidget->ui.horizontalLayout);

	connect(LeftWidget->ui.SizeSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &SortingBaseClass::SizeSpinboxChanged);
	connect(LeftWidget->ui.ShuffleBtn, &QPushButton::clicked, this, &SortingBaseClass::ShuffleBtnClicked);

	ThisTab->ui.AlgoComboBox->addItem("Testing");
	ThisTab->ui.AlgoComboBox->addItem("Testing2");
}

SortingBaseClass::~SortingBaseClass()
{
	LeftWidget->close();
	delete LeftWidget;
}

void SortingBaseClass::PrimaryBtnClicked()
{

}

void SortingBaseClass::SecondaryBtnClicked()
{

}

void SortingBaseClass::AlgoComboBoxChanged(int index)
{

}

void SortingBaseClass::SizeSpinboxChanged(int value)
{
	Size = value;
}

void SortingBaseClass::ShuffleBtnClicked()
{
	int x = 1;
}