#include "Heap.h"



Heap::Heap()
{
}


Heap::~Heap()
{
}


bool Heap::CompareFields::operator() (const Field& field1, const Field& field2)
{
	return field1.getF() > field2.getF();
}


void Heap::make(FieldIter begin, FieldIter end)
{
	std::make_heap(begin, end, Heap::CompareFields());
	unsigned idx = 0;
	for (FieldIter iter = begin; iter < end; ++iter)
	{
		iter->get().setHeapIdx(idx);
		++idx;
	}
}


void Heap::push(FieldIter begin, FieldIter end)
{
	FieldIter i_iter = end - 1;
	FieldIter j_iter = begin + ((std::distance(begin, i_iter) - 1) / 2);

	std::reference_wrapper<Field> val = (*i_iter);

	while (i_iter > begin && j_iter->get() > val.get())
	{
		(*i_iter) = (*j_iter);
		i_iter->get().setHeapIdx((int)std::distance(begin, i_iter));
		i_iter = j_iter;
		int iter_part = (int)(std::distance(begin, j_iter) - 1) / 2;
		if (iter_part < 0) break;
		j_iter = begin + ((std::distance(begin, j_iter) - 1) / 2);
	}

	(*i_iter) = val;
	i_iter->get().setHeapIdx((int)std::distance(begin, i_iter));
}


void Heap::pop(FieldIter begin, FieldIter end)
{
	if (std::distance(begin, end) == 1)
		return;

	std::reference_wrapper<Field> val = (*(end - 1));

	(*(end - 1)) = (*begin);
	(end - 1)->get().setHeapIdx((int)std::distance(begin, end - 1));

	FieldIter i_iter = begin;
	FieldIter j_iter = begin + 1;

	while (j_iter < end - 1)
	{
		if (j_iter + 1 < end - 1 && (j_iter + 1)->get() < j_iter->get())
			j_iter++;

		if (val.get() <= j_iter->get()) break;
		(*i_iter) = (*j_iter);
		i_iter->get().setHeapIdx((int)std::distance(begin, i_iter));
		i_iter = j_iter;
		int iter_part = 2 * (int)std::distance(begin, j_iter) + 1;
		if (iter_part >= std::distance(begin, end) - 1) break;
		j_iter = begin + (2 * std::distance(begin, j_iter) + 1);
	}

	(*i_iter) = val;
	i_iter->get().setHeapIdx((int)std::distance(begin, i_iter));
}
