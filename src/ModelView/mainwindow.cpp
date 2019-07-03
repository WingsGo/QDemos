#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pTableModel(new QSqlTableModel)
{
    ui->setupUi(this);
    m_pTableModel->setTable("TestTb");
    m_pTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_pTableModel->select();
    m_pTableModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("编号"));
    m_pTableModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("名称"));
    m_pTableModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("接收数据"));
    m_pTableModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("接收时间"));

    ui->tableView->setModel(m_pTableModel);
    ui->tableView->verticalHeader()->hide();

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::submitChanges);
    connect(ui->delBtn, &QPushButton::clicked, this, &MainWindow::deleteSelections);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (m_pTableModel != nullptr) {
        delete m_pTableModel;
    }
}

void MainWindow::submitChanges()
{
    if (!m_pTableModel->submitAll()) {
        QMessageBox::critical(this, QString::fromLocal8Bit("警告"), m_pTableModel->lastError().text());
    } else {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("提交成功"));
    }
}

void MainWindow::deleteSelections()
{
    QItemSelectionModel* selectModel = ui->tableView->selectionModel();
    QModelIndexList selectIdx = selectModel->selectedIndexes();
    foreach (QModelIndex idx, selectIdx) {
        // m_pTableModel->removeRow(idx.row());
        qDebug() << idx.row();
    }
}
