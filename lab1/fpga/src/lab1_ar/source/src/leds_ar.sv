// Abraham Rock
// arock@hmc.edu
// August 31, 2025

module leds_ar(input logic clk, reset,
	input logic [3:0] s,
	output logic [2:0] led);
	
	logic [24:0] counter;
	
	assign led[0] = ~s[0] ^ ~s[1];	// switch 0 XOR switch 1
	assign led[1] = ~s[2] & ~s[3];	// switch 2 AND switch 2
	
	always_ff @(posedge clk, posedge reset) begin
		if (reset) begin
			led[2] <= 0;
			counter <= 0;
		end else begin
			if(counter == 25'd5000000) begin
				led[2] <= ~led[2]; 
				counter <= 0;
			end else begin
			counter <= counter + 25'd1;
			end
		end
	end
endmodule