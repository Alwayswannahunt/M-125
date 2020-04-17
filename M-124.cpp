
#include <iostream>

class point {
	int32_t x = 0;
	int32_t y = 0;
	bool downS = false; // в какой из оболочек (выше АБ или ниже)
	bool isInShell = false;
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
void SortArrayOfPointsYLeavingXsorting(class point* array_p, uint16_t length);
int32_t FindOrientedAreaOfSubtractionTreePoints(point p1, point p2, point p3);

int main()
{
	uint16_t N=0;
	int32_t A,B,numSave;
	class point* array_point;

	std::cin >> N;

	array_point = new class point[N];
	if (array_point == NULL) return(1);

	for (uint16_t i = 0; i < N; i++) {
		std::cin >> A >> B;
		array_point[i].setx(A);
		array_point[i].sety(B);
	}

	SortArrayOfPointsX(array_point, N);
	SortArrayOfPointsYLeavingXsorting(array_point, N);

	B = N-1;
	for (uint16_t i = N-1; i > 0; i--) {
		if (array_point[i].getx() < array_point[B].getx())  break;
		else
		{
			if (array_point[B].gety() > array_point[i].gety()) B = i;
		}
	}
	array_point[B].setisInShell(true);

	A = 0;
	array_point[A].setisInShell(true);
	array_point[A].setdownS(true);
	array_point[B].setdownS(true);

	for (uint16_t i = 1; i < N; i++) {
		if (FindOrientedAreaOfSubtractionTreePoints(array_point[B], array_point[i], array_point[A]) > 0) array_point[i].setdownS(true);
	}

	numSave = 2;
	for (uint16_t i = 1; i < N-1; i++) {
		if (array_point[A].getx() < array_point[i].getx() && array_point[i].getx() < array_point[i + 1].getx() && array_point[i].getdownS() == true) {
			for (uint16_t j = i + 1; j < N; j++) {
				if (FindOrientedAreaOfSubtractionTreePoints(array_point[i], array_point[j], array_point[A]) >= 0 && array_point[j].getx() != array_point[i].getx() && array_point[j].gety() != array_point[i].gety()) break;
				if (j == N - 1) {
					A = i;
					array_point[i].setisInShell(true);
					numSave++;
				}
			}
		}

	}
	array_point[B].setdownS(false);
	A = 0;
	for (uint16_t i = 1; i < N - 2; i++) {
		if (array_point[A].getx() < array_point[i].getx() && array_point[i].gety() < array_point[i + 1].gety() && array_point[i].getdownS() == false) {
			for (uint16_t j = i + 1; j < N - 1; j++) {
				if (FindOrientedAreaOfSubtractionTreePoints(array_point[i], array_point[j], array_point[A]) <= 0 && array_point[j].getx() != array_point[i].getx() && array_point[j].gety() != array_point[i].gety()) break;
				if (j == N - 2) {
					A = i;
					array_point[i].setisInShell(true);
					numSave++;
				}
			}
		}

	}


	std::cout << numSave << '\n';
	for (uint16_t i = 0; i < N; i++) {
		if (array_point[i].getisInShell() == true && array_point[i].getdownS() == true) std::cout << array_point[i].getx() << ' ' << array_point[i].gety() << '\n';
	}
	for (int32_t i = N-1; i >= 0; i--) {
		if (array_point[i].getisInShell() == true && array_point[i].getdownS() == false) std::cout << array_point[i].getx() << ' ' << array_point[i].gety() << '\n';
	}


	delete[] array_point;
	return(0);
}


void SortArrayOfPointsX(class point* array_p, uint16_t length) {
	int32_t key = 0;
	int32_t i = 0;
	point bubble;
	for (uint16_t j = 1; j < length; j++) {
		key = array_p[j].getx();
		i = j - 1;
		for (i; i >= 0 && array_p[i].getx() > key; i--) {
			bubble = array_p[i];
			array_p[i] = array_p[i + 1];
			array_p[i + 1] = bubble;

		}
	}
}

void SortArrayOfPointsYLeavingXsorting(class point* array_p, uint16_t length) {
	int32_t key = 0;
	int32_t i = 0;
	point bubble;
	for (uint16_t j = 1; j < length; j++) {
		key = array_p[j].gety();
		i = j - 1;
		for (i; i >= 0 && array_p[i].gety() > key && array_p[i].getx() == array_p[i + 1].getx(); i--) {
			bubble = array_p[i];
			array_p[i] = array_p[i + 1];
			array_p[i + 1] = bubble;
		}
	}
}


int32_t FindOrientedAreaOfSubtractionTreePoints(point p1, point p2, point p3) {
	return(((p1.getx() - p3.getx()) * (p2.gety() - p3.gety()))  - ((p2.getx() - p3.getx()) * (p1.gety() - p3.gety()))); // {p1-p3} X {p2-p3}
}