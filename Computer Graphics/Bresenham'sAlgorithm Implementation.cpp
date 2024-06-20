#include <iostream>
#include <math.h>
#include <graphics.h>
using namespace std;
class ddaBresh{
	private:
		int x1,y1,x2,y2;
		float xn,yn,xi,yi,dx,dy,step;
		int r,xc,yc;
	public:
		void dda_line();
		void breshCircle();
};
void ddaBresh :: dda_line(){
	cout<<"Enter value of x1 and y1 : "<<endl;
	cin>>x1>>y1;
	cout<<"Enter values of x2 and y2 : "<<endl;
	cin>>x2>>y2;
	dx = x2-x1;
	dy = y2-y1;
	if(abs(dx) >= abs(dy)){
		step  = abs(dx);
	}
	else{
		step = abs(dy);
	}
	xi = dx/step;
	yi = dy/step;
	xn = x1;
	yn = y1;
	for(int i = 1;i<=step;i++){
		putpixel(floor(xn),floor(yn),4);
		xn += xi;
		yn += yi;
	}
}

void ddaBresh :: breshCircle(){
	cout<<"Enter value of r,xc and yc : "<<endl;
	cin>>r>>xc>>yc;
	int x=0,y=r,d=3-2*r;
	while(x<=y){
		if(d>=0){
			d += 4*(x-y)+10;
			x++;
			y--;
		}
		else{
			d+= 4*x+6;
			x++;
		}
		putpixel(xc+x,yc+y,1);
		putpixel(xc+x,yc-y,2);
		putpixel(xc-x,yc+y,3);
		putpixel(xc-x,yc-y,4);
		putpixel(xc+y,yc+x,5);
		putpixel(xc+y,yc-x,6);
		putpixel(xc-y,yc+x,7);
		putpixel(xc-y,yc-x,8);
	}
}

int main(){
	ddaBresh p;
	initwindow(800,800);
	p.breshCircle();
	p.dda_line();
	p.dda_line();
	p.dda_line();
	p.breshCircle();
	getch();
}
