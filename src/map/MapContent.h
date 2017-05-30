#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <vector>

#include <QOpenGLWidget>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

//QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class Point {

public:
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int x, y;
};

class Sphere;

class MapContent: public QOpenGLWidget {
Q_OBJECT

public:
	MapContent(QWidget *parent = 0);
	~MapContent();

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

	void translate(float delta_x, float delta_y, float delta_z);
	void mousePositionChanged(int x, int y);
	void mouseWheelChanged(int delta);
	void setCheckPoints(std::vector<std::vector<float>>);
	void setPathPoints(std::vector<glm::vec3> points);
	void newPathPoint(float x, float y, float z);

public slots:
	void cleanup();
	void periodicDraw();
protected:
	void initializeGL() override;
	void paintGL() override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

private:

	void updateMatrices();
	void updateProjectionMatrix();
	void updateViewMatrix();
	void updateModelMatrix();
	void updateDirectionVectors();
	void calcFrontVector();
	void calcRightVector();
	void calcUpVector();
	static void setNearestCheckPoint(std::vector<Sphere> &checkPoints,
			glm::vec3 currentPoint);
	GLuint vertexArrayID, pathPointBuffer, programID, matrixID, colorID,
			pointSizeID;
	int nPathPoints, nMaxPathPoints, millisSinceStart, updateInterval;

	std::vector<Sphere> checkPoints;

	glm::mat4 mvp, modelMatrix, viewMatrix, projectionMatrix;
	glm::vec3 upVector, rightVector, frontVector, cameraPosition,
			currentPosition;

	float horizontalAngle, verticalAngle;
};

class Sphere {

public:
	Sphere(float *x0, float r, int N_phi, int N_theta);
	~Sphere();
	std::vector<glm::vec3> getVertices();
	std::vector<unsigned int> getIndices();
	int getNumIndices();
	GLuint* getVertexBufferReference();
	GLuint getVertexBuffer();
	GLfloat* getVertexArrayReference();
	GLuint* getIndexBufferReference();
	GLuint getIndexBuffer();
	unsigned int* getIndexArrayReference();
	int getNumVertexCoordinates();
	void setCheckpoint(bool checkPoint);
	float distToPointSquared(glm::vec3 point) const;
	bool isCheckPoint();
	float center[3];

private:

	void createVertices(float *x0, float r, int N_phi, int N_theta);
	void createIndices(int N_phi, int N_theta);
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;

	GLuint vertexBuffer, indexBuffer;
	bool checkPoint = false;
};

#endif
