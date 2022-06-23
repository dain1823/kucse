/* half adder */
module ha (
	input x,
	input y,
	output s,
	output c);

assign s = x^y;
assign c = x&y;

endmodule

/* full adder */
module fa (
	input x,
	input y,
	input z,
	output s,
	output c);

wire p, g, cc;

ha HA1 (.x(x), .y(y), .s(p), .c(cc));

assign c = cc | g;

endmodule

/* carry look ahead generator */
module cla_gen #(parameter W = 4)(P, G, C0, C);
input[W-1:0] P, G;
input C0;
output[W:0] C;

assign C[0] = C0;

for (i = 0; i < W; i=i+1)
begin
	assign C[i+1] = G[i] + P[i]*C[i];
end

endmodule

/* cla adder and subtractor */
module addsub_cla (A, B, S, C, M, V);
parameter W=4;
input[W-1:0] A, B;
output[W-1:0] S;
output C;
input M;
output V;

wire[W-1:0] P, G;
wire[W:0] carry;
wire[W-1:0] b;

genvar i;

for (i = 0; i < W; i=i+1)
begin
	assign b[i] = B[i]^M;
end

for (i = 0; i < W; i=i+1)
begin: adc_ha
	ha HA(.x(A[i]), .y(b[i]), .s(P[i]), .c(G[i]));
end

cla_gen #(W) CLAGEN (.P(P), .G(G), .C0(M), .C(carry));

for (i = 0; i < W; i=i+1)
begin
	assign S[i] = carry[i]^P[i];
end

assign C = carry[W];

assign V = carry[W]^carry[W-1];

endmodule