#include "Text.h"

Text::Text(Graphics & gfx, int xup, int yup, int xd, int yd,int wi,int he)
	:
	gfx(gfx)
{
	xtext = xup;
	ytext = yup;
	xdim = xd;
	ydim = yd;
	w = wi;
	h = he;
}

void Text::DrawCell(int x, int y, Color c)
{
	gfx.DrawRectPoints(xtext + xdim*x,ytext + ydim*y, xtext + xdim*(x+1), ytext + ydim*(y+1), c);

}

void Text::Draw4Line(int poz, int y, Color c)
{
	for (int i = poz; i < poz + 4; i++) {
		DrawCell(i, y, c);
	}
}

void Text::Draw7Col(int x, int y, Color c)
{
	for (int i = y; i < y + 7; i++) {
		DrawCell(x, i, c);
	}
}

void Text::DrawHalfCol(int x, int y, Color c)
{
	for (int i = y; i < y + 4; i++) {
		DrawCell(x, i, c);
	}
}

void Text::DrawLineK(int x, int y, int k, Color c)
{
	for (int i = x; i < x + k; i++) {
		DrawCell(i, y, c);
	}
}

void Text::DrawColK(int x, int y, int k, Color c)
{
	for (int i = y; i < y + k; i++) {
		DrawCell(x, i, c);
	}
}

void Text::draw1(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz + 1, ypoz, c);
}
void Text::draw2(int xpoz, int ypoz, Color c)
{
	Draw4Line(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz + 3, c);
	Draw4Line(xpoz, ypoz + 6, c);

	DrawHalfCol(xpoz, ypoz + 3, c);
	DrawHalfCol(xpoz + 3, ypoz, c);
}
void Text::draw3(int xpoz, int ypoz, Color c)
{
	Draw4Line(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz + 3, c);
	Draw4Line(xpoz, ypoz + 6, c);

	Draw7Col(xpoz + 3, ypoz, c);
}
void Text::draw4(int xpoz, int ypoz, Color c)
{
	DrawHalfCol(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz + 3, c);
	Draw7Col(xpoz + 3, ypoz, c);
}
void Text::draw5(int xpoz, int ypoz, Color c)
{
	Draw4Line(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz + 3, c);
	Draw4Line(xpoz, ypoz + 6, c);

	DrawHalfCol(xpoz, ypoz, c);
	DrawHalfCol(xpoz+3, ypoz + 3, c);
}
void Text::draw6(int xpoz, int ypoz, Color c)
{
	Draw4Line(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz + 3, c);
	Draw4Line(xpoz, ypoz + 6, c);

	Draw7Col(xpoz, ypoz, c);
	DrawHalfCol(xpoz + 3, ypoz + 3, c);
}
void Text::draw7(int xpoz, int ypoz, Color c)
{
	Draw4Line(xpoz, ypoz, c);
	Draw7Col(xpoz+3, ypoz, c);
}
void Text::draw8(int xpoz, int ypoz, Color c)
{
	Draw4Line(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz + 3, c);
	Draw4Line(xpoz, ypoz + 6, c);

	Draw7Col(xpoz, ypoz, c);
	Draw7Col(xpoz+3, ypoz, c);
}
void Text::draw9(int xpoz, int ypoz, Color c)
{
	Draw4Line(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz + 3, c);
	Draw4Line(xpoz, ypoz + 6, c);

	DrawHalfCol(xpoz, ypoz, c);
	Draw7Col(xpoz + 3, ypoz, c);
}
void Text::draw0(int xpoz, int ypoz, Color c)
{
	Draw4Line(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz + 6, c);

	Draw7Col(xpoz, ypoz, c);
	Draw7Col(xpoz+3, ypoz, c);
}

void Text::drawint(int n, int x, int y, Color c)
{
	int poz = x;
	if (n)
	{
		int cn = n;
		int nr = 0;
		int v[8];

		if(n<0){
			Draw4Line(poz, y+3, c);
			poz += 5;
			cn = -cn;
		}

		while (cn) {
			v[nr] = cn % 10;
			cn = cn / 10;
			nr++;
		}
		for (int i = nr - 1; i >= 0; i--,poz+=5) {
			if (v[i] == 1) {
				draw1(poz,y, c);
				poz -= 1;
			}
			else if (v[i] == 2) {
				draw2(poz, y, c);
			}
			else if (v[i] == 3) {
				draw3(poz, y, c);
			}
			else if (v[i] == 4) {
				draw4(poz, y, c);
			}
			else if (v[i] == 5) {
				draw5(poz, y, c);
			}
			else if (v[i] == 6) {
				draw6(poz, y, c);
			}
			else if (v[i] == 7) {
				draw7(poz, y, c);
			}
			else if (v[i] == 8) {
				draw8(poz, y, c);
			}
			else if (v[i] == 9) {
				draw9(poz, y, c);
			}
			else if (v[i] == 0) {
				draw0(poz, y, c);
			}
		}

	}
	else
	{
		draw0(poz,y, c);
	}
	
}

