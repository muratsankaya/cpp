
#include <vector>
#include <string>
#include <iostream>
using namespace std;

template<typename T>
void merge(vector<T>& v, size_t leftleft, size_t leftright, size_t rightleft, size_t rightright) {
	T* temp = new T[rightright - leftleft + 1];
	size_t tempcursor = 0, initalLeftLeft = leftleft, arraySize = rightright - leftleft + 1;
	while (leftleft <= leftright && rightleft <= rightright) {
		if (v[leftleft] < v[rightleft]) {
			temp[tempcursor] = v[leftleft];
			++leftleft;
		}
		else {
			temp[tempcursor] = v[rightleft];
			++rightleft;
		}
		++tempcursor;
	}
	while (rightleft <= rightright) {
		temp[tempcursor] = v[rightleft];
		++tempcursor;
		++rightleft;
	}
	while (leftleft <= leftright) {
		temp[tempcursor] = v[leftleft];
		++tempcursor;
		++leftleft;
	}
	for (size_t i = 0; i < arraySize; ++i) {
		v[initalLeftLeft] = temp[i];
		++initalLeftLeft;
	}
	delete[] temp;
}

template<typename T>
void mergeSort(vector<T>& v, size_t left, size_t right) {
	if (left == right) return;
	size_t mid = left + (right - left) / 2;
	mergeSort(v, left, mid);
	mergeSort(v, mid+1, right);
	merge(v, left, mid, mid + 1, right);
}

template<typename T>
void mergeSort(vector<T>& v) {
	mergeSort(v, 0, v.size() - 1);
}

template<typename T>
void printVector(vector<T>& v) {
	for (size_t i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}cout << endl;
}

int main(){
	vector<int> v{ 1, 3, 423, -423, 43, 213, -903, 5, 2, 534, 32, 234, -23 };
	mergeSort(v);
	printVector(v);
}

