#include "TextWidget.h"

TextWidget::TextWidget(std::vector<std::string>* TextFile) : QWidget(nullptr)
{
	ui.setupUi(this);

	Editor = new QTextEdit(this);
	Editor->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
	Editor->setText(QStringConversion(TextFile));
	ui.scrollArea->setWidget(Editor);
}

QString TextWidget::QStringConversion(std::vector<std::string>* TextFile)
{
	QString output;
	for (int i = 0; i < TextFile->size(); i++)
	{
		output += QString::fromStdString(TextFile->at(i)) + "\n";
	}
	delete TextFile;
	return output;
}

TextWidget::~TextWidget()
{

}

void TextWidget::Delete()
{
	qDebug() << "in slot";
	this->deleteLater();
}
