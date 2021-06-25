#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Shape Shape;
typedef struct Triangle Triangle;
typedef struct Circle Circle;
typedef struct Square Square;
typedef struct Rectangle Rectangle;

typedef double (*VirtualMethodPointer)(void *); 
typedef VirtualMethodPointer * VTableType;

#define PI 3.14159


//Shape class 

	struct Shape
	{
		VTableType VPointer; 
		char* name;
	};

	double Shape_area(Shape * _this)
	{
		return 0.0; 
	}

	void Shape_draw(Shape * _this)
	{
		printf("Shape_draw You should never see this.\n");

	}

	void Shape_print(Shape * _this)
	{
		printf("%s\n",_this->name);

	}

	VirtualMethodPointer Shape_VTable [] = 
	{
		(VirtualMethodPointer)Shape_area,//VTable[0]
		(VirtualMethodPointer)Shape_draw, //VTable[1]
		(VirtualMethodPointer)Shape_print //VTable[2]
	};

	Shape* Shape_Shape(Shape * _this, char* newName)
	{
		_this->VPointer = Shape_VTable;
		_this->name = newName;
		return _this;
	}
// End of class Shape 

//Triangle class
	struct Triangle 
	{
		VTableType VPointer;
		char* name;
		double myHeight;
		double myBase;
	};

	double Triangle_area(Triangle* _this)
	{
		return 0.5 * _this->myHeight * _this->myBase;
	}

	void Triangle_draw(Triangle* _this)
	{
		char visual[30] = ""; 
		for(int i = 0; i<5;i++) 
		{
			strcat(visual, "*"); 
			printf("%s",visual);
			printf("\n");
		}
	}

	void Triangle_print(Triangle* _this)
	{
		printf("%s(%3.1f,%3.1f): %4.2f\n", _this->name,_this->myHeight,_this->myBase,_this->VPointer[0](_this));
	} 

	VirtualMethodPointer Triangle_VTable [] = 
	{
		(VirtualMethodPointer)Triangle_area, //VTable[0]
		(VirtualMethodPointer)Triangle_draw, //VTable[0]
		(VirtualMethodPointer)Triangle_print //VTable[0]
	};

	Triangle* Triangle_Triangle(Triangle* _this, char* newName, double height, double base)
	{
		Shape_Shape((Shape *)_this, newName);
		_this->VPointer = Triangle_VTable;
		_this->myHeight = height;
		_this->myBase = base; 
		return _this;
	}
// End of class Triangle 


// Circle class
	struct Circle //extends Shape
	{ 
		VTableType VPointer;
		char* name;
		double myRadius;
	};

	double Circle_area(Circle* _this)
	{
		return PI * _this->myRadius * _this->myRadius;
	}

	void Circle_draw(Circle * _this)
	{
		printf("  * * * *  \n");
		for(int i = 0; i < 4; i = i + 1) 
		{
			printf("* * * * * *\n");
		}
		printf("  * * * *  \n");
	}

	void Circle_print(Circle* _this)
	{
		printf("%s(%3.1lf): %4.2lf\n", _this->name,_this->myRadius,_this->VPointer[0](_this));
	} 
	

	VirtualMethodPointer Circle_VTable [] =
	{
		(VirtualMethodPointer)Circle_area, //Over-ride area 
		(VirtualMethodPointer)Circle_draw, // Over-ride draw
		(VirtualMethodPointer)Circle_print // Over-ride print
	};

	Circle * Circle_Circle(Circle* _this, char* newName, double radius)
	{
		Shape_Shape((Shape *)_this, newName);
		_this->VPointer = Circle_VTable;
		_this->myRadius = radius;
		return _this;
	}
//End of Circle class



//Square class
	struct Square //extends Shape 
	{
		VTableType VPointer;
		char* name;
		double myHeight;
	};

	double Square_area(Square* _this)
	{
		return _this->myHeight * _this->myHeight;
	}

	void Square_draw(Square* _this) 
	{
		char side[] = "* * * * * *";
		for(int i = 0; i<5; i++) 
		{
			printf("%s\n",side);
		}
	}

	void Square_print(Square* _this)
	{
		printf("%s(%3.1lf): %4.2lf\n", _this->name,_this->myHeight,_this->VPointer[0](_this));
	}

	VirtualMethodPointer Square_VTable [] = 
	{
		(VirtualMethodPointer)Square_area,
		(VirtualMethodPointer)Square_draw, 
		(VirtualMethodPointer)Square_print
	};

	Square * Square_Square(Square* _this, char* newName, double height)
	{
		Shape_Shape((Shape *)_this, newName);
		_this->VPointer = Square_VTable;
		_this->myHeight = height;
		return _this;
	}
//End of Square class 



// //Rectangle class 
	struct Rectangle //extends Square
	{
		VTableType VPointer;
		char* name; 
		double myHeight;
		double myWidth;
	};

	double Rectangle_area(Rectangle* _this)
	{
		return _this->myHeight * _this->myWidth;
	}

	void Rectangle_draw(Rectangle* _this) 
	{
		char side[] = "* * * * * *";
		for(int i = 0; i<3; i++) 
		{
			printf("%s\n",side);
		}
	}

	void Rectangle_print(Rectangle* _this)
	{
		printf("%s(%3.1lf,%3.1lf): %4.2lf\n", _this->name,_this->myHeight,_this->myWidth,_this->VPointer[0](_this));
	}

	VirtualMethodPointer Rectangle_VTable [] = 
	{
		(VirtualMethodPointer)Rectangle_area,
		(VirtualMethodPointer)Rectangle_draw, 
		(VirtualMethodPointer)Rectangle_print
	};

	Rectangle* Rectangle_Rectangle(Rectangle* _this, char* newName, double height, double width)
	{
		Square_Square((Square *)_this, newName, height);
		_this->VPointer = Rectangle_VTable;
		_this->myWidth = width;
		return _this;
	}
//End of Rectangle class 



int main(int argc, char* argv[])
{
	int arg1 = 2, arg2 = 2;
	if (argc == 3)
	{
		arg1 = atoi(argv[1]);
		arg2 = atoi(argv[2]);
	}
	

	Shape* a [] = {
		(Shape*)Triangle_Triangle((Triangle*)malloc(sizeof(Triangle)),"FirstTriangle",arg1,arg2),
		(Shape*)Triangle_Triangle((Triangle*)malloc(sizeof(Triangle)),"SecondTriangle",arg1-1,arg2-1),
		(Shape*)Circle_Circle((Circle*)malloc(sizeof(Circle)),"FirstCircle",arg1),
		(Shape*)Circle_Circle((Circle*)malloc(sizeof(Circle)),"SecondCircle",arg1-1),
		(Shape*)Square_Square((Square*)malloc(sizeof(Square)),"FirstSquare",arg1),
		(Shape*)Square_Square((Square*)malloc(sizeof(Square)),"SecondSquare",arg1-1),
		(Shape*)Rectangle_Rectangle((Rectangle*)malloc(sizeof(Rectangle)),"FirstRectangle",arg1,arg2),
		(Shape*)Rectangle_Rectangle((Rectangle*)malloc(sizeof(Rectangle)),"SecondRectangle",arg1-1,arg2-1)
	};

	double sum = 0;
	for (int i=0; i<sizeof(a)/sizeof(*a); i++)
    {
       a[i]->VPointer[2](a[i]); //Print function 
       a[i]->VPointer[1](a[i]); //Draw 
       sum = sum + (a[i]->VPointer[0])(a[i]); // Adding up all the areas
       free(a[i]);
    }

    printf("Total: %lf\n", sum);
}





