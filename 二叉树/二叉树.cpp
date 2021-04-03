#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class BinaryTree
{
public:
    TreeNode* Node;
    vector<TreeNode*> List;

    BinaryTree() {
        Node = nullptr;
    }
    void PreInsertOrder(int data) {
        PreInsertOrder(Node, data);
    }
    void PreOrder(bool output = false) {
        List.clear();
        PreOrder(Node, output);
    }
    void InOrder(bool output = false) {
        List.clear();
        InOrder(Node, output);
    }
    void PostOrder(bool output = false) {
        List.clear();
        PostOrder(Node, output);
    }

    // 前序遍历，递归
    void PreOrder(TreeNode* root, bool output = false) {
        if (root == nullptr)
            return;
        if (output)
            cout << root->val << " ";
        else
            List.push_back(root);
        PreOrder(root->left, output);
        PreOrder(root->right, output);
    }

    // 中序遍历，递归
    void InOrder(TreeNode* root, bool output = false) {
        if (root == nullptr)
            return;
        InOrder(root->left, output);
        if (output)
            cout << root->val << " ";
        else
            List.push_back(root);
        InOrder(root->right, output);
    }

    // 后序遍历，递归
    void PostOrder(TreeNode* root, bool output = false) {
        if (root != nullptr) {
            PostOrder(root->left, output);
            PostOrder(root->right, output);
            if (output)
                cout << root->val << " ";
            else
                List.push_back(root);
        }
    }

    // 先序插入二叉树
    void PreInsertOrder(TreeNode* &root, int data) {
        if (root == nullptr) {
            root = new TreeNode(data);
            /*root = (TreeNode*)malloc(sizeof(TreeNode));     // new TreeNode(data);
            root->val = data;
            root->left = nullptr;
            root->right = nullptr;*/
            return;
        }
        if (data < root->val)
            PreInsertOrder(root->left, data);
        else
            PreInsertOrder(root->right, data);
    }

    // 通过先序遍历删除对应参数
    bool DeleteOrder(TreeNode* root, int data) {
        if (root == nullptr)
            return false;
        if (root->val == data) {

            return true;
        }
        if (DeleteOrder(root->left, data))
            return true;
        if(DeleteOrder(root->right, data))
            return true;
    }
};

int main()
{
    BinaryTree binaryTree;
    binaryTree.PreInsertOrder(3);
    binaryTree.PreInsertOrder(1);
    binaryTree.PreInsertOrder(2);
    binaryTree.PreInsertOrder(5);
    binaryTree.PreOrder(true);
    cout << endl;
    binaryTree.InOrder(true);
    cout << endl;
    binaryTree.PostOrder(false);
    for (int i = 0; i < binaryTree.List.size(); i++)
        cout << binaryTree.List[i]->val << " ";
}
