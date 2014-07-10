#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QWidget>

class QVBoxLayout;
class QPushButton;

class Navigation : public QWidget 
{
	Q_OBJECT

    public:
	    Navigation (QWidget* parent = 0);
	
	private slots:
		void showRolesInfo();
		void showOUInfo();
		void showDataEntityInfo();
        void showPhysicalTechComponentInfo();
        void showInformationSystemService();
    private:
		QVBoxLayout* mainlayout;
        void deleteScreenWidgets();
};
#endif
