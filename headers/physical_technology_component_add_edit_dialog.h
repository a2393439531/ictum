#ifndef PHYSICAL_TECHNOLOGY_COMPONEN_ADD_EDIT_DIALOG_H
#define PHYSICAL_TECHNOLOGY_COMPONENT_ADD_EDIT_DIALOG_H

#include<QDialog>

class QLineEdit;
class QComboBox;
class QTextEdit;

class PhysicalTechnologyComponentAddEditDialog : public QDialog
{
 public:
	PhysicalTechnologyComponentAddEditDialog(QWidget* parent = 0);
	
	//getters
	const QString name() const;
	const QString objective() const;
	const QString description() const;
	const QString location() const;

	//setters
	void setName(const QString&);
	void setObjective(const QString&);
	void setDescription(const QString&);
	
 private:
	QLineEdit* nameEdit;
	QLineEdit* objectiveEdit;
	QTextEdit* descriptionTextEdit;
	QComboBox* locationComboBox;
	
};
#endif
