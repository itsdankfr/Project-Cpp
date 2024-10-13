#include <graphics.h>
#include <conio.h>

void drawTallerTree(int x, int y) {
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    bar(x-30, y, x+30, y-150);
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(x, y-170, 70, 70);
    fillellipse(x-50, y-130, 60, 60);
    fillellipse(x+50, y-130, 60, 60);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    drawTallerTree(200, 400);
    getch();
    closegraph();
    return 0;
}

