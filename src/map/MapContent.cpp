#include <math.h>
#include <iostream>
#include <algorithm>
#include <ctime>


#include <GL/glew.h>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QTimer>

#include "MapContent.h"
#include "ArrayUtils.h"
#include "shader.hpp"

#define GLM_FORCE_RADIANS

using namespace std;
using namespace glm;
using namespace utils;

MapContent::MapContent(QWidget *parent) :
		QOpenGLWidget(parent), cameraPosition(5, 2, 10), nPathPoints(0), nMaxPathPoints(
				1e4), millisSinceStart(0), updateInterval(100), horizontalAngle(
				3.14f), verticalAngle(0.0f) {

	setMouseTracking(true);
}

MapContent::~MapContent() {
    cleanup();
}

QSize MapContent::minimumSizeHint() const {

	return QSize(50, 50);
}

QSize MapContent::sizeHint() const {

	return QSize(800, 800);
}

void MapContent::cleanup()
{
    makeCurrent();
    // Cleanup VBO
	glDeleteBuffers(1, &pathPointBuffer);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteProgram(programID);
    doneCurrent();
}

void MapContent::periodicDraw() {

	millisSinceStart += updateInterval;
	millisSinceStart = millisSinceStart > 1000 ? 0 : millisSinceStart;
	//update();
}
void MapContent::initializeGL() {

	glewExperimental = GL_TRUE;
    glewInit();
	glClearColor(0.0f, 0.0f, 0.05f, 0.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
    glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

    programID = LoadShaders( "/home/vvirkkal/Documents/development/rover-controller/src/map/SimpleVertexShader.vertexshader", "/home/vvirkkal/Documents/development/rover-controller/src/map/SimpleFragmentShader.fragmentshader" );
    matrixID = glGetUniformLocation(programID, "MVP");
	colorID = glGetUniformLocation(programID, "currentColor");
	pointSizeID = glGetUniformLocation(programID, "pointSize");

    updateMatrices();
    glGenBuffers(1, &pathPointBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, pathPointBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * nMaxPathPoints, 0,
			GL_DYNAMIC_DRAW);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(periodicDraw()));
	timer->start(updateInterval);
}

void MapContent::paintGL() {

    glClear( GL_COLOR_BUFFER_BIT );
    glUseProgram(programID);
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniform4f(colorID, 0.0f, 1.0f, 0.0f, 1.0f);

    glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, pathPointBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glDrawArrays(GL_LINE_STRIP, 0, nPathPoints);

//	for (Sphere sphere : checkPoints) {
//		if (sphere.isCheckPoint()) {
//			float redColor = sinf(float(millisSinceStart)) / 2.0f + 0.5f;
//			glUniform4f(colorID, redColor, 0.0f, 0.0f, 1.0f);
//		} else {
//			glUniform4f(colorID, 1.0f, 0.0f, 0.0f, 1.0f);
//		}
//		glBindBuffer(GL_ARRAY_BUFFER, sphere.getVertexBuffer());
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere.getIndexBuffer());
//
//		glDrawElements(GL_TRIANGLES, sphere.getIndices().size(),
//		GL_UNSIGNED_INT, (void*) 0);
//	}
    glDisableVertexAttribArray(0);
}

void MapContent::translate(float delta_x, float delta_y, float delta_z) {

	cameraPosition += glm::vec3(delta_x, delta_y, delta_z);
	updateMatrices();
    update();
}

void MapContent::mousePositionChanged(int x, int y) {

	horizontalAngle = 3.0f / 2.0f * 3.14f - float(x) / float(width()) * 3.14f;
	verticalAngle = 3.14f / 2.0f - float(y) / float(height()) * 3.14f;
	updateMatrices();
	update();
}

void MapContent::mouseMoveEvent(QMouseEvent *e) {
	mousePositionChanged(e->x(), e->y());
}

void MapContent::mouseWheelChanged(int delta) {

	float sign = delta < 0 ? -1.0f : 1.0f;
	float deltaX = sign * frontVector[0] / float(sqrt(3));
	float deltaY = sign * frontVector[1] / float(sqrt(3));
	float deltaZ = sign * frontVector[2] / float(sqrt(3));

	translate(deltaX, deltaY, deltaZ);

}
void MapContent::wheelEvent(QWheelEvent *e) {
	int delta = e->delta();
	mouseWheelChanged(delta);

}

