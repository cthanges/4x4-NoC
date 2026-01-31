// source.cpp
#include "source.h"
void source:: func()
{
	packet v_packet_out;
	v_packet_out.data = 1000;
	v_packet_out.pkt_clk = '0'; // Imaginary clock for packets

	sc_time t_sent;

	while(true)
	{
		wait();
		if(!ach_in.read())
		{ 
			if(ch_k.read() == source_id.read())
			{
				v_packet_out.data = v_packet_out.data + 1;
				v_packet_out.id = source_id.read();
				v_packet_out.dest= d_est.read(); // Assign a destination ID
				if(v_packet_out.id == v_packet_out.dest) goto exclode; // Prevent from receiving flits by itself 		 
				v_packet_out.pkt_clk= ~v_packet_out.pkt_clk ; // Add an imaginary clock to each flit 
				v_packet_out.h_t=false;
				pkt_snt++;
				if((pkt_snt%5)==0)v_packet_out.h_t=true; // Make tail flit (the packet size is 5)
				packet_out.write(v_packet_out);
				t_sent = sc_time_stamp();
				cout << "\nt: " << sc_time_stamp() << "  ||  Packet: " << v_packet_out.data << " is sent by Source: " << source_id.read()  << " to Destination/Sink: "<< v_packet_out.dest <<endl;
exclode:;
			}
		}  
	}
}
