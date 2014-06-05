#ifndef ADD_PHYSICAL_COMPONENT_HELPER_DIALOG_H
#define ADD_PHYSICAL_COMPONENT_HELPER_DIALOG_H

#include <QDialog>

class QListView;

class AddPhysicalComponentHelperDialog : public QDialog
{
 public:
	AddPhysicalComponentHelperDialog(QWidget* parent = 0);
	QListView* physicalComponentsList;
};
#endif
