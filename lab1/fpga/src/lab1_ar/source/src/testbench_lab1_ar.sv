`timescale 1 ns / 1 ps // sets #1 as a 1 ns delay

module testbench_lab1_ar();
	logic	clk, reset;
	logic [3:0] s;
	logic [2:0] led, led_expected;
	logic [6:0] seg, seg_expected;
	
	logic [31:0] vectornum, errors;
	logic [15:0] testvectors[10000:0];
	
	lab1_ar dut(reset, s, led, seg);
	
	// generate clock
	always begin
		clk = 1; #5; clk = 0; #5;
	end
	
	// at start of test, load vectors and pulse reset
	initial begin
		$readmemb("leds.tv", testvectors);
		vectornum = 0; errors = 0;
		reset = 1; #22; reset = 0;
	end
	
	always @(posedge clk) begin
		#1; {s, led_expected} = testvectors[vectornum];
		#1; {s, seg_expected} = testvectors[vectornum];
	end
	
	// check results on falling edge of clk
	always @(negedge clk)
		if (~reset) begin // skip during reset
			if (led !== led_expected) begin
				$display("Error: inputs = %b", {s});
				$display(" outputs = %b (%b expected)", led, led_expected);
				errors = errors + 1;
			end
			if (seg !== seg_expected) begin
				$display("Error: inputs = %b", {s});
				$display(" outputs = %b (%b expected)", seg, seg_expected);
				errors = errors + 1;
			end
			vectornum = vectornum + 1;
			if (testvectors[vectornum] === 4'bx) begin
				$display(	"%d tests completed with %d errors",
							vectornum, errors);
				$stop;
			end
		end
endmodule
