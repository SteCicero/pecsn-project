package Multiprogrammed_Server;

module Server
{
    
    parameters:
        int N;
    
    @display("bgb=532,346");
    
    gates:
        input in[];
        output out[];

    submodules:
        processor: Processor {
            @display("p=110,182");
        }
        disk: Disk {
            @display("p=387,106");
        }
    connections:
        //Processor connections
        processor.out++ --> {  delay = 1ms; } --> disk.in; //out[0] -> disk
        processor.in++ <-- {delay = 1ms; } <-- disk.out; // in[0] proc <- disk
        
        processor.in++ <-- {delay = 1ms;} <-- in++; //in[1] <- in[0] server (query)
        processor.out++ -->{delay = 1ms;} --> out++; //out[1] -> out[0] server (query)
        
        for i = 0..N-1{
           processor.in++ <-- {  delay = 1ms; } <-- in++;    //in[2+] proc  <- in[0+] server
           processor.out++ --> {  delay = 1ms; } --> out++; //out[2+] proc -> out[0+] server
        }
        


}