void Text::drawintCenter(int n, int x, int y, Color c)
{
	drawint(n, x - nrcifre(n) / 2 * 5, y, c);
}

void Text::drawintRight(int n, int x, int y, Color c)
{
	drawint(n, x - nrcifre(n) * 5, y, c);
}

void Text::drawfloat(float n, int x, int y, Color c)
{
	//7 decimals at most
	int countdecimals = 1;
	int poz = x;
	int k = 0;

	while (k < 4 && float(int(n)) != n && n<2000000000.0f) {
		n = n * 10;
		countdecimals =countdecimals*10 ;
		k++;
	}

	drawint(int(n / countdecimals), poz, y, c);
	poz += nrcifre(int(n / countdecimals)) * 5;

	DrawCell(poz, y + 6, c);
	poz += 3;

	drawint(int(n) % countdecimals, poz, y, c);
	

}

int Text::nrcifre(int n)
{
	int k = 0;
	if (n == 0) {
		return 1;
	}
	else
	{
		while (n)
		{
			k++;
			n = n / 10;
		}
		return k;
	}
}


void Text::drawA(int xpoz, int ypoz, Color c)
{
	/*
	Draw7Col(xpoz, ypoz, c);
	Draw7Col(xpoz + 3, ypoz, c);
	Draw4Line(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz + 3, c);
	*/

	DrawLineK(xpoz + 1, ypoz, 2, c);
	DrawColK(xpoz, ypoz + 1, 6, c);
	DrawColK(xpoz+3, ypoz + 1, 6, c);
	Draw4Line(xpoz, ypoz + 3, c);
}
void Text::drawB(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	for (int i = 1; i <= 2; i++)
	{
		DrawCell(xpoz + i, ypoz,c);
		DrawCell(xpoz + i, ypoz+3,c);
		DrawCell(xpoz + i, ypoz+6,c);
		DrawCell(xpoz + 3, ypoz + i,c);
		DrawCell(xpoz + 3, ypoz + i + 3,c);
	}
}
void Text::drawC(int xpoz, int ypoz, Color c)
{
	DrawLineK(xpoz + 1, ypoz, 2, c);
	DrawLineK(xpoz + 1, ypoz+6, 2, c);
	DrawColK(xpoz, ypoz + 1, 5, c);
	DrawCell(xpoz + 3, ypoz + 1, c);
	DrawCell(xpoz + 3, ypoz + 5, c);
}
void Text::drawD(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	DrawLineK(xpoz + 1, ypoz, 2, c);
	DrawLineK(xpoz + 1, ypoz+6, 2, c);
	DrawColK(xpoz + 3, ypoz + 1, 5, c);

}
void Text::drawE(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz, c);
	DrawLineK(xpoz + 1, ypoz + 3, 2, c);
	Draw4Line(xpoz, ypoz+6, c);
}
void Text::drawF(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz, c);
	DrawLineK(xpoz + 1, ypoz + 3, 2, c);
	
}
void Text::drawG(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz, c);
	DrawColK(xpoz + 3, ypoz + 3, 3, c);
	DrawCell(xpoz + 2, ypoz + 3, c);
	Draw4Line(xpoz, ypoz+6, c);
}
void Text::drawH(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	Draw7Col(xpoz+3, ypoz, c);
	Draw4Line(xpoz, ypoz + 3, c);
}
void Text::drawI(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz + 1, ypoz, c);
}
void Text::drawJ(int xpoz, int ypoz, Color c)
{

	Draw7Col(xpoz + 3, ypoz, c);

	Draw4Line(xpoz, ypoz + 6, c);
	DrawColK(xpoz, ypoz + 4, 2, c);
}
void Text::drawK(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	DrawColK(xpoz + 1, ypoz + 2, 3, c);
	DrawColK(xpoz + 2, ypoz + 2, 1, c);
	DrawColK(xpoz + 3, ypoz, 2, c);
	DrawColK(xpoz + 2, ypoz+4, 1, c);
	DrawColK(xpoz + 3, ypoz+5, 2, c);
}
void Text::drawL(int xpoz, int ypoz, Color c)
{
	Draw4Line(xpoz, ypoz + 6, c);
	Draw7Col(xpoz, ypoz, c);
}
void Text::drawM(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	Draw7Col(xpoz+4, ypoz, c);
	DrawColK(xpoz + 1, ypoz + 1, 2, c);
	DrawColK(xpoz + 3, ypoz + 1, 2, c);
	DrawColK(xpoz + 2, ypoz + 2, 2, c);
}
void Text::drawN(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	Draw7Col(xpoz + 4, ypoz, c);
	DrawColK(xpoz + 1, ypoz + 1, 2, c);
	DrawColK(xpoz + 3, ypoz + 3, 2, c);
	DrawColK(xpoz + 2, ypoz + 2, 2, c);
}
void Text::drawO(int xpoz, int ypoz, Color c)
{
	draw0(xpoz, ypoz, c);
}
void Text::drawP(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	DrawHalfCol(xpoz + 3, ypoz, c);
	Draw4Line(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz+3, c);
}
void Text::drawQ(int xpoz, int ypoz, Color c)
{
	drawO(xpoz, ypoz, c);
	DrawLineK(xpoz + 2, ypoz + 4, 3, c);
}
void Text::drawR(int xpoz, int ypoz, Color c)
{
	Draw7Col(xpoz, ypoz, c);
	Draw4Line(xpoz, ypoz, c);
	DrawLineK(xpoz + 1, ypoz + 3, 2, c);
	DrawLineK(xpoz + 1, ypoz + 4, 2, c);
	DrawLineK(xpoz + 2, ypoz + 5, 2, c);
	DrawCell(xpoz + 3, ypoz + 6, c);
	DrawColK(xpoz + 3, ypoz + 1, 2, c);

}
void Text::drawS(int xpoz, int ypoz, Color c)
{
	draw5(xpoz, ypoz, c);
	DrawCell(xpoz + 3, ypoz + 1, c);
	DrawCell(xpoz, ypoz + 5, c);
}
void Text::drawT(int xpoz, int ypoz, Color c)
{
	DrawLineK(xpoz, ypoz, 5, c);
	Draw7Col(xpoz + 2, ypoz, c);
}
void Text::drawW(int xpoz, int ypoz, Color c)
{
	DrawColK(xpoz, ypoz, 6, c);
	DrawColK(xpoz+2, ypoz, 6, c);
	DrawColK(xpoz+4, ypoz, 6, c);
	DrawCell(xpoz + 1, ypoz + 6, c);
	DrawCell(xpoz + 3, ypoz + 6, c);
}
void Text::drawX(int xpoz, int ypoz, Color c)
{
	DrawColK(xpoz, ypoz, 2, c);
	DrawColK(xpoz+1, ypoz+1, 2, c);
	DrawColK(xpoz + 2, ypoz + 2, 2, c);
	DrawColK(xpoz, ypoz + 5, 2, c);
	DrawColK(xpoz+1, ypoz + 4, 2, c);
	DrawColK(xpoz+2, ypoz + 3, 2, c);
	DrawColK(xpoz+3, ypoz + 4, 2, c);
	DrawColK(xpoz + 3, ypoz + 1, 2, c);
	DrawColK(xpoz + 4, ypoz, 2, c);
	DrawColK(xpoz + 4, ypoz+5, 2, c);
}
void Text::drawY(int xpoz, int ypoz, Color c)
{
	DrawColK(xpoz, ypoz, 2, c);
	DrawColK(xpoz + 1, ypoz + 1, 2, c);
	DrawColK(xpoz + 2, ypoz + 2, 2, c);
	DrawColK(xpoz + 3, ypoz + 1, 2, c);
	DrawColK(xpoz + 4, ypoz, 2, c);
	DrawColK(xpoz + 2, ypoz + 3, 4, c);
}
void Text::drawZ(int xpoz, int ypoz, Color c)
{
	DrawColK(xpoz, ypoz + 5, 2, c);
	DrawColK(xpoz + 1, ypoz + 4, 2, c);
	DrawColK(xpoz + 2, ypoz + 2, 3, c);
	DrawColK(xpoz + 3, ypoz + 1, 2, c);
	DrawColK(xpoz + 4, ypoz, 2, c);
	DrawLineK(xpoz, ypoz, 5, c);
	DrawLineK(xpoz, ypoz + 6,5, c);
}
void Text::drawV(int xpoz, int ypoz, Color c)
{
	DrawColK(xpoz, ypoz, 5, c);
	DrawColK(xpoz + 4, ypoz, 5, c);
	DrawColK(xpoz + 1, ypoz+4, 2, c);
	DrawColK(xpoz + 3, ypoz + 4, 2, c);
	DrawColK(xpoz + 2, ypoz + 5, 2, c);

}
void Text::drawU(int xpoz, int ypoz, Color c)
{
	Draw4Line(xpoz, ypoz + 6, c);

	Draw7Col(xpoz, ypoz, c);
	Draw7Col(xpoz + 3, ypoz, c);
}

