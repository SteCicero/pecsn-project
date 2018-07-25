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

#include "client.h"
#include "message_m.h"

Define_Module(Client);

void Client::initialize()
{
    Message * request = new Message("Client request");
    send (request, "out");
}

void Client::handleMessage(cMessage *msg)
{
    //A response from the server arrives, so a new request is issued
    Message * request = new Message("Client request");
    send (request, "out");
}
