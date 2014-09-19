#ifndef N_TREE_H
#define N_TREE_H

#include <iostream>

template<typename T>
class N_Tree {
public:

  typedef typename std::vector<N_Tree *>::const_iterator const_iterator;
  typedef typename std::vector<N_Tree *>::iterator iterator;
  typedef unsigned long long size_type;

  N_Tree(T value) : node_value(value) { }

  void add_child(N_Tree *child) {
    children.push_back(child);
  }

  const_iterator begin() const
  {
    return children.begin();
  }

  iterator begin()
  {
    return children.begin();
  }

  iterator end()
  {
    return children.end();
  }

  const_iterator end() const
  {
    return children.end();
  }

  T &operator*()
  {
    return node_value;
  }

private:
  T node_value;
  std::vector<N_Tree *> children;
};
#endif
