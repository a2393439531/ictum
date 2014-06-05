#ifndef ACTOR_ADD_EDIT_DIALOG_H
#define ACTOR_ADD_EDIT_DIALOG_H

#include <QDialog>

class QLineEdit;
class QComboBox;

class ActorAddEditDialog : public QDialog
{
 Q_OBJECT
 public:
	ActorAddEditDialog (QWidget* parent=0);
	
	//getters functions
	const QString name() const;
	const QString middleName() const;
	const QString lastName() const;
	const QString role() const;
	const QString ou() const;

	//setters functions
	void setName(const QString&);
	void setMiddleName(const QString&);
	void setLastName(const QString&);
	void setRole(const QString&);
	void setOu(const QString&);
	
	private:
	QLineEdit* nameEdit;
	QLineEdit* middleNameEdit;
	QLineEdit* lastNameEdit;
	QComboBox* roleComboBox;
	QComboBox* ouComboBox;
};
#endif
