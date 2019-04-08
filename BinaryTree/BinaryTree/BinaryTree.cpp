#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class BSTNode {
private:
	double key;
	BSTNode *lchild;
	BSTNode *rchild;
	BSTNode *parent;
	friend class BSTree;

public:
	//���캯�����ó�ʼ������
	BSTNode(double k = 0.0, BSTNode *l = NULL, BSTNode *r = NULL, BSTNode *p = NULL)  :key(k), lchild(l), rchild(r), parent(p) {}
};

class BSTree {
private:
	BSTNode *root; //���ڵ�

	/*----------�ڲ��ӿڣ�����Ľڵ������Ϊ���ڵ㣩---------*/

	//�������
	/*----�ݹ�ʵ��-----*/
	vector<double> PreTraverse(BSTNode *x) {
		vector<double> pre_vector; ///�洢�����������
		if (x != NULL) {
			pre_vector.push_back(x->key);
			//cout<< x->key << " ";
			PreTraverse(x->lchild);
			PreTraverse(x->rchild);
		}
		return pre_vector;
	}

	/*----����ʵ�֣����ö�ջ�ṹ��-----*/
	vector<double> IterPreTraverse(BSTNode *x) {
		vector<double> pre_vector;
		stack<BSTNode*> stk;
		stk.push(x);             //�Ƚ�����ջ
	    
		while (!stk.empty()) {
			BSTNode *curr = NULL;
			curr = stk.top();    //C++�е�pop����void�������Ҫʹ��topȡԪ��
			stk.pop();
			pre_vector.push_back(curr->key);

			if (curr->rchild != NULL)
				stk.push(curr->rchild);
			if (curr->lchild != NULL)
				stk.push(curr->lchild);
		}
		return pre_vector;
	}

	//�������
	/*----�ݹ�ʵ��-----*/
	vector<double> InTraverse(BSTNode *x) {
		vector<double> in_vector;
		if (x != NULL) {
			InTraverse(x->parent);
			in_vector.push_back(x->key);
			//cout<< x->key << " ";
			InTraverse(x->rchild);
		}
		return in_vector;
	}

	/*----����ʵ�֣��Ƚ����ڵ���������ӽڵ�ѹ��ջ�������������������-----*/
	vector<double> IterInTraverse(BSTNode *x) {
		vector<double> in_vector;
		stack<BSTNode*> stk;

		do {
			while (x != NULL) {
				stk.push(x);
				x = x->lchild;
			}
			if (!stk.empty()) {
				BSTNode *curr = NULL;
				curr = stk.top();
				in_vector.push_back(curr->key);
				x = x->rchild;
			}
		} while (!stk.empty() || x != NULL);  //���������ڵ�ʱstkջΪ�գ�����Ҫ������ȡ��������������x�ǿյ�ѭ������
		return in_vector;
	}

    //�������
	/*----�ݹ�ʵ��-----*/
	vector<double> PostTraverse(BSTNode *x) {
		vector<double> post_vector;
		if (x != NULL) {
			PostTraverse(x->lchild);
			PostTraverse(x->rchild);
			post_vector.push_back(x->key);
			//cout<< x->key << " ";
		}
		return post_vector;
	}
	/*-------����ʵ��--------*/
	/*˼·һ��ǰ�������˳����������,��������˳���������У�����ʵ�ֺ��������һ�ַ�������ʵ��������ı�����Ȼ��ѱ����Ľ������*/
	/*˼·�����Ƚ����ڵ���ջ����ѹ��δ���������������ȡδ������������preָ���¼��һ���ڵ��Ƿ�Ϊ��ǰ�ڵ���ӽڵ�*/
	vector<double> IterPostTraverse(BSTNode *x) {
		vector<double> post_vector;
		stack<BSTNode*> stk;
		BSTNode *pre = x;
		BSTNode *curr = NULL;
		stk.push(x);

		while (!stk.empty()) {
			curr = stk.top();
			//����ǰ�ڵ���δ�������ӽڵ�����ѹ��ջ
			if (curr->lchild != NULL && pre != curr->lchild && pre != curr->rchild)
				stk.push(curr->lchild);
			//����ǰ�ڵ�û��δ�����ӽڵ㣬����δ�����ӽڵ㣬ͬ������ѹ��ջ
			else if (curr->rchild != NULL && pre != curr->rchild)
				stk.push(curr->rchild);
			//��ǰ�ڵ�������������Ѷ�ȡ�����ߵ�ǰ�ڵ�ΪҶ�ӽڵ㣬��ֱ��pop
			else {
				post_vector.push_back(curr->key);
				pre = curr;
				stk.pop();
			}
		}
		return post_vector;
	}


	//���Ҽ�k���������򷵻�NTL
	/*----�ݹ�ʵ��-----*/
	BSTNode* SearchKey(BSTNode *x, double k) {
		if (x == NULL || k == x->key)
			return x;
		if (k < x->key)
			  return SearchKey(x->lchild, k);
		else  return SearchKey(x->rchild, k);

	}

	/*---����ʵ��-----*/
	BSTNode* IterSearchKey(BSTNode *x, double k) {
		while (x != NULL && x->key != k) {
			if (x->key > k)
				x = x->lchild;
			else
				x = x->rchild;
		}
		return x;
	}


	//������xΪ���ڵ����������Сkey
	BSTNode* SearchMin(BSTNode *x) {
		while (x->lchild != NULL) {
			x = x->lchild;
		}
		return x;
	}

