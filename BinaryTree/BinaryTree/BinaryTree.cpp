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
	BSTNode(double k = 0.0, BSTNode *l = NULL, BSTNode *r = NULL, BSTNode *p = NULL) {
		key = k;
		lchild = l;
		rchild = r;
		parent = p;
	}
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
			BSTNode *tmp = NULL;
			tmp = stk.top();    //C++�е�pop����void�������Ҫʹ��topȡԪ��
			stk.pop();
			pre_vector.push_back(tmp->key);

			if (tmp->rchild != NULL)
				stk.push(tmp->rchild);
			if (tmp->lchild != NULL)
				stk.push(tmp->lchild);
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
	}

	/*----����ʵ�֣��Ƚ����ڵ���������ӽڵ�ѹ��ջ�������������������-----*/
	vector<double> IterInTraverse(BSTNode *x) {
		vector<double> in_vector;
		stack<BSTNode*> stk;
		BSTNode *root = x;

		do {
			while (root != NULL) {
				stk.push(root);
				root = root->lchild;
			}
			if (!stk.empty()) {
				BSTNode *tmp = NULL;
				tmp = stk.top();
				in_vector.push_back(tmp->key);
				root = root->rchild;
			}
		} while (!stk.empty() || root != NULL);  //���������ڵ�ʱstkջΪ�գ�����Ҫ������ȡ��������������root�ǿյ�ѭ������
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
		BSTNode *tmp = NULL;  //tmpָ��ʼ��ָ��ǰ�ڵ�ĸ��ڵ�
		//��x���Һ��ӷǿգ��򷵻�����������С�ڵ�
		if (x->rchild != NULL)
			return SearchMin(x->rchild);
		/*��x���Һ���Ϊ�գ���һֱ�����Ķ���Ѱ�ң�ֱ���ڵ�P���丸�ڵ�Q�����ӣ���QΪ�ýڵ�ĺ�̽ڵ�*/
		tmp = x->parent;
		while (tmp != NULL && x == tmp->rchild) {
			x = tmp;
			tmp = tmp->parent;

		}
		return tmp;
	}

	//���ҽڵ�x��ǰ���ڵ�
	BSTNode* SearchPreSuccessor(BSTNode *x) {
		BSTNode *tmp = NULL; //ͬ��ָ��ǰ�ڵ�ĸ��ڵ�
		//��x�����ӷǿգ��򷵻������������ڵ�
		if (x->lchild != NULL)
			return SearchMax(x->lchild);
		/*��x������Ϊ�գ���һֱ�����Ķ���Ѱ�ң�ֱ���ڵ�P���丸�ڵ�Q���Һ��ӣ���QΪ�ýڵ��ǰ���ڵ�*/
		tmp = x->parent;
		while (tmp != NULL && x == tmp->lchild) {
			x = tmp;
			tmp = tmp->parent;
		}
		return tmp;
	}

	//���Խڵ�TΪ���ڵ��BSTree�в���ڵ�N,����ڵ��λ��ʼ��ΪҶ�ӽڵ�
	void InserNode(BSTNode *&T, BSTNode *N) {
		BSTNode *x = T;         //TΪָ������ã����Ըı�BSTree����
		BSTNode *tmp = NULL;      //���ڱ������λ�õĸ��ڵ�
        /*������һֱ�����ҵ����Բ����NIL�ڵ�*/
		while (x != NULL) {
			tmp = x;
			if (x->key < N->key)
				x = x->lchild;
			else
				x = x->rchild;
		}
		N->parent = tmp;
		if (tmp == NULL)       //�������Ϊ�����µĽڵ�N��Ϊ���ڵ�
			T = N;
		else if (tmp->key < tmp->key)
			tmp->lchild = N;
		else
			tmp->rchild = N;
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
		BSTNode *tmp; //��̽ڵ�
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