#pragma once

#include <vector>
#include "Field.h"
#include <functional>
#include <algorithm>
#include <iterator>


/* Class to perform heap operations for Dijkstra algorithm */
class Heap
{
private:
	Heap();
	~Heap();

	/* Class with overloaded operator() used by make_heap function */
	class CompareFields
	{
	public:
		bool operator() (const Field& field1, const Field& field2);
	};
public:
	typedef std::vector<std::reference_wrapper<Field> >::iterator FieldIter;

	/* Construct min heap in the range [begin, end) 
	 * @param {std::vector<std::reference_wrapper>::iterator}: first element to make the heap from
	 * @param {std::vector<std::reference_wrapper>::iterator}: element after last to make the heap from
	 */
	static void make(FieldIter& begin, FieldIter& end);

	/* Inserts the element at the position last-1 into min heapdefined by the range [begin, end-1).
	 * @param {std::vector<std::reference_wrapper>::iterator}: first element at the heap
	 * @param {std::vector<std::reference_wrapper>::iterator}: element after element to insert
	 */
	static void push(FieldIter& begin, FieldIter& end);
	
	/* Swaps the value in position begin and the value in the position end-1 and makes
	 * the subrange [begin, end-1) into min heap
	 * @param {std::vector<std::reference_wrapper>::iterator}: first element at the heap
	 * @param {std::vector<std::reference_wrapper>::iterator}: element after last element at the heap
	 */
	static void pop(FieldIter& begin, FieldIter& end);
};

