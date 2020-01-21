// Name: Valentina Derksen
// Seneca Student ID: 153803184
// Seneca email: vderksen@myseneca.ca
// Date of completion: 2019-12-01
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Utilities.h"
#include <string>
#include <iostream>

// Initialize STATIC_variable
char Utilities::m_delimiter;

// sets the field width of the current object to the value of the parameter
void Utilities::setFieldWidth(size_t width) {
	this->m_widthField = width;
}

// returns the field width of the current object
size_t Utilities::getFieldWidth() const {
	return this->m_widthField;
}

// extracts tokens from the first parameter
const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	std::string token;	
	size_t start = next_pos;
	size_t end = str.find(m_delimiter, start); // set the end position to the index of the next dilimeter

	// reports an exception if there are two delimiters with no token between them.
	if (start == end)
		throw "ERROR";
	else {
		// sets more to true if the end of the string was not reached; false otherwise
		if (end != std::string::npos)
			more = true;
		 else more = false;
		// set next_pos to extract next token
		next_pos = end + 1;
		
		// extract token
		token = str.substr(start, end - start);
		// updates the current object's m_widthField data member if its current value is less than the size of the token extracted. 
		if (m_widthField < token.length() && end != std::string::npos)
			setFieldWidth(token.length());
	} return token;
}

// sets the delimiter for this class to the character received
void Utilities::setDelimiter(const char delimeter) {
	m_delimiter = delimeter;
}

// returns the delimiter character of the current object
const char Utilities::getDelimiter() const {
	return m_delimiter;
}