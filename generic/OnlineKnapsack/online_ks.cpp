#include <algorithm>
#include <set>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


template<typename T>
class KnapsackSolution {
private:

	class ElementPtrComparator {
	public:
		bool operator()(T* const &lhs, T* const &rhs) {
			return *lhs < *rhs;
		}
	};

	unsigned total_value;
	set<T*, ElementPtrComparator> elements;

public:
	typedef typename set<T*, ElementPtrComparator>::const_iterator const_iterator;
	typedef typename set<T*, ElementPtrComparator>::size_type size_type;

	KnapsackSolution() : total_value(0) { }

	unsigned get_value() const { return total_value; }

	typename KnapsackSolution::const_iterator begin() const {
		return elements.begin();
	}

	typename KnapsackSolution::const_iterator end() const {
		return elements.end();
	}

	typename KnapsackSolution::size_type size() const {
		return elements.size();
	}

	void add_element(T *new_element) {
		total_value += new_element->value();
		elements.insert(new_element);
	}

	bool operator<(const KnapsackSolution &rhs) const {
		if (total_value < rhs.get_value())
			return true;
		if (elements.size() > rhs.size())
			return true;
		if (total_value == rhs.get_value() && elements.size() == rhs.size())
			return lexicographical_compare(rhs.begin(), rhs.end(),
						       this->begin(), this->end());
		return false;
	}
};

template<typename T>
KnapsackSolution<T> operator+(KnapsackSolution<T> lhs, const KnapsackSolution<T> &rhs) {
	for (typename KnapsackSolution<T>::const_iterator it = rhs.begin();
	     it != rhs.end();
	     it++)
		lhs.add_element(*it);
	return lhs;
}

template<typename T>
class OnlineKnapsackSolver {
private:
	vector<T*> elem_buff;
	typename vector<T*>::size_type elem_head;
	typename vector<T*>::size_type elem_tail;
	typename vector<T*>::size_type elem_buff_sz;

	vector<vector<KnapsackSolution<T> > > insert_tbl;
	vector<vector<KnapsackSolution<T> > > delete_tbl;
	typename vector<vector<KnapsackSolution<T> > >::size_type insert_cnt;
	typename vector<vector<KnapsackSolution<T> > >::size_type delete_cnt;
	
	typename vector<T*>::size_type max_elements;

	unsigned knapsack_capacity;

	KnapsackSolution<T> solution_buff;

public:
	typedef typename vector<T*>::size_type size_type;
	OnlineKnapsackSolver(size_type nmax_elements, unsigned nknapsack_capacity) :
		max_elements(nmax_elements), knapsack_capacity(nknapsack_capacity) {

		elem_buff = vector<T*>(max_elements+1);
		elem_head = elem_tail = 0;
		elem_buff_sz = max_elements+1;

		insert_tbl = vector<vector<KnapsackSolution<T> > >(max_elements+1);
		for (typename vector<vector<KnapsackSolution<T> > >::iterator it = insert_tbl.begin();
		     it != insert_tbl.end();
		     it++)
			*it = vector<KnapsackSolution<T> >(knapsack_capacity+1);
		insert_cnt = 1;

		delete_tbl = vector<vector<KnapsackSolution<T> > >(max_elements+1);
		for (typename vector<vector<KnapsackSolution<T> > >::iterator it = delete_tbl.begin();
		     it != delete_tbl.end();
		     it++)
			*it = vector<KnapsackSolution<T> >(knapsack_capacity+1);
		delete_cnt = 1;
	}

	void insert(T *new_element) {

		assert(0 < insert_cnt && insert_cnt < max_elements+1);

		elem_buff[elem_tail] = new_element;

		for (unsigned w = 0; w < knapsack_capacity+1; w++) {
			unsigned nweight = elem_buff[elem_tail]->weight();

			if (nweight <= w) {
				KnapsackSolution<T> tmp = insert_tbl[insert_cnt-1][w-nweight];
				tmp.add_element(elem_buff[elem_tail]);

				insert_tbl[insert_cnt][w] = max(insert_tbl[insert_cnt-1][w], tmp);

			} else {
				insert_tbl[insert_cnt][w] = insert_tbl[insert_cnt-1][w];
			}

		}

		elem_tail = (elem_tail+1)%elem_buff_sz;
		insert_cnt++;
	}

