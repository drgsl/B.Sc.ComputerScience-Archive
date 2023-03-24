module Clock (c);
output reg c;
initial 
    c=0;
always
    #5 c = ~c;
endmodule


module ROM(Clk,start, addr, data, rd);
input Clk, rd;
input [7:0]addr;
input [0:0]start;
output reg [7:0]data;
reg[7:0]mem[255:0];
reg[3:0]stare;

reg[2:0] stare_urm;


integer i;
initial begin
    stare = 0;
    for(i=0; i<=255; i++)
    mem[i] = i;
end

always @(posedge Clk)
if(start == 1)
    if(stare == 0)
    begin
        stare <= 1;
    end
        else if(stare == 1)
        begin
            stare <=0;
        end
endmodule

module main();

wire Clk;
Clock cc(Clk);
reg[7:0]addr;
wire[7:0]data;
reg[0:0]start;
reg[0:0]rd;
ROM rom(Clk, start, addr, data, rd);
initial
begin
    $monitor("%d", data);
    start = 1;
    addr =5;
    #5 $finish();
end
endmodule