#include<iostream>
#include<math.h>

using namespace std;

struct node{
	int data;
	node *left;
	node *right;
};
node *insert(node *tree, int x){
	if (tree == NULL){
		node *temp = new node;
		temp->data =x;
		temp->left = NULL;
		temp->right = NULL;
		return temp;
	} else{
		if (x < tree->data){
			tree->left = insert(tree->left, x);
		} else{
			tree->right = insert(tree->right, x);
		}
	}	
	return tree;
}
int treeLevel(node *tree){
	if (tree == NULL) return 0;
	return 1 + max(treeLevel(tree->left), treeLevel(tree->right));
}
bool checkAvl(node *tree){
	if (tree == NULL) 	return true;
	if (tree->left == NULL && tree->right == NULL) return true;
	if (abs(treeLevel(tree->left) - treeLevel(tree->right)) > 1) return false;
	return checkAvl(tree->left) && checkAvl(tree->right);
}
node *turnRight(node *tree){//Lenh trai
	node *b = tree->left;
	node *d = b->right;
	tree->left = d;
	b->right = tree;
	return b;
}
node *turnLeft(node *tree){//Lenh phai
	node *b = tree->right;
	node *c = b->left;
	tree->right = c;
	b->left = tree;
	return b;
}
void printTree(node *tree){
	if (tree != NULL){
		printTree(tree->left);
		cout << tree->data << " ";
		if (tree->left != NULL) cout <<tree->left->data << " ";
		if (tree->right != NULL) cout << tree->right->data << " ";
		cout << endl;
		printTree(tree->right);
	}
}
node *updateTreeAvl(node *tree){
	if (abs(treeLevel(tree->left) - treeLevel(tree->right)) > 1){
		if (treeLevel(tree->left) > treeLevel(tree->right)){
			node *p = tree->left;
			if (treeLevel(p->left) >= treeLevel(p->right)){
				tree = turnRight(tree);
			} else{
				tree->left = turnLeft(tree->left);
				tree = turnRight(tree);
			}
		} else {
			node *p = tree->right;
			if (treeLevel(p->right) >= treeLevel(p->left)){
				tree = turnLeft(tree);
			} else{
				tree->right = turnRight(tree->right);
				tree = turnLeft(tree);
			
			}
		}	
	}
	if (tree->left != NULL) tree->left = updateTreeAvl(tree->left);
	if (tree->right != NULL) tree->right = updateTreeAvl(tree->right);
	return tree;
}
int main(){
	int n, temp;
	cin >> n;
	node * tree = NULL;
	for (int i = 0; i < n; i++){
		cin >> temp;
		tree = insert(tree, temp);
	}
	while(!checkAvl(tree)){
		tree = updateTreeAvl(tree);		
	}
	//printTree(tree);
	cout << treeLevel(tree);
	system("pause");
	return 0;
}