#ifndef OU_ADD_EDIT_DIALOG_H
#define OU_ADD_EDIT_DIALOG_H
#include <QDialog>

class QLineEdit;
class QTextEdit;
class QComboBox;

class OuAddEditDialog : public QDialog
{
 public:
	OuAddEditDialog(QWidget* parent=0);
	//getters
	const QString name() const;
	const QString objective() const;
	const QString location() const;
	const QString tasks() const;

	//setters
	void setName(const QString&);
	void setObjective(const QString&);
	void setLocation(const QString&);
	void setTasks(const QString&);

 private:
	QLineEdit* nameEdit;
	QLineEdit* objectiveEdit;
	QComboBox* locationComboBox;
	QTextEdit* tasksTextEdit;
};
#endif
