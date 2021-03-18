#pragma once

#include <QOpenGLWidget>
#include "ui_MyQtOpenGLWidgets.h"

#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class MyQtOpenGLWidgets : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	MyQtOpenGLWidgets(QWidget *parent = Q_NULLPTR);
	~MyQtOpenGLWidgets();

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

private:
	GLuint                          m_uiVertLoc;
	QOpenGLTexture          *       m_pTextures;
	QOpenGLShaderProgram    *       m_pProgram;
	GLfloat                 *       m_pVertices;

	void createShaderProgram();
	void makeObject();

private:
	Ui::MyQtOpenGLWidgets ui;
};
