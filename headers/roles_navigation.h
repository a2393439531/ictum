#ifndef ROLES_NAVIGATION_H
#define ROLES_NAVIGATION_H

#include <QWidget>

class QPushButton;
class QGridLayout;
class QTableView;
class QListView;
class QTextEdit;
class QLineEdit;
class QPushButton;
class QString;

class RolesNavigation : public QWidget 
{
    Q_OBJECT

    public:
        RolesNavigation(QWidget* parent = 0);

    private slots:
		void rolesEntities(const QModelIndex& index);     // Display informaytion about the roles related entities
		void showRolesEntitiesElementInfo(const QModelIndex& index);  // shows information of a clicked element
        void rolesSearch(const QString& text);           //Enable the search by roles
    private:
        QGridLayout* dataViewLayout;
        QTableView* currentAnalyzedEntityTable; 
        QListView* releatedEntityInformationListView;    
		QListView* relatedEntitiesListView;
		QTextEdit* elementDescriptionTextEdit;
		QTextEdit* descriptionTextEdit;
};
#endif

