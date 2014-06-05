#include "../headers/add_physical_component_helper_dialog.h"
#include <QListView>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QtSql>

AddPhysicalComponentHelperDialog::AddPhysicalComponentHelperDialog(QWidget* parent) : QDialog(parent)
{
	QHBoxLayout* mainlayout = new QHBoxLayout(this);
	//create dialog widgets
	physicalComponentsList = new QListView;
	QDialogButtonBox* physicalComponentHelperDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	physicalComponentHelperDialogButtonBox->setOrientation(Qt::Vertical);
 
	QSqlQueryModel* physicalComponentListQueryModel = new QSqlQueryModel();
	physicalComponentListQueryModel->setQuery("SELECT name FROM PhysicalTechnologiesComponents");
	physicalComponentsList->setSelectionMode(QAbstractItemView::MultiSelection);
	physicalComponentsList->setSelectionBehavior(QAbstractItemView::SelectRows);
	physicalComponentsList->setModel(physicalComponentListQueryModel);
	
	mainlayout->addWidget(physicalComponentsList);
	mainlayout->addStretch();
	mainlayout->addWidget(physicalComponentHelperDialogButtonBox);

	connect(physicalComponentHelperDialogButtonBox, SIGNAL(accepted()),
			this, SLOT(accept()));
	connect(physicalComponentHelperDialogButtonBox, SIGNAL(rejected()),
			this, SLOT(reject()));
}
