#ifndef  MYCIRCLE_H
#define  MYCIRCLE_H

using namespace std;

void createPoints(int centerx, int centery, int x, int y, int& count, int (&circlePoints)[16000]) {
	if (count < 8000) {
		circlePoints[count++] = x+centerx;
		circlePoints[count++] = y+centery;

		circlePoints[count++] = y + centerx;
		circlePoints[count++] = x + centery;

		circlePoints[count++] = -x + centerx;
		circlePoints[count++] = y + centery;

		circlePoints[count++] = -y + centerx;
		circlePoints[count++] = x + centery;

		circlePoints[count++] = -x + centerx;
		circlePoints[count++] = -y + centery;

		circlePoints[count++] = -y + centerx;
		circlePoints[count++] = -x + centery;

		circlePoints[count++] = x + centerx;
		circlePoints[count++] = -y + centery;

		circlePoints[count++] = y + centerx;
		circlePoints[count++] = -x + centery;

	}
}

void createCircle(int center[2], int radius, int& count, int(&circlePoints)[16000]) {
	int centerx = center[0],
		centery = center[1];

	int x = 0, y = radius, d = 3 - 2 * radius;
	while (y > x) {
		createPoints(centerx, centery, x, y, count, circlePoints);
		if (d < 0) {
			d += (2 * x + 3);
		} else {
			d += (2 * (x - y) + 5);
			y--;
		}
		x++;
	}
}

#endif // ! MYCIRCLE_H
