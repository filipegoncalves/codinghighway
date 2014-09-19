#include <iostream>
#include <vector>
#include <limits>
#include "n_tree.h"
#include "lca.h"

using namespace std;

int main()
{
  cout << "How many nodes?" << endl;
  vector<N_Tree<int> >::size_type nodes;
  cin >> nodes;

  vector<N_Tree<int> > tree;
  for (vector<N_Tree<int> >::size_type i = 0; i < nodes; i++)
    tree.push_back(N_Tree<int>(i));

  cout << "Enter lines of the form:" << endl;
  cout << "i n ..." << endl;
  cout << "Where i is the node number, n the number of children, and then list every children." << endl;

  vector<N_Tree<int> >::size_type node, children;
  while (cin >> node >> children) {
    while (children--) {
      vector<N_Tree<int> >::size_type child;
      cin >> child;
      tree[node].add_child(&tree[child]);
    }
  }

  //  LCA_Solver<int> lca_solver(&tree[0], LCA_Solver<int>::Impl::RMQ_SegTree);
  LCA_Solver<int> lca_solver(&tree[0], LCA_Solver<int>::Impl::RMQ_SparseTable);

  cout << "Type in nodes ids for lca query." << endl;

  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  vector<N_Tree<int> >::size_type n1, n2;

  while (cin >> n1 >> n2)
    cout << "LCA(" << n1 << ", " << n2 << ") = " <<
      **(lca_solver.query(&tree[n1], &tree[n2])) << endl;

  return 0;
}
