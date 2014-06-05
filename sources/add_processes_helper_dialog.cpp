#include "../headers/add_processes_helper_dialog.h"
#include <QListView>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QtSql>

AddProcessesHelperDialog::AddProcessesHelperDialog(QWidget* parent) : QDialog(parent)
{
	QHBoxLayout* mainlayout = new QHBoxLayout(this);
	//create dialog widgets
	processList = new QListView;
	QDialogButtonBox* processeshelperDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	processeshelperDialogButtonBox->setOrientation(Qt::Vertical);
 
	QSqlQueryModel* processListQueryModel = new QSqlQueryModel();
	processListQueryModel->setQuery("SELECT name FROM Processes");
	processList->setSelectionMode(QAbstractItemView::MultiSelection);
	processList->setSelectionBehavior(QAbstractItemView::SelectRows);
	processList->setModel(processListQueryModel);
	
	mainlayout->addWidget(processList);
	mainlayout->addStretch();
	mainlayout->addWidget(processeshelperDialogButtonBox);

	connect(processeshelperDialogButtonBox, SIGNAL(accepted()),
			this, SLOT(accept()));
	connect(processeshelperDialogButtonBox, SIGNAL(rejected()),
			this, SLOT(reject()));
}
