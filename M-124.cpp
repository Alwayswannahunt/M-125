
#include <iostream>

class point {
	int32_t x;
	int32_t y;
	bool downS; // в какой из оболочек (выше АБ или ниже)
	bool isInShell;
public:
	int32_t getx() {
		return(x);
	}
	int32_t gety() {
		return(y);
	}
	bool getdownS() {
		return(downS);
	}
	bool getisInShell() {
		return(isInShell);
	}
	void setx(uint32_t in) {
		x = in;
	}
	void sety(uint32_t in) {
		y = in;
	}
	void setdownS(bool in) {
		downS = in;
	}
	void setisInShell(bool in) {
		isInShell = in;
	}
};

void SortArrayOfPointsX(class point* array_p, uint16_t length);
void SortArrayOfPointsY(class point* array_p, uint16_t length);
int32_t FindOrientedAreaOfSubtractionTreePoints(point p1, point p2, point p3);

int main()
{
	uint16_t N=0;
	int32_t A,B;
	class point* array_point;

	std::cin >> N;

	array_point = new class point[N];

	for (uint16_t i = 0; i < N; i++) {
		std::cin >> A >> B;
		array_point[i].setx(A);
		array_point[i].sety(B);
	}

	SortArrayOfPointsX(array_point, N);

	A = N;
	for (uint16_t i = N; i > 0; i--) {
		if (array_point[i].getx > array_point[i - 1].getx) break;
		else
		{
			if (array_point[N].gety < array_point[i].gety) N = i;
		}
	}

	B = 0;
	for (uint16_t i = 0; i < N; i++) {
		if (array_point[i].getx > array_point[i + 1].getx) break;
		else
		{
			if (array_point[N].gety > array_point[i]) N = i;
		}
	}

	for (uint16_t i = 0; i < N; i++) {
		if (FindOrientedAreaOfSubtractionTreePoints(array_point[A], array_point[i], array_point[B]) > 0) array_point->setdownS(true);
		else array_point->setdownS(false);
	}


	for (uint16_t i = 0; i < N; i++) {
		std::cout << i << " x: " << array_point[i].getx << " y: " << array_point[i].gety << " downS: " << array_point[i].getdownS << '\n';
	}

	delete(array_point);
	return(0);
}

void SortArrayOfPointsX(class point* array_p, uint16_t length) {
	int32_t key = 0;
	uint16_t i = 0;
	point bubble;
	for (uint16_t j = 1; j < length; j++) {
		key = array_p[j].getx;
		i = j - 1;
		while (i >= 0 && array_p[i].getx > key) {
			bubble = array_p[i];
			array_p[i + 1] = array_p[i];
			i = i - 1;
			array_p[i + 1] = bubble;
		}
	}
}

void SortArrayOfPointsY(class point* array_p, uint16_t length) {
	uint32_t key = 0;
	uint16_t i = 0;
	point bubble;
	for (uint16_t j = 1; j < length; j++) {
		key = array_p[j].gety;
		i = j - 1;
		while (i >= 0 && array_p[i].gety > key) {
			bubble = array_p[i];
			array_p[i + 1] = array_p[i];
			i = i - 1;
			array_p[i + 1] = bubble;
		}
	}
}


int32_t FindOrientedAreaOfSubtractionTreePoints(point p1, point p2, point p3) {
	return((p1.getx-p3.getx) * (p2.gety-p3.gety)  - (p2.getx-p3.getx) * (p1.gety- p3.gety)); // {p1-p3} X {p2-p3}
}