	void delete_oldest() {

		assert(elem_head != elem_tail);
		assert(delete_cnt > 0);

		if (delete_cnt > 1) {
			elem_head = (elem_head+1)%elem_buff_sz;
			delete_cnt--;
			return;
		}

		assert(delete_cnt == 1);
		assert(insert_cnt > 1);

		typename vector<T*>::size_type i = (elem_tail == 0 ? elem_buff_sz-1 : elem_tail-1);
		while (i != elem_head) {

			assert(delete_cnt < max_elements+1);

			for (unsigned w = 0; w < knapsack_capacity+1; w++) {
				unsigned nweight = elem_buff[i]->weight();
				if (nweight <= w) {
					KnapsackSolution<T> tmp = delete_tbl[delete_cnt-1][w-nweight];
					tmp.add_element(elem_buff[i]);

					delete_tbl[delete_cnt][w] = max(delete_tbl[delete_cnt-1][w], tmp);

				} else {
					delete_tbl[delete_cnt][w] = delete_tbl[delete_cnt-1][w];
				}
			}

			i = (i == 0 ? elem_buff_sz-1 : i-1);
			delete_cnt++;
		}

		elem_head = (elem_head+1)%elem_buff_sz;
		insert_cnt = 1;
	}

	const KnapsackSolution<T> &solve() {
		if (insert_cnt == 1 || delete_cnt == 1) {
			if (insert_cnt == 1)
				return delete_tbl[delete_cnt-1][knapsack_capacity];
			else
				return insert_tbl[insert_cnt-1][knapsack_capacity];
		}

		assert(insert_cnt > 1 && delete_cnt > 1);

		solution_buff = insert_tbl[insert_cnt-1][knapsack_capacity]+delete_tbl[delete_cnt-1][0];
		for (unsigned w = 1; w < knapsack_capacity+1; w++) {
			const KnapsackSolution<T> &ins_tmp = insert_tbl[insert_cnt-1][knapsack_capacity-w];
			const KnapsackSolution<T> &del_tmp = delete_tbl[delete_cnt-1][w];
			unsigned comb_value = ins_tmp.get_value()+del_tmp.get_value();

			if (comb_value > solution_buff.get_value())
				solution_buff = ins_tmp+del_tmp;
		}

		return solution_buff;
	}
};



class Item {
private:
	unsigned id;
	unsigned val;
	unsigned w;

public:
	void set_info(unsigned nid, unsigned nvalue, unsigned nweight) {
		id = nid;
		val = nvalue;
		w = nweight;
	}

	unsigned value() const { return val; }
	unsigned weight() const { return w; }

	bool operator<(const Item &rhs) const {
		return id < rhs.id;
	}

	friend ostream &operator<<(ostream &os, const Item &it);
};

ostream &operator<<(ostream &os, const Item &it) {
	os << it.id;
	return os;
}

#define MAX_INSERTS 10000
static Item items[MAX_INSERTS+1];
static size_t items_i;

void op_query(OnlineKnapsackSolver<Item> &solver) {
	const KnapsackSolution<Item> &solution = solver.solve();

	cout << "The best choice is to take " << solution.size() << " items (total: " << solution.get_value() << ")" << endl;
	cout << "Items:";
	for (KnapsackSolution<Item>::const_iterator it = solution.begin();
	     it != solution.end();
	     it++)
		cout << " " << **it;
	cout << endl;
}

void op_add(OnlineKnapsackSolver<Item> &solver) {
	unsigned value, weight;

	cin >> value >> weight;
	assert(cin);

	items[items_i].set_info(items_i, value, weight);
	solver.insert(&items[items_i]);
	items_i++;
}

void op_del(OnlineKnapsackSolver<Item> &solver) {
	solver.delete_oldest();
}

int main() {

	unsigned items_window, knapsack_cap;

	cout << "How many items will be active at once?" << endl;
	cin >> items_window;
	assert(cin);

	cout << "What is the knapsack's capacity?" << endl;
	cin >> knapsack_cap;
	assert(cin);

	OnlineKnapsackSolver<Item> slv(items_window, knapsack_cap);

	cout << "Each item added is assigned a sequential id starting from 0." << endl;
	cout << "You are allowed to perform at most " << MAX_INSERTS << " insertions" << endl;
	cout << "TO perform queries: QUERY" << endl;
	cout << "To insert an item: ADD value weight" << endl;
	cout << "To delete the oldest item: DEL" << endl;
	cout << "To quit: QUIT" << endl;

	string op;
	while (cin >> op) {
		if (op == "QUERY")
			op_query(slv);
		else if (op == "ADD")
			op_add(slv);
		else if (op == "DEL")
			op_del(slv);
		else if (op == "QUIT")
			break;
		else
			assert(0);
	}

	return 0;
}
