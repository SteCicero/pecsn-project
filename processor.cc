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

#include "processor.h"
#include "message_m.h"

Define_Module(Processor);

void Processor::initialize()
{
    responseSignal = registerSignal("response"); //When a client request is served
    respCount = 0;

    processing = false;

}

void Processor::handleMessage(cMessage *msg)
{
  if(msg->isSelfMessage()){
      int random = intuniform(1, 100);

      EV << " -- Random: " << random;

      int p1 = par("p1");
      int p2 = par("p2");

      if(random <= p1){ //p1

          EV << "Sending response to client";

          Message * temp = check_and_cast<Message *>(msg);
          int gateIndex =  temp->getGateIndex();
          temp->setName("Response to client");

          respCount++;
          emit(responseSignal, respCount); //Send a signal


          send(msg, "out", gateIndex); //Respond to client

      }
      else if(random > p1 && random <= p2){ //p2
          EV << "Requesting disk access";

          send(msg, "out", 0); //Disk
      }
      else{ //1-p1-p2
          EV << "Requesting remote query";

          send(msg, "out", 1); //Query
      }



       if(!FIFO_queue->isEmpty()){
           cMessage * self = check_and_cast<cMessage *>(FIFO_queue->pop());

           double processing_time = exponential(par("proc_mean").doubleValue());

           EV << " - Processing time: " << processing_time;

           scheduleAt(simTime() + processing_time, self);
           processing = true;
       }
       else
           processing = false;
   }
  else{

      EV << "Request arrived";

      Message* temp = check_and_cast<Message*>(msg);

      if(!processing){

          EV << " - Processing";

          temp->setGateIndex(msg->getArrivalGate()->getIndex());

          double processing_time = exponential(par("proc_mean").doubleValue());

          EV << " - Processing time 0: " << processing_time;

          scheduleAt(simTime() + processing_time, temp);
          processing = true;
      }
      else{

          EV << " - Added to queue";

         temp->setGateIndex(msg->getArrivalGate()->getIndex());
         FIFO_queue->insert(temp); //Message added to the queue
      }
  }

}
