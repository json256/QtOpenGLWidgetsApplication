#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtOpenGLWidgetsApplication.h"

class QtOpenGLWidgetsApplication : public QWidget
{
    Q_OBJECT

public:
    QtOpenGLWidgetsApplication(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtOpenGLWidgetsApplicationClass ui;
};
