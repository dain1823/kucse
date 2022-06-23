module huffman_decoder (
output [2:0] y,
input x,
input clk,
input reset
);
reg [3:0] state;
reg [3:0] next_state;

parameter S00 = 4'b0000, S01 = 4'b0001, S02 = 4'b0010,
S03 = 4'b0011, S04 = 4'b0100, S05 = 4'b0101,
S06 = 4'b0110, S07 = 4'b0111, S08 = 4'b1000,
S09 = 4'b1001, S10 = 4'b1010;

always @ (posedge clk or posedge reset)
if (reset == 1) state <= S00;
else state <= next_state;

always @(*)
begin
	case (state)
	S00: if(x) next_state = S02; else next_state = S01;
	S01: if(x) next_state = S02; else next_state = S01;//
	S02: if(x) next_state = S04; else next_state = S03;
	S03: if(x) next_state = S06; else next_state = S05;
	S04: if(x) next_state = S08; else next_state = S07;
	S05: if(x) next_state = S02; else next_state = S01;//
	S06: if(x) next_state = S02; else next_state = S01;//
	S07: if(x) next_state = S10; else next_state = S09;
	S08: if(x) next_state = S02; else next_state = S01;//
	S09: if(x) next_state = S02; else next_state = S01;//
	S10: if(x) next_state = S02; else next_state = S01;//
	default: next_state = 4'bxxxx;
	endcase
end	

assign y[0] = (~state[3]&~state[1]&state[0])|(state[3]&state[1]);
assign y[1] = (state[2]&~state[1]&state[0])|(state[3]&state[0])|(state[2]&state[1]&~state[0]);
assign y[2] = state[3];

endmodule