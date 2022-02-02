#include<iostream>
using namespace std;

#define alphabet 26

struct node
{
	node* children[alphabet];
	bool is_word;
};

void init(node* root) {
	root->is_word = false;
	for (int i = 0; i < alphabet; i++)
	{
		root->children[i] = nullptr;
	}
}

void insert(node* root, string key) {
	node* current = root;
	for (int  i = 0; i < key.length(); i++)
	{
		int letter = (int)key[i] - (int)'a';
		if (current->children[letter] == nullptr)
			current->children[letter] = new node();
		current = current->children[letter];
	}
	current->is_word = true;
}

bool search(node* root, string key) {
	node* current = root;
	for (int i = 0; i < key.length(); i++)
	{
		if (current->children[((int)key[i] - (int)'a')] == nullptr)
			return false;
		current = current->children[((int)key[i] - (int)'a')];
	}
	return current->is_word;
}

bool isEmpty(node* root) {
	for (int i = 0; i < alphabet; i++)
	{
		if (root->children[i])
			return false;
	}
	return true;
}

node* remove(node* root, string key, int depth = 0) {
	if (!root)
		return nullptr;
	if (depth == key.length()) {
		if (root->is_word)
			root->is_word = false;

		if (isEmpty(root)) {
			delete root;
			root = nullptr;
		}
		return root;
	}

	int index = (int)key[depth] - (int)'a';
	root->children[index] = remove(root->children[index], key, depth + 1);

	if (isEmpty(root) && root->is_word == false) {
		delete root;
		root = nullptr;
	}

	return root;
}



int main() {

	node* root = new node;
	init(root);

	insert(root, "taxi");
	insert(root, "tea");
	insert(root, "monkey");
	insert(root, "hero");
	insert(root, "heart");

	cout << search(root, "taxi") << endl;
	cout << search(root, "toy") << endl;


	cout << search(root, "hero") << endl;
	remove(root, "hero");
	cout << search(root, "hero") << endl;

	remove(root, "taxi");
	cout << search(root, "taxi") << endl;


	return 0;
}