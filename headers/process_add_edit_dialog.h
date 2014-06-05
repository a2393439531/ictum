#ifndef PROCESS_ADD_EDIT_DIALOG_H 
#define PROCESS_ADD_EDIT_DIALOG_H

#include <QDialog>

class QLineEdit;
class QTextEdit;
class QComboBox;

class ProcessAddEditDialog : public QDialog
{
 public:
	ProcessAddEditDialog(QWidget* parent = 0);
	//getters
	const QString name() const;
	const QString objective() const;
	const QString description() const;
	
	//setters
	void setName(const QString&);
	void setObjective(const QString&);
	void setDescription (const QString&);

 private:
	QLineEdit* nameEdit;
	QLineEdit* objectiveEdit;
	QTextEdit* descriptionTextEdit;
};
#endif
