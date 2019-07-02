#include "cflip.h"
#include <QHBoxLayout>

CFlip::CFlip(QWidget *parent)
    : QWidget(parent)
{
    m_iAllPageNum = 100;
    m_iCurPageNo = 1;

    m_oGotoPrePageBtn = new QPushButton(this);
    m_oFirstPageBtn = new QPushButton(this);
    m_oPrePageBtn = new QPushButton(this);
    m_oCurPageBtn = new QPushButton(this);
    m_oNextPageBtn = new QPushButton(this);
    m_oLastPageBtn = new QPushButton(this);
    m_oGotoNextPageBtn = new QPushButton(this);


    m_oGotoPrePageBtn->setMinimumSize(56, 23);
    m_oFirstPageBtn->setMinimumSize(33, 23);
    m_oPrePageBtn->setMinimumSize(23, 23);
    m_oCurPageBtn->setMinimumSize(23, 23);
    m_oNextPageBtn->setMinimumSize(23, 23);
    m_oLastPageBtn->setMinimumSize(33, 23);
    m_oGotoNextPageBtn->setMinimumSize(56, 23);


    m_oGotoPrePageBtn->setMaximumSize(56, 23);
    m_oFirstPageBtn->setMaximumSize(33, 23);
    m_oPrePageBtn->setMaximumSize(23, 23);
    m_oCurPageBtn->setMaximumSize(23, 23);
    m_oNextPageBtn->setMaximumSize(23, 23);
    m_oLastPageBtn->setMaximumSize(33, 23);
    m_oGotoNextPageBtn->setMaximumSize(56, 23);



    m_oGotoPrePageBtn->setText(tr("Prev"));
    m_oFirstPageBtn->setText(tr("1..."));
    m_oPrePageBtn->setText(tr("1"));
    m_oCurPageBtn->setText(tr("1"));
    m_oNextPageBtn->setText(tr("1"));
    m_oLastPageBtn->setText(tr("...1"));
    m_oGotoNextPageBtn->setText(tr("Next"));


    QHBoxLayout *pHLayout = new QHBoxLayout();
    pHLayout->setContentsMargins(1, 1, 1, 1);
    pHLayout->addStretch();
    pHLayout->addWidget(m_oGotoPrePageBtn);
    pHLayout->addWidget(m_oFirstPageBtn);
    pHLayout->addWidget(m_oPrePageBtn);
    pHLayout->addWidget(m_oCurPageBtn);
    pHLayout->addWidget(m_oNextPageBtn);
    pHLayout->addWidget(m_oLastPageBtn);
    pHLayout->addWidget(m_oGotoNextPageBtn);
    this->setLayout(pHLayout);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setMaximumSize(295, 23);

    m_oFirstPageBtn->setHidden(true);
    m_oPrePageBtn->setHidden(true);
    m_oNextPageBtn->setHidden(true);
    m_oLastPageBtn->setHidden(true);

    this->setStyleSheet(
        "QPushButton{border:1px solid #D7E2EE; border-radius:4px; background:#F5F5F5; color:#000; margin:1px;}"
        "QPushButton:hover{border:1px solid #C5D3E3}"
        );
    m_oCurPageBtn->setStyleSheet("background: #006699;");


    m_oGotoPrePageBtn->installEventFilter(this);
    m_oFirstPageBtn->installEventFilter(this);
    m_oPrePageBtn->installEventFilter(this);
    m_oCurPageBtn->installEventFilter(this);
    m_oNextPageBtn->installEventFilter(this);
    m_oLastPageBtn->installEventFilter(this);
    m_oGotoNextPageBtn->installEventFilter(this);


    connect(m_oGotoPrePageBtn, SIGNAL(clicked()), this, SLOT(slot_GotoPrePageBtn_clicked()));
    connect(m_oFirstPageBtn, SIGNAL(clicked()), this, SLOT(slot_FirstPageBtn_clicked()));
    connect(m_oPrePageBtn, SIGNAL(clicked()), this, SLOT(slot_PrePageBtn_clicked()));
    connect(m_oCurPageBtn, SIGNAL(clicked()), this, SLOT(slot_CurPageBtn_clicked()));
    connect(m_oNextPageBtn, SIGNAL(clicked()), this, SLOT(slot_NextPageBtn_clicked()));
    connect(m_oLastPageBtn, SIGNAL(clicked()), this, SLOT(slot_LastPageBtn_clicked()));
    connect(m_oGotoNextPageBtn, SIGNAL(clicked()), this, SLOT(slot_GotoNextPageBtn_clicked()));


}

