#pragma once

/* Describe line in table with results */
class TableLine
{
public:
	TableLine(int _n, long long _t_n, long long _T_n);
	~TableLine();

	/* Get n - data size
	 * @returns {int}: n - data size
	 */
	int get_n();

	/* Get t(n) - execution time
	 * returns {long long}: t(n) - execution time
	 */
	long long get_t_n();

	/* Get T(n) - theoretical execution time
	 * @returns {long long}: T(n) - theoretical execution time
	 */
	long long get_T_n();

	/* Get q coefficient
	 * returns {double}: q coefficient
	 */
	double get_q();

	/* Set q coefficient
	 * @param {double} new_q: new q coefficient
	 */
	void set_q(double new_q);
private:
	int n;
	long long t_n;
	long long T_n;
	double q;
};

