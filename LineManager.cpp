// Name: Valentina Derksen
// Seneca Student ID: 153803184
// Seneca email: vderksen@myseneca.ca
// Date of completion: 2019-12-01
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "LineManager.h"
#include "Utilities.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


// Custom constructor
// std::string& src -  the filename to be used for linking the assembly line objects
// std::vector<Task*>& tasks - contains the addresses of all the Task objects created for the assembly line
// std::vector<CustomerOrder>& orders - contains all the CustomerOrder objects to be filled

LineManager::LineManager(const std::string& src, std::vector<Task*>&  tasks, std::vector<CustomerOrder>& orders){
	// set the number of CustomerOrder objects the assembly line
	m_cntCustomerOrder = orders.size(); 
	
	// Read the records from file and setup all the m_pNextTask references in the Task objects, 
	std::fstream file(src, std::fstream::in); // open the file in reading mode
	// If there was an error opening the file, throw an error
	if (!file)
		throw std::string("Unable to open [") + src + "] file.";

	std::string token;
	while (!file.eof()) {
		std::getline(file, token);
		
		Utilities util;
		std::vector<std::string> tokens;
		size_t start = 0;
		bool more = false;
		
		util.setDelimiter('|');
		// extract all tokens from the file
		do {
			tokens.push_back(util.extractToken(token, start, more));
		} while (more);
		
		// Pointer variables to form the assembly line chains
		Task * left_chain = nullptr; // for current tasks
		Task * right_chain = nullptr; // for next tasks

		// Iterate through the tasks vector forming the assembly line chain
		for (Task * task : tasks) {
			if (task->getName() == tokens[0]) {
				left_chain = task; 
			} else if (tokens.size() > 1) {
				if (task->getName() == tokens[1]) {
					right_chain = task; 
				} 
			} 
		} 
		if (right_chain != nullptr) {
			// Set m_pNextTask references to the current task
			left_chain->setNextTask(*right_chain);
		}
	}

	// Linking each Task object together to form the assembly line
	for (Task * task : tasks)
		AssemblyLine.push_back(task);

	// Move all the CustomerOrder objects onto the front of the ToBeFilled queue
	for (size_t i = 0; i < orders.size(); i++)
		ToBeFilled.push_front(std::move(orders[i]));

	// Get the first and last elements of the assembly
	std::vector<Task *> sorted;

	for (auto task : AssemblyLine)
		if (task->getNext() == nullptr)
			sorted.push_back(task);

	for (size_t i = 0; i < AssemblyLine.size(); i++)
		for (auto task : AssemblyLine)
			if (task->getNext() != nullptr)
				if (task->getNext() == sorted.back())
					sorted.push_back(task);

	std::reverse(sorted.begin(), sorted.end());

	First = sorted.front();
	Last = sorted.back();

	// Close the file
	file.close();
	}


// this function performs  one cycle of operations on the assembly line
bool LineManager::run(std::ostream& os) {
	bool completed = true;
	
	// check if there is any CustomerOrder objects in the ToBeFilled queue
	if (!ToBeFilled.empty()) {
		// move the last CustomerOrder object onto the starting point of the AssemblyLine
		*First += std::move(ToBeFilled.back());
		ToBeFilled.pop_back();
	}
	
	// Loop through all tasks on the assembly line and run one cycle of the task's process
	for (Task * task : AssemblyLine)
		task->runProcess(os);

	// queue to hold complete orders
	CustomerOrder filled_order;
	// Check if the order at the end of the line is completed
	if (Last->getCompleted(filled_order))
		// If true, completed orders should be moved into the Completed queue
		Completed.push_back(std::move(filled_order));

	// Loop through all tasks on the assembly line and move the CustomerOrder objects down the line
	for (Task * task : AssemblyLine) {
		// If the lines moved, repeat
		if (task->moveTask())
			completed = false;
	}

	// return true if all customer orders have been filled
	return completed;
}

// displays all the orders that were completed
void LineManager::displayCompleted(std::ostream& os) const {
	for(auto& i : Completed) {
		i.display(os); 
	}
}

//  validates each task on the assembly line
void LineManager::validateTasks() const {
	for (auto i : AssemblyLine) {
		 i->validate(std::cout);
	}
}

