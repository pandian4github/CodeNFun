#ifndef COLLISIONRECTANGLES_H
#define COLLISIONRECTANGLES_H

#include<SFML\System.hpp>
#include<SFML\Graphics.hpp>


class collRect
{
	
	public:
		sf::IntRect box;
		int type;

		collRect();
		collRect(int x,int y,int w, int h,int type);
		void setValues(int x,int y,int w, int h,int type);
		void set_type(int);
		
		static const int SOLID = 0;
		static const int OBJECT = 1;
};

collRect::collRect()
{
		box.left=0;
		box.top=0;
		box.width=0;
		box.height=0;
		type=SOLID;
}

collRect::collRect(int x,int y,int w,int h,int recttype)
{
		box.left=x;
		box.top=y;
		box.width=w;
		box.height=h;
		type=recttype;
}

void collRect::setValues(int x,int y,int w,int h,int recttype)
{
		box.left=x;
		box.top=y;
		box.width=w;
		box.height=h;
		type=recttype;
}
void collRect::set_type(int newtype)
{
	type=newtype;
}



#endif