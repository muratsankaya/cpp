
#include <utility>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

template <typename T>
class myHeap {
private:
	size_t theSize;
	size_t theCapacity;
	T* heap;
public:
	myHeap() {
		theSize = 0;
		theCapacity = 1; //I don't want to deal with the doubling problem when the capacity = 0
		heap = new T[1];
	}
	~myHeap() { delete[] heap; } //log(n)
	void push_heap(T val) {
		if (theSize == theCapacity) {
			T* old = heap;
			heap = new T[theCapacity * 2];
			theCapacity *= 2;
			for (size_t i = 0; i < theSize; ++i) {
				heap[i] = old[i];
			}
			delete[] old;
		}
		heap[theSize] = val;
		++theSize;
		size_t cursor = theSize - 1;
		while (cursor != 0 && heap[(cursor - 1) / 2] > heap[cursor]) {
			swap(heap[(cursor - 1) / 2], heap[cursor]);
			cursor = (cursor - 1) / 2;
		}
	}
	void make_heap(vector<int>::iterator start, vector<int>::iterator end) { //nlog(n)
		while (start != end) {
			this->push_heap(*start);
			++start;
		}
	}
	T front() { return heap[0]; } //I don't think there is a need to make it const here, I can not think of I case where the user would like to change the min value manually. Its deosn't make sense!
	void pop_heap() {
		if (theSize == 0) throw exception("The heap is empty!");
		swap(heap[0], heap[theSize - 1]);
		--theSize;
		size_t leftChild = 1, rightChild = 2, cursor = 0;
		while (leftChild < theSize && rightChild < theSize && 
			min(heap[leftChild], heap[rightChild]) < heap[cursor]){
			size_t toSwap = cursor;
			(heap[leftChild] < heap[rightChild]) ? cursor = leftChild : cursor = rightChild;
			swap(heap[cursor], heap[toSwap]);
			leftChild = cursor * 2 + 1;
			rightChild = cursor * 2 + 2;
		}
		if (leftChild < theSize && heap[leftChild] < heap[cursor]) swap(heap[leftChild], heap[rightChild]);
	}
	void printHeap() {
		size_t breakPoints = 1;
		for (size_t i = 0; i < theSize; ++i) {
			cout << heap[i] << " ";
		}
		cout << endl;
	}
};

int	main() {
	vector<int> v{ 1, 43, -2, 34, 9, 45, 34, 21 };
	myHeap<string> m;
	m.push_heap("Murat");
	m.push_heap("Selim");
	m.push_heap("Sedat");
	m.push_heap("Serra");
	m.push_heap("Ali");
	m.push_heap("Kemal");
	m.printHeap();
	myHeap<int> m2;
	m2.make_heap(v.begin(), v.end());
	m2.push_heap(0);
	m2.printHeap();
	cout << m.front() << endl;
	for(int count = 0; count < 4 ; ++count) m2.pop_heap();
	m2.printHeap();
}

