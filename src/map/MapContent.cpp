#include <GL/glew.h>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <MapContent.h>
#include <iostream>
#include "shader.hpp"

#define GLM_FORCE_RADIANS
using namespace glm;

MapContent::MapContent(QWidget *parent)
    : QOpenGLWidget(parent), horizontalAngle(3.14f), verticalAngle(0.0f),
	  mouseSpeed(0.005f), cameraPosition(5,2,10), prevPoint(-1, -1) {

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

	return QSize(600, 600);
}

void MapContent::cleanup()
{
    makeCurrent();
    // Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
    doneCurrent();
}

void MapContent::initializeGL() {

	glewExperimental = GL_TRUE;
    glewInit();
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    programID = LoadShaders( "/home/vvirkkal/Documents/development/rover-controller/src/map/SimpleVertexShader.vertexshader", "/home/vvirkkal/Documents/development/rover-controller/src/map/SimpleFragmentShader.fragmentshader" );
    matrixID = glGetUniformLocation(programID, "MVP");

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

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset7
    );
    // Draw the triangle !
    glDrawArrays(GL_LINE_STRIP, 0, len_buffer/3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

void MapContent::translate(float delta_x, float delta_y, float delta_z) {

	cameraPosition += glm::vec3(delta_x, delta_y, delta_z);
	updateMatrices();
    update();
}

void MapContent::mousePositionChanged(int x, int y) {

	if(prevPoint.x == -1) {
		prevPoint.x = x;
		prevPoint.y = y;
		return;
	}

	horizontalAngle += mouseSpeed * float(prevPoint.x - x);
	verticalAngle   += mouseSpeed * float(prevPoint.y - y );

	prevPoint.x = x;
	prevPoint.y = y;
	updateMatrices();
	update();
}

void MapContent::mouseMoveEvent(QMouseEvent *e) {
	mousePositionChanged(e->x(), e->y());
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

