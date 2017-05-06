#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class Point {

public:
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int x, y;
};

class MapContent: public QOpenGLWidget {
Q_OBJECT

public:
	MapContent(QWidget *parent = 0);
	~MapContent();

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

	void translate(float delta_x, float delta_y, float delta_z);
	void mousePositionChanged(int x, int y);

public slots:
	void cleanup();
protected:
	void initializeGL() override;
	void paintGL() override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:

	void updateMatrices();
	void updateProjectionMatrix();
	void updateViewMatrix();
	void updateModelMatrix();
	void updateDirectionVectors();
	void calcFrontVector();
	void calcRightVector();
	void calcUpVector();
	GLuint VertexArrayID, vertexbuffer, programID, matrixID;
	int len_buffer = 39;
	GLfloat g_vertex_buffer_data[39];

	glm::mat4 mvp, modelMatrix, viewMatrix, projectionMatrix;
	glm::vec3 upVector, rightVector, frontVector, cameraPosition;

	float horizontalAngle, verticalAngle, mouseSpeed;

	Point prevPoint;
};

#endif
