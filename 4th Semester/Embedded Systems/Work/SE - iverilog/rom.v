module ceas(c);
output reg c;
always
	#2 c=~c;
initial
	c=0;
endmodule

module ROM(Clk,address,data,rd);
input Clk,rd;
input [7:0]address;
output reg [7:0]data;
reg [7:0]mem[255:0];
reg [3:0]stare;

always @(posedge Clk)
    if(stare==0)
        if(rd==1) begin
            stare<=1;
        end
        else stare<=0;
    else if(stare==1)  begin
        stare<=2;
    end
    else if(stare==2) begin
        data<=mem[address];
        stare<=0;
    end

initial
begin 
    stare<=0;
    data<=0;
    mem[25]<=8;
end
endmodule

module main();
wire Clk;
reg rd;
reg [7:0] address;
wire [7:0]data;
reg [7:0]mem[255:0];
reg [3:0]stare;
ceas c(Clk);
ROM r(Clk,address,data,rd);
initial
begin
    $monitor("%d",data);
    address=25;
    rd=1;
    #4 rd=0;
    
end
endmodule

/*
initial
for(i=0;i<=255;i++)
    mem[i]<=i;
*/






    


