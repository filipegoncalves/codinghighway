#ifndef RMQ_H
#define RMQ_H

#include <vector>

template<typename Value>
class RMQ {
public:
  RMQ(Value (*fun)(const Value v1, const Value v2),
      const std::vector<Value> input_arr) :
    f_ptr(fun), arr(input_arr) { }

  virtual Value query(const typename std::vector<Value>::size_type i,
		      const typename std::vector<Value>::size_type j) const = 0;

protected:
  Value (*f_ptr)(Value v1, Value v2);
  std::vector<Value> arr;
};

#endif
