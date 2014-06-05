#ifndef INFORMATION_SYSTEM_SERVICE_ADD_EDIT_DIALOG_H
#define INFORMATION_SYSTEM_SERVICE_ADD_EDIT_DIALOG_H

#include <QDialog>

class QLineEdit;
class QTextEdit;
class QComboBox;

class InformationSystemServiceAddEditDialog : public QDialog
{
 public:
	InformationSystemServiceAddEditDialog(QWidget* parent = 0);
	
	//getters
	const QString name() const;
	const QString description() const;
	const QString physicalTechnologyComponent() const;

	//setters
	void setName(const QString&);
	void setDescription(const QString&);

 private:
	QLineEdit* nameEdit;
	QTextEdit* descriptionTextEdit;
	QComboBox* physicalTechCompComboBox;
};
#endif