CFlip::~CFlip()
{

}

int
CFlip::m_iSetPageInfo(int iAllPageNum, int iCurPageNo)
{
    if(iAllPageNum <= 0 || iCurPageNo <= 0 || iAllPageNum<iCurPageNo)
    {
        return -1;
    }

    m_iAllPageNum = iAllPageNum;
    m_iCurPageNo = iCurPageNo;

    m_oGotoPrePageBtn->setHidden(false);
    m_oFirstPageBtn->setHidden(false);
    m_oPrePageBtn->setHidden(false);
    m_oCurPageBtn->setHidden(false);
    m_oNextPageBtn->setHidden(false);
    m_oLastPageBtn->setHidden(false);
    m_oGotoNextPageBtn->setHidden(false);


    m_oCurPageBtn->setText(QString::number(iCurPageNo, 10));
    if(iCurPageNo==1)
    {
        m_oFirstPageBtn->setHidden(true);
        m_oPrePageBtn->setHidden(true);
    }
    else if(iCurPageNo==2)
    {
        m_oFirstPageBtn->setHidden(true);
        m_oPrePageBtn->setText(tr("1"));
    }
    else
    {
        m_oFirstPageBtn->setText(tr("1..."));
        m_oPrePageBtn->setText(QString::number(iCurPageNo-1, 10));
    }

    if(iCurPageNo == iAllPageNum)
    {
        m_oNextPageBtn->setHidden(true);
        m_oLastPageBtn->setHidden(true);
    }
    else if(iCurPageNo+1 == iAllPageNum)
    {
        m_oLastPageBtn->setHidden(true);
        m_oNextPageBtn->setText(QString::number(iCurPageNo+1, 10));
    }
    else
    {
        m_oNextPageBtn->setText(QString::number(iCurPageNo+1, 10));
        m_oLastPageBtn->setText(tr("...")+QString::number(m_iAllPageNum, 10));
    }
    return 0;
}


void
CFlip::slot_GotoPrePageBtn_clicked()
{
    if(m_iSetPageInfo(m_iAllPageNum, m_iCurPageNo-1) == 0)
    {
        emit sigPageChanged(m_iCurPageNo);
    }
}

void
CFlip::slot_FirstPageBtn_clicked()
{
    if(m_iSetPageInfo(m_iAllPageNum, 1) == 0)
    {
        emit sigPageChanged(m_iCurPageNo);
    }
}

void
CFlip::slot_PrePageBtn_clicked()
{
    if(m_iSetPageInfo(m_iAllPageNum, m_iCurPageNo-1) == 0)
    {
        emit sigPageChanged(m_iCurPageNo);
    }
}

void
CFlip::slot_CurPageBtn_clicked()
{
    return;
}

void
CFlip::slot_NextPageBtn_clicked()
{
    if(m_iSetPageInfo(m_iAllPageNum, m_iCurPageNo+1) == 0)
    {
        emit sigPageChanged(m_iCurPageNo);
    }
}

void
CFlip::slot_LastPageBtn_clicked()
{
    if(m_iSetPageInfo(m_iAllPageNum, m_iAllPageNum) == 0)
    {
        emit sigPageChanged(m_iCurPageNo);
    }
}

void
CFlip::slot_GotoNextPageBtn_clicked()
{
    if(m_iSetPageInfo(m_iAllPageNum, m_iCurPageNo+1) == 0)
    {
        emit sigPageChanged(m_iCurPageNo);
    }
}

bool
CFlip::eventFilter(QObject *obj, QEvent *event)
{
    QPushButton *pBtn = qobject_cast<QPushButton*>(obj);
    if( (m_oGotoPrePageBtn == pBtn) ||
        (m_oFirstPageBtn == pBtn) ||
        (m_oPrePageBtn == pBtn) ||
        (m_oCurPageBtn == pBtn) ||
        (m_oNextPageBtn == pBtn) ||
        (m_oLastPageBtn == pBtn) ||
        (m_oGotoNextPageBtn == pBtn) )
    {
        if(event->type() == QEvent::Enter)
        {
            setCursor(Qt::PointingHandCursor);
        }
    }
    return QObject::eventFilter(obj, event);
}
