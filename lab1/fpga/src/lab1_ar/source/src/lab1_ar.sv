// Abraham Rock
// arock@hmc.edu
// August 27, 2025

module lab1_ar(input logic reset,
	input logic [3:0] s,
	output logic [2:0] led, 
	output logic [6:0] seg);
	
	logic int_osc;
	
	// Internal high-speed oscillator
	HSOSC #(.CLKHF_DIV(2'b01)) 
		hf_osc (.CLKHFPU(1'b1), .CLKHFEN(1'b1), .CLKHF(int_osc));
	
	leds_ar blinkModule(int_osc, reset, s, led);
	seven_seg_ar sevenModule(s, seg);
	
endmodule