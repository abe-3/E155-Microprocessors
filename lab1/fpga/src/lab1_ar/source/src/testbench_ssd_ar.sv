`timescale 1 ns / 1 ps // sets #1 as a 1 ns delay

module testbench_ssd_ar();
	logic	clk, reset;
	logic [3:0] s;
	logic [6:0] seg, seg_expected;
	
	logic [31:0] vectornum, errors;
	logic [3:0] testvectors[10000:0];
	
	seven_seg_ar dut(s, seg);
	
	// generate clock
	always begin
		clk = 1; #5; clk = 0; #5;
	end
	
	// at start of test, load vectors and pulse reset
	initial begin
		$readmemb("seg.tv", testvectors);
		vectornum = 0; errors = 0;
		reset = 1; #22; reset = 0;
	end
	
	always @(posedge clk) begin
		#1; {s, seg_expected} = testvectors[vectornum];
	end
	
	// check results on falling edge of clk
	always @(negedge clk)
		if (~reset) begin // skip during reset
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