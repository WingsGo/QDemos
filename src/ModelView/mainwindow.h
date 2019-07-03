#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlError>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void submitChanges();
    void deleteSelections();

private:
    Ui::MainWindow *ui;
    QSqlTableModel* m_pTableModel;
};

#endif // MAINWINDOW_H
