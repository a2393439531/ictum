#ifndef ROLE_ADD_EDIT_DIALOG_H
#define ROLE_ADD_EDIT_DIALOG_H

#include <QDialog>

class QLineEdit;
class QTextEdit;

class RoleAddEditDialog : public QDialog
{
 public:
	RoleAddEditDialog(QWidget* parent=0);
	
	//getters
	const QString name() const;
	const QString objective() const;
	const QString tasks() const;

	//setters
	void setName(const QString&);
	void setObjective(const QString&);
	void setTasks(const QString&);
	
 private:
	QLineEdit* nameEdit;
	QLineEdit* objectiveEdit;
	QTextEdit* tasksTextEdit;
};
#endif
