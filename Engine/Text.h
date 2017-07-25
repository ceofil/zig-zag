#pragma once
#include "Graphics.h"
#include <cstring>

class Text
{
public:
	Text(Graphics& gfx, int xup, int yup, int xd, int yd, int wi, int he);
	void DrawCell(int x, int y, Color c);
	void Draw4Line(int x, int y, Color c);
	void Draw7Col(int x, int y, Color c);
	void DrawHalfCol(int x, int y, Color c);
	void DrawLineK(int x, int y, int k, Color c);
	void DrawColK(int x, int y, int k, Color c);
	
		void draw1(int xpoz, int ypoz, Color c);
		void draw2(int xpoz, int ypoz, Color c);
		void draw3(int xpoz, int ypoz, Color c);
		void draw4(int xpoz, int ypoz, Color c);
		void draw5(int xpoz, int ypoz, Color c);
		void draw6(int xpoz, int ypoz, Color c);
		void draw7(int xpoz, int ypoz, Color c);
		void draw8(int xpoz, int ypoz, Color c);
		void draw9(int xpoz, int ypoz, Color c);
		void draw0(int xpoz, int ypoz, Color c);

		void drawint(int n, int x, int y, Color c);
		void drawintCenter(int n, int x, int y, Color c);
		void drawintRight(int n, int x, int y, Color c);
		void drawfloat(float n, int x, int y, Color c);
		int nrcifre(int n);

		void drawA(int xpoz, int ypoz, Color c);
		void drawB(int xpoz, int ypoz, Color c);
		void drawC(int xpoz, int ypoz, Color c);
		void drawD(int xpoz, int ypoz, Color c);
		void drawE(int xpoz, int ypoz, Color c);
		void drawF(int xpoz, int ypoz, Color c);
		void drawG(int xpoz, int ypoz, Color c);
		void drawH(int xpoz, int ypoz, Color c);
		void drawI(int xpoz, int ypoz, Color c);
		void drawJ(int xpoz, int ypoz, Color c);
		void drawK(int xpoz, int ypoz, Color c);
		void drawL(int xpoz, int ypoz, Color c);
		void drawM(int xpoz, int ypoz, Color c);
		void drawN(int xpoz, int ypoz, Color c);
		void drawO(int xpoz, int ypoz, Color c);
		void drawP(int xpoz, int ypoz, Color c);
		void drawQ(int xpoz, int ypoz, Color c);
		void drawR(int xpoz, int ypoz, Color c);
		void drawS(int xpoz, int ypoz, Color c);
		void drawT(int xpoz, int ypoz, Color c);
		void drawW(int xpoz, int ypoz, Color c);
		void drawX(int xpoz, int ypoz, Color c);
		void drawY(int xpoz, int ypoz, Color c);
		void drawZ(int xpoz, int ypoz, Color c);
		void drawV(int xpoz, int ypoz, Color c);
		void drawU(int xpoz, int ypoz, Color c);

		void drawstring(char string[],int xpoz,int ypoz,Color c);
		void drawstringCenter(char string[], int xpoz, int ypoz, Color c);
	
	int getw();
	int geth();
private:
	int xtext=1;
	int ytext=1;
	int xdim=10;
	int ydim=10;
	int w = gfx.ScreenWidth / xdim;
	int h = gfx.ScreenHeight / ydim;
	Graphics& gfx;
};