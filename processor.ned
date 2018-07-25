package Multiprogrammed_Server;

//
// TODO auto-generated module
//
simple Processor
{    
    parameters:
        double proc_mean;
        int p1;
        int p2;
        
        @signal[response](type="long");
        @statistic[respCount](title="Client response"; source="response"; record=count,vector;);
        
    gates:
        input in[];
        output out[];
}