	//������xΪ���ڵ�����������key
	BSTNode* SearchMax(BSTNode *x) {
		while (x->rchild != NULL) {
			x = x->rchild;
		}
		return x;
	}

	//���ҽڵ�x�ĺ�̽ڵ�
	BSTNode* SearchSuccessor(BSTNode *x) {
		BSTNode *curr = NULL;  //currָ��ʼ��ָ��ǰ�ڵ�ĸ��ڵ�
		//��x���Һ��ӷǿգ��򷵻�����������С�ڵ�
		if (x->rchild != NULL)
			return SearchMin(x->rchild);
		/*��x���Һ���Ϊ�գ���һֱ�����Ķ���Ѱ�ң�ֱ���ڵ�P���丸�ڵ�Q�����ӣ���QΪ�ýڵ�ĺ�̽ڵ�*/
		curr = x->parent;
		while (curr != NULL && x == curr->rchild) {
			x = curr;
			curr = curr->parent;

		}
		return curr;
	}

	//���ҽڵ�x��ǰ���ڵ�
	BSTNode* SearchPreSuccessor(BSTNode *x) {
		BSTNode *curr = NULL; //ͬ��ָ��ǰ�ڵ�ĸ��ڵ�
		//��x�����ӷǿգ��򷵻������������ڵ�
		if (x->lchild != NULL)
			return SearchMax(x->lchild);
		/*��x������Ϊ�գ���һֱ�����Ķ���Ѱ�ң�ֱ���ڵ�P���丸�ڵ�Q���Һ��ӣ���QΪ�ýڵ��ǰ���ڵ�*/
		curr = x->parent;
		while (curr != NULL && x == curr->lchild) {
			x = curr;
			curr = curr->parent;
		}
		return curr;
	}

	//���Խڵ�TΪ���ڵ��BSTree�в���ڵ�N,����ڵ��λ��ʼ��ΪҶ�ӽڵ�
	void InserNode(BSTNode *&T, BSTNode *N) {
		BSTNode *x = T;         //TΪָ������ã����Ըı�BSTree����
		BSTNode *curr = NULL;      //���ڱ������λ�õĸ��ڵ�
        /*������һֱ�����ҵ����Բ����NIL�ڵ�*/
		while (x != NULL) {
			curr = x;
			if (x->key < N->key)
				x = x->lchild;
			else
				x = x->rchild;
		}
		N->parent = curr;
		if (curr == NULL)       //�������Ϊ�����µĽڵ�N��Ϊ���ڵ�
			T = N;
		else if (N->key < curr->key)
			curr->lchild = N;
		else
			curr->rchild = N;
	}

	
	//����NΪ�����������滻��OΪ�������������ں���ɾ���е��滻����
	void ReplaceSubTree(BSTNode *&T, BSTNode *O, BSTNode *N) {
		/*��ԭ�����������ڵ�O�ĸ��ڵ��Ҷ��ָ��ָ���µ��������ڵ�*/
		if (O->parent == NULL)
			T = N;             //��Ϊ�������½ڵ�NΪ���ڵ�
		else if (O->parent->lchild == O)
			O->parent->lchild = N;
		else
			O->parent->rchild = N;
		/*���µ��������ڵ�ĸ�ָ��ָ��ԭ���������ڵ��ָ��*/
		if (N != NULL)
			N->parent = O->parent;
	}
	
	//ɾ���Խڵ�TΪ���ڵ��BSTree�еĽڵ�D
	/*�����жϴ�ɾ���Ľڵ�D�Ƿ�ΪҶ�ӽڵ㣺
	----���ΪҶ�ӽڵ���ֱ��ɾ��
	----����ΪҶ�ӽڵ㣺
	------�ڵ�Dֻ��һ���ӽڵ㣬��ֱ�����ӽڵ��滻�ýڵ�
	------�ڵ�D�������ӽڵ㣬�����ҵ���̽ڵ�S����̽ڵ�û���������������ж����̽ڵ�S�Ƿ�Ϊ�������ӽڵ㣺
	--------����̽ڵ�SΪ�ڵ�D�����ӽڵ㣬��ֱ���ýڵ�S�滻�ڵ�D���������ڵ�S��������
	--------����̽ڵ�S��Ϊ�ڵ�D�����ӽڵ㣬�����ýڵ�S�����ӽڵ��滻�����ýڵ�S�滻�ڵ�D*/
	void DeleteNode(BSTNode *&T, BSTNode *D) {
		BSTNode *curr; //��̽ڵ�
		if (D->lchild == NULL)
			ReplaceSubTree(T, D, D->rchild);
		else if (D->rchild == NULL)
			ReplaceSubTree(T, D, D->lchild);
		else {
			curr = SearchMin(D->rchild);
			if (curr->parent != D) {
				ReplaceSubTree(T, curr, curr->rchild);
				curr->lchild = D->lchild;
				curr->lchild->parent = D->lchild->parent;
			}
			ReplaceSubTree(T, D, curr);
			curr->rchild = D->rchild;
			curr->rchild->parent = D->rchild->parent;
		}
	}


	/*----------�ⲿ�ӿڣ�����Ľڵ������Ϊ���ڵ㣩---------*/
public:
	BSTree() :root(NULL){}

	//����
	void preTraverse() {
		IterPreTraverse(root);
	}
	void inTraverse() {
		IterInTraverse(root);
	}
	void postTraverse() {
		IterPostTraverse(root);
	}
};