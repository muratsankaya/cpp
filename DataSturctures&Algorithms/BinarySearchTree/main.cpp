
#include <random>
#include <functional>
#include <iostream>
#include <stack>
#define COUNT 10
using namespace std;

template<typename T>
struct Node {
	T val;
	Node* left;
	Node* right;
	Node(T val, Node* left=nullptr, Node* right=nullptr) : val(val), left(left), right(right) {}
};

template <typename T>
class BinarySearchTree {
public:
	BinarySearchTree(Node<T>* nodePtr=nullptr) : headNodePtr(nodePtr), theSize(0) {}

	void insert(T val) {
		if (!headNodePtr) headNodePtr = new Node<T>(val);
		else {
			Node<T>* cursor = headNodePtr;
			while (cursor) {
				if (cursor->val <= val) {
					if (!cursor->right) {
						cursor->right = new Node<T>(val);
						return;
					}
					cursor = cursor->right;
				}
				else {
					if (!cursor->left) {
						cursor->left = new Node<T>(val);
						return;
					}
					cursor = cursor->left;
				}
			}
		}
		++theSize;
	}

	T replaceOnRight(Node<T>*& toReplace) {
		T toReturn = toReplace->val;
		if (toReplace->right) toReplace->val = replaceOnLeft(toReplace->right);
		else if (toReplace->left) toReplace->val = replaceOnLeft(toReplace->left);
		else {
			delete toReplace;
			toReplace = nullptr;
		}
		return toReturn;
	}

	T replaceOnLeft(Node<T>*& toReplace) {
		T toReturn = toReplace->val;
		if (toReplace->left) toReplace->val = replaceOnRight(toReplace->left);
		else if (toReplace->right) toReplace->val = replaceOnRight(toReplace->right);
		else {
			delete toReplace;
			toReplace = nullptr;
		}
		return toReturn;
	}
	void erase(T val) {
		deleteNode(headNodePtr, val);
	}
	Node<T>** findNodeToDelete(Node<T>*& root, int key) {
		Node<T>** cursor = &root;
		while (*cursor) {
			if ((*cursor)->val == key) return cursor;
			if ((*cursor)->val > key) cursor = &(*cursor)->left;
			else cursor = &(*cursor)->right;
		}
		return nullptr;
	}

	Node<T>* deleteNode(Node<T>*& root, int key) {
		Node<T>** toDelete = findNodeToDelete(root, key);
		if (!toDelete) return root; //Node to delete was not found
		if ((*toDelete)->right) {
			Node<T>** cursor = &(*toDelete)->right;
			while ((*cursor)->left) cursor = &(*cursor)->left;
			(*toDelete)->val = (*cursor)->val;
			Node<T>* heapDelete = &**cursor;
			if ((*cursor)->right) *cursor = (*cursor)->right;
			else *cursor = nullptr;
			delete heapDelete;
		}
		else if ((*toDelete)->left) {
			Node<T>** cursor = &(*toDelete)->left;
			while ((*cursor)->right) cursor = &(*cursor)->right;
			(*toDelete)->val = (*cursor)->val;
			Node<T>* heapDelete = &**cursor;
			if ((*cursor)->left) *cursor = (*cursor)->left;
			else *cursor = nullptr;
			delete heapDelete;
		}
		else {//node to delete is a leaf
			Node<T>* heapDelete = &**toDelete;
			if (*toDelete == root) {
				root = nullptr;
			}
			else {
				*toDelete = nullptr;
			}
			delete heapDelete;
		}
		return root;
	}

	void iteretiveInorder() {
		Node<T>* cursor = headNodePtr;
		stack<Node<T>*> s;
		while (cursor || !s.empty()) {
			while (cursor) {
				s.push(cursor);
				cursor = cursor->left;
			}
			cursor = s.top();
			s.pop();
			cout << cursor->val << " ";
			cursor = cursor->right;
		}
		cout << endl;
	}

	void print2DUtil() {
		print2DUtil(headNodePtr, 0);
	}

	void print2DUtil(Node<T>* root, int space) {
		// Base case
		if (root == NULL)
			return;

		// Increase distance between levels
		space += COUNT;

		// Process right child first
		print2DUtil(root->right, space);

		// Print current node after space
		// count
		cout << endl;
		for (int i = COUNT; i < space; i++)
			cout << " ";
		cout << root->val << "\n";

		// Process left child
		print2DUtil(root->left, space);
	}
private:
	Node<T>* headNodePtr;
	size_t theSize;
};

int main() {
	BinarySearchTree<int> bst;
	//for (int i = 0; i < 10; ++i) {
	//	random_device dev;
	//	mt19937 rng(dev());
	//	uniform_int_distribution<std::mt19937::result_type> dist6(0, 1000); // distribution in range [1, 6]
	//	bst.insert(dist6(rng));
	//}
	/*bst.insert(50);
	bst.insert(30);
	bst.insert(40);
	bst.insert(15);
	bst.insert(17);
	bst.insert(10);
	bst.insert(12);
	bst.insert(8);*/
	bst.insert(50);
	bst.insert(30);
	bst.insert(20);
	bst.insert(40);
	bst.insert(70);
	bst.insert(60);
	bst.insert(80);
	bst.iteretiveInorder();
	cout << endl;
	bst.print2DUtil();
	
	/*bst.insert(5);
	bst.insert(3);
	bst.insert(6);
	bst.insert(2);
	bst.insert(4);
	bst.insert(7);*/
	/*bst.print2DUtil();
	cout << endl << endl << endl;
	bst.erase(20);
	bst.print2DUtil();
	cout << endl << endl << endl;
	bst.erase(30);
	bst.print2DUtil();
	cout << endl << endl << endl;
	bst.erase(50);
	bst.print2DUtil();*/
}

