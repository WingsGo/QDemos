#include "vscrolllabel.h"
#include "vscrolllabelplugin.h"

#include <QtPlugin>

VScrollLabelPlugin::VScrollLabelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void VScrollLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool VScrollLabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *VScrollLabelPlugin::createWidget(QWidget *parent)
{
    return new VScrollLabel(parent);
}

QString VScrollLabelPlugin::name() const
{
    return QLatin1String("VScrollLabel");
}

QString VScrollLabelPlugin::group() const
{
    return QLatin1String("");
}

QIcon VScrollLabelPlugin::icon() const
{
    return QIcon();
}

QString VScrollLabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString VScrollLabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool VScrollLabelPlugin::isContainer() const
{
    return false;
}

QString VScrollLabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"VScrollLabel\" name=\"vScrollLabel\">\n</widget>\n");
}

QString VScrollLabelPlugin::includeFile() const
{
    return QLatin1String("vscrolllabel.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(vscrolllabelplugin, VScrollLabelPlugin)
#endif // QT_VERSION < 0x050000
