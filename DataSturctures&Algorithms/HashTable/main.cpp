
#include <functional>
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

template <typename K, typename V>
class HashTable {
	friend ostream& operator<<(ostream& os, const HashTable<K, V>& rhs) {
		for (size_t i = 0; i < rhs.theCapacity; ++i) {
			//cout << &rhs.table[i] << '\t';
			for (const pair<K, V>& elem : rhs.table[i]) {
				//cout << &elem << '\t';
				os << '{' << elem.first << ':' << elem.second << "} ";
			}
		}os << endl;
		return os;
	}
public:
	class iterator {
		friend bool operator!=(const HashTable<K, V>::iterator& lhs, const HashTable<K, V>::iterator& rhs) {
			return lhs.iter1 != rhs.iter1;
		}
	private:
		vector<pair<K, V>>* iter1;
		size_t bucketcursor;
	public:
		iterator(vector<pair<K, V>>* iter1) : iter1(iter1), bucketcursor(0) {}
		iterator& operator++() {
			if(bucketcursor == iter1->size()) {
				++iter1; bucketcursor = 0;
			}
			else { ++bucketcursor; }
			return *this;
		}
		K& operator*() const {
			if (bucketcursor != iter1->size()) {
				//cout << iter1[bucketcursor].first << endl;
				return  (*iter1)[bucketcursor].first;
			}
		}

	};


private:
	vector<pair<K, V>>* table;
	size_t theSize;
	size_t theCapacity;
	size_t keySearch(size_t i, K key) {
		for (size_t j = 0; j < table[i].size(); ++j) {
			if (table[i][j].first == key) return j;
		}return table[i].size();
	}
	size_t hashFunc(K key) {
		return hash<K>()(key) % theCapacity;
	}
public:
	HashTable(size_t tablesize = 64) { //All the data members are primitive types
		table = new vector<pair<K, V>>[tablesize];
		theSize = 0;
		theCapacity = tablesize;
	}
	HashTable(const HashTable& rhs) {
		theCapacity = rhs.theCapacity;
		table = new vector<pair<K, V>>[theCapacity];
		for (size_t i = 0; i < theCapacity; ++i) {
			table[i] = rhs.table[i];
		}
		theSize = rhs.theSize;
	}
	~HashTable() {
		delete[] table;
	}
	HashTable& operator=(const HashTable& rhs) {
		if (this != &rhs) {
			delete[] table;
			theCapacity = rhs.theCapacity;
			table = new vector<pair<K, V>>[theCapacity];
			for (size_t i = 0; i < theCapacity; ++i) {
				table[i] = rhs.table[i];
			}
			theSize = rhs.theSize;
		} return *this;
	}
	size_t size() const { return theSize; }
	V& operator[](K key) {
		size_t i = hashFunc(key);
		size_t j = keySearch(i, key);
		if (j == table[i].size()) {
			table[i].push_back({ key, V()}); ++theSize; 
		}return table[i][j].second;
	}
	iterator begin() {
		return iterator(table);
	}
	iterator end() {
		return iterator(table+theCapacity);
	}
};


int main(){
	HashTable<char, int> mapOfCharsAndInts;
	string myDog = "toto";
	for (char c : myDog) {
		mapOfCharsAndInts[c] += 1;
	}
	//cout << mapOfCharsAndInts;
	HashTable<char, int> mp2 = mapOfCharsAndInts;
	//mapOfCharsAndInts.begin();
	//tests for deep copy
	//mp2['k'] = 2; mp2['t'] += 1;
	//cout << mp2 << mapOfCharsAndInts;
	for (char c : mapOfCharsAndInts) {
		cout << c << " ";
	}
}