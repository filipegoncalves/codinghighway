#ifndef LCA_H
#define LCA_H

#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "rmq_sparse_table.h"
#include "rmq_segtree.h"
#include "n_tree.h"

template<typename Value>
class LCA_Solver {
public:
  enum class Impl { RMQ_SegTree, RMQ_SparseTable };

  LCA_Solver(N_Tree<Value> *root, Impl rmq_impl) : tree_root(root)
  {
    reduce_to_rmq(rmq_impl);
  }

  N_Tree<Value> *query(N_Tree<Value> *n1, N_Tree<Value> *n2)
  {
    typename std::vector<RMQ_Elem>::size_type i, j;
    i = occurrences[n1];
    j = occurrences[n2];

    return rmq_solver->query(std::min(i, j), std::max(i, j)).node;
  }
  
private:

  struct RMQ_Elem {
    typename N_Tree<Value>::size_type depth;
    N_Tree<Value> *node;
    
    RMQ_Elem(typename N_Tree<Value>::size_type d, N_Tree<Value> *n) :
      depth(d), node(n) { }
    RMQ_Elem() : depth(0), node(NULL) { }

  };

  N_Tree<Value> *tree_root;
  RMQ<RMQ_Elem> *rmq_solver;
  std::vector<RMQ_Elem> rmq_input_array;
  std::map<N_Tree<Value> *, typename std::vector<RMQ_Elem>::size_type> occurrences;

  static RMQ_Elem rmq_f_min(const RMQ_Elem v1, const RMQ_Elem v2)
  {
    return v1.depth < v2.depth ? v1 : v2;
  }

  void reduce_to_rmq(Impl rmq_impl)
  {

    build_rmq_array(tree_root, 0);
    
    switch (rmq_impl) {
    case Impl::RMQ_SegTree:
      rmq_solver = new RMQ_SegTree<RMQ_Elem>(rmq_f_min, rmq_input_array);
      break;
    case Impl::RMQ_SparseTable:
      rmq_solver = new RMQ_SparseTable<RMQ_Elem>(rmq_f_min, rmq_input_array);
      break;
    default:
      throw std::invalid_argument("rmq_impl"); // Should never happen, we're using enum class
      }

  }

  void build_rmq_array(N_Tree<Value> *node, typename N_Tree<Value>::size_type depth)
  {
    rmq_input_array.push_back(RMQ_Elem(depth, node));
    occurrences[node] = rmq_input_array.size()-1;

    for (typename N_Tree<Value>::const_iterator it = node->begin();
	 it != node->end();
	 it++) {
      build_rmq_array(*it, depth+1);
      rmq_input_array.push_back(RMQ_Elem(depth, node));
    }
  }
  
};

#endif
