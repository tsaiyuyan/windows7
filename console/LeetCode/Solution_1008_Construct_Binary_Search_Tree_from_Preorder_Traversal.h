#pragma once
class Solution_1008_Construct_Binary_Search_Tree_from_Preorder_Traversal : public Solution
{
public:
	/**
	* Definition for a binary tree node.
	* struct TreeNode {
	*     int val;
	*     TreeNode *left;
	*     TreeNode *right;
	*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	* };
	*/
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	void tree_insert(TreeNode **node, int val)
	{
		if (*node == nullptr)
		{
			*node = new TreeNode(val);
			return;
		}

		TreeNode *pre, *cur = *node;

		while (cur)
		{
			pre = cur;
			cur = (val < cur->val) ? cur->left : cur->right;
		}

		if (val > pre->val)
			pre->right = new TreeNode(val);
		else if (val < pre->val)
			pre->left = new TreeNode(val);
	}

	TreeNode* bstFromPreorder(vector<int>& preorder) {
		TreeNode *root = nullptr;

		for (auto val : preorder)
		{
			tree_insert(&root, val);
		}
		return root;
	}
	int test()
	{
		vector<int> preorder = { 8,5,1,7,10,12 };
		auto res = bstFromPreorder(preorder);//"race a car""0P"
		return 0;
	}
};
