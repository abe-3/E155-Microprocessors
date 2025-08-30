// Abraham Rock
// arock@hmc.edu
// August 27, 2025

module lab1_ar(input logic [3:0] s,
	output logic [2:0] led,
	output logic [6:0] seg);
	
	 // Internal high-speed oscillator
   HSOSC #(.CLKHF_DIV(2'b01)) 
         hf_osc (.CLKHFPU(1'b1), .CLKHFEN(1'b1), .CLKHF(int_osc));
	
	logic [24:0] counter;
	
	assign led[0] = s[0] ^ s[1];	// switch 0 XOR switch 1
	assign led[1] = s[2] & s[3];	// switch 2 AND switch 2 
	
	always_ff @(posedge int_osc)
		begin
			if(counter == 25'd5000000) begin
				led[2] <= ~led[2]; 
				counter <= 0;
			end else begin
				counter <= counter + 1;
			end
		end
endmodule