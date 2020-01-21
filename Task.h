#pragma once
// Name: Valentina Derksen
// Seneca Student ID: 153803184
// Seneca email: vderksen@myseneca.ca
// Date of completion: 2019-12-01
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef TASK_H
#define TASK_H

#include "Item.h"
#include "CustomerOrder.h"
#include <deque>
#include <iostream>
#include <string>

class Task : public Item {
	std::deque<CustomerOrder> m_orders; // double ended queue with new CustomerOrders coming in one side and exiting out the other once filled
	Task* m_pNextTask; // a pointer to the next task on the assembly line
public:
	// custom constructor
	Task(const std::string&);
	// a Task oblect can't be copied or moved
	Task(const Task&) = delete;
	Task& operator = (const Task&) = delete;
	Task(Task&&) = delete;
	Task& operator = (Task&&) = delete;
	// runs a single cycle of the assembly line for the current task
	void runProcess(std::ostream&);
	// moves the last CustomerOrder in the queue to the next task on the assembly line
	bool moveTask();
	// stores the provided Task object's reference into the m_pNextTask pointer
	void setNextTask(Task&);
	// removes the last CustomerOrder from the queue
	bool getCompleted(CustomerOrder&);
	//  writes the name of the Item this Task is responsible for into the parameter
	void validate(std::ostream&);
	// moves the parameter onto the front of the CustomerOrder queue
	Task& operator += (CustomerOrder&&);

	// Return the next task in the line
	Task * getNext();
};


#endif // !TASK_H
