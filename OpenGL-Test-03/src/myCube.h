#ifndef MYCUBE_H
#define MYCUBE_H

class myCube {
public:
	myCube(float points[36]);
	~myCube();
private:
	float points[36];
};

myCube::myCube(float _points[36]) {
	for (int i = 0; i < 36; i++) {
		points[i] = _points[i];
	}
}

myCube::~myCube() {}



#endif // !MYCUBE_H