void Text::drawstring(char string[], int xpoz, int ypoz, Color c)
{
	int poz = xpoz;
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] == 'A' || string[i] == 'a') {
			drawA(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'B' || string[i] == 'b') {
			drawB(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'C' || string[i] == 'c') {
			drawC(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'D' || string[i] == 'd') {
			drawD(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'E' || string[i] == 'e') {
			drawE(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'F' || string[i] == 'f') {
			drawF(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'G' || string[i] == 'g') {
			drawG(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'H' || string[i] == 'h') {
			drawH(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'I' || string[i] == 'i') {
			drawI(poz, ypoz, c);
			poz += 4;
		}
		else if (string[i] == 'J' || string[i] == 'j') {
			drawJ(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'K' || string[i] == 'k') {
			drawK(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'L' || string[i] == 'l') {
			drawL(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'M' || string[i] == 'm') {
			drawM(poz, ypoz, c);
			poz += 6;
		}
		else if (string[i] == 'N' || string[i] == 'n') {
			drawN(poz, ypoz, c);
			poz += 6;
		}
		else if (string[i] == 'O' || string[i] == 'o') {
			drawO(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'P' || string[i] == 'p') {
			drawP(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'Q' || string[i] == 'q') {
			drawQ(poz, ypoz, c);
			poz += 6;
		}
		else if (string[i] == 'R' || string[i] == 'r') {
			drawR(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'S' || string[i] == 's') {
			drawS(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == 'T' || string[i] == 't') {
			drawT(poz, ypoz, c);
			poz += 6;
		}
		else if (string[i] == 'W' || string[i] == 'w') {
			drawW(poz, ypoz, c);
			poz += 6;
		}
		else if (string[i] == 'X' || string[i] == 'x') {
			drawX(poz, ypoz, c);
			poz += 6;
		}
		else if (string[i] == 'Y' || string[i] == 'y') {
			drawY(poz, ypoz, c);
			poz += 6;
		}
		else if (string[i] == 'Z' || string[i] == 'z') {
			drawZ(poz, ypoz, c);
			poz += 6;
		}
		else if (string[i] == 'V' || string[i] == 'v') {
			drawV(poz, ypoz, c);
			poz += 6;
		}
		else if (string[i] == ' ') {
			poz += 4;
		}
		else if (string[i] == '-') {
			Draw4Line(poz, ypoz + 3, c);
			poz += 5;
		}
		else if (string[i] == '.') {
			DrawCell(poz, ypoz + 6, c);
			poz += 2;
		}
		else if (string[i] == 'U' || string[i] == 'u') {
			drawU(poz, ypoz, c);
			poz += 5;
		}
		else if (string[i] == '0') {
			draw0(poz, ypoz  , c);
			poz += 5;
		}
		else if (string[i] == '1') {
			draw1(poz, ypoz  , c);
			poz += 4;
		}
		else if (string[i] == '2') {
			draw2(poz, ypoz  , c);
			poz += 5;
		}
		else if (string[i] == '3') {
			draw3(poz, ypoz  , c);
			poz += 5;
		}
		else if (string[i] == '4') {
			draw4(poz, ypoz  , c);
			poz += 5;
		}
		else if (string[i] == '5') {
			draw5(poz, ypoz  , c);
			poz += 5;
		}
		else if (string[i] == '6') {
			draw6(poz, ypoz  , c);
			poz += 5;
		}
		else if (string[i] == '7') {
			draw7(poz, ypoz  , c);
			poz += 5;
		}
		else if (string[i] == '8') {
			draw8(poz, ypoz  , c);
			poz += 5;
		}
		else if (string[i] == '9') {
			draw9(poz, ypoz  , c);
			poz += 5;
		}

	}
}

void Text::drawstringCenter(char string[], int xpoz, int ypoz, Color c)
{
	drawstring(string, xpoz - strlen(string) * 5 / 2, ypoz, c);
}







int Text::getw()
{
	return w;
}
int Text::geth()
{
	return h;
}
