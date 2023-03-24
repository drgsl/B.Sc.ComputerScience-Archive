module ceas(c);
output reg c;
always
	#5 c=~c;
initial
	c=0;
endmodule

module main();
wire clk;
ceas cc(clk);
initial
begin
	$monitor();
	#50 $finish();
end

endmodule

