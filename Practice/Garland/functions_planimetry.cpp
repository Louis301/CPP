#include <graphics.h>
#include <iostream>
#include <Windows.h>
#include <Conio.h>
#include <math.h>
using namespace std;

#define x_monitor 500
#define y_monitor 500
int k = 20, 
      x_u = x_monitor / 2,
	  y_u = y_monitor / 2;


main()
{
	initwindow(x_monitor, y_monitor);
	
	float x_user, y_user;
	float x_start, y_start, x_end, y_end;
	float koaf = 1;
	short value;
	int i2 = 0;
	
	do{ 
	    setcolor(10);
	    for(short i = 0; i < x_u; i += 14) {
	        line(x_u + i2 * k, y_u - k * 14, x_u + i2 * k, y_u + k * 14);	
	        line(x_u - i2 * k, y_u - k * 14, x_u - i2 * k, y_u + k * 14);
	        line(x_u - k * 14, y_u - i2 * k, x_u + k * 14, y_u - i2 * k);
	        line(x_u - k * 14, y_u + i2 * k, x_u + k * 14, y_u + i2 * k);
	        i2++;
		} i2 = 0;
		
		setcolor(14);
	    line(0, y_u, x_monitor, y_u); //oX
	    line(x_u, 0, x_u, y_monitor); //oY
		
		//===================================================
	
	    for(float i = -x_u / 14; i < x_u / 14; i += 0.2) {
	    	x_user = i;
	    	
	    	y_user = x_user * x_user; //user's function
	    	x_end = x_u + x_user * k;
	        y_end = y_u - y_user * k;
	        
	        if(i == -x_u / 14) goto a;
	
	        setcolor(15);
	        line(x_start, y_start, x_end, y_end);
	        
	        a:  
			x_start = x_end;
	        y_start = y_end;
		}
	    
	    value = getch();
	    switch(value) {
	    	case 43: k += 1; break;
            case 45: k -= 1; break;
            case 72: y_u += 10; break;
            case 80: y_u -= 10; break;
            case 75: x_u += 10; break;
            case 77: x_u -= 10; break;
		}
	    
	    clearviewport();
	    
	} while(value != 27);
	
	//getch();
	closegraph();
	return 0;
}
