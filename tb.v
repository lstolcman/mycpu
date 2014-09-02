`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   19:47:41 01/21/2014
// Design Name:   cpu_v1
// Module Name:   C:/dev/projects/Xilinx/cpu_ostateczne/tb.v
// Project Name:  cpu_ostateczne
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: cpu_v1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb;

	// Inputs
	reg clk;
	reg rst;

	// Outputs
	wire [7:0] Aout;
	wire [7:0] Bout;
	wire [9:0] PCout;
	wire [13:0] IRout;
	wire Zout;
	wire Cout;

	// Instantiate the Unit Under Test (UUT)
	cpu_v1 uut (
		.clk(clk), 
		.rst(rst), 
		.Aout(Aout), 
		.Bout(Bout), 
		.PCout(PCout), 
		.IRout(IRout), 
		.Zout(Zout), 
		.Cout(Cout)
	);

	always
	begin
		clk = ~clk;
		#50;
	end
	
	initial begin
		// Initialize Inputs
		clk = 0;
		rst = 0;

		// Wait 100 ns for global reset to finish
		#100;
		
		rst=1;
        
		// Add stimulus here

	end
      
endmodule

