#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class CBookmarkFilterDataModel;
class CBookmarkFilter;
class CManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Quit_triggered();

    void on_action_Save_triggered();

private:
    Ui::MainWindow *ui;
    CBookmarkFilterDataModel *dataModel;
    CBookmarkFilter *filter;
    CManager *mgr;
};

#endif // MAINWINDOW_H
