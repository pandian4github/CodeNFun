#ifndef COLLRECTMANAGER_H
#define COLLRECTMANAGER_H

#include "collisionRectangles.h"

class collRectManager
{
	public:
		collRect *myCollRect;
		int totalRects;
		int LEVEL_WIDTH,LEVEL_HEIGHT;
		collRectManager();

		void initRects(int level);
		void changePosition(int x,int y,int w,int h,int collisionRectangle);
		void setTotalRects(int);

};
collRectManager *myManager = new collRectManager();

void collRectManager::setTotalRects(int i)
{
	totalRects=i;
}
collRectManager::collRectManager()
{
	LEVEL_WIDTH=1000;
	LEVEL_HEIGHT=562;
}
void collRectManager::initRects(int level)
{
	switch(level)
	{
	case 1:
		myCollRect=new collRect[5];
		myCollRect[0].setValues(0,435,1000,165,0); // Lower floor
		myCollRect[1].setValues(0,385,275,50,0);  // Upper floor
		myCollRect[2].setValues(555,315,51,120,1);  // Computer
		myCollRect[3].setValues(0,210,156,140,0);  // Eva initial position
		myCollRect[4].setValues(0,210,100,140,1);  // Exit door
		break;
	
	case 2:
		myCollRect=new collRect[4];
		myCollRect[0].setValues(560,490,450,1,0); //right side platform
		myCollRect[1].setValues(20,490,310,1,0);  //left side platform
		myCollRect[2].setValues(597,390,50,100,1); //computer
		myCollRect[3].setValues(0,390,40,100,1); //exit door
		break;

	case 3:
		myCollRect =  new collRect[4];
		myCollRect[0].setValues(0,475,1000,1,0); //platform
		myCollRect[1].setValues(0,300,90,200,0); //gate closed
		myCollRect[2].setValues(205,365,50,100,1); //computer
		myCollRect[3].setValues(0,300,40,200,1); //gate opened
		break;
	
	case 4:
		myCollRect = new collRect[6];
		myCollRect[0].setValues(0,470,1000,1,0); //platform
		myCollRect[1].setValues(500,280,1,270,0); //gate 1
		myCollRect[2].setValues(320,280,1,270,0); //gate 2
		myCollRect[3].setValues(165,280,1,270,0); //gate 3
		myCollRect[4].setValues(720,365,50,100,1); //computer
		myCollRect[5].setValues(5,280,1,270,1); //end
		break;

	default:
		std::cout<<"\nError initializing collision rectangles";
	}
}

void collRectManager::changePosition(int x,int y,int w,int h,int collisionRectangle)
{
	myCollRect[collisionRectangle].setValues(x,y,w,h,0);//3
}
#endif