module date_day (Data_in, Command, Data_out);
	input[15:0] Data_in;
	input [7:0] Command;
	output [15:0] Data_out;
	reg [15:0] Data_in_buf;
	reg [15:0] Data_out_buf;
	reg [15:0] Year;
	reg [15:0] Month;
	reg [15:0] Date;

	
	assign Data_out = Command[1] ? Data_out_buf : 16'bz; //if Command[0] is high, write data to tri-state buffer. else high impedance
	
		always@(Command)
			begin
				case (Command)
					8'b00000101: Year = Data_in;
					8'b00001001: Month = Data_in;
					8'b00001101: Date = Data_in;
					8'b00000011: Data_out_buf=Year+Month+Date;
					default:Data_out_buf=16'b1111111111111111;
				endcase
			end

endmodule
		