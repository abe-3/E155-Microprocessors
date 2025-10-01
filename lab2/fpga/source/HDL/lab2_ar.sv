// Abraham Rock
// September 7th, 2025
// E155 - Microprocessors

// Top Level Module to control multiplexed power and
// combinational output of 7-Segment-Display

module lab2_ar(
	input logic reset,
	input logic [3:0] s_1, s_2,
	output logic [6:0] seg,
	output logic display_select, not_display_select,
	output logic [4:0] sum);

	logic int_osc;
	logic [4:0] not_sum;
	logic [6:0] decoded_seg1, decoded_seg2;

	// Internal high-speed oscillator
	HSOSC #(.CLKHF_DIV(2'b01))
		hf_osc (.CLKHFPU(1'b1), .CLKHFEN(1'b1), .CLKHF(int_osc));
		
	// Multiplexing Clock
	display_mux_ar mux_controller(int_osc, ~reset, display_select, not_display_select);
	
	// Control combinatonal logic of 7-Segment-Displays 
	seven_seg_ar sevenModule(~s_1, ~s_2, decoded_seg1, decoded_seg2);
	
	// Makes sure if 1 display is on, other is off
	always_comb begin
		if (~reset) begin
			seg = 7'b1111111;
		end else if (display_select == 0) begin
			seg = decoded_seg1;
		end else if (display_select == 1) begin
			seg = decoded_seg2;
		end else begin
			seg = 7'b1111111;
		end
	end
	
	// Digit Sum
	digit_sum_ar digit_adder(s_1, s_2, not_sum);
	assign sum = ~not_sum;
endmodule