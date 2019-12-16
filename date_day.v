module date_day (Data_in, Command, Data_out);
	input[15:0] Data_in;
	input [7:0] Command;
	output [15:0] Data_out;
	reg [15:0] Data_in_buf;
	reg [15:0] Data_out_buf;
	reg [15:0] Year;
	reg [15:0] Month;
	reg [15:0] Date;
	reg [7:0] Month_Offset;
	reg [7:0] Decade_Offset;
	reg [7:0] Leap_Offset;
	reg [7:0] Decade;
	reg [7:0] Year_End;
	reg [7:0] Day_Remainder;
	reg [7:0] Day;
	
		
	assign Data_out = Command[1] ? Data_out_buf : 16'bz; //if Command[0] is high, write data to tri-state buffer. else high impedance
	
		always@(Command)
			begin
				case (Command)
					8'b00000101: Year = Data_in;
					8'b00001001: Month = Data_in;
					8'b00001101: Date = Data_in;
					8'b00000011: Data_out_buf=Day;
					default:Data_out_buf=16'b1111111111111111;
				endcase
				
				Decade=Year/10;
				
				case (Decade)
					'd 190: Decade_Offset='d 1;
					'd 191: Decade_Offset='d 6;
					'd 192: Decade_Offset='d 5;
					'd 193: Decade_Offset='d 3;
					'd 194: Decade_Offset='d 2;
					'd 195: Decade_Offset='d 0;
					'd 196: Decade_Offset='d 6;
					'd 197: Decade_Offset='d 4;
					'd 198: Decade_Offset='d 3;
					'd 199: Decade_Offset='d 1;
					'd 200: Decade_Offset='d 0;
					'd 201: Decade_Offset='d 5;
					default:Data_out_buf='d 100;
				endcase
				
				case (Month)
					'd 1: Month_Offset='d 6;					
					'd 2: Month_Offset='d 2;
					'd 3: Month_Offset='d 2;
					'd 4: Month_Offset='d 5;
					'd 5: Month_Offset='d 0;
					'd 6: Month_Offset='d 3 ;
					'd 7: Month_Offset='d 5;
					'd 8: Month_Offset='d 1;
					'd 9: Month_Offset='d 4;
					'd 10: Month_Offset='d 6;
					'd 11: Month_Offset='d 2;
					'd 12: Month_Offset='d 4;
					default: Month_Offset= 'd 100;
				endcase

				Year_End=Year%10;
				
				case (Year_End)
					'd 0: Leap_Offset= 'd 0;
					'd 1: Leap_Offset= 'd 0;
					'd 2: Leap_Offset= ((Decade%2)== 0)? 'd 0: 'd 1;
					'd 3: Leap_Offset= ((Decade%2)== 0)? 'd 0: 'd 1;
					'd 4: Leap_Offset= 'd 1;
					'd 5: Leap_Offset= 'd 1;
					'd 6: Leap_Offset= ((Decade%2)== 0)? 'd 1: 'd 2;
					'd 7: Leap_Offset= ((Decade%2)== 0)? 'd 1: 'd 2;
					'd 8: Leap_Offset= 'd 2;
					'd 9: Leap_Offset= 'd 2;				
					default: Leap_Offset='d 100;
				endcase

					
				Day= (Date+ Month_Offset+Decade_Offset+Year_End+Leap_Offset)% 'd 7;
				
			end

endmodule
		