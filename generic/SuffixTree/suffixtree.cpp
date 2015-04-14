#include <ostream>
#include <algorithm>
#include <cassert>
#include <map>
#include <vector>
#include <string>
#include <cstddef>
#include <iostream>

struct SuffixTreeNode {
private:
  int path_start;
  int string_depth;
  SuffixTreeNode *suffix_link;
  std::map<char, SuffixTreeNode*> children;

public:
  SuffixTreeNode(int start, int str_depth) :
    path_start(start), string_depth(str_depth), suffix_link(NULL) { }
  SuffixTreeNode() : path_start(0), string_depth(0), suffix_link(NULL) { }

  int str_depth(void) const { return string_depth; }
  void set_str_depth(int str_depth) { string_depth = str_depth; }

  int head(void) const { return path_start; }
  void set_head(int head) { path_start = head; }

  void link_to(SuffixTreeNode *target) { suffix_link = target; }
  SuffixTreeNode *slink(void) const { return this->suffix_link; }

  SuffixTreeNode *child(char letter) const;

  void add_child(char letter, SuffixTreeNode *new_node) { children[letter] = new_node; }
  void erase_child(char letter) { children.erase(letter); }

  const std::map<char, SuffixTreeNode*> &get_children(void) const { return children; }
};

struct SuffixTreePoint {
private:
  SuffixTreeNode *above;
  SuffixTreeNode *below;
  int string_depth;

public:

  SuffixTreePoint(SuffixTreeNode *above, SuffixTreeNode *below, int str_depth) :
    above(above), below(below), string_depth(str_depth) { }

  bool is_node(void) const { return this->above == this->below; }
  // Only valid if `is_node()` returns true
  const SuffixTreeNode *get_node(void) const { assert(is_node()); return this->above; }

  SuffixTreeNode *node_above(void) const { return this->above; }
  void set_node_above(SuffixTreeNode *new_above) { this->above = new_above; }

  SuffixTreeNode *node_below(void) const { return this->below; }
  void set_node_below(SuffixTreeNode *new_below) { this->below = new_below; }

  int str_depth(void) const { return this->string_depth; }
  void set_str_depth(int new_depth) { this->string_depth = new_depth; }
};

// TODO Think about making `SuffixTreePoint` an attribute of `SuffixTree`
class SuffixTree {

  std::vector<SuffixTreeNode> nodes_buff;
  std::vector<SuffixTreeNode>::size_type next_node;
  std::string text;
  SuffixTreeNode *root;
  SuffixTreeNode *last_internal_added;

private:
  SuffixTreeNode *get_free_node(int path_start, int string_depth);
  void build_suffixtree(void);
  SuffixTreeNode *can_descend(SuffixTreePoint *point, char letter) const;
  void add_suffix(SuffixTreePoint *point, std::string::size_type curr_start);
  void suffix_jump(SuffixTreePoint *point);
  void descend(SuffixTreePoint *point, char letter);

public:
  SuffixTree(const std::string &input);
  friend std::ostream &operator<<(std::ostream &os, const SuffixTree &stree);
  friend std::ostream &dump_node(std::ostream &os, SuffixTreeNode *node, unsigned depth, const SuffixTree &tree);
};




// Implementation

using namespace std;

SuffixTreeNode *SuffixTree::get_free_node(int path_start, int string_depth) {
  assert(next_node < nodes_buff.size());

  SuffixTreeNode *ret = &nodes_buff[next_node++];
  ret->set_head(path_start);
  ret->set_str_depth(string_depth);

  return ret;
}

SuffixTreeNode *SuffixTreeNode::child(char letter) const {
  map<char, SuffixTreeNode*>::const_iterator it = children.find(letter);
  return it != children.end() ? it->second : NULL;
}

SuffixTree::SuffixTree(const string &input) {

  assert(find(input.begin(), input.end()-1, input[input.size()-1]) == input.end()-1);

  /* Text of size `n`:
   * There are `n` leaves; at most `n-1` internal nodes, 1 root,
   * and 1 pseudo-node to serve as root's suffix link
   * `n+n-1+1+1 = 2*n+1`
   */
  nodes_buff.resize(2*input.size()+1);

  next_node = 0;
  text = input;
  last_internal_added = NULL;
  root = get_free_node(0, 0);
  root->link_to(get_free_node(0, -1));

  // The core algorithm
  build_suffixtree();

}

void SuffixTree::build_suffixtree(void) {
  string::size_type text_i = 0;
  string::size_type curr_start = 0;

  SuffixTreePoint curr_point(root, root, 0);
  const SuffixTreeNode *next_node;
  while (text_i < text.size()) {
    next_node = can_descend(&curr_point, text[text_i]);

    while (next_node == NULL) {
      add_suffix(&curr_point, curr_start);
      suffix_jump(&curr_point);
      curr_start++;
      next_node = can_descend(&curr_point, text[text_i]);
    }

    descend(&curr_point, text[text_i]);
    text_i++;
  }

}

