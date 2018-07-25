package Multiprogrammed_Server;

network Queuing_Network
{
    parameters:
        int N; //Number of clients, modified with a varying level of multiprogramming

        @display("bgb=724,337");
    submodules:
        client[N]: Client;
        query: Query {

            @display("p=697,163");
        }
        server: Server {
            @display("p=531,208");
        }
    connections:
        server.out++ --> {  delay = 40ms; } --> query.in;
        server.in++ <-- {  delay = 40ms; } <-- query.out;
        
        for i=0..N-1 {
            client[i].out --> {  delay = 40ms; } --> server.in++;

            client[i].in <-- {  delay = 40ms; } <-- server.out++;
        }
}
