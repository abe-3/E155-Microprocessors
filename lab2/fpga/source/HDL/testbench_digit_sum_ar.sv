`timescale 1 ns / 1 ps

module testbench_digit_sum_ar();
	logic clk, reset;
	logic [3:0] s_1, s_2;
	logic [4:0] sum, not_sum;
	
	logic [31:0] errors;
	logic [7:0] counter;
	
	digit_sum dut(s_1, s_2, not_sum);
	assign sum = ~not_sum;
	
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
		counter <= counter + 1;
		s_1 <= counter[3:0];
		s_2 <= counter[7:4];
		
		if(!reset) begin
			assert(sum == s_1 + s_2) else begin
				errors = errors + 1;
				$error("Sum Error. Expected: %b. Got: %b.", s_1+s_2, sum);
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
	
	function automatic logic [6:0] seg_decoder(input logic[3:0] sw);
		case(sw)
			4'b1111: seg_decoder =	7'b1000000;	// 0
			4'b1110: seg_decoder =	7'b1111001;	// 1
			4'b1101: seg_decoder =	7'b0100100;	// 2
			4'b1100: seg_decoder =	7'b0110000;	// 3
			4'b1011: seg_decoder =	7'b0011001;	// 4
			4'b1010: seg_decoder =	7'b0010010;	// 5
			4'b1001: seg_decoder =	7'b0000010;	// 6
			4'b1000: seg_decoder =	7'b1111000;	// 7
			4'b0111: seg_decoder =	7'b0000000;	// 8
			4'b0110: seg_decoder =	7'b0010000;	// 9
			4'b0101: seg_decoder =	7'b0001000;	// A
			4'b0100: seg_decoder =	7'b0000011;	// b
			4'b0011: seg_decoder =	7'b1000110;	// C
			4'b0010: seg_decoder =	7'b0100001;	// d
			4'b0001: seg_decoder =	7'b0000110;	// E
			4'b0000: seg_decoder =	7'b0001110;	// f
			default: seg_decoder =	7'b1111111; // all off
		endcase
	endfunction
endmodule