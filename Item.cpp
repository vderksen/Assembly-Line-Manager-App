// Name: Valentina Derksen
// Seneca Student ID: 153803184
// Seneca email: vderksen@myseneca.ca
// Date of completion: 2019-12-01
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Item.h"
#include "Utilities.h"

#include <iomanip>
#include <string>
#include <iostream>
#include<algorithm> // std::max

// Initialize STATIC_variable
unsigned int  Item::m_widthField = 1;

// custom constructor
Item::Item(const std::string& str) {
	size_t pos = 0u;
	bool more = true;

	Utilities util;

	m_name = util.extractToken(str, pos, more);
	m_widthField = std::max<int>(m_widthField, m_name.length());

	std::string serialNumber = util.extractToken(str, pos, more);
	m_widthField = std::max<int>(m_widthField, 6);
	m_serialNumber = std::stoi(serialNumber);

	std::string quantity = util.extractToken(str, pos, more);
	m_widthField = std::max<int>(m_widthField, quantity.length());
	m_quantity = std::stoi(quantity);

	m_description = util.extractToken(str, pos, more);
	m_widthField = std::max<int>(m_widthField, m_description.length());

	m_widthField = std::max<int>(m_widthField, util.getFieldWidth());
}

// returns the name of the current Item object
const std::string& Item::getName() const {
	return this->m_name;
}

// returns the next serial number to be used on the assembly line 
const unsigned int Item::getSerialNumber() {
	return m_serialNumber++;
}

// returns the remaining quantity of the current Item object
const unsigned int Item::getQuantity() {
	return this->m_quantity;
}

// substracts 1 from the available quantity; should not go below 0
void Item::updateQuantity() {
	if (this->m_quantity > 0)
		this->m_quantity--;
	else
		this->m_quantity = 0;
}

//  inserts the content of the current object into first parameter
void Item::display(std::ostream& os, bool full) const {
	os << std::setfill(' ');
	if (full == false) {
		// NAME [######]
		os << std::setw(m_widthField - 10) << std::left << m_name
			<< "[" << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << "]" << std::endl;
	}
	else {
		// NAME [######] Quantity: QTY Description: DESCRIPTION
		os << std::setw(m_widthField - 10) << std::left << m_name
			<< "[" << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << "]"
			<< std::setfill(' ') << " Quantity: " << std::setw(m_widthField - 10) << std::left << m_quantity
			<< " Description: " << m_description << std::endl;
	}
}