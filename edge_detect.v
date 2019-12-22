module edge_detect (Data_in, Command, Data_out);
	input[15:0] Data_in;
	input [15:0] Command;
	output [15:0] Data_out;
	reg [15:0] pixel1;
	reg [15:0] pixel2;
	reg [15:0] pixel3;
	reg [15:0] pixel4;
	reg [15:0] pixel5;
	reg [15:0] pixel6;
	reg [15:0] pixel7;
	reg [15:0] pixel8;
	reg [15:0] pixel9;
	reg [15:0] Conv;
	reg [15:0] Data_out_buf;
	
		
	assign Data_out = Command[9] ? Data_out_buf : 16'bz; //if Command[0] is high, write data to tri-state buffer. else high impedance
	
		always@(Command)
			begin
				case (Command)
					16'h0001: pixel1 = Data_in;
					16'h0002: pixel2= Data_in;
					16'h0004: pixel3 = Data_in;
					16'h0008: pixel4=Data_in;
					16'h0010: pixel5 = Data_in;
					16'h0020: pixel6 = Data_in;
					16'h0040: pixel7 = Data_in;
					16'h0080: pixel8= Data_in;
					16'h0100: pixel9= Data_in;
					16'h0200: Data_out_buf= Conv;
					default:Data_out_buf=16'b1111111111111111;
				endcase
				
								
				Conv= -pixel1-pixel2-pixel3-pixel4+(pixel5<<3)-pixel6-pixel7-pixel8-pixel9;
				
			end

endmodule
		