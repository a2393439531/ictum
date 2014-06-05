#include "../headers/location_add_edit_dialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>

LocationAddEditDialog::LocationAddEditDialog(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* locationDialogMainLayout = new QVBoxLayout;    // creates the dialog layout
	QGridLayout* inputFieldsLayout = new QGridLayout;
	
	//initializes dialog widgets
	locationTextEdit = new QTextEdit;
	
	QDialogButtonBox* locationDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);

	//add widgets to the grid layout
	inputFieldsLayout->addWidget(new QLabel("Ubicacion"),0,0);
	inputFieldsLayout->addWidget(locationTextEdit,1,0);
	
	locationDialogMainLayout->addLayout(inputFieldsLayout);
	locationDialogMainLayout->addStretch();
	locationDialogMainLayout->addWidget(locationDialogButtonBox);
	this->setLayout(locationDialogMainLayout);

	// signals slots connections
	connect(locationDialogButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(locationDialogButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));
}
const QString LocationAddEditDialog::location() const
{
	return locationTextEdit->toPlainText();
}

void LocationAddEditDialog::setLocation(const QString& aLocation)
{
	locationTextEdit->setPlainText(aLocation);
}
