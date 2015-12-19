#pragma once

/* Class representing coordinates */
class Coords 
{
	/* x coordinate */
	int x;

	/* y coordinate */
	int y;

public:
	Coords();
	Coords(int _x, int _y);
	~Coords();

	/* Set x coordinate
	 * @param {int} _x: new x coordinate
	 */
	void setX(int _x);

	/* Set y coordinate
	 * @param {int} _y: new y coordinate
	 */
	void setY(int _y);

	/* Set x and y coordinates 
	 * @param {int} _x: new x coordinate
	 * @param {int} _y: new y coordinate
	 */
	void setXY(int _x, int _y);

	/* Get x coordinate
	 * @returns {int}: x coordinate
	 */
	int getX() const;

	/* Get y coordinate
	* @returns {int}: y coordinate
	*/
	int getY() const;

	bool operator== (const Coords& _coords) const;
};
