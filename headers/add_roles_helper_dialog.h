#ifndef ADD_ROLES_HELPER_DIALOG_H
#define ADD_ROLES_HELPER_DIALOG_H

#include <QDialog>

class QListView;

class AddRolesHelperDialog : public QDialog
{
 public:
	AddRolesHelperDialog(QWidget* parent = 0);
	QListView* rolesList;
};
#endif
