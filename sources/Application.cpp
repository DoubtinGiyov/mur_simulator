#include "Application.h"
#include "QUrhoWidget.h"
#include "ApplicationWindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QDirIterator>
#include <QDebug>

namespace QUrho
{
    int Application::execute(int argc, char **argv)
    {
        QApplication application(argc, argv);
        application.setApplicationName("Simulator");
        
        QScopedPointer<ApplicationWindow> mainWindow{new ApplicationWindow};
        
#ifdef Q_OS_MACOS
        SetupEnvironment();
#endif
        mainWindow->show();
        mainWindow->InitializeEngine();
        
        size_t size = sizeof(Urho3D::VariantMap);
        return QApplication::exec();
    }

    void Application::SetupEnvironment()
    {
        auto path = QDir{QApplication::applicationDirPath()};
        path.cdUp();
        auto contentsDirectory = path.absolutePath();
        auto gstFrameworkDirectory = contentsDirectory + "/Frameworks/GStreamer.framework";
        
        SetEnvironmentVariable("GST_PLUGIN_SYSTEM_PATH",
                               gstFrameworkDirectory + "/Versions/Current/lib/gstreamer-1.0");
        
        SetEnvironmentVariable("GST_PLUGIN_SCANNER",
                               gstFrameworkDirectory + "/Versions/Current/libexec/gstreamer-1.0/gst-plugin-scanner");
        
        SetEnvironmentVariable("GTK_PATH",
                               gstFrameworkDirectory + "/Versions/Current/");
        
        SetEnvironmentVariable("GIO_EXTRA_MODULES",
                               gstFrameworkDirectory + "/Versions/Current/lib/gio/modules");
    }

    void Application::SetEnvironmentVariable(const char* variableName, const QString variableValue)
    {
        if (!qputenv(variableName, variableValue.toUtf8()))
        {
            qWarning() << "Unable to set " << variableName;
        }
    }
}

