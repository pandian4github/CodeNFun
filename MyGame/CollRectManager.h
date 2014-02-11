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
	if(level == 1)
	{
		myCollRect=new collRect[5];
		myCollRect[0].setValues(0,435,1000,165,0); // Lower floor
		myCollRect[1].setValues(0,385,275,50,0);  // Upper floor
		myCollRect[2].setValues(555,315,51,120,1);  // Computer
		myCollRect[3].setValues(0,210,156,140,0);  // Eva initial position
		myCollRect[4].setValues(0,210,100,140,1);  // Exit door
	}
	if(level == 2)
	{
		myCollRect=new collRect[2];
		myCollRect[0].setValues(0,435,1000,165,0);
		myCollRect[1].setValues(0,385,275,50,0);
	}
}

void collRectManager::changePosition(int x,int y,int w,int h,int collisionRectangle)
{
	myCollRect[collisionRectangle].setValues(x,y,w,h,0);//3
}
#endif