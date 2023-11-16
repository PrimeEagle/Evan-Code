// Run in Repl.it
// clang++-7 -pthread -std=c++17 -o bst_lca bst_lca.cpp; ./bst_lca < bst_lca1.in
//Run in zeus.cs.txstate.edu:
//g++ -pthread -o bst_lca bst_lca.cpp; ./bst_lca < bst_lca1.in
#include <iostream>
#include <sstream>
#include <vector>
/** QUESTION 6: LOWEST COMMON ANCESTOR **/

// EFFECTS: Returns the value of the lowest common ancestor of nodes l and m.
// 
// PSEUDOCODE:
// algorithm GetLCA
//   Input:
//   Output: 
//   Your pseudocode goes here.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
void GetDepthAndPathHelper(std::vector<int>& bst, int target, std::vector<int>& path) {
    // Implement this function.
    int target_index = 0;
    for (int i = 0; i < bst.size(); i++)
    {
        if (bst[i] == target)
        {
            target_index = i;
            path.push_back(bst[target_index]);
        }
    }
    while (target_index > 0)
    {
        target_index = (target_index - 1) / 2;
        path.push_back(bst[target_index]);
    }
    for (int k = 0; k <= (path.size() - 1) / 2; k++)
    {
        int temp_index = path[k];
        path[k] = path[path.size() - k - 1];
        path[path.size() - k - 1] = temp_index;
    }
}

int GetLCA(std::vector<int> &bst, int l, int m) {
  // Implement this function.
    int lca = 0;
    std::vector<int> path_one;
    std::vector<int> path_two;
    GetDepthAndPathHelper(bst, l, path_one);
    GetDepthAndPathHelper(bst, m, path_two);
   for(int i = 0; i < path_one.size(); i++)
   {
       if(path_one[i] == path_two[i])
       {
           lca = path_one[i];
       }
   }
  return lca;
}

/**** INSTRUCTOR NOTE: DO NOT MODIFY BELOW THIS LINE ****/

int main() {
  std::vector<int> bst;
  std::string input;
  getline(std::cin, input);
  std::stringstream iss(input);
  int number;
  while (iss >> number) {
    bst.push_back(number);
  }
  int l, m;
  std::cin >> l;
  std::cin >> m;
  
  std::vector<int> path;
  int lca = GetLCA(bst, l, m);

  std::cout << "lca = " << lca;
  return 0;
}
