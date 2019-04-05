#include <iostream>
#include <vector>
using namespace std;

class BSTNode {
private:
	double key;
	BSTNode *lchild;
	BSTNode *rchild;
	BSTNode *parent;
	friend class BSTree;

public:
	BSTNode(double k = 0.0, BSTNode *l = NULL, BSTNode *r = NULL, BSTNode *p = NULL) {
		key = k;
		lchild = l;
		rchild = r;
		parent = p;
	}
};

class BSTree {
private:
	BSTNode *root; //根节点

	/*----------内部接口（传入的节点参数均为根节点）---------*/
	//先序遍历
	vector<double> PreTraverse(BSTNode *x) {
		vector<double> pre_vector;
		if (x != NULL) {
			pre_vector.push_back(x->key);
			//cout<< x->key << " ";
			PreTraverse(x->lchild);
			PreTraverse(x->rchild);
		}
		return pre_vector;
	}

	//中序遍历
	vector<double> InTraverse(BSTNode *x) {
		vector<double> in_vector;
		if (x != NULL) {
			
			InTraverse(x->parent);
			in_vector.push_back(x->key);
			//cout<< x->key << " ";
			InTraverse(x->rchild);
		}
	}

    //后序遍历
	vector<double> PostTraverse(BSTNode *x) {
		vector<double> post_vector;
		if (x != NULL) {
			PostTraverse(x->lchild);
			PostTraverse(x->rchild);
			post_vector.push_back(x->key);
			//cout<< x->key << " ";
		}
	}

	//查找键k，不存在则返回NTL
	BSTNode* SearchKey(BSTNode *x, double k) {
		if (x == NULL || k == x->key)
			return x;
		if (k < x->key)
			  return SearchKey(x->lchild, k);
		else  return SearchKey(x->rchild, k);

	}

	//查找以x为根节点的子树的最小key
	BSTNode* SearchMin(BSTNode *x) {
		while (x->lchild != NULL) {
			x = x->lchild;
		}
		return x;
	}

	//查找以x为根节点的子树的最大key
	BSTNode* SearchMax(BSTNode *x) {
		while (x->rchild != NULL) {
			x = x->rchild;
		}
		return x;
	}

	//查找节点x的后继节点
	BSTNode* SearchSuccessor(BSTNode *x) {
		BSTNode *tmp = NULL;  //tmp指针始终指向当前节点的父节点
		//若x的右孩子非空，则返回右子树的最小节点
		if (x->rchild != NULL)
			return SearchMin(x->rchild);
		/*若x的右孩子为空，则一直向树的顶端寻找，直到节点P是其父节点Q的左孩子，则Q为该节点的后继节点*/
		tmp = x->parent;
		while (tmp != NULL && x == tmp->rchild) {
			x = tmp;
			tmp = tmp->parent;

		}
		return tmp;
	}

	//查找节点x的前驱节点
	BSTNode* SearchPreSuccessor(BSTNode *x) {
		BSTNode *tmp = NULL; //同样指向当前节点的父节点
		//若x的左孩子非空，则返回左子树的最大节点
		if (x->lchild != NULL)
			return SearchMax(x->lchild);
		/*若x的左孩子为空，则一直向树的顶端寻找，直到节点P是其父节点Q的右孩子，则Q为该节点的前驱节点*/
		tmp = x->parent;
		while (tmp != NULL && x == tmp->lchild) {
			x = tmp;
			tmp = tmp->parent;
		}
		return tmp;
	}

	//向以节点T为根节点的BSTree中插入节点N,插入节点的位置始终为叶子节点
	void InserNode(BSTNode *&T, BSTNode *N) {
		BSTNode *x = T;         //T为指针的引用，可以改变BSTree本身
		BSTNode *tmp = NULL;      //用于保存插入位置的父节点
        /*沿树根一直向下找到可以插入的NIL节点*/
		while (x != NULL) {
			tmp = x;
			if (x->key < N->key)
				x = x->lchild;
			else
				x = x->rchild;
		}
		N->parent = tmp;
		if (tmp == NULL)       //如果该树为空则将新的节点N变为根节点
			T = N;
		else if (tmp->key < tmp->key)
			tmp->lchild = N;
		else
			tmp->rchild = N;
	}

	
	//用以N为根的子树来替换以O为根的子树，便于后续删除中的替换操作
	void ReplaceSubTree(BSTNode *&T, BSTNode *O, BSTNode *N) {
		/*将原来的子树根节点O的父节点的叶子指针指向新的子树根节点*/
		if (O->parent == NULL)
			T = N;             //若为空树则新节点N为根节点
		else if (O->parent->lchild == O)
			O->parent->lchild = N;
		else
			O->parent->rchild = N;
		/*将新的子树根节点的父指针指向原来子树根节点的指针*/
		if (N != NULL)
			N->parent = O->parent;
	}
	
	//删除以节点T为根节点的BSTree中的节点D
	/*首先判断待删除的节点D是否为叶子节点：
	----如果为叶子节点则直接删除
	----若不为叶子节点：
	------节点D只有一个子节点，则直接用子节点替换该节点
	------节点D有两个子节点，则先找到后继节点S（后继节点没有左子树），并判断其后继节点S是否为它的右子节点：
	--------若后继节点S为节点D的右子节点，则直接用节点S替换节点D，并保留节点S的右子树
	--------若后继节点S不为节点D的右子节点，则先用节点S的右子节点替换，再用节点S替换节点D*/
	void DeleteNode(BSTNode *&T, BSTNode *D) {
		BSTNode *tmp; //后继节点
		if (D->lchild == NULL)
			ReplaceSubTree(T, D, D->rchild);
		else if (D->rchild == NULL)
			ReplaceSubTree(T, D, D->lchild);
		else {
			tmp = SearchMin(D->rchild);
			if (tmp->parent != D) {
				ReplaceSubTree(T, tmp, tmp->rchild);
				tmp->lchild = D->lchild;
				tmp->lchild->parent = D->lchild->parent;
			}
			ReplaceSubTree(T, D, tmp);
			tmp->rchild = D->rchild;
			tmp->rchild->parent = D->rchild->parent;
		}
	}



};