// Name: Valentina Derksen
// Seneca Student ID: 153803184
// Seneca email: vderksen@myseneca.ca
// Date of completion: 2019-12-01
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Item.h"
#include "Utilities.h"
#include "CustomerOrder.h"

#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm> // std::max

// Initialize STATIC_variable
size_t CustomerOrder::m_widthField = 1;

// custom constructor
CustomerOrder::CustomerOrder() {
	m_name = "";
	m_product = "";
	m_cntItem = 0u;
	m_lstItem = nullptr;
}

// custom constructor
CustomerOrder::CustomerOrder(const std::string& str) {
	bool more = true;
	size_t pos = 0u;

	Utilities util;

	m_name = util.extractToken(str, pos, more);
	m_widthField = std::max<int>(m_widthField, m_name.length());

	m_product = util.extractToken(str, pos, more);
	m_widthField = std::max<int>(m_widthField, m_product.length());

	auto start_pos = pos;

	while (more) {
		util.extractToken(str, pos, more);
		m_cntItem++;
	}

	m_lstItem = new ItemInfo *[m_cntItem];

	more = true;
	for (auto i = 0u; i < m_cntItem; i++) {
		m_lstItem[i] = new ItemInfo(util.extractToken(str, start_pos, more));
	}

	if (m_widthField < util.getFieldWidth()) {
		m_widthField = util.getFieldWidth();
	}
}

// move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
	*this = std::move(other);
}

//move assignment operator
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
	// check if try to assign the object to itself
	if (this != &other) {

		// free the existing resource
		if (this->m_lstItem) {
			for (auto i = 0u; i < m_cntItem; i++)
				delete this->m_lstItem[i];
		}
		delete[] this->m_lstItem;

		//  transfer the data members from the source object 
		// to the object that is being constructed
		this->m_name = other.m_name;
		this->m_product = other.m_product;
		this->m_cntItem = other.m_cntItem;
		this->m_lstItem = other.m_lstItem;

		// release the data pointer from the source object
		other.m_name = "";
		other.m_product = "";
		other.m_cntItem = 0u;
		other.m_lstItem = nullptr;
	}
	// return a reference to the current object
	return *this;
}

// a destructor
CustomerOrder::~CustomerOrder() {
	m_name = "";
	m_product = "";
	m_cntItem = 0u;

	if (m_lstItem) {
		for (auto i = 0u; i < m_cntItem; i++)
			delete m_lstItem[i];
	}
	delete[] m_lstItem;
	m_lstItem = nullptr;
}

// returns the ItemInfo::m_fillState of the item specified as a parameter
bool CustomerOrder::getItemFillState(std::string str) const {
	for (auto i = 0u; i < this->m_cntItem; i++)
		if (m_lstItem[i]->m_itemName == str)
			return m_lstItem[i]->m_fillState;

	return true;
}

// returns true if all the items in the order have been filled
bool CustomerOrder::getOrderFillState() const {
	for (auto i = 0u; i < m_cntItem; i++)
		if (!m_lstItem[i]->m_fillState)
			return false;

	return true;
}

//  fills the item in the current order that corresponds to the item passed into the function
void CustomerOrder::fillItem(Item& item, std::ostream& os) {
	for (auto i = 0u; i < m_cntItem; i++) {
		// check if there is  the item in the current order
		if (item.getName() == m_lstItem[i]->m_itemName) {
			// check the inventory contains at least one element
			if (item.getQuantity() > 0) {
				// substracts 1 from the inventory
				item.updateQuantity();
				//  updates ItemInfo::m_serialNumber and ItemInfo::m_fillState
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				m_lstItem[i]->m_fillState = true;
				os << "Filled " << m_name << ", "
					<< m_product << "[" << item.getName() << "]" << std::endl;
			}
			else {
				os << "Unable to fill " << m_name << ", "
					<< m_product << "[" << item.getName() << "]" << std::endl;
			}
		}
	}
}

// displays the state of the current object in the format 
// CUSTOMER_NAME - PRODUCT
// [SERIAL] ITEM_NAME - STATUS
// [SERIAL] ITEM_NAME - STATUS
// ...
void CustomerOrder::display(std::ostream& os) const {
	os << m_name << " - " << m_product << std::endl;
	for (auto i = 0u; i < m_cntItem; i++) {
		os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber
			<< std::setfill(' ') << "] " << std::setw(m_widthField) << m_lstItem[i]->m_itemName
			<< " - " << (m_lstItem[i]->m_fillState ? "FILLED" : "MISSING") << std::endl;
	}
}

