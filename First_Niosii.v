module First_Niosii
(
		CLOCK_50,
		LED
);
input CLOCK_50;
output [7:0] LED;

De0_Nano_Qsys2019 DE0_NANO_QSYS_inst
(
		.clk_clk (CLOCK_50),
		.pio_led_external_connection_export(LED),
		.reset_reset_n(1'b1)
);
endmodule