#ifndef RMQ_SEGTREE_H
#define RMQ_SEGTREE_H

#include <vector>
#include "rmq.h"

template<typename Value>
class RMQ_SegTree : public RMQ<Value> {
public:

  RMQ_SegTree(Value (*f)(const Value v1, const Value v2),
	      const std::vector<Value> in_arr) :
    RMQ<Value>(f, in_arr), segtree(std::vector<Value>(4*in_arr.size()))
  {
    build_segtree(0, in_arr.size()-1, 0);
  }

  Value query(const typename std::vector<Value>::size_type i,
	      const typename std::vector<Value>::size_type j) const
  {
    return query_aux(0, this->arr.size()-1, i, j, 0);
  }

private:

  typedef typename std::vector<Value>::size_type vsize_t;
  std::vector<Value> segtree;

  Value build_segtree(vsize_t l, vsize_t r, vsize_t pos);
  Value query_aux(vsize_t l, vsize_t r, vsize_t in_l, vsize_t in_r, vsize_t pos) const;
  bool interval_intersects(vsize_t i, vsize_t j, vsize_t p, vsize_t k) const
  {
    return k > j ? p <= j : i <= k;
  }
};

template<typename Value>
Value RMQ_SegTree<Value>::build_segtree(vsize_t l, vsize_t r, vsize_t pos)
{
  if (l == r)
    return segtree[pos] = this->f_ptr(this->arr[l], this->arr[l]);

  vsize_t mid = l+(r-l)/2;
  vsize_t left = pos*2+1;
  vsize_t right = left+1;

  return segtree[pos] = this->f_ptr(build_segtree(l, mid, left),
				    build_segtree(mid+1, r, right));
}

template<typename Value>
Value RMQ_SegTree<Value>::query_aux(vsize_t l, vsize_t r,
				    vsize_t in_l, vsize_t in_r, vsize_t pos) const
{
  if (l == in_l && r == in_r)
    return segtree[pos];

  vsize_t mid = l+(r-l)/2;
  vsize_t left = pos*2+1;
  vsize_t right = left+1;

  bool recurse_left = interval_intersects(l, mid, in_l, in_r);
  bool recurse_right = interval_intersects(mid+1, r, in_l, in_r);

  if (recurse_left && recurse_right)
    return this->f_ptr(query_aux(l, mid, in_l, mid, left),
		       query_aux(mid+1, r, mid+1, in_r, right));
  else if (recurse_left)
    return query_aux(l, mid, in_l, in_r, left);
  else
    return query_aux(mid+1, r, in_l, in_r, right);
}

#endif
