

module excess3_dataflow(X, S, V, clock);
	input X, clock;
	output S, V;
	
	reg Q1, Q2, Q3; //Q1 and Q2 is the state, Q3 is the carry
	reg o;
	
	initial begin
		Q1 <= 1'b0;
		Q2 <= 1'b0;
		Q3 <= 1'b0;
	end
	
	//(~X & ~Q1 & ~Q3) | (X & ~Q1 & Q2 & Q3) | (X & Q1 & ~Q3) | (~X & Q1 & Q3) | (~X & ~Q1 & ~Q2);
	assign S = (!Q1 && !Q2 && !X) || (!Q1 && Q2 && !(X ^ Q3)) || (Q1 && !Q2 && (X ^ Q3)) || (Q1 && Q2 && (X^Q3));
	assign V = (!Q1 && !Q2 && Q3);
	
	
	always @(posedge clock) begin
		Q1 <= (~Q1 & Q2) | (Q1 & ~Q2);
		Q2 <= ~Q2;
		Q3 <= (X & Q3) | (X & ~Q1 & Q2) | (~Q1 & Q2 & Q3) | (~Q1 & ~Q2 & X);
		
		
	end

endmodule


/*

state table 
a	c	c	10	00		
b	c	d	11	01
c	e	f	10	00
d	f	f	00	10
e	g	g	00	10
f	g	h	10	00
g	a	a	00	10
h	a	b	10	00
*/

/*     Simplification Routine:  PI Chart

D(Q1)  =  Q1'Q2 + Q1 Q2' 

D(Q2)  =  Q2' 

D(Q3)  =  X1 Q3 + X1 Q1'Q2 + Q1'Q2 Q3 

Z1  =  X1'Q1'Q3' + X1 Q1'Q2 Q3 + X1 Q1 Q3' + X1'Q1 Q3 + X1'Q1'Q2' 

Z2  =  Q1'Q2'Q3 
*/