#ifndef MYGUI_H
#define MYGUI_H

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

using namespace std;

class myGUI {
public:
	myGUI() {}
	~myGUI() {}
	void createOptions() {
		ImGui::RadioButton("Same color", &radioChecked, 0);
		ImGui::ColorEdit3("All-vertices", allVertexColor);

		ImGui::RadioButton("Different color", &radioChecked, 1);
		ImGui::ColorEdit3("Vertex-1", newVertexColor[0]);
		ImGui::ColorEdit3("Vertex-2", newVertexColor[1]);
		ImGui::ColorEdit3("Vertex-3", newVertexColor[2]);

		ImGui::RadioButton("Reset all", &radioChecked, 2);
	}

	void updateVertices(float (&vertices)[2][9]) {
		switch (radioChecked) {
		case 0:
			for (int i = 0; i < 3; i++) {
				vertices[1][i] = allVertexColor[i];
				vertices[1][i + 3] = allVertexColor[i];
				vertices[1][i + 6] = allVertexColor[i];
			}
			changedFlag = true;
			break;
		case 1:
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (vertices[1][i * 3 + j] != newVertexColor[i][j]) {
						changedFlag = true;
						vertices[1][i * 3 + j] = newVertexColor[i][j];
					}
				}
			}
			break;
		case 2:
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (vertices[1][i * 3 + j] != resetColor[i][j]) {
						changedFlag = true;
						vertices[1][i * 3 + j] = resetColor[i][j];
					}
				}
			}
			break;
		default:
			break;
		}
	}
	bool isChanged() {
		return changedFlag;
	}
	void resetChangedFlag() {
		changedFlag = false;
	}


private:
	float allVertexColor[3] = { 0.0f, 0.0f, 1.0f };
	float newVertexColor[3][3] = {
		{ 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f }
	};
	float resetColor[3][3] = {
		{ 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f }
	};

	bool changedFlag = false;
	int radioChecked = 2;
};

#endif
