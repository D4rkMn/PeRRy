// general purpose
POP: pops top of stack
STP: stop program

// scope
MST: mark stack for scope
RET: exit scope and restore stack

// function defining and calling
ENT name (function name): declare function start
MSTp: mark stack for procedure
RETn: exit procedure and restore stack
RETv: exit procedure, restore stack but keep top of stack (return value)
CUP name (function name): call procedure (takes params as top of stack)

// values for stack
LDA x: push address of variable x 
LDCc x: push constant value x
LODc x: push value of variable x

// storing for variables
STOc: store first top of stack into second tops address (pops twice)
INCc: add first top of stack to second top address (pops twice)
SROc x: store top of stack into address of variable x (pops stack)

// branching
Lk (k is a number): label k
UJP Lk (k is a number): jump to label Lk
FJP Lk (k is a number): jump to label Lk if top of stack is false (pops stack)

// binary operations (double pop as operands, push result)
ADI: integer addition
SBI: integer substraction
MPI: integer multiplication
DVI: integer division
LESc: logical less than
LEQc: logical less equals
GRTc: logical greater than
GEQc: logical greater equals
EQUc: logical equals
NEQc: logical not equals

// unary operations (pops as operand, push result)
NGI: makes value negative
NOT: logical not

// print
PRINT: print top of stack and pop it
PRINTLN: print endline (\n)