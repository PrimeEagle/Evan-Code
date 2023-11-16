// Run in Repl.it
// clang++-7 -pthread -std=c++17 -o bst_depth bst_depth.cpp; ./bst_depth < bst_depth1.in
//Run in zeus.cs.txstate.edu:
//g++ -pthread -o bst_depth bst_depth.cpp; ./bst_depth < bst_depth1.in

#include <iostream>
#include <sstream>
#include <vector>

/** QUESTION 5: DEPTH AND PATH **/

// EFFECTS: Returns the depth of the target node. Modifies the path vector
//          so that it contains the node values in the path from the root to
//          the target node.
// 
// PSEUDOCODE:
// algorithm GetDepthAndPath
//   Input:
//   Output: 
//   Your pseudocode goes here.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
int GetDepthAndPath(std::vector<int> &bst, int target, std::vector<int> &path) {
  // Implement this function.
    int target_index = 0;
    int depth = 0;
    for(int i = 0; i < bst.size(); i++)
    {
        if(bst[i] == target)
        {
            target_index = i;
            path.push_back(bst[target_index]);
        }
    }
    while(target_index > 0)
    {
        target_index = (target_index - 1) / 2;
        path.push_back(bst[target_index]);
        depth++;
    }
    for(int k = 0; k <= (path.size() - 1) / 2; k++)
    {
        int temp_index = path[k];
        path[k] = path[path.size() - k - 1];
        path[path.size() - k - 1] = temp_index;
    }
  return depth;
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
  int target;
  std::cin >> target;
  
  std::vector<int> path;
  int depth = GetDepthAndPath(bst, target, path);

  std::cout << "depth = " << depth << std::endl;
  std::cout << "path = ";
  for(int i = 0; i < path.size(); i++) {
    std::cout << path[i] ;
    if (i < path.size() - 1) {
      std::cout << " ";
    }
  }
  return 0;
}
