module echo (fabric_in, fabric_out);
	input [7:0] fabric_in;
	output [7:0] fabric_out;
	
	assign fabric_out=fabric_in<<2;
	
endmodule
		