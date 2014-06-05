#ifndef FUNCTION_ADD_EDIT_DIALOG_H
#define FUNCTION_ADD_EDIT_DIALOG_H

#include <QDialog>

class QLineEdit;
class QListView;
class QTextEdit;
class QStandardItemModel;

class FunctionAddEditDialog : public QDialog
{
	Q_OBJECT
		
 public:
	FunctionAddEditDialog(QWidget* parent);
	
	//getters
	const QString name() const;
	const QString description() const;
	const QString usedBy() const;
	
	//setters
	void setName(const QString&);
	void setDescription(const QString&);
	void setUsedBy();
	
	private slots:
		void addRoles();

 private:
		QLineEdit* nameEdit;
		QTextEdit* descriptionTextEdit;
		QListView* usedByListView;
		QStandardItemModel* selectedRolesModel;
	
};
#endif
