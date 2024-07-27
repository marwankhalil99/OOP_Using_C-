#include<iostream>
#include <conio.h>
#include <graphics.h>
/* COMMAND PROMPT TO BUILD THE CODE : g++ .\Points.cpp -o point.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32    */

using namespace std;
class Shape
{
protected:
    /*The standard Borland 16 colors
                enum colors { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
                LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE };*/
    int color ;
    int thickness; //NORM_WIDTH      1   THICK_WIDTH     3
public:
    Shape(){color = 15; thickness = 1;}
    Shape(int c , int t){color = c; thickness = t;}
    void setColor(int c){color = c;}
    void setThick(int t){thickness = t;}
    virtual void draw() = 0;
};
class Point : public Shape
{
    int x;
    int y;
public:
    Point() : Shape(){x = 0; y =0;}
    Point(int tx , int ty): Shape() {x = tx; y = ty;}
    Point(int tx , int ty , int col , int thick): Shape(col,thick) {x = tx; y = ty;}
    Point(const Point & tp){x = tp.x; y = tp.y; color = tp.color; thickness=tp.thickness;}
    int getX(){return x;}
    int getY(){return y;}
    void draw()
    {
        setcolor(color);
        //void setlinestyle( int linestyle, unsigned upattern, int thickness );
        setlinestyle( SOLID_LINE, 0 , thickness );
        line(x,y,x,y);
    }
};
class Line: public Shape
{
    Point start;
    Point end;
public:
    Line() : start() , end() , Shape() {}
    Line(int x1 , int y1 , int x2 , int y2 ) : start(x1 , y1) , end(x2 , y2) , Shape(){}
    Line(int x1 , int y1 , int x2 , int y2 , int col , int thick ) : start(x1 , y1) , end(x2 , y2) , Shape(col,thick){}
    Line(Point p1 , Point p2) : start(p1) , end(p2) {}
    Line(Point p1 , Point p2 , int col , int thick) : start(p1) , end(p2) , Shape(col , thick){}
    Line(const Line & tl) : start(tl.start) , end(tl.end) , Shape(tl.color , tl.thickness){}
    void draw()
    {
        setcolor(color);
        setlinestyle( SOLID_LINE, 0 , thickness );
        line(start.getX(),start.getY(),end.getX(),end.getY());
    }

};
class Circle : public Shape
{
    Point center;
    int ridus;
public:
    Circle():center() , Shape(){ridus = 0;}
    Circle(Point tc , int r) : center(tc) , Shape(){ridus = r;}
    Circle(Point tc , int r , int col , int thick) : center(tc) , Shape(col , thick){ridus = r;}
    Circle(int c1, int c2 , int r) : center(c1,c2) , Shape() {ridus = r;}
    Circle(int c1, int c2 , int r , int col , int thick) : center(c1,c2) , Shape(col , thick) {ridus = r;}
    Circle(const Circle & tc) : center(tc.center) , Shape(tc.color , tc.thickness) {ridus = tc.ridus;}
    void draw()
    {
        setcolor(color);
        setlinestyle( SOLID_LINE, 0 , thickness );
        circle(center.getX(),center.getY() , ridus);
        
    }
};
class Rect : public Shape
{
    Point rec1;
    Point rec2;
public:
    Rect(): rec1() , rec2() , Shape(){}
    Rect(Point tr1 , Point tr2) : rec1(tr1) , rec2(tr2){}
    Rect(Point tr1 , Point tr2 , int col , int thick) : rec1(tr1) , rec2(tr2) , Shape(col , thick){}
    Rect(int rec1x, int rec1y , int rec2x , int rec2y) : rec1(rec1x,rec1y) , rec2(rec2x , rec2y) , Shape(){}
    Rect(int rec1x, int rec1y , int rec2x , int rec2y , int col , int thick) : rec1(rec1x,rec1y) , rec2(rec2x , rec2y) , Shape(col , thick){}
    Rect(const Rect & tr) : rec1(tr.rec1) , rec2(tr.rec2) , Shape(tr.color,tr.thickness){}
    void draw()
    {
        setcolor(color);
        setlinestyle( SOLID_LINE, 0 , thickness );
        rectangle(rec1.getX(),rec1.getY() , rec2.getX(),rec2.getY());
    }
};

class Picture 
{
  private :
	int cNum ;
	int rNum ;
	int lNum ;

	Circle *pCircles;
	Rect *pRects;
	Line *pLines;

  public :
	Picture()
	{
		cNum=0;
		rNum=0;
		lNum=0;
		pCircles = NULL ;
		pRects = NULL ;
		pLines = NULL ;
	}

	Picture(int cn, int rn, int ln, Circle *pC, Rect *pR, Line *pL)
	{
		cNum = cn;
		rNum = rn;
		lNum = ln;
		pCircles = pC ;
		pRects = pR ;
		pLines = pL ;
	}

	void setCircles(int, Circle *);
	void setRects(int, Rect *);
	void setLines(int, Line *);
	void paint();
};

void Picture::setCircles(int cn, Circle * cptr)
{
	cNum = cn ;
	pCircles = cptr ;
}

void Picture::setRects(int rn, Rect * rptr)
{
	rNum = rn ;
	pRects = rptr ;
}

void Picture::setLines(int ln, Line * lptr)
{
	lNum = ln ;
	pLines = lptr ;
}

void Picture::paint()
{
	int i;
	for(i=0; i<cNum ; i++)
	{
		pCircles[i].draw();
	}

	for(i=0 ; i<rNum ; i++)
	{
		pRects[i].draw();
	}

	for(i=0 ; i<lNum; i++)
	{
		pLines[i].draw();
	}
}

int graphicsInit(void)
{
    int gm, x, y, gd = DETECT, i;
    char data[] = "./libbgi.a"; //static file
    initgraph(&gd, &gm, data);
    
}
int main ()
{
    graphicsInit();
    int errorCode = graphresult();
    if(errorCode != grOk)
    {
        cout << "cant Open GD !";
        return 0;
    }
    Picture myPic;
    Line l1[] = {
        Line(250, 200, 250, 330, 11,3 ),Line(170, 260, 170, 330 ),
        Line(170, 260, 210, 260),Line(210, 260, 210, 330 ),Line(290, 110, 290, 150),
        Line(310, 110, 310, 150),Line(350, 150, 400, 200 , 12,3 ),
        Line(300, 250, 350, 280 , 10 , 3),
        Line(5, 330, 600, 330, 9 , 3 ),Line(200, 150, 350, 150 , 12,3),Line(140, 200, 200, 150 , 12,3),Line(200, 150, 250, 200 , 12,3)}; 

    Circle c1[] = {Circle(196, 180, 15 , 10 , 3) , Circle (300,110,10 , 10 , 3) } ;
    Rect r1[] = {Rect(300, 250 , 350, 280 , 10 , 3) , Rect(140,200,400,330 , 15 ,3)};
    myPic.setLines(sizeof(l1) / sizeof(Line) , l1);
    myPic.setCircles(sizeof(c1) / sizeof(Circle),c1);
    myPic.setRects(sizeof(r1) / sizeof(Rect),r1);
    myPic.paint();
        for (int i = 0; i < 1030; i = i + 10)
        {
            setcolor(13);
            settextstyle(7, 0, 5);

            char stringData1[] = "**Marwan Khalil**";

            outtextxy(-400 + i, 390, stringData1);
            delay(100);
            setcolor(0);
            settextstyle(7, 0, 5);
            outtextxy(-400 + i, 390, stringData1);
            if (i == 1020)
                i = -10;
        }
    closegraph();
    return 0;
}