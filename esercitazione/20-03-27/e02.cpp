//
// Created by paolo on 28/03/20.
//

class CPoint{
private:
    int x,y;
public:
    CPoint(int x, int y): x(x), y(y){};

};

class CRect{
private:
    CPoint p1,p2; // p1, p2 sono interni a Crect, stessa area di memoria
public:
    CRect(int x1, int y1, int x2, int y2): p1(x1,y1), p2(x2,y2){};
};

class CRect1{
private:
    CPoint *p1,*p2; // p1, p2 sono interni a Crect, stessa area di memoria
public:
    CRect1(int x1, int y1, int x2, int y2){
        p1 = new CPoint(x1,y1);
        p2 = new CPoint(x2,y2);
    };
    ~CRect1(){
        delete(p1);
        delete(p2);
    };
};
