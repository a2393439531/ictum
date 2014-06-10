#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QWidget>
#include <QStack>

class QVBoxLayout;
class QPushButton;
class QGridLayout;
class QTableView;
class QListView;
class QTextEdit;
class QLineEdit;
class QPushButton;
class QString;
//class QStack<QString>;

class Navigation : public QWidget 
{
	Q_OBJECT

    public:
	    Navigation (QWidget* parent = 0);
	
	private slots:
		void showRolesInfo();
		void showOUInfo();
		void oUEntities(const QModelIndex& index);
		void showOUEntitiesElementInfo(const QModelIndex& index);
		void showDataEntityInfo();
		void dataEntities(const QModelIndex& index);
		void showDataEntitiesElementInfo(const QModelIndex& index);
		//void showTechnologiesComponentsInfo();
		//void technologiesComponentsEntities(const QModelIndex& index);
		//void showTechnologiesComponentsEntitiesElementInfo(const QModelIndex& index);
		void entitySearch(const QString& text);
		void goBack();

    private:
        QWidget* startScreen;
		QWidget* screen;
		QVBoxLayout* mainlayout;
		QGridLayout* dataViewLayout;
		QTableView* currentAnalyzedEntityTable;
		QListView* releatedEntityInformationListView;
		QListView* relatedEntitiesListView;
		QTextEdit* elementDescriptionTextEdit;
		QTextEdit* descriptionTextEdit;
		QLineEdit* searchEdit;
		QPushButton* back;
	    //bool isFirstTime = true;
		QString currentScreen;
		QStack<QString> navigationController;
};
#endif
