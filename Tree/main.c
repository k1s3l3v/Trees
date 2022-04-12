#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct tree {
	int key;
	struct tree* left;
	struct tree* right;
	struct tree* parent;
} node;

node* create(node* root, int key) {
	node* tmp = malloc(sizeof(node));
	tmp->key = key;
	tmp->parent = NULL;
	tmp->left = tmp->right = NULL;
	root = tmp;
	return root;
}

node* add(node* root, int key) {
	node* root2 = root, * root3 = NULL; 
	node* tmp = malloc(sizeof(node)); 
	tmp->key = key; 
	while (root2 != NULL) {
		root3 = root2;
		if (key < root2->key) root2 = root2->left;
		else root2 = root2->right;
	}
	tmp->parent = root3;
	tmp->left = NULL;
	tmp->right = NULL;
	if (key < root3->key) root3->left = tmp;
	else root3->right = tmp;
	return root;
}

node* search(node* root, int key) {
	if ((root == NULL) || (root->key == key)) return root;
	if (key < root->key) return search(root->left, key);
	else return search(root->right, key);
}

node* min(node* root) {
	node* m = root;
	while (m->left != NULL) m = m->left;
	return m;
}

node* max(node* root) {
	node* mx = root;
	while (mx->right != NULL) mx = mx->right;
	return mx;
}

node* succ(node* root) {
	node* p = root, * l = NULL;
	if (p->right != NULL) return min(p->right);
	l = p->parent;
	while ((l != NULL) && (p == l->right)) {
		p = l;
		l = l->parent;
	}
	return l;
}

node* delete(node* root, int key) {
	node* p = root, * l = NULL, * m = NULL;
	l = search(root, key);
	if ((l->left == NULL) && (l->right == NULL)) {
		m = l->parent;
		if (l == m->right) m->right = NULL;
		else m->left = NULL;
		free(l);
	}
	if ((l->left == NULL) && (l->right != NULL)) {
		m = l->parent;
		if (l == m->right) m->right = l->right;
		else m->left = l->right;
		free(l);
	}
	if ((l->left != NULL) && (l->right == NULL)) {
		m = l->parent;
		if (l == m->right) m->right = l->left;
		else m->left = l->left;
		free(l);
	}
	if ((l->left != NULL) && (l->right != NULL)) {
		m = succ(l);
		l->key = m->key;
		if (m->right == NULL)
			m->parent->left = NULL;
		else m->parent->left = m->right;
		free(m);
	}
	return root;
}

void preorder(node* root)
{
	if (root == NULL) return;
	if (root->key) printf("%d ", root->key);
	preorder(root->left);
	preorder(root->right);
}

void print(node* tree, int level) {
	if (tree->right != NULL) print(tree->right, ++level);
	for (int i = 0; i < (4 * level); i++) printf(" ");
	printf("%d\n", tree->key);
	if (tree->left != NULL) print(tree->left, ++level);
	--level;
}

int main() {
	node* root = NULL;
	root = create(root, 8);
	add(root, 3);
	add(root, 1);
	add(root, 6);
	add(root, 4);
	add(root, 7);
	add(root, 10);
	add(root, 14);
	add(root, 13);
	puts("------------------");
	print(root, 4);
	puts("------------------");
	delete(root, 6);
	print(root, 4);	
	puts("------------------");
	add(root, 9);
	puts("------------------");
	print(root, 4);
	return 0;
}
