#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QListView;
class QWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
   MainWindow();
   
   private slots:
     void changeCentralWidget(const QModelIndex & index);
     
 private:
     QListView* options;
};
#endif

