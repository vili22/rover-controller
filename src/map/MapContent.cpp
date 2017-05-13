#include <math.h>
#include <iostream>


#include <GL/glew.h>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>

#include "MapContent.h"
#include "ArrayUtils.h"
#include "shader.hpp"

#define GLM_FORCE_RADIANS

using namespace std;
using namespace glm;
using namespace utils;

MapContent::MapContent(QWidget *parent)
    : QOpenGLWidget(parent), horizontalAngle(3.14f), verticalAngle(0.0f),
	  mouseSpeed(
				0.005f), cameraPosition(5, 2, 10), nCheckPoints(0) {

	setMouseTracking(true);
}

MapContent::~MapContent() {
    cleanup();
}

static void createInitialData(GLfloat *data) {

    data[0] = 0.0f;
    data[1] = 0.0f;
    data[2] = 0.0f;
    data[3] = 1.0f;
    data[4] = 0.0f;
    data[5] = 0.0f;
    data[6] = 2.0f;
    data[7] = 0.0f;
    data[8] = 0.0f;
    data[9] = 3.0f;
    data[10] = 0.0f;
    data[11] = 0.0f;
    data[12] = 4.0f;
    data[13] = 0.0f;
    data[14] = 0.0f;
    data[15] = 5.0f;
    data[16] = 0.0f;
    data[17] = 0.0f;
    data[18] = 5.0f;
    data[19] = 0.0f;
    data[20] = -1.0f;
    data[21] = 5.0f;
    data[22] = 0.0f;
    data[23] = -2.0f;
    data[24] = 5.0f;
    data[25] = 0.0f;
    data[26] = -3.0f;
    data[27] = 6.0f;
    data[28] = 0.0f;
    data[29] = -3.0f;
    data[30] = 7.0f;
    data[31] = 0.0f;
    data[32] = -3.0f;
    data[33] = 8.0f;
    data[34] = 0.0f;
    data[35] = -3.0f;
    data[36] = 9.0f;
    data[37] = 0.0f;
    data[38] = -3.0f;
}

static void printMatrix(glm::mat4 matrix) {

    for(int k = 0; k < 4; k++) {
        for(int l = 0; l < 4; l++) {
            std::cout << matrix[k][l] << " ";
        }
        std::cout << "\n\n";
    }
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
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteProgram(programID);
	if (nCheckPoints > 0) {
		glDeleteBuffers(1, &checkPointBuffer);
		delete checkPoints;
	}
    doneCurrent();
}

void MapContent::initializeGL() {

	glewExperimental = GL_TRUE;
    glewInit();
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
    glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

    programID = LoadShaders( "/home/vvirkkal/Documents/development/rover-controller/src/map/SimpleVertexShader.vertexshader", "/home/vvirkkal/Documents/development/rover-controller/src/map/SimpleFragmentShader.fragmentshader" );
    matrixID = glGetUniformLocation(programID, "MVP");
	colorID = glGetUniformLocation(programID, "currentColor");
	pointSizeID = glGetUniformLocation(programID, "pointSize");

    updateMatrices();

    createInitialData(g_vertex_buffer_data);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void MapContent::paintGL() {


    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );
    // Use our shader
    glUseProgram(programID);
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniform4f(colorID, 0.0f, 1.0f, 0.0f, 1.0f);

    glEnableVertexAttribArray(0);




	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glDrawArrays(GL_LINE_STRIP, 0, len_buffer / 3);


	if (nCheckPoints > 0) {
		glUniform4f(colorID, 1.0f, 0.0f, 0.0f, 1.0f);
		glUniform1ui(pointSizeID, 20);
		glBindBuffer(GL_ARRAY_BUFFER, checkPointBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
		glDrawArrays(GL_POINTS, 0, nCheckPoints / 3);
	}
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
		nCheckPoints = cPoints.at(0).size() * cPoints.size();
		if (nCheckPoints == 0) {
			return;
		}


		checkPoints = new GLfloat[nCheckPoints];
		utils::convert_vector_array_to_array<float>(checkPoints, cPoints);

		glGenBuffers(1, &checkPointBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, checkPointBuffer);
		glBufferData(GL_ARRAY_BUFFER, 4 * nCheckPoints, checkPoints,
				GL_STATIC_DRAW);
		update();
	}
}



