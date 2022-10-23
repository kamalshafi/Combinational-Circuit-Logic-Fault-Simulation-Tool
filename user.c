#include "input.h"
/***************************************************************************************************************************
Truth Table
****************************************************************************************************************************/
int NOTG[5] = {1,0,DC,Db,D};
int ANDG[5][5]={{0,0,0,0,0},{0,1,DC,D,Db},{0,DC,DC,DC,DC},{0,D,DC,D,0},{0,Db,DC,0,Db}};
int ORG[5][5]={{0,1,DC,D,Db},{1,1,1,1,1},{DC,1,DC,DC,DC},{D,1,DC,D,1},{Db,1,DC,1,Db}};
int NOC[10]={0,0,0,0,0,1,1,0,0,0};
int fault[3][3]={{0,D,DC},{Db,1,DC},{DC,DC,DC}};

int ReadPat(FILE *Pat, PATTERN *Patterns){
	char line[Mlin];
	int n,i;
	while(!feof(Pat)){
		if(fgets(line,Mlin,Pat)!=NULL){//reads the characters in the stream
			for(n=0;n<strlen(line);n++){//strlen=measures the string length
				if(line[n]=='1')			Patterns[i].Pat[n]=1;
				else if(line[n]=='0')			Patterns[i].Pat[n]=0;
				else if(line[n]=='x'||line[n]=='X')	Patterns[i].Pat[n]=DC;
			}
			i++;
			if(i==100) break;
		}
	}
	return i; //total number of patterns
}

int readfault(FILE *faults,FAULT *stuck){
	int i=0;	
	char line[Mft];
	char arr[2][Mft];
	while(fgets(line,Mft ,faults)!=NULL){
			char *token = strtok(line,"/"); //splits the string 
			int j=0;
			while(token!=NULL)
			{
				strcpy(arr[j],token);
				token= strtok(NULL,"/");
				j++;
			}
			stuck[i].GateNum=atoi(arr[0]);
			stuck[i].Gateval=atoi(arr[1]);
			printf("%d\n",stuck[i].GateNum);
			printf("%d\n",stuck[i].Gateval);
			i++;
	}
return i;
}		
	

void LogicSim(GATE *Node, PATTERN *Patterns, int Tgat, int Tpat, FILE *Res)
{
	int i,j,k; //i=total patterns,j=total gates
	for(i=0;i<Tpat;i++){
		k=0;
printf(" %d\n", i);
		for(j=0;j<=Tgat;j++){printf("%d",i);//getchar();
			if(Node[j].Type !=0){
				if(Node[j].Type==INPT){
					Node[j].Val = Patterns[i].Pat[k];
					k++;
				}
				else{
					Gout(Node, j);
				}
				if(Node[j].Po) {
					printf("%d",Node[j].Val);
					if(Node[j].Val==2) fputc('x' , Res);
					else fputc(Node[j].Val+'0' , Res);
				}
			}
		}//PrintGats(Node,Tgat); 

		printf("\n");
		fputc('\n', Res);
	}
}

void faultsim(GATE *Node, PATTERN *Patterns,FAULT *stuck, int Tgat, int Tpat,int Tfs, FILE *result)
{
int i,j,k,a; //i=total number of patterns,j=total # gates
int detected;
	for(a=0;a<Tfs;a++){
		Node[stuck[a].GateNum].Fval= stuck[a].Gateval;
		fprintf(result,"%d %d:\n",stuck[a].GateNum,stuck[a].Gateval);
		for(i=0;i<Tpat;i++){
			k=0;detected=0;
			printf(" %d\n", i);
			for(j=0;j<=Tgat;j++){
				if(Node[j].Type !=0){
					if(Node[j].Type==INPT){
						Node[j].Val = Patterns[i].Pat[k];
						if(Node[j].Val==2) fputc('x' , result);
						else fputc(Node[j].Val+'0' , result);
						k++;
					}
					else{
						Gout(Node, j);
					}
					if(Node[j].Fval!=6){
							Node[j].Val = fault[Node[j].Fval][Node[j].Val];//
					} 
				if(Node[j].Po){
					if((Node[j].Val==3)||(Node[j].Val==4))
						detected=1;
						}
				}
			}if(detected) fprintf(result,"  Detected\n");
			else  fprintf(result," NotDetected\n");
		}
		Node[stuck[a].GateNum].Fval=6;
		fprintf(result,"\n");
	}//PrintGats(Node,Tgat); 

}		

void Gout(GATE *Node, int a)
{
	LIST *lfin;
	int val; // local variable
	if(Node[a].Type==FROM){
		lfin=Node[a].Fin;
		while(lfin!=NULL){
			Node[a].Val=Node[lfin->Id].Val; 
			lfin=lfin->Next;
		}
	}
	else if(Node[a].Type==BUFF){
		lfin=Node[a].Fin;
		while(lfin!=NULL){
			Node[a].Val=Node[lfin->Id].Val; 
			lfin=lfin->Next;
		}
	}
	else if(Node[a].Type==NOT){
		lfin=Node[a].Fin;
		while(lfin!=NULL){
			Node[a].Val=NOTG[Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		}
	}
	else if(Node[a].Type==AND){
		lfin=Node[a].Fin;
		val=Node[lfin->Id].Val;// non control for AND gate
		lfin=lfin->Next;
		while(lfin!=NULL){
			val=ANDG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		}
		Node[a].Val=val;
	}
	else if(Node[a].Type==NAND){
		lfin=Node[a].Fin;
		val=Node[lfin->Id].Val;
		lfin=lfin->Next;// non control for AND gate
		while(lfin!=NULL){
			val=ANDG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		}
		Node[a].Val=NOTG[val];
	}
	else if(Node[a].Type==OR){
		lfin=Node[a].Fin;
		val=Node[lfin->Id].Val;// non control for OR gate
		lfin=lfin->Next;
		while(lfin!=NULL){
			val=ORG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		 }
		Node[a].Val=val;
	}
	else if(Node[a].Type==NOR){
		lfin=Node[a].Fin;
		val=Node[lfin->Id].Val;// non control for nOR gate
		lfin=lfin->Next;
		while(lfin!=NULL){
			val=ORG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		 }
		Node[a].Val=NOTG[val];
	}
	else if(Node[a].Type==XOR) {printf("ERROR: XOR GATE FOUND\n");exit(0);}
	else if(Node[a].Type==XNOR){printf("ERROR: XNOR GATE FOUND\n");exit(0);}
}

/***************************************************************************************************/

