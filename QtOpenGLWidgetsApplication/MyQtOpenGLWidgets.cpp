#include "MyQtOpenGLWidgets.h"

#define MY_BIND_VALUE 0

MyQtOpenGLWidgets::MyQtOpenGLWidgets(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);
}

MyQtOpenGLWidgets::~MyQtOpenGLWidgets()
{
	m_pTextures->release();
	delete m_pTextures;
	delete m_pProgram;
	delete[] m_pVertices;
}

void MyQtOpenGLWidgets::initializeGL()
{
	initializeOpenGLFunctions();

	createShaderProgram();

	makeObject();

	glEnable(GL_DEPTH_TEST);
}

void MyQtOpenGLWidgets::resizeGL(int w, int h)
{
	//glViewport(0, 0, w, h);
}

void MyQtOpenGLWidgets::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pTextures->bind(MY_BIND_VALUE);
		
	glDrawArrays(GL_TRIANGLES, 0, 6);

	m_pTextures->release();
}

void MyQtOpenGLWidgets::createShaderProgram()
{
	QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	const char *vsrc =
		"#version 330\n"
		"in vec3 pos;\n"
		"out vec2 texCoord;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = vec4(pos, 1.0);\n"
		"    texCoord = pos.xy;\n"
		"}\n";
	vshader->compileSourceCode(vsrc);

	QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	const char *fsrc =
		"#version 330\n"
		"out mediump vec4 color;\n"
		"in vec2 texCoord;\n"
		"uniform sampler2D Tex\n;"
		"void main()\n"
		"{\n"
		"    color = texture(Tex, texCoord);\n"
		//"      color = vec4(1.0, 0.0, 0.0, 0.0);\n"
		"}\n";
	fshader->compileSourceCode(fsrc);

	m_pProgram = new QOpenGLShaderProgram;
	m_pProgram->addShader(vshader);
	m_pProgram->addShader(fshader);
	m_pProgram->link();
	m_pProgram->bind();
}

void MyQtOpenGLWidgets::makeObject()
{
	m_pVertices = new GLfloat[18];
	GLfloat arrVertices[18] = { -1.0, 1.0, 0.0,
		-1.0, -1.0, 0.0,
		1.0, -1.0, 0.0,
		1.0, -1.0, 0.0,
		1.0, 1.0, 0.0,
		-1.0, 1.0, 0.0 };
	//GLfloat arrVertices[18] = { 0.0, 1.0, 0.0,
	//	0.0, 0.0, 0.0,
	//	1.0, 0.0, 0.0,
	//	1.0, 0.0, 0.0,
	//	1.0, 1.0, 0.0,
	//	0.0, 1.0, 0.0 };
	m_pVertices = new GLfloat[18];
	memcpy(m_pVertices, arrVertices, 18 * sizeof(GLfloat));

	m_uiVertLoc = m_pProgram->attributeLocation("pos");
	m_pProgram->enableAttributeArray(m_uiVertLoc);
	m_pProgram->setAttributeArray(m_uiVertLoc, m_pVertices, 3, 0);

	m_pTextures = new QOpenGLTexture(QImage(QString("01.png")).mirrored());
	m_pTextures->setMinificationFilter(QOpenGLTexture::Nearest);
	m_pTextures->setMagnificationFilter(QOpenGLTexture::Linear);
	m_pTextures->setWrapMode(QOpenGLTexture::MirroredRepeat);
	m_pProgram->setUniformValue("Tex", MY_BIND_VALUE);
}