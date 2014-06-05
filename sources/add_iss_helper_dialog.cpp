#include "../headers/add_iss_helper_dialog.h"
#include <QListView>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QtSql>

AddISSHelperDialog::AddISSHelperDialog(QWidget* parent) : QDialog(parent)
{
	QHBoxLayout* mainlayout = new QHBoxLayout(this);
	//create dialog widgets
	iSSList = new QListView;
	QDialogButtonBox* iSShelperDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	iSShelperDialogButtonBox->setOrientation(Qt::Vertical);
 
	QSqlQueryModel* iSSListQueryModel = new QSqlQueryModel();
	iSSListQueryModel->setQuery("SELECT name FROM InformationSystemServices");
	iSSList->setSelectionMode(QAbstractItemView::MultiSelection);
	iSSList->setSelectionBehavior(QAbstractItemView::SelectRows);
	iSSList->setModel(iSSListQueryModel);
	
	mainlayout->addWidget(iSSList);
	mainlayout->addStretch();
	mainlayout->addWidget(iSShelperDialogButtonBox);

	connect(iSShelperDialogButtonBox, SIGNAL(accepted()),
			this, SLOT(accept()));
	connect(iSShelperDialogButtonBox, SIGNAL(rejected()),
			this, SLOT(reject()));
}
