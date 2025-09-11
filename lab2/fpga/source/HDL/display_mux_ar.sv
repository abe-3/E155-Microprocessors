// Abraham Rock
// Module to generate a high-speed switching signal for display multiplexing

module display_mux_ar(
	input logic clk, reset,
	output logic display_select, not_display_select);

	logic [24:0] counter;

	always_ff @(posedge clk, posedge reset) begin
		if (reset) begin
			counter <= 0;
			display_select <= 0;
		end else begin
			if(counter == 25'd200000) begin
				counter <= 0;
				display_select <= ~display_select; // Toggle displays
			end else begin
				counter <= counter + 1;
			end
		end
	end
	
	// To drive the other 7 Segment Display
	assign not_display_select = ~display_select;
	
endmodule