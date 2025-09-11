// Abraham Rock
// September 7th, 2025
// E155 - Microprocessors

// Module to output to pull-up 7-Segment-Displays.

module seven_seg_ar(input logic [3:0] s_1, s_2,
	output logic [6:0] seg_1, seg_2);

	seg_1 = seg_decoder(s_1);
	seg_2 = seg_decoder(s_2);

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