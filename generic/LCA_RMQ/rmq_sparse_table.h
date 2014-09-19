#ifndef RMQ_SPARSE_TABLE_H
#define RMQ_SPARSE_TABLE_H

#include <vector>
#include <stdexcept>
#include "rmq.h"

template<typename Value>
class RMQ_SparseTable : public RMQ<Value> {
  public:

  RMQ_SparseTable(Value (*f)(const Value v1, const Value v2),
		  const std::vector<Value> in_arr) :
    RMQ<Value>(f, in_arr)
  {
    build_rmq_array();
  }

  Value query(const typename std::vector<Value>::size_type i,
	      const typename std::vector<Value>::size_type j) const
  {
    typename std::vector<Value>::size_type l = int_log(j-i+1);
    return this->f_ptr(rmq_array[i][l], rmq_array[j+1-(1<<l)][l]);
  }

private:
  std::vector<std::vector<Value> > rmq_array;

  typename std::vector<Value>::size_type int_log(typename std::vector<Value>::size_type val) const;
  void build_rmq_array();
};

template<typename Value>
typename std::vector<Value>::size_type RMQ_SparseTable<Value>::int_log(typename std::vector<Value>::size_type val) const
{

  if (val == 0)
    throw std::invalid_argument("val");

  typename std::vector<Value>::size_type shifts = 0;
  for (; val != 1; val >>= 1, shifts++);
  return shifts;

}

template<typename Value>
void RMQ_SparseTable<Value>::build_rmq_array()
{

  for (typename std::vector<Value>::size_type i = 0; i < this->arr.size(); i++) {
    rmq_array.push_back(std::vector<Value>());
    rmq_array[rmq_array.size()-1].push_back(this->f_ptr(this->arr[i], this->arr[i]));
  }

  for (typename std::vector<Value>::size_type j = 1; (1U << j) <= this->arr.size(); j++)
    for (typename std::vector<Value>::size_type i = 0; i + (1 << j) - 1 < this->arr.size(); i++)
      rmq_array[i].push_back(this->f_ptr(rmq_array[i][j-1], rmq_array[i+(1 << (j-1))][j-1]));

}

#endif
