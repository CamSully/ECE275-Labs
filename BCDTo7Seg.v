// BCD to 7-segment display.
// Input is hex number, output is 7-bit binary to control each LED segment.
// Note ~ operator performs 1's complement.

module BCDTo7Seg(hex, leds);
	input [3:0] hex;
	output reg [6:0] leds;
	
	always @(hex)
		case (hex)
			0: leds =~ 7'b1111110;
			1: leds =~ 7'b0110000;
			2: leds =~ 7'b1101101;
			3: leds =~ 7'b1111001;
			4: leds =~ 7'b0110011;
			5: leds =~ 7'b1011011;
			6: leds =~ 7'b1011111;
			7: leds =~ 7'b1110000;
			8: leds =~ 7'b1111111;
			9: leds =~ 7'b1111011;
			10: leds =~ 7'b1110111;
			11: leds =~ 7'b0011111;
			12: leds =~ 7'b1001110;
			13: leds =~ 7'b0111101;
			14: leds =~ 7'b1001111;
			15: leds =~ 7'b1000111;
		endcase
	
	endmodule