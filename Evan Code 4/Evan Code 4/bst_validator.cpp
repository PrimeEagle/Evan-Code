// Run in Repl.it 
// clang++-7 -pthread -std=c++17 -o bst_validator bst_validator.cpp; ./bst_validator < bst_validator1.in
//Run in zeus.cs.txstate.edu:
//g++ -pthread -o bst_validator bst_validator.cpp; ./bst_validator < bst_validator1.in

#include <iostream>
#include <sstream>
#include <vector>


void GetSubtree(std::vector<int>& binary_tree, std::vector<int>& result, int index, int depth = 0)
{
	int tree_size = (int)binary_tree.size();
	int left_child_idx;
	int right_child_idx;
	int num_children;

	if (index < tree_size)
	{
		result.push_back(binary_tree[index]);
		num_children = (depth + 1) * 2;

		for (int c = index; c < num_children; c = c + 2)
		{
			left_child_idx = 2 * index + 1;
			right_child_idx = 2 * index + 2;

			if (left_child_idx < tree_size)
			{
				result.push_back(binary_tree[left_child_idx]);
			}

			if (right_child_idx < tree_size)
			{
				result.push_back(binary_tree[right_child_idx]);
			}
		}

		for (int c = index; c < num_children; c = c + 2)
		{
			left_child_idx = 2 * index + 1;
			right_child_idx = 2 * index + 2;

			int left_subchild_idx = 2 * left_child_idx + 1;
			int right_subchild_idx = 2 * left_child_idx + 2;

			if (left_subchild_idx < tree_size)
			{
				GetSubtree(binary_tree, result, left_subchild_idx, depth + 1);
			}

			if (right_subchild_idx < tree_size)
			{
				GetSubtree(binary_tree, result, right_subchild_idx, depth + 1);
			}

			left_subchild_idx = 2 * right_child_idx + 1;
			right_subchild_idx = 2 * right_child_idx + 2;

			if (left_subchild_idx < tree_size)
			{
				GetSubtree(binary_tree, result, left_subchild_idx, depth + 1);
			}

			if (right_subchild_idx < tree_size)
			{
				GetSubtree(binary_tree, result, right_subchild_idx, depth + 1);
			}
		}
	}
}

/** QUESTION 4: BST VALIDATOR **/

// EFFECTS: Returns true if the tree is a valid BST, or false otherwise.
// 
// PSEUDOCODE:
// algorithm IsBST
//   Input:
//   Output: 
//   Your pseudocode goes here.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
bool IsBST(std::vector<int>& binary_tree) {
	// Implement this function.
	bool bst = true;
	int tree_size = (int)binary_tree.size();

	int parent_val;
	int left_child_val;
	int right_child_val;

	if (tree_size > 0)
	{
		int left_child_idx = 1;
		int right_child_idx = 2;

		parent_val = binary_tree[0];

		if (left_child_idx < tree_size)
		{
			left_child_val = binary_tree[left_child_idx];
		}

		if (right_child_idx < tree_size)
		{
			right_child_val = binary_tree[right_child_idx];
		}

		bool left_valid = false;
		bool right_valid = false;
		bool all_left_children_valid = true;
		bool all_right_children_valid = true;
		std::vector<int> left_subtree = std::vector<int>();
		std::vector<int> right_subtree = std::vector<int>();

		GetSubtree(binary_tree, left_subtree, left_child_idx);
		for (int i = 0; i < left_subtree.size(); i++)
		{
			if (left_subtree[i] >= parent_val)
			{
				all_left_children_valid = false;
				break;
			}
		}

		if (left_child_idx < tree_size && left_child_val < parent_val && all_left_children_valid && IsBST(left_subtree))
		{
			left_valid = true;
		}

		GetSubtree(binary_tree, right_subtree, right_child_idx);
		for (int i = 0; i < right_subtree.size(); i++)
		{
			if (right_subtree[i] <= parent_val)
			{
				all_right_children_valid = false;
				break;
			}
		}

		if (right_child_idx < tree_size && right_child_val > parent_val && all_right_children_valid && IsBST(right_subtree))
		{
			right_valid = true;
		}

		bst = (tree_size < 2) || (left_valid && right_valid);
	}

	return bst;
}

/**** INSTRUCTOR NOTE: DO NOT MODIFY BELOW THIS LINE ****/

int main() {
	std::vector<int> binary_tree;
	std::string input;
	getline(std::cin, input);

	std::stringstream iss(input);
	int number;
	while (iss >> number) {
		binary_tree.push_back(number);
	}
	if (IsBST(binary_tree)) {
		std::cout << "True";
	}
	else {
		std::cout << "False";
	}
	return 0;
}
