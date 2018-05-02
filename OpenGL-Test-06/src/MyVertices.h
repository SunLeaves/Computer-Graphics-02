#ifndef MYVERTICES_H
#define MYVERTICES_H

void setObjVertices(float(&vertices)[36][6]);
void setLightVertices(float(&vertices)[36][3]);
void setPlaneVertices(float(&vertices)[6][6]);


float init_obj_vertices[] = {
	//  后表面
	-0.2f, -0.2f, -0.2f, 0.0f, 0.0f, -1.0f,
	0.2f, -0.2f, -0.2f, 0.0f, 0.0f, -1.0f,
	0.2f,  0.2f, -0.2f, 0.0f, 0.0f, -1.0f,
	0.2f,  0.2f, -0.2f, 0.0f, 0.0f, -1.0f,
	-0.2f,  0.2f, -0.2f, 0.0f, 0.0f, -1.0f,
	-0.2f, -0.2f, -0.2f, 0.0f, 0.0f, -1.0f,

	//  前表面
	-0.2f, -0.2f,  0.2f, 0.0f, 0.0f, 1.0f,
	0.2f, -0.2f,  0.2f, 0.0f, 0.0f, 1.0f,
	0.2f,  0.2f,  0.2f, 0.0f, 0.0f, 1.0f,
	0.2f,  0.2f,  0.2f, 0.0f, 0.0f, 1.0f,
	-0.2f,  0.2f,  0.2f, 0.0f, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, 0.0f, 0.0f, 1.0f,

	//  左表面
	-0.2f,  0.2f,  0.2f, -1.0f, 0.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, -1.0f, 0.0f, 0.0f,
	-0.2f, -0.2f, -0.2f, -1.0f, 0.0f, 0.0f,
	-0.2f, -0.2f, -0.2f, -1.0f, 0.0f, 0.0f,
	-0.2f, -0.2f,  0.2f, -1.0f, 0.0f, 0.0f,
	-0.2f,  0.2f,  0.2f, -1.0f, 0.0f, 0.0f,

	//  右表面
	0.2f,  0.2f,  0.2f, 1.0f, 0.0f, 0.0f,
	0.2f,  0.2f, -0.2f, 1.0f, 0.0f, 0.0f,
	0.2f, -0.2f, -0.2f, 1.0f, 0.0f, 0.0f,
	0.2f, -0.2f, -0.2f, 1.0f, 0.0f, 0.0f,
	0.2f, -0.2f,  0.2f, 1.0f, 0.0f, 0.0f,
	0.2f,  0.2f,  0.2f, 1.0f, 0.0f, 0.0f,

	//  上表面
	-0.2f, -0.2f, -0.2f, 0.0f, -1.0f,  0.0f,
	0.2f, -0.2f, -0.2f, 0.0f, -1.0f,  0.0f,
	0.2f, -0.2f,  0.2f, 0.0f, -1.0f,  0.0f,
	0.2f, -0.2f,  0.2f, 0.0f, -1.0f,  0.0f,
	-0.2f, -0.2f,  0.2f, 0.0f, -1.0f,  0.0f,
	-0.2f, -0.2f, -0.2f, 0.0f, -1.0f,  0.0f,

	//  下表面
	-0.2f,  0.2f, -0.2f, 0.0f, 1.0f,  0.0f,
	0.2f,  0.2f, -0.2f, 0.0f, 1.0f,  0.0f,
	0.2f,  0.2f,  0.2f, 0.0f, 1.0f,  0.0f,
	0.2f,  0.2f,  0.2f, 0.0f, 1.0f,  0.0f,
	-0.2f,  0.2f,  0.2f, 0.0f, 1.0f,  0.0f,
	-0.2f,  0.2f, -0.2f, 0.0f, 1.0f,  0.0f
};

float init_plane_vertices[6][6] = {
	// Positions          // Normals
	25.0f, 0.0f, 25.0f, 0.0f, 1.0f, 0.0f, 
	-25.0f, 0.0f, -25.0f, 0.0f, 1.0f, 0.0f, 
	-25.0f, 0.0f, 25.0f, 0.0f, 1.0f, 0.0f, 

	25.0f, 0.0f, 25.0f, 0.0f, 1.0f, 0.0f, 
	25.0f, 0.0f, -25.0f, 0.0f, 1.0f, 0.0f, 
	-25.0f, 0.0f, -25.0f, 0.0f, 1.0f, 0.0f
};

float init_quad_vertices[4][5] = {
	// positions       // texCoords
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f
};

float init_light_vertices[36][3] = {
	-0.05f, -0.05f, -0.05f,
	0.05f, -0.05f, -0.05f,
	0.05f,  0.05f, -0.05f,
	0.05f,  0.05f, -0.05f,
	-0.05f,  0.05f, -0.05f,
	-0.05f, -0.05f, -0.05f,

	-0.05f, -0.05f,  0.05f,
	0.05f, -0.05f,  0.05f,
	0.05f,  0.05f,  0.05f,
	0.05f,  0.05f,  0.05f,
	-0.05f,  0.05f,  0.05f,
	-0.05f, -0.05f,  0.05f,

	-0.05f,  0.05f,  0.05f,
	-0.05f,  0.05f, -0.05f,
	-0.05f, -0.05f, -0.05f,
	-0.05f, -0.05f, -0.05f,
	-0.05f, -0.05f,  0.05f,
	-0.05f,  0.05f,  0.05f,

	0.05f,  0.05f,  0.05f,
	0.05f,  0.05f, -0.05f,
	0.05f, -0.05f, -0.05f,
	0.05f, -0.05f, -0.05f,
	0.05f, -0.05f,  0.05f,
	0.05f,  0.05f,  0.05f,

	-0.05f, -0.05f, -0.05f,
	0.05f, -0.05f, -0.05f,
	0.05f, -0.05f,  0.05f,
	0.05f, -0.05f,  0.05f,
	-0.05f, -0.05f,  0.05f,
	-0.05f, -0.05f, -0.05f,

	-0.05f,  0.05f, -0.05f,
	0.05f,  0.05f, -0.05f,
	0.05f,  0.05f,  0.05f,
	0.05f,  0.05f,  0.05f,
	-0.05f,  0.05f,  0.05f,
	-0.05f,  0.05f, -0.05f
};


void setObjVertices(float(&vertices)[36][6]) {
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 6; j++) {
			vertices[i][j] = init_obj_vertices[i * 6 + j];
		}
	}
}

void setLightVertices(float(&vertices)[36][3]) {
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 3; j++) {
			vertices[i][j] = init_light_vertices[i][j];
		}
	}
}

void setPlaneVertices(float(&vertices)[6][6]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			vertices[i][j] = init_plane_vertices[i][j];
		}
	}
}

void setQuadVertices(float(&vertices)[4][5]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			vertices[i][j] = init_quad_vertices[i][j];
		}
	}
}

#endif