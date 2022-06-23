
module num_7seg_B (out,w,x,y,z);

input w,x,y,z;
output out;

wire out1,out2,out3;

assign out1 = ~y & ~z;
assign out2 = x & ~y;
assign out3 = x & ~z;

assign out = w | out1 | out2 | out3;

endmodule