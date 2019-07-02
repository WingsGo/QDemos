#ifndef CFLIP_H
#define CFLIP_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QEvent>

class CFlip : public QWidget
{
    Q_OBJECT
public:
    CFlip(QWidget *parent = 0);
    ~CFlip();

    int m_iSetPageInfo(int iAllPageNum, int iCurPageNo);

signals:
    void sigPageChanged(int iPageNo);

public slots:
    void slot_GotoPrePageBtn_clicked();
    void slot_FirstPageBtn_clicked();
    void slot_PrePageBtn_clicked();
    void slot_CurPageBtn_clicked();
    void slot_NextPageBtn_clicked();
    void slot_LastPageBtn_clicked();
    void slot_GotoNextPageBtn_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QPushButton *m_oGotoPrePageBtn;
    QPushButton *m_oFirstPageBtn;
    QPushButton *m_oPrePageBtn;
    QPushButton *m_oCurPageBtn;
    QPushButton *m_oNextPageBtn;
    QPushButton *m_oLastPageBtn;
    QPushButton *m_oGotoNextPageBtn;

    int m_iAllPageNum;
    int m_iCurPageNo;
};

#endif // CFLIP_H
