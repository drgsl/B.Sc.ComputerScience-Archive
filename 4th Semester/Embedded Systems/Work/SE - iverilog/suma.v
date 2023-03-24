module sumator(nr1,nr2,cin,suma,cout);
input [3:0]nr1,nr2;
input cin;
output [3:0]suma;
output cout;
assign {cout,suma}=nr1+nr2+cin;
endmodule

module main();
reg [3:0]A,B;
reg Cin;
wire [3:0]C;
wire Cout;
sumator s(A,B,Cin,C,Cout);
initial
begin
	$monitor("%d %d %d %d %d",A,B,Cin,C,Cout);
	Cin=1;
	A=10;
	B=7;
end
endmodule

