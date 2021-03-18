#include "QtOpenGLWidgetsApplication.h"
#include <QtWidgets/QApplication>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
	qDebug() << "currentPath" << QDir::currentPath();

    QApplication a(argc, argv);
    QtOpenGLWidgetsApplication w;
    w.show();
    return a.exec();
}
