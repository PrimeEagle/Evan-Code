// Run in repl.it:
// g++ -pthread -std=c++17 -o call call.cpp; ./call < call_test1.in
// Run in zeus:
//g++ -pthread -o call call.cpp; ./call < call_test1.in

#include <iostream>
#include <string>
#include <cassert>

#include "dlist.h"

/*
 * Format of input line:
 *
 *  <timestamp> <Name> <status> <duration>
 *
 * Note: first four fields terminated by whitespace
 *       request terminated by newline.
 *
 * Format of input file:
 * 
 * A single line with the number of requests
 * zero or more input lines followed by EOF.
 */

enum Status {
  NONE = 0, SILVER = 1, GOLD = 2, PLATINUM = 3
};

struct reqNode {
  int         timestamp;
  std::string name;
  Status      status;
  int         duration;
};

/**** INSTRUCTOR NOTE: DO NOT MODIFY ABOVE THIS LINE ****/

/***************************************************
 * INSTRUCTOR NOTE: Implement the functions below. *
 **************************************************/

// EFFECTS: Reads and parses each request from the standard input stream
// std::cin. For each request, creates a reqNode struct and enqueues their
// pointers in the requests queue, which is a Dlist of pointers to reqNode
// structs. 

/*PSEDUOCODE:

int numrequests
cin >> numrequests

for(numrequests)
{
    reqnode n = new reqnode
    requests.InsertFront(n)

    string timestamp;
    string name;
    string status;
    string duration;

    cin >> timestamp >> name >> status >> duration;
       
    n.timestamp = stingtoint(timestamp)
    n.name = name
    n.duration = stringtoint(duration)
    if(status == "none")
    {
         n.status = NONE
    }
    else if (status == "silver")
    {
         n.status = SILVER
    }
    else if (status == "gold")
    {
         n.status = GOLD
    }
    else if (status == "platinum")
    {
         n.status = PLATINUM
    }
}

*
*/

void ObtainRequests(Dlist<reqNode*> &requests) {
  // Implement this function.
    int num_requests;

    std::cin >> num_requests;
    for (int i = 0; i < num_requests; i++)
    {
        reqNode* node = new reqNode();
        requests.InsertFront(node);

        std::string timestamp_string;
        std::string name_string;
        std::string status_string;
        std::string duration_string;

        std::cin >> timestamp_string >> name_string >> status_string >> duration_string;
        //std::cout << timestamp_string << " " << name_string << " " << status_string << " " << duration_string << std::endl;
        
        node->timestamp = stoi(timestamp_string);
        node->name = name_string;
        node->duration = stoi(duration_string);

        if(status_string == "none")
        {
            node->status = Status::NONE;
        }
        else if (status_string == "silver")
        {
            node->status = Status::SILVER;
        }
        else if (status_string == "gold")
        {
            node->status = Status::GOLD;
        }
        else if (status_string == "platinum")
        {
            node->status = Status::PLATINUM;
        }
    }
}

// EFFECTS: Insert any callers with timestamps equal to the tick number
// (the clock param) into their appropriate queues. When a caller is
// inserted, you should print a message that exactly matches the following 
// example (with the correct name and status):
// 
// Call from Jeff a silver member
//
// You can get the appropriate status by calling status_names[status]. 
// Note: If two (or more) calls have the same timestamp, they should be
// printed in input file-order, not in priority-order.

/*PSEDUOCODE:

 bool done = false;

    while(!done && !requests.IsEmpty)
    {
        reqnode n = requests.RemoveBack()

        if (n.timestamp == clock)
        {
            queues[n.status].InsertFront(n)
            if (n.status == NONE)
            {
                cout << "Call from " << n.name << " a regular member" << endl
            }
            else if (n.status == SILVER)
            {
                cout << "Call from " << n.name << " a silver member" << endl
            }
            else if (n.status == GOLD)
            {
                cout << "Call from " << n.name << " a gold member" << endl
            }
            else if (n.status == PLATINUM)
            {
                cout << "Call from " << n.name << " a platinum member" << endl
            }
        }
        else
        {
            requests.InsertBack(n)
            done = true
        }
    }

*
*/
void InsertRequests(Dlist<reqNode*> &requests, Dlist<reqNode*> queues[], int clock, std::string status_names[]) {
  // Implement this function.

    bool done = false;

    while(!done && !requests.IsEmpty())
    {
        reqNode* node = requests.RemoveBack();

        if (node->timestamp == clock)
        {
            queues[node->status].InsertFront(node);
            if (node->status == Status::NONE)
            {
                std::cout << "Call from " << node->name << " a regular member" << std::endl;
            }
            else if (node->status == Status::SILVER)
            {
                std::cout << "Call from " << node->name << " a silver member" << std::endl;
            }
            else if (node->status == Status::GOLD)
            {
                std::cout << "Call from " << node->name << " a gold member" << std::endl;
            }
            else if (node->status == Status::PLATINUM)
            {
                std::cout << "Call from " << node->name << " a platinum member" << std::endl;
            }
        }
        else
        {
            requests.InsertBack(node);
            done = true;
        }
    }
}

