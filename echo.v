module echo (Data_in, Command, Data_out);
	input[15:0] Data_in;
	input [7:0] Command;
	output [15:0] Data_out;
	reg [15:0] Data_in_buf;
	reg [15:0] Data_out_buf;

	
	assign Data_out = Command[0] ? Data_out_buf : 16'bz; //if Command[0] is high, write data to tri-state buffer. else high impedance
	
		always@(Command)
			begin
				if(Command[0]==0)
					Data_in_buf=Data_in; //read data to Data_in
					
				else if (Command[0]==1)
					Data_out_buf=Data_in_buf<<3;

			end

	
endmodule
		