#ifndef ADD_ISS_HELPER_DIALOG_H
#define ADD_ISS_HELPER_DIALOG_H

#include <QDialog>

class QListView;

class AddISSHelperDialog : public QDialog
{
 public:
	AddISSHelperDialog(QWidget* parent = 0);
	QListView* iSSList;
};
#endif
