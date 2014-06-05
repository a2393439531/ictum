#ifndef ADD_PROCESSES_HELPER_DIALOG_H
#define ADD_PROCESSES_HELPER_DIALOG_H

#include <QDialog>

class QListView;

class AddProcessesHelperDialog : public QDialog
{
 public:
	AddProcessesHelperDialog(QWidget* parent = 0);
	QListView* processList;
};
#endif
