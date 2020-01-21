#pragma once
// Name: Valentina Derksen
// Seneca Student ID: 153803184
// Seneca email: vderksen@myseneca.ca
// Date of completion: 2019-11-24
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
	std::string m_name = ""; // the name of the Item
	std::string m_description = ""; // description of the item
	unsigned int m_serialNumber = 0u; // the next serial number to be assigned on the assembly line
	unsigned int m_quantity = 0u; // the number of current items left in stock
	static unsigned int m_widthField; //  the maximum characters to be displayed for a field
public:
	Item(){};
	// custom constructor
	Item(const std::string&);
	// returns the name of the current Item object
	const std::string& getName() const;
	// returns the next serial number to be used on the assembly line 
	const unsigned int getSerialNumber();
	// returns the remaining quantity of the current Item object
	const unsigned int getQuantity();
	// substracts 1 from the available quantity; should not go below 0
	void updateQuantity();
	//  inserts the content of the current object into first parameter
	void display(std::ostream& os, bool full) const;
};

#endif // !ITEM_H
