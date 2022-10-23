#include "input.h"
/***************************************************************************************************
Command Instructions
***************************************************************************************************/
//To Compile: make
//To Run: ./project c17.isc 
/***************************************************************************************************
 Main Function
***************************************************************************************************/
int main(int argc,char **argv)
{
FILE *Isc,*Pat,*faults,*Res,*result;                  //File pointers used for .isc, .pattern, and .res files
int Npi,Npo,Tgat;                     //Tot no of PIs,Pos,Maxid,Tot no of patterns in.vec,.fau
GATE *Node;                           //Structure to store the ckt given in .isc file 
  FAULT stuck[Mft];                      //structure used to store the faults information in .faults file                          
int Tpat,Tfs;
PATTERN Patterns[Mpt];




/****************PART 1.-Read the .isc file and store the information in Node structure***********/
Npi=Npo=Tgat=0;                                //Intialize values of all variables
Isc=fopen(argv[1],"r");                        //File pointer to open .isc file 
Node=(GATE *) malloc(Mnod * sizeof(GATE));     //Dynamic memory allocation for Node structure
Tgat=ReadIsc(Isc,Node);                        //Read .isc file and return index of last node
fclose(Isc);                                   //Close file pointer for .isc file
PrintGats(Node,Tgat);                          //Print the information of each active gate in Node structure after reading .isc file
CountPri(Node,Tgat,&Npi,&Npo);                 //Count the No of Pis and Pos
printf("\n\nNpi: %d Npo: %d\n",Npi,Npo);           //Print the no of primary inputs and outputs
/***************************************************************************************************/
Pat=fopen(argv[2],"r");                        //File pointer to open .pat file 
Tpat=ReadPat(Pat,Patterns);                    //Read .isc file and return index of last node
fclose(Pat);				      //close the file

faults=fopen(argv[3],"r");
Tfs=0;
Tfs=readfault(faults, stuck);
fclose(faults);
result=fopen(argv[4],"w");
faultsim(Node, Patterns,stuck,Tgat, Tpat,Tfs, result);
fclose(result);
/****************************************************************************************************************************/
// clearGat(Node,Tgat); free(Node);
return 0;
}
