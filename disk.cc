//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "disk.h"

Define_Module(Disk);

void Disk::initialize()
{
    processing = false;
}

void Disk::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        send(msg, "out"); //Send message to processor

         if(!FIFO_queue->isEmpty()){
             cMessage * self = check_and_cast<cMessage *>(FIFO_queue->pop());

             scheduleAt(simTime() + exponential(par("disk_mean").doubleValue()), self);
             processing = true;
         }
         else
             processing = false;

    }
    else
    {

         if(!processing){
             scheduleAt(simTime() + exponential(par("disk_mean").doubleValue()), msg);
             processing = true;
         }
         else{
            FIFO_queue->insert(msg); //Message added to the queue
         }
    }
}
