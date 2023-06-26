#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;

main()
{
	const short 
        x_mon = 1000,
        y_mon = 1000,
        n = 16, //number of points
        k = 100, //coefficient space_monitor
        x_u = x_mon / 2, 
	    y_u = y_mon / 2,
	    radius = 4; //constants
	    
	float x_p_s[n] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0};
    float y_p_s[n] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1};
    float z_p_s[n] = {0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}; 
	
	float x_s_u = 0, 
	      y_s_u = 0, 
	      z_s_u = 0; //modifiable by keyboard input
	float x_monitor[n], 
	      y_monitor[n];
	float h = 0; 
	short value;
	
	initwindow(x_mon, y_mon);
	
	do{ 
	    float *x_p_u = new float[n];
	    float *y_p_u = new float[n];
	    float *z_p_u = new float[n];
	
	    for(short i = 0; i < n; i++) {
		    x_p_u[i] = x_s_u + x_p_s[i];
		    y_p_u[i] = y_s_u + y_p_s[i];
		    z_p_u[i] = z_s_u + z_p_s[i];
	    }
	
	    for(short i = 0; i < n; i++) {
	    	float *coeff_gomotetia = new float((z_p_u[i] + radius) / radius);
	        x_monitor[i] = x_p_u[i] / *coeff_gomotetia;
	        y_monitor[i] = y_p_u[i] / *coeff_gomotetia;
	        delete coeff_gomotetia;
	    }
	
	    for(short i = 0; i < n - 1; i++) {
		    int x_start = x_u + x_monitor[i] * k;
	        int y_start = y_u - y_monitor[i] * k;
	        int x_end = x_u + x_monitor[i + 1] * k;
	        int y_end = y_u - y_monitor[i + 1] * k;
	        line(x_start, y_start, x_end, y_end);
	    }
	    
	    value = getch();
	    switch(value) {
	    	case 43: if(z_s_u > 0) z_s_u -= 0.1; break;
            case 45: z_s_u += 0.1; break;
            case 72: y_s_u += 0.1; break;
            case 80: y_s_u -= 0.1; break;
            case 75: x_s_u -= 0.1; break;
            case 77: x_s_u += 0.1; break;
		}
	    
	    delete [] x_p_u;
	    delete [] y_p_u;
	    delete [] z_p_u;
	    clearviewport();
	    
	} while(value != 27);
	
	//getch();
	closegraph();
	return 0;
}

