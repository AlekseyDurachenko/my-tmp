#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
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
protected:
//    virtual void dragEnterEvent(QDragEnterEvent *event);

private:
    Ui::MainWindow *ui;
    CBookmarkFilterDataModel *dataModel;
    CBookmarkFilter *filter;
    CManager *mgr;
};

#endif // MAINWINDOW_H
