//LOGO 
#include <stdio.h>
#include <Windows.h> 
#include <Conio.h> 
#define size 15

main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int x, y, i, j, a[size][size]={0}, b[size]={0}, command, x1=0, y1=0, line, x2, y2, z, z1, pero=1; 

printf("����� ���������� � ����.\n\n��� ��������� ������������ ��� �������� ������������, \n"
       "�������������� � ������������ �����\n�� �������� ��������� ����� (�� ��������� �=0; �=0). \n"
       "\n����� �������� � ������� ������:"
       "\n-----------------------------------------\n1 - ����� �����\n2 - ����� ������\n3 - ����� ����\n4 - ����� �����"
       "\n5 - ����� ��������� ����� \n"
	   "12 - ����� �����-������\n32 - ����� ����-������\n34 - ����� ����-�����\n14 - ����� �����-�����\n6 - ��������� ���� (0 - �������, 1 - ��������"
	    ", \n                    2 - ������� ���������)\n"
	   "0 - ����� ������, ����� �� ���������\n-----------------------------------------\n");
	
do{
	printf("������� �������: ");
	scanf("%d", &command); 
	
	if(command==0) break;

	if(command==5) {
	    printf("x: " ); scanf("%d", &x1);
		printf("y: " ); scanf("%d", &y1);
	} 

	if(command==3 || command==2) {
	    printf("������� ����� �����: "); 
	    scanf("%d", &line); 
	    x2=x1+line;
	    y2=y1+line;
    }
    
    if(command==1 || command==4) {
	    printf("������� ����� �����: "); 
	    scanf("%d", &line); 
	    z=x1; x2=z-line;
	    z1=y1; y2=z1-line;
    }
    
    if(command==32) {
	    printf("������� ����� �����: "); 
	    scanf("%d", &line); 
	    x2=x1+line;
	    y2=y1+line;
    }
    
    if(command==12) {
	    printf("������� ����� �����: "); 
	    scanf("%d", &line); 
	    z=x1; x2=x1+line;
	    z1=y1; y2=y1-line;
    }
    
    if(command==34) {
	    printf("������� ����� �����: "); 
	    scanf("%d", &line); 
	    x2=x1-line;
	    y2=y1+line;
    } 
    
    if(command==14) {
	    printf("������� ����� �����: "); 
	    scanf("%d", &line); 
	    z=x1; x2=x1-line;
	    z1=y1; y2=y1-line;
    }
    
    if(command==6) {
    	printf("����: "); 
	    scanf("%d", &pero); 
	}
        
	for(y=0; y<=size-1; y++) {
		for(x=0; x<=size-1; x++) {
			if(command==2) {				
			    if(x==x1+1 && x<=x2 && y==y1) {if(pero==1) {a[y][x]=1; x1++;} 
				                               if(pero==2) {a[y][x]=0; x1++;}
											   if(pero==0) x1++;} 				
			} 

			if(command==3) { 	
			    if(y==y1+1 && y<=y2 && x==x1) {if(pero==1) {a[y][x]=1; y1++;} 
				                               if(pero==2) {a[y][x]=0; y1++;} 
											   if(pero==0) y1++;} 				
			}  	
			
			if(command==4) { 	
			    if(x==x2 && x<=z-1 && y==y1) {if(pero==1) {a[y][x]=1; x2++; x1--;} 
				                              if(pero==2) {a[y][x]=0; x2++; x1--;}
											  if(pero==0) {x2++; x1--;}} 				
			}                               
			
			if(command==1) { 	
			    if(y==y2 && y<=z1-1 && x==x1) {if(pero==1) {a[y][x]=1; y2++; y1--;} 
				                               if(pero==2) {a[y][x]=0; y2++; y1--;}
											   if(pero==0) {y2++; y1--;}} 				
			}  	
			
			if(command==32) { 	
			    if(x==x1+1 && y==y1+1 && (x1+y1)%2==(x2+y2)%2 && x<=x2 && y<=y2) {if(pero==1) {a[y][x]=1; x1++; y1++;} 
				                                                                  if(pero==2) {a[y][x]=0; x1++; y1++;}
																				  if(pero==0) {x1++; y1++;}} 			
			}  
			
			if(command==12) { 	
			    if(x==x2 && y==y2 && (x2+y2)==(z+z1) && x>=z+1 && y<=z1+1) {if(pero==1) {a[y][x]=1; x2--; y2++; x1++; y1--;} 
				                                                            if(pero==2) {a[y][x]=0; x2--; y2++; x1++; y1--;}
																			if(pero==0) {x2--; y2++; x1++; y1--;}} 				
			} 
			
			if(command==34) { 	
			    if(x==x1-1 && y==y1+1 && (x2+y2)==(x1+y1) && x>=x2 && y<=y2) {if(pero==1) {a[y][x]=1; x1--; y1++;} else {x1--; y1++;}
				                                                              if(pero==2) {a[y][x]=0; x1--; y1++;}
																			  if(pero==0) {x1--; y1++;}} 				
			}  
			
			if(command==14) { 	
			    if(x==x2 && y==y2 && (x1+y1)%2==(x2+y2)%2 && x<=z-1 && y<=z1-1) {if(pero==1) {a[y][x]=1; x2++; y2++; x1--; y1--;} 
				                                                                 if(pero==2) {a[y][x]=0; x2++; y2++; x1--; y1--;}
				                                                                 if(pero==0) {x2++; y2++; x1--; y1--;}} 				
			} 	 		    
		}
	}

if(command!=6 && command!=5 && command!=7) {
	printf("\n ");
	for(i=0; i<=size-1; i++) printf("-");
	printf("\n");
	for(i=0; i<=size-1; i++) {
		printf("|");
		for(j=0; j<=size-1; j++) {
			if(a[i][j]==1) printf("*");
		    if(a[i][j]==0) printf(" ");
		    
	    }
	printf("\n");    
    }
    printf("\n"); 
}

} while(command!=0);

	return 0;
}


