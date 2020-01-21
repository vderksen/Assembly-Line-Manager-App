// Name: Valentina Derksen
// Seneca Student ID: 153803184
// Seneca email: vderksen@myseneca.ca
// Date of completion: 2019-12-01
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Task.h"
#include "CustomerOrder.h"
#include <string>
#include <iostream>
#include <deque>

// custom constructor
Task::Task(const std::string& str) : Item(str) // Item instantiation
{
	m_pNextTask = nullptr;
}

// runs a single cycle of the assembly line for the current task
void Task::runProcess(std::ostream& os) {
	// check If there are CustomerOrders in the queue
	if (!m_orders.empty()) {
		//  verify the fill status of the last CustomerOrder
		if(!m_orders.back().getOrderFillState())
			// fill the order  if the order contains the Item specified by the current Task
			m_orders.back().fillItem(*this, os);
	}
}

// moves the last CustomerOrder in the queue to the next task on the assembly line
bool Task::moveTask() {
	bool move_task = false;

	// check is there is next Task
	if (m_pNextTask != nullptr) {
		// chek if queue is not empty
		if (!m_orders.empty()) {
			//if (m_orders.back().getItemFillState(Item::getName()) || Item::getQuantity() == 0)
			if (m_orders.back().getItemFillState(getName())) {
				// moves the last CustomerOrder in the queue to the next task on the assembly line 
				*m_pNextTask += std::move(m_orders.back());
				// Remove from the queue
				m_orders.pop_back();

				move_task = true;
			}
		}
	}
	return move_task;
}

// stores the provided Task object's reference into the m_pNextTask pointer
void Task::setNextTask(Task& nxtTask) {
	m_pNextTask = &nxtTask;
}

// removes the last CustomerOrder from the queue
bool Task::getCompleted(CustomerOrder& order) {
	bool order_completed = false;
	
	// chek if queue is empty
	if (!m_orders.empty()) {
		// Place it in the parameters
		order = std::move(m_orders.back());
		// removes the last CustomerOrder from the queue
		m_orders.pop_back();
		
		order_completed = true;
	}
	return order_completed;
}

// writes the name of the Item this Task is responsible for into the parameter
// ITEM_NAME --> NEXT_ITEM_NAME
void Task::validate(std::ostream& os) {
	os << getName() << " -- > " << ((m_pNextTask == nullptr) ? "END OF LINE" : m_pNextTask->getName()) << std::endl;
}

// moves the parameter onto the front of the CustomerOrder queue
Task& Task::operator += (CustomerOrder&& order) {
	m_orders.push_front(std::move(order));
	return *this;
}

// Return the address of the next task in the line
Task * Task::getNext() {
	return m_pNextTask;
}

	
