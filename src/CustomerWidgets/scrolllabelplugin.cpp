#include "scrolllabel.h"
#include "scrolllabelplugin.h"

#include <QtPlugin>

ScrollLabelPlugin::ScrollLabelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ScrollLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ScrollLabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ScrollLabelPlugin::createWidget(QWidget *parent)
{
    return new ScrollLabel(parent);
}

QString ScrollLabelPlugin::name() const
{
    return QLatin1String("ScrollLabel");
}

QString ScrollLabelPlugin::group() const
{
    return QLatin1String("");
}

QIcon ScrollLabelPlugin::icon() const
{
    return QIcon();
}

QString ScrollLabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ScrollLabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ScrollLabelPlugin::isContainer() const
{
    return false;
}

QString ScrollLabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ScrollLabel\" name=\"scrollLabel\">\n</widget>\n");
}

QString ScrollLabelPlugin::includeFile() const
{
    return QLatin1String("scrolllabel.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(scrolllabelplugin, ScrollLabelPlugin)
#endif // QT_VERSION < 0x050000
