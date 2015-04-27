Implements a variant of the 0/1 knapsack problem over a stream of operations:

- ADD: adds an item
- DEL: deletes the oldest item
- QUERY: solves the knapsack problem with the active items

The optimized algorithm takes O(W) for ADDs, amortized O(1) for DELs,
and O(W) to answer a query, where W is the knapsack capacity.

Please refer to http://filipegoncalves.github.io/2015/01/25/online-knapsack-problem-optimizing-the-traditional-approach/ for further information.
