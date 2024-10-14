#include <graphics.h>
#include <conio.h>
#include<cmath>
void drawTree(int x, int y) {
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    rectangle(x - 15, y, x + 15, y + 150);
    floodfill(x, y + 75, BROWN);

    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(x, y, 70, 70);
    fillellipse(x - 50, y + 30, 60, 60);
    fillellipse(x + 50, y + 30, 60, 60);
    fillellipse(x - 30, y - 30, 50, 50);
    fillellipse(x + 30, y - 30, 50, 50);
}

void drawFlowersOnTree(int x, int y) {
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(x - 50, y - 30, 5, 5);
    fillellipse(x + 50, y - 30, 5, 5);
    fillellipse(x - 50, y + 30, 5, 5);
    fillellipse(x + 50, y + 30, 5, 5);
    setcolor(YELLOW);
    fillellipse(x - 50, y - 30, 2, 2);
    fillellipse(x + 50, y - 30, 2, 2);
    fillellipse(x - 50, y + 30, 2, 2);
    fillellipse(x + 50, y + 30, 2, 2);
}

void drawBird(int x, int y) {
    setcolor(WHITE);
    line(x, y, x + 10, y - 10);
    line(x + 10, y - 10, x + 20, y);
    line(x + 20, y, x + 30, y - 10);
    line(x + 30, y - 10, x + 40, y);
}

void drawCloud(int x, int y) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, 20, 15);
    fillellipse(x + 20, y, 30, 20);
    fillellipse(x + 40, y, 20, 15);
}

void drawGrass(int x, int y) {
    setcolor(GREEN);
    for (int i = 0; i < 10; i++) {
        line(x + (i * 10), y + 170, x + 5 + (i * 10), y + 150);
        line(x + 5 + (i * 10), y + 170, x + 10 + (i * 10), y + 150);
    }
}

void drawSun(int x, int y) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(x, y, 40, 40);
    for (int i = 0; i < 360; i += 30) {
        int dx = 50 * cos(i * M_PI / 180);
        int dy = 50 * sin(i * M_PI / 180);
        line(x, y, x + dx, y + dy);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    drawTree(250, 200);
    drawFlowersOnTree(250, 200);
    drawGrass(200, 200);
    drawSun(100, 100);
    drawBird(300, 100);
    drawBird(350, 120);
    drawBird(400, 110);
    drawCloud(150, 50);
    drawCloud(350, 70);

    getch();
    closegraph();
    return 0;
}
