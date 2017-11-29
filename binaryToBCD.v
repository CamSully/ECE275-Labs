// 5-bit  binary to 2-digit BCD.

module binaryToBCD(binaryIn, tensDigit, onesDigit);
	input[4:0] binaryIn;
	output reg [3:0] tensDigit, onesDigit;
	
	always @(binaryIn)
	begin
		tensDigit = binaryIn / 10;
		onesDigit = binaryIn % 10;
	end	
	
	endmodule