#pragma once
// Name: Valentina Derksen
// Seneca Student ID: 153803184
// Seneca email: vderksen@myseneca.ca
// Date of completion: 2019-12-01
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Utilities {
	size_t m_widthField = 1; // specifying the length of the token extracted
	static char m_delimiter;  // separates the tokens from a given std::string
public:
	// sets the field width of the current object to the value of the parameter
	void setFieldWidth(size_t);
	// returns the field width of the current object
	size_t getFieldWidth() const;
	// extracts tokens from the first parameter
	const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	// sets the delimiter for this class to the character received
	static void setDelimiter(const char delimeter);
	// returns the delimiter character of the current object
	const char getDelimiter() const;
};

#endif // !UTILITIES_H


