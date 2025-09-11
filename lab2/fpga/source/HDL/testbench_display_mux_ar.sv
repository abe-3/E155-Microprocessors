`timescale 1 ns / 1 ps

module testbench_display_mux_ar();
	logic clk, reset;
	logic display_select, not_display_select;
	
	logic [31:0] errors;
	logic [7:0] counter;
	
	display_mux_ar dut(clk, reset, display_select, not_display_select);
	
	// Generate Clock
	always begin
		clk = 1; #5; clk = 0; #5;
	end
	
	// at start of test, pulse reset
	initial begin
		errors = 0; counter = 0;
		reset = 1; #22; reset = 0;
	end
	
	always @(posedge clk) begin	
		if(!reset) begin
			if(display_select == 0) begin
				assert(not_display_select == 0) else begin
					errors = errors + 1;
					$error("display_select: %b, not_display_select: %b", display_select, not_display_select);
				end
			end else begin
				assert(not_display_select == 1) else begin
					errors = errors + 1;
					$error("display_select: %b, not_display_select: %b", display_select, not_display_select);
				end
			end
		end
	end
	
	always @(negedge clk) begin
		if(counter == 8'hFF) begin
			$display(	"All tests completed with %d errors",
							errors);
			$stop;
		end
	end
endmodule