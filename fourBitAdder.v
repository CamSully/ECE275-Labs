// 4-bit adder


// Create a module with ports carryI, X, Y, and S.
module fourBitAdder(X, Y, S);
	// Set X, Y as 4-bit vectors.
	input[3:0] X, Y;
	// Set the sum as a 4-bit vector.
	output reg [4:0] S;
	
	// Whenever X or Y changes, re-evaluate the sum.
	always @(X, Y)
		S = X + Y;
		
	endmodule