SuffixTreeNode *SuffixTree::can_descend(SuffixTreePoint *point, char letter) const {
  int next_i;

  if (!point->is_node()) {
    next_i = point->node_below()->head() + point->str_depth();
    assert(next_i > 0);
    assert((string::size_type) next_i < text.size());
    return text[next_i] == letter ? point->node_below() : NULL;
  }

  // Sentinel boundary case
  if (point->get_node() == root->slink())
    return root;

  // If we get here, `point` is a node, so we just need to see
  // if it's possible to descend with `letter` on that node
  return point->get_node()->child(letter);
}

void SuffixTree::add_suffix(SuffixTreePoint *point, string::size_type start) {
  SuffixTreeNode *father;

  if (!point->is_node()) {

    /* We need to create a new internal node */
    SuffixTreeNode *new_internal = get_free_node(start, point->str_depth());

    string::size_type below_i = point->node_below()->head()+point->node_above()->str_depth();
    assert(below_i < text.size());
    assert(point->node_above()->child(text[below_i]) != NULL);
    point->node_above()->erase_child(text[below_i]);
    point->node_above()->add_child(text[below_i], new_internal);

    string::size_type internal_i = point->node_below()->head()+point->str_depth();
    assert(internal_i < text.size());
    new_internal->add_child(text[internal_i], point->node_below());

    if (last_internal_added != NULL)
      last_internal_added->link_to(new_internal);

    last_internal_added = new_internal;
    father = new_internal;

  } else {
    father = point->node_above();
  }

  SuffixTreeNode *new_leaf = get_free_node(start, text.size()-start);
  string::size_type leaf_i = new_leaf->head()+father->str_depth();
  assert(leaf_i < text.size());
  father->add_child(text[leaf_i], new_leaf);
}

void SuffixTree::suffix_jump(SuffixTreePoint *point) {
  SuffixTreePoint old_point = *point;

  assert(old_point.node_above()->slink() != NULL);

  point->set_node_above(old_point.node_above()->slink());
  point->set_node_below(old_point.node_above()->slink());
  point->set_str_depth(point->node_above()->str_depth());

  assert(point->str_depth() == old_point.node_above()->str_depth()-1);

  while (point->str_depth() != old_point.str_depth()-1) {
    string::size_type text_i = old_point.node_below()->head()+point->str_depth()+1;
    point->set_node_below(can_descend(point, text[text_i]));

    assert(point->node_below() != NULL);

    int diff1 = point->node_below()->str_depth() - point->node_above()->str_depth();
    int diff2 = old_point.str_depth()-1 - point->node_above()->str_depth();

    if (diff1 <= diff2) {
      point->set_str_depth(point->str_depth()+diff1);
      point->set_node_above(point->node_below());
    } else {
      point->set_str_depth(point->str_depth()+diff2);
    }
  }

  /* Now on the new spot. Any suffix links to create? */
  if (point->is_node() && last_internal_added != NULL) {
    last_internal_added->link_to(point->node_above());
    last_internal_added = NULL;
  }
}

void SuffixTree::descend(SuffixTreePoint *point, char letter) {
  SuffixTreeNode *new_below = can_descend(point, letter);

  assert(new_below != NULL);
  if (new_below->str_depth() != point->str_depth()+1) {
    point->set_node_below(new_below);
  } else {
    point->set_node_above(new_below);
    point->set_node_below(new_below);
  }
  point->set_str_depth(point->str_depth()+1);
}

ostream &operator<<(ostream &os, const SuffixTree &stree) {

  os << "~~~ SUFFIX TREE ~~~" << endl;
  os << "Text:\t\t" << stree.text << endl;
  os << "Nodes in use:\t" << stree.next_node << endl;
  os << "(Nodes in use include the sentinel, the root, internal nodes, and leaves)" << endl;
  os << "Printing suffix tree; root is node 0" << endl;

  return dump_node(os, stree.root, 0, stree);
}

ostream &dump_node(ostream &os, SuffixTreeNode *node, unsigned depth, const SuffixTree &tree) {
  string spaces(4*depth+1, ' ');

  os << spaces << "*** Node " << node-tree.root << "; ";
  if (node->slink() != NULL)
    os << "suffix link = " << node->slink()-tree.root;
  else
    os << "no suffix link.";
  os << endl;

  const map<char, SuffixTreeNode*> &children = node->get_children();
  for (map<char, SuffixTreeNode*>::const_iterator it = children.begin();
       it != children.end();
       it++) {
    string sub_str = tree.text.substr(it->second->head()+node->str_depth(),
				      it->second->str_depth() - node->str_depth());
    os << spaces << sub_str << " -> " << it->second-tree.root << endl;
    if (!dump_node(os, it->second, depth+1, tree))
      return os;
  }

  os << spaces << "*** End of node " << node-tree.root << endl;

  return os;
}

int main(void) {
  cout << "Enter a string terminated with $" << endl;
  cout << "(or with another character that is not part of the string's alphabet(" << endl;

  while (1) {
    string text;
    cin >> text;
    SuffixTree my_tree(text);
    cout << my_tree;
  }

  return 0;
}
