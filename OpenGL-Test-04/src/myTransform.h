#ifndef MYTRANSFORM_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace std;

void modifyModel(glm::mat4& model);
void modifyView(glm::mat4& view);
void modifyProjection(glm::mat4& projection);


void modifyModel(glm::mat4& model) {
	//model = glm::translate(model, glm::vec3(-1.5f, 0.5f, -1.5f));
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void modifyView(glm::mat4& view) {
	//view = glm::lookAt(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.5f, 0.5f, -1.5f), glm::vec3(0.0f, 1.0f, 0.0f));
	//view = glm::lookAt(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
}

void modifyProjection(glm::mat4& projection) {
	//projection = glm::ortho(0.0f, 100.0f, 0.0f, 100.0f, 0.1f, 100.0f);
	//projection = glm::perspective(glm::radians(100.0f), 1.0f, 0.01f, 100.0f);
}
#endif // !MYTRANSFORM_H
