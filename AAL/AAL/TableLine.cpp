#include "TableLine.h"



TableLine::TableLine(int _n, long long _t_n, long long _T_n) : n(_n), t_n(_t_n), T_n(_T_n), q(-1.0)
{
}


TableLine::~TableLine()
{
}


int TableLine::get_n()
{
	return n;
}


long long TableLine::get_t_n()
{
	return t_n;
}


long long TableLine::get_T_n()
{
	return T_n;
}


double TableLine::get_q()
{
	return q;
}


void TableLine::set_q(double new_q)
{
	q = new_q;
}



