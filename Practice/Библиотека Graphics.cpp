#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <graphics.h>
#include <math.h>
#include <time.h>
using namespace std;

int main()
{
	int x_mon = 1000;
	int y_mon = 700;
	int n = 5;
	int k = 100, x_u = x_mon / 2, y_u = y_mon / 2;
	  
	double x_p_s[n];
    	double y_p_s[n];
    	double z_p_s[n * n]; 
    	double h = 0.7, begin = -n/2, end = n/2 / h;
    
	int i = 0, j = 0;
	for(double x = begin; x < end; x += h)
	{
		x_p_s[j] = x;
		y_p_s[j++] = x;
		for(double y = begin; y < end; y += h)
		{
			z_p_s[i++] = x*x * y*y + 2;
		}
	} i = 0; j = 0;
    
	double x_p_u[n];
	double y_p_u[n];
	double z_p_u[n * n];
	double x_s_u = 0,
	      y_s_u = 0,
	      z_s_u = 0;
	int radius = 5;
	double const_gomotetia;
	double x_monitor[n * n], y_monitor[n * n];
	int value;
	
	initwindow(x_mon, y_mon);
	
	do
	{ 
	    for(double x = begin; x < end; x += h)
		{
			for(double y = begin; y < end; y += h)
			{
				const_gomotetia = (z_s_u + z_p_u[i] + radius) / (float)radius;
				x_monitor[i] = (x_s_u + x) / const_gomotetia;
	        	y_monitor[i++] = (y_s_u + y) / const_gomotetia;
			}
		} i = 0;
	
	    for(short i = 0; i < n * n - 1; i++) {
		    int x_start = x_u + x_monitor[i] * k;
	        int y_start = y_u - y_monitor[i] * k;
	        int x_end = x_u + x_monitor[i + 1] * k;
	        int y_end = y_u - y_monitor[i + 1] * k;
	        line(x_start, y_start, x_end, y_end);
	    }
	    
	    value = getch();
	    switch(value) 
		{
	    	case 43: if(z_s_u > 0) z_s_u -= 0.1; clearviewport(); break; 
            case 45: z_s_u += 0.1; clearviewport(); break;
            case 72: y_s_u += 0.1; break;
            case 80: y_s_u -= 0.1; break;
            case 75: x_s_u -= 0.1; break;
            case 77: x_s_u += 0.1; break;
		}
	    
	    //clearviewport();
	    
	} while(value != 27);
	
	getch();
	closegraph();
	return 0;
}
