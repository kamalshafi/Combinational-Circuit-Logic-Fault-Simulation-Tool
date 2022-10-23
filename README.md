# Combinational-Circuit-Logic-Fault-Simulation-Tool

Implementation of a serial fault simulation tool in C language for combinational circuits. 


## Input Files 

The input to your program is an ISCAS-85 benchmark combinational circuit (.isc), corresponding file that contains the input vectors (.vec) and faults information (.faults).
".isc" This file contains information about the combinational circuit
vec: This file contains information about the input vectors (values at the primary inputs). Each line in this file is a input vector. The total number of characters in each line is equal to the number of primary inputs in the corresponding circuit. The characters in the line represents ’0’: logic zero, ’1’: logic one, ’x’: don’t care value. During simulation, the ’x’ is considered as ’2’. The .vec file contains only few input vector of all possible input vectors of the circuit.
.faults: This file contains information about the fault nodes and its struck at value of a particular circuit. Each line in this file is about the single stuck-at fault. The line 3n1 represents gate with the id ’3’ has struck at the value ’1’. The .faults file contains only few faults among all possible faults of the circuit

## Implementation
Run the make file with arrguments of input and output

## Output 
".Response" Contains data of logic simulation of the circuit
".result" contains data of the fault simulation of the circuit

The information provided in the first 2 inputs is storted in respective data structures. "readfault" fuction was created to read and store the fault informatin. 

First a fault free simulation of the circuit is done. Then one fault injected at a time and all the input patterns of that circuit is applied. If there is a difference between faultfree and faulty respose, the fault is observed at the output 
