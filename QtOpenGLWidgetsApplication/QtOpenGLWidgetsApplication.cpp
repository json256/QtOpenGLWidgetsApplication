#include "QtOpenGLWidgetsApplication.h"
#include "MyQtOpenGLWidgets.h"
#include <QVBoxLayout>

QtOpenGLWidgetsApplication::QtOpenGLWidgetsApplication(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	MyQtOpenGLWidgets *w = new MyQtOpenGLWidgets;
	QVBoxLayout *v = new QVBoxLayout(this);
	v->addWidget(w);
	v->setMargin(0);
	this->setLayout(v);
}