void MapContent::updateDirectionVectors() {

	calcFrontVector();
	calcRightVector();
	calcUpVector();
}

void MapContent::calcFrontVector() {

	frontVector = glm::vec3(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
			);
}

void MapContent::calcRightVector() {

	 rightVector = glm::vec3(
			 sin(horizontalAngle - 3.14f/2.0f),
			 0,
			 cos(horizontalAngle - 3.14f/2.0f)
			 );
}

void MapContent::calcUpVector() {

	upVector = glm::cross( rightVector, frontVector);
}

void MapContent::updateMatrices() {

	updateDirectionVectors();
	updateProjectionMatrix();
	updateViewMatrix();
	updateModelMatrix();

	mvp = projectionMatrix * viewMatrix * modelMatrix;
}

void MapContent::updateProjectionMatrix() {

	 projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

void MapContent::updateViewMatrix() {

	 viewMatrix = glm::lookAt(cameraPosition,
			 	 	 	 	 cameraPosition + frontVector,
							 upVector
							 );
}

void MapContent::updateModelMatrix() {

	 modelMatrix = glm::mat4(1.0f);
}

void MapContent::setCheckPoints(vector<vector<float>> cPoints) {

	if (cPoints.size() > 0) {

		for (vector<vector<float>>::iterator it = cPoints.begin();
				it != cPoints.end(); ++it) {
			float origin[] = { (*it)[0], (*it)[2], -(*it)[1] };
			Sphere checkPointSphere(origin, 0.125, 10, 10);
			glGenBuffers(1, checkPointSphere.getVertexBufferReference());
			glBindBuffer(GL_ARRAY_BUFFER, checkPointSphere.getVertexBuffer());
			glBufferData(GL_ARRAY_BUFFER,
					checkPointSphere.getVertices().size() * sizeof(glm::vec3),
					checkPointSphere.getVertexArrayReference(),
					GL_STATIC_DRAW);
			glGenBuffers(1, checkPointSphere.getIndexBufferReference());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
					checkPointSphere.getIndexBuffer());
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					sizeof(unsigned int) * checkPointSphere.getIndices().size(),
					checkPointSphere.getIndexArrayReference(),
					GL_STATIC_DRAW);
			checkPoints.push_back(checkPointSphere);
		}
		setNearestCheckPoint(checkPoints, currentPosition);
		update();
	}
}

void MapContent::newPathPoint(float x, float y, float z) {

	//makeCurrent();
	if (nPathPoints == nMaxPathPoints) {
		return;
	}

	GLfloat newPoint[] = { x, z, -y };
	std::cout << "x: " << x << " y: " << y << " z: " << z << " pathPointBuffer"
			<< pathPointBuffer << " npathPoints: " << nPathPoints << "\n";
	glBindBuffer(GL_ARRAY_BUFFER, pathPointBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * nPathPoints * sizeof(GLfloat),
			sizeof(newPoint), newPoint);
	nPathPoints++;
	currentPosition = glm::vec3(x, z, -y);
	setNearestCheckPoint(checkPoints, currentPosition);
	update();
	//doneCurrent();
}

void MapContent::setPathPoints(vector<glm::vec3> points) {

	GLfloat newPoints[3 * points.size()];
	for (size_t k = 0; k < points.size(); k++) {
		newPoints[3 * k] = points[k][0];
		newPoints[3 * k + 1] = points[k][2];
		newPoints[3 * k + 2] = -points[k][1];
	}

	glBindBuffer(GL_ARRAY_BUFFER, pathPointBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * nPathPoints * sizeof(GLfloat),
			sizeof(newPoints), newPoints);
	nPathPoints += points.size();
	currentPosition = points.at(points.size() - 1);
	setNearestCheckPoint(checkPoints, currentPosition);
	update();
}
void MapContent::setNearestCheckPoint(vector<Sphere> &checkPoints,
		glm::vec3 point) {

	if (checkPoints.size() == 0) {
		return;
	} else if (checkPoints.size() == 1) {
		checkPoints.at(0).setCheckpoint(true);
		return;
	}

	for (Sphere &s : checkPoints) {
		s.setCheckpoint(false);
	}

	vector<Sphere>::iterator it = min_element(checkPoints.begin(),
			checkPoints.end(),
					[&point](const Sphere &sp1,
							const Sphere &sp2) {return sp1.distToPointSquared(point) < sp2.distToPointSquared(point);});
	(*it).setCheckpoint(true);
}

