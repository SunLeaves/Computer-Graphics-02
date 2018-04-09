#ifndef MYGUI_H
#define MYGUI_H

#include <imgui\imgui.h>


class myGUI {
public:
	myGUI() {}
	~myGUI() {}
	void createOptions() {

		//ImGui::Text("Choose Kind of Tranform");
		ImGui::RadioButton("Translation", &transSelected, 0);

		ImGui::RadioButton("Scale-largely", &transSelected, 1);

		ImGui::RadioButton("Scale-smally", &transSelected, 2);

		ImGui::RadioButton("Rotate", &transSelected, 3);
	}

	int getTransSelected() {
		return transSelected;
	}
	void render() {
		ImGui::Render();
	}
private:
	int transSelected = 0;
};

#endif // !MYGUI_H
