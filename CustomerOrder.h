#pragma once
// Name: Valentina Derksen
// Seneca Student ID: 153803184
// Seneca email: vderksen@myseneca.ca
// Date of completion: 2019-12-01
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include "Item.h"
#include "Utilities.h"
#include <string>

struct ItemInfo
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder {
	std::string m_name;  // Customer Name
	std::string m_product; //  Order Name
	unsigned int m_cntItem{}; // a count of the number of items for the customer's order
	ItemInfo **m_lstItem{}; // the list of items making up the order
	static size_t m_widthField; //  the maximum width of a field, used for display purposes
public:
	// default constructor
	CustomerOrder();
	// custom constructor
	CustomerOrder(const std::string&);
	// copy operations is not allowed
	CustomerOrder(const CustomerOrder&) { throw "Copy Not allowed"; }
	CustomerOrder& operator=(const CustomerOrder&) = delete;
	//move constructor
	CustomerOrder(CustomerOrder&&) noexcept;
	// move assigment operator
	CustomerOrder& operator=(CustomerOrder&&) noexcept;
	// a destructor
	~CustomerOrder();
	// returns the ItemInfo::m_fillState of the item specified as a parameter
	bool getItemFillState(std::string) const;
	// returns true if all the items in the order have been filled
	bool getOrderFillState() const;
	//  fills the item in the current order that corresponds to the item passed into the function
	void fillItem(Item& item, std::ostream&);
	// displays the state of the current object in the format 
	void display(std::ostream&) const;
};


#endif // !CUSTOMERORDER_H