Sphere::Sphere(float *x0, float r, int N_phi, int N_theta) {

	center[0] = x0[0];
	center[1] = x0[1];
	center[2] = x0[2];
	createVertices(x0, r, N_phi, N_theta);
	createIndices(N_phi, N_theta);
}

Sphere::~Sphere() {

}


void Sphere::createVertices(float *x0, float r, int N_phi, int N_theta) {

	glm::vec3 point = { x0[0], x0[1] + r, x0[2] };
	vertices.push_back(point);
	for (int k = 1; k < N_phi; k++) {
		int N_theta_true = k == N_phi - 1 ? 1 : N_theta;
		float phi = float(k) * float(M_PI / (N_phi - 1));
		for (int l = 0; l < N_theta_true; l++) {
			float theta = float(l) * float(2.0 * M_PI / (N_theta - 1));
			point = {x0[0] + r * sinf(phi) * cosf(theta), x0[1] + r * cosf(phi), x0[2] + r * sinf(phi) * sinf(theta)};
			vertices.push_back(point);
		}
	}
}

void Sphere::createIndices(int N_phi, int N_theta) {

	for (int k = 1; k <= N_theta; k++) {
		indices.push_back(0);
		indices.push_back(k);
		indices.push_back(k + 1 <= N_theta ? k + 1 : 1);
	}

	if (N_phi > 3) {
		for (int k = 1; k < N_phi - 2; k++) {
			for (int l = 1 + k * N_theta; l <= (k + 1) * N_theta; l++) {
				indices.push_back(l);
				indices.push_back(l - N_theta);
				indices.push_back(
						l - N_theta + 1 <= k * N_theta ?
								l - N_theta + 1 : (k - 1) * N_theta + 1);
				indices.push_back(l);
				indices.push_back(
						l + 1 <= (k + 1) * N_theta ? l + 1 : k * N_theta + 1);
				indices.push_back(
						l - N_theta + 1 < k * N_theta ?
								l - N_theta + 1 : (k - 1) * N_theta + 1);
			}
		}
	}

	for (int k = 1 + (N_phi - 3) * N_theta; k <= (N_phi - 2) * N_theta; k++) {
		indices.push_back(vertices.size() - 1);
		indices.push_back(k);
		indices.push_back(
				k + 1 < (int) vertices.size() - 1 ?
						k + 1 : 1 + (N_phi - 3) * N_theta);
	}
}

vector<unsigned int> Sphere::getIndices() {
	return indices;
}

vector<glm::vec3> Sphere::getVertices() {
	return vertices;
}

int Sphere::getNumIndices() {
	return indices.size();
}

GLuint* Sphere::getVertexBufferReference() {

	return &vertexBuffer;
}

GLuint Sphere::getVertexBuffer() {
	return vertexBuffer;
}
GLfloat* Sphere::getVertexArrayReference() {
	return &vertices[0][0];
}
GLuint* Sphere::getIndexBufferReference() {

	return &indexBuffer;
}

GLuint Sphere::getIndexBuffer() {
	return indexBuffer;
}

int Sphere::getNumVertexCoordinates() {
	return 3 * vertices.size();
}

unsigned int* Sphere::getIndexArrayReference() {

	return &indices[0];
}
void Sphere::setCheckpoint(bool val) {
	checkPoint = val;
}


bool Sphere::isCheckPoint() {
	return checkPoint;
}

float Sphere::distToPointSquared(glm::vec3 point) const {

	return float(
			pow(center[0] - point[0], 2) + pow(center[1] - point[1], 2)
					+ pow(center[2] - point[2], 2));
}



