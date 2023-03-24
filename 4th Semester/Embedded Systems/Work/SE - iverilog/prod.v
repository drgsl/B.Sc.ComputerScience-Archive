module ceas(c);
output reg c;
always
	#5 c=~c;
initial
	c=0;
endmodule

module produs(Clk,start,nr1, nr2,prod,ack);
input Clk, start;
input [3:0]nr1,nr2;
output reg [7:0]prod;
output reg ack;
reg [3:0]contor;
reg [1:0]state;
always @(posedge Clk)
	if(state==0)
		if(start==1) begin
			prod<=0;
			ack<=0;
			contor<=0;
			state<=1;
		end
	    else state<=0;
	else if(state==1)
		if(contor==nr1) begin
			state<=2;
		end
		else begin
			prod<=prod+nr2;
			contor<=contor+1;
			state<=1;
		end
	else if(state==2) begin
		ack<=1;
		state<=0;
	end
initial 
begin
    state<=0;
	ack<=0;
end
endmodule

module main();
reg start;
reg [3:0]A,B;
wire [7:0]C;
wire Clk,ack;
produs p(Clk,start,A,B,C,ack);
ceas c(Clk);
initial
begin
	$monitor("%d %d %d %d %d",$time,A,B,C,ack);
	start=0;
    A=7;
	B=10;
    #2 start=1;
    #5 start=0;
    #100 $finish();
end
endmodule
		
