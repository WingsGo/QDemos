#ifndef VSCROLLLABEL_H
#define VSCROLLLABEL_H

#include <QLabel>
#include <QTimer>
#include <QTimerEvent>
#include <QPainter>
#include <QDebug>
#include <QtDesigner/QDesignerExportWidget>

/**************** 自定义插件使用注意事项 ********************************
 **************** https://www.cnblogs.com/georgeOfChina/p/7773141.html*/

class QDESIGNER_WIDGET_EXPORT VScrollLabel : public QLabel
{
    Q_OBJECT
public:
    explicit VScrollLabel(QWidget *parent = 0);
    virtual ~VScrollLabel();

    void setScrollSpeed(int speed);

protected:

public Q_SLOTS:
    void setText(const QString &curText);

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    void updateRollingState();

private:
    int m_iScrollPixel;
    int m_iScrollSpeed;
    int m_iTopMargin;
    int m_iLeftMargin;
    int m_iTimerId;
    const QString m_cTextMargin;
};

#endif // VSCROLLLABEL_H
