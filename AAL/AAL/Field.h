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
	unsigned G;

	/* Estimated path length from current field to end field */
	unsigned H;

	/* Sum of actual path length from start to current field and estimated from current to end field */
	unsigned F;

	/* Field's parent */
	Field* parent;
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
	 * @param {unsigned} _newG: new G length
	 * @param {unsigned} _newH: new H length
	 */
	void updateGHF(unsigned newG, unsigned newH);

	/* Set update all path lengths
	 * @param {unsigned} _newG: new G length
	 */
	void updateGHF(unsigned newG);

	/* Set update all lengths: G and F
	 * @param {unsigned} _newG: new G length
	 */
	void updateGF(unsigned newG);

	/* Get coordinates 
	 * @returns {Coords}: coordinates
	 */
	Coords getCoords() const;

	/* Get allowed
	 * @returns {bool}: allowed
	 */
	bool getAllowed() const;

	/* Get allowed
	 * @returns {unsigned}: sum of actual and estimated path lengths
	 */
	unsigned getF() const;

	/* Get allowed
	 * @returns {unsigned}: actual path length
	 */
	unsigned getG() const;

	/* Get allowed
	 * @returns {Field*}: parent
	 */
	Field* getParent();

	bool operator== (const Field& _field) const;
	bool operator!= (const Field& _field) const;
};

