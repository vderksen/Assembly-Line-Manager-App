#pragma once
// Name: Valentina Derksen
// Seneca Student ID: 153803184
// Seneca email: vderksen@myseneca.ca
// Date of completion: 2019-12-01
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include "CustomerOrder.h"
#include "Task.h"

#include <vector>
#include <deque>
#include <string>
#include <iostream>


class LineManager {
	std::vector<Task*> AssemblyLine; //  all the references of the Task objects on the assembly line
	std::deque<CustomerOrder> ToBeFilled; // a queue of customer orders to be filled
	std::deque<CustomerOrder> Completed; // a queue of customer orders completed
	unsigned int m_cntCustomerOrder; // the number of CustomerOrder objects the assembly line started with

	// Set the first and last element of the assembly line
	Task * First; 
	Task * Last;
public:
	// custom constructor
	LineManager(const std::string&, std::vector<Task*>&, std::vector<CustomerOrder>&);
	// this function performs one cycle of operations on the assembly line
	bool run(std::ostream&);
	// displays all the orders that were completed
	void displayCompleted(std::ostream&) const;
	//  validates each task on the assembly line
	void validateTasks() const;
};

#endif // !LINEMANAGER_H
