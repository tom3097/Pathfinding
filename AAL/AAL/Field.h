#pragma once

#include "Coords.h"

/* Class representing field */
class Field 
{
	/* Field's coordinates */
	Coords coords;

	/* Informs if field is white (allowed) or black (not allowed) */
	bool allowed;

	/* Actual path length from start fielt to current field */
	int G;

	/* Estimated path length from current field to end field */
	int H;

	/* Sum of actual path length from start to current field and estimated from current to end field */
	int F;

	/* Field's parent */
	Field* parent;

	/* Index in heap */
	int idx;
public:
	Field();
	Field(Coords _coords, bool _allowed);
	~Field();

	/* Reset path length info and parent*/
	void reset();
	
	/* Set coordinates
	 * @param {Coords} _coords: new coordinates
	 */
	void setCoords(Coords _coords);

	/* Set allowed
	 * @param {bool} _flag: new allowed status
	 */
	void setAllowed(bool flag);

	/* Set parent
	 * @param {Field*} _parent: new parent
	 */
	void setParent(Field *_parent);

	/* Set update all path lengths
	 * @param {int} _newG: new G length
	 * @param {int} _newH: new H length
	 */
	void updateGHF(int newG, int newH);

	/* Set update all path lengths
	 * @param {int} _newG: new G length
	 */
	void updateGHF(int newG);

	/* Set update all lengths: G and F
	 * @param {int} _newG: new G length
	 */
	void updateGF(int newG);

	/* Get coordinates 
	 * @returns {Coords}: coordinates
	 */
	Coords getCoords() const;

	/* Get allowed
	 * @returns {bool}: allowed
	 */
	bool getAllowed() const;

	/* Get allowed
	 * @returns {int}: sum of actual and estimated path lengths
	 */
	int getF() const;

	/* Get allowed
	 * @returns {int}: actual path length
	 */
	int getG() const;

	/* Get allowed
	 * @returns {Field*}: parent
	 */
	Field* getParent();

	/* Get index in heap
	 * @returns {int}: index in heap
	 */
	int getHeapIdx();

	/* Set index in heap
	 * @param {int} newIdx: new index in heap
	 */
	void setHeapIdx(int newIdx);

	bool operator== (const Field& _field) const;
	bool operator!= (const Field& _field) const;
	bool operator> (const Field& _field) const;
	bool operator<= (const Field& _field) const;
	bool operator< (const Field& _field) const;
};

