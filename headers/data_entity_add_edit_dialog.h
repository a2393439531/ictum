#ifndef DATA_ENTITY_ADD_EDIT_DIALOG_H
#define DATA_ENTITY_ADD_EDIT_DIALOG_H

#include <QDialog>

class QLineEdit;
class QTextEdit;
class QComboBox;
class QListView;

class DataEntityAddEditDialog : public QDialog
{
 
 Q_OBJECT

 public:
	DataEntityAddEditDialog(QWidget* parent = 0);

	//getters
	const QString name() const;
	const QString description() const;
	const QString processedBy() const;

	//setters
	void setName(const QString& aName);
	void setDescription(const QString& aDescription);

 private:
	QLineEdit* nameEdit;
	QTextEdit* descriptionTextEdit;
	QComboBox* processedByComboBox;
};
#endif
