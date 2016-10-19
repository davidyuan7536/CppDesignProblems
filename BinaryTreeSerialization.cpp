#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <deque>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <math.h> 
#include <time.h>
#include <cstdio> 
#include <time.h>

using namespace std;

struct TreeNode{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BTreeSerializer {
public:

	void inOrder(TreeNode * root, string & inO){

		if (root == nullptr)
			return;

		inOrder(root->left, inO);
		inO += to_string(root->val);
		inO += '/';
		inOrder(root->right, inO);

	}

	void preOrder(TreeNode * root, string & preO){
		if (root == nullptr)
			return;

		preO += to_string(root->val);
		preO += '/';
		preOrder(root->left, preO);
		preOrder(root->right, preO);
	}

	string serialize(TreeNode* root) {

		string retString;
		inOrder(root, retString);
		retString += 'a';
		preOrder(root, retString);
		return retString;
	}

	TreeNode* deserializeHelper(string inOrder, string preOrder, TreeNode * head){

		if (inOrder.length() == 0 || preOrder.length() == 0){
			return nullptr;
		}

		int pos = preOrder.find('/');
		string headElement = preOrder.substr(0, pos);
		if (head == nullptr){
			head = new TreeNode(stoi(headElement));
		}

		if (inOrder.find('/') == inOrder.length() - 1){
			return head;
		}

		int x = 0;
		int y = 1;
		int counter = 0;
		for (; x < inOrder.length(); x++){

			if (inOrder[x] == '/'){
				counter++;
				continue;
			}

			if (inOrder[x] == headElement[0] && (x == 0 || inOrder[x - 1] == '/')){
				bool match = true;
				for (; y < headElement.length(); y++){
					if (inOrder[x + y] != headElement[y]){
						match = false;
						break;
					}
				}
				if (inOrder[x + y] != '/'){
					match = false;
				}
				if (match){
					break;
				}
				else
					y = 1;
			}
		}

		string firstInO = inOrder.substr(0, x);
		string secondInO = inOrder.substr(x + y + 1, inOrder.length());

		string firstPreO;
		string secondPreO;

		for (int x = headElement.length() + 1; x < preOrder.length(); x++){

			if (counter > 0){
				firstPreO += preOrder[x];
			}
			else{
				secondPreO += preOrder[x];
			}
			if (preOrder[x] == '/'){
				counter--;
			}

		}


		head->left = deserializeHelper(firstInO, firstPreO, head->left);
		head->right = deserializeHelper(secondInO, secondPreO, head->right);

		return head;
	}

	TreeNode* deserialize(string data) {
		if (data.empty() || data.length() == 1){
			return nullptr;
		}

		int pos = data.find("a");
		string inOrder = data.substr(0, pos);
		string preOrder = data.substr(pos + 1, data.length());
		TreeNode * head = nullptr;
		head = deserializeHelper(inOrder, preOrder, head);
		return head;

	}
};

/*
int main(){

	
	TreeNode *cool = new TreeNode(10);
	TreeNode *cool5 = new TreeNode(5);
	TreeNode *cool2 = new TreeNode(2);
	TreeNode *cool6 = new TreeNode(6);
	TreeNode *cool14 = new TreeNode(14);
	TreeNode *cool12 = new TreeNode(12);
	TreeNode *cool16 = new TreeNode(16);

	cool->left = cool5;
	cool5->left = cool2;
	cool5->right = cool6;
	cool->right = cool14;
	cool14->left = cool12;
	cool14->right = cool16;



	BTreeSerializer myBTreeSerializer;
	string serialized = myBTreeSerializer.serialize(cool);
	myBTreeSerializer.deserialize(serialized);

}

*/