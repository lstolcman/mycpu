

`timescale 1ns / 1ps

module cpu_v1(clk, rst, Aout, Bout, PCout, IRout, Zout, Cout);

input clk;
input rst;

output [7:0]	Aout;
output [7:0]	Bout;
output [9:0]	PCout;
output [13:0]	IRout;
output Zout;
output Cout;


reg [7:0]	A;
reg [7:0]	B;
reg [9:0]	PC;
reg [13:0]	IR;
reg Z;
reg C;

reg [7:0] RAM[0:15];
reg [13:0] ROM[0:1023];


wire [3:0] OPCODE=IR[13:10];
wire [9:0] ADDRESS=IR[9:0];
wire [7:0] OPERATOR=IR[7:0];

assign Aout=A;
assign Bout=B;
assign PCout=PC;
assign IRout=IR;
assign Zout=Z;
assign Cout=C;



initial
begin

ROM[0] = 14'b1010_00_00000101; //mva 5
ROM[1] = 14'b0000_0000000000; //nop
ROM[2] = 14'b0000_0000000000; //nop
ROM[3] = 14'b0000_0000000000; //nop
ROM[4] = 14'b0001_00_00000100; //mvb 4
ROM[5] = 14'b0000_0000000000; //nop
ROM[6] = 14'b0000_0000000000; //nop
ROM[7] = 14'b1010_00_11111111; //mva 255
ROM[8] = 14'b0001_00_00000001; //mvb 1
ROM[9] = 14'b1111_0000000000; //sub
ROM[10] = 14'b0001_00_00000011; //mvb 3
ROM[11] = 14'b1110_0000000000; //add
ROM[12] = 14'b0000_0000000000; //nop



end

always @(posedge clk)
begin
	if (~rst)
		begin
			PC <= 0;
			A <= 0;
			B <= 0;
			Z <= 0;
			C <= 0;
		end
	else
		begin
			IR <= ROM[PC];
			PC <= PC+1;
		end
end

always @(negedge clk)
begin
	case (OPCODE)
		4'b0000:		//nop
			A <= A;
			
		4'b1010:		//mva arg
			A <= OPERATOR;
			
		4'b0001:				//mvb arg
			B <= OPERATOR;
			
		4'b0010:				//load addr
			A <= RAM[ADDRESS];
		
		4'b0011:				//store addr
			RAM[ADDRESS] <= A;
		
		4'b0100:				//xchg
			begin
				A <= B;
				B <= A;
			end
			
		4'b0101:				//jmp addr
			PC <= ADDRESS;
		
		4'b0110:				//jz addr
			if (Z == 1'b1)
				PC <= ADDRESS;
			
		4'b0111:				//jc addr
			if (C == 1'b1)
				PC <= ADDRESS;
			
		4'b1000:		//jnz addr
			if (Z == 1'b0)
				PC <= ADDRESS;
				
			
		4'b1001:				//jnc addr
			if (C == 1'b0)
				PC <= ADDRESS;
		
		4'b1011:				//and
		begin
			A <= A&B;
			if ((A&B) == 8'b0)
				Z <= 1;
			else
				Z <= 0;
		end
			
		4'b1100:				//or
		begin
			A <= A|B;
			
			if ((A&B) == 8'b0)
				Z <= 1;
			else
				Z <= 0;
		end
		
		4'b1101:			//not
		begin
			A <= ~A;
			
			if ((A) == 8'b0)
				Z <= 1;
			else
				Z <= 0;
		end
		
		4'b1110:				//add
		begin
			A <= A + B;
			
			if ((A+B) < A)
				C <= 1;
			else
				C <= 0;
			
			if ((A+B) == 8'b0)
				Z <= 1;
			else
				Z <= 0;
		end
		
		4'b1111:				//sub
		begin
			A <= A - B;
			
			if ((A-B) > A)
				C <= 1;
			else
				C <= 0;
				
			if ((A - B) == 8'b0)
				Z <= 1;
			else
				Z <= 0;
		end
			

	endcase
	
end


endmodule