// EFFECTS: Simulate the actions of the agent at this tick. The agent must
// follow these rules:
// 1. If the agent is not busy, the agent checks each queue, in priority order
// from Platinum to None. If the agent finds a call, the agent answers the
// call, and you should print a message that exactly matches the following 
// example (with the correct name):
// 
// Answering call from Jeff
// 
// You will need to decrement time_agent_busy by 1. 
// 
// 2. If the agent was already busy at the beginning of this tick, the agent
// continues servicing the current client. You will need to decrement
// time_agent_busy by 1. 
// 
// 3. If the agent is not busy, and there are no current calls, the agent
// does nothing. 
//
// If all calls have been placed, answered, and completed, then return true
// to end the program. Otherwise, return false.


/*PSEDUOCODE:

if (time_agent_busy > 0)
    {
        time_agent_busy -= 1
    }

    if(time_agent_busy == 0)
    {
        if (!queues[3].IsEmpty())
        {
            reqnode n = queues[3].RemoveBack()
            cout << "Answering call from " << n.name << endl
            time_agent_busy = n.duration
        }
        else if (queues[3].IsEmpty() && !queues[2].IsEmpty())
        {
            reqnode n = queues[2].RemoveBack()
            cout << "Answering call from " << n.name << endl
            time_agent_busy = n.duration

        }
        else if (queues[2].IsEmpty() && !queues[1].IsEmpty())
        {
            reqnode n = queues[1].RemoveBack()
            cout << "Answering call from " << n.name << endl
            time_agent_busy = n.duration

        }
        else if (queues[1].IsEmpty() && !queues[0].IsEmpty())
        {
            reqnode n = queues[0].RemoveBack()
            cout << "Answering call from " << n.name << endl
            time_agent_busy = n.duration
        }
    }
    if(queues[3].IsEmpty() && queues[2].IsEmpty() && queues[1].IsEmpty() && queues[0].IsEmpty() && time_agent_busy == 0)
    {
        return true;
    }

  return false;

*
*/
bool SimulateAgent(Dlist<reqNode*> &requests, Dlist<reqNode*> queues[], int &time_agent_busy) {
  // Implement this function.
    if (time_agent_busy > 0)
    {
        time_agent_busy -= 1;
    }

    if(time_agent_busy == 0)
    {
        if (!queues[3].IsEmpty())
        {
            reqNode* node = queues[3].RemoveBack();
            std::cout << "Answering call from " << node->name << std::endl;
            time_agent_busy = node->duration;
        }
        else if (queues[3].IsEmpty() && !queues[2].IsEmpty())
        {
            reqNode* node = queues[2].RemoveBack();
            std::cout << "Answering call from " << node->name << std::endl;
            time_agent_busy = node->duration;

        }
        else if (queues[2].IsEmpty() && !queues[1].IsEmpty())
        {
            reqNode* node = queues[1].RemoveBack();
            std::cout << "Answering call from " << node->name << std::endl;
            time_agent_busy = node->duration;

        }
        else if (queues[1].IsEmpty() && !queues[0].IsEmpty())
        {
             reqNode* node = queues[0].RemoveBack();
             std::cout << "Answering call from " << node->name << std::endl;
             time_agent_busy = node->duration;
        }   
    }
    if(requests.IsEmpty() && queues[3].IsEmpty() && queues[2].IsEmpty() && queues[1].IsEmpty() && queues[0].IsEmpty() && time_agent_busy == 0)
    {
        return true;
    }

  return false;
}

/**** INSTRUCTOR NOTE: DO NOT MODIFY BELOW THIS LINE ****/

int main() {
  // The current time, starting at tick 0. 
  int clock = 0;

  // The remaining time that the agent is busy with the current
  // caller, or 0 if the agent is not busy. 
  int time_agent_busy = 0;

  // An array of four queues, one for each status: regular, silver,
  // gold, platinum. Each queue is a DList of pointers to reqNode
  // structs. 
  Dlist<reqNode*> queues[4]; 

  // A queue of requests matching the input. The queue is a DList of 
  // pointers to reqNode structs.
  Dlist<reqNode*> requests;

  // Flag for whether or not the program should terminate. 
  bool done = false;

  // Array of status name strings for each Status. 
  std::string status_names[4];
  status_names[NONE] = "regular";
  status_names[SILVER] = "silver";
  status_names[GOLD] = "gold";
  status_names[PLATINUM] = "platinum";

  // Run call center simulation.
  ObtainRequests(requests);
  while (!done) {
    std::cout << "Starting tick #" << clock << std::endl;
    InsertRequests(requests, queues, clock, status_names);
    done = SimulateAgent(requests, queues, time_agent_busy);
    clock++;
  }

  return 0;
}