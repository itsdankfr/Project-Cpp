#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int size = 100;
Vector2f offset(28, 28);

Sprite f[32]; //figures
std::string position = "";

int board[8][8] =
{ -1,-2,-3,-4,-5,-3,-2,-1,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  1, 2, 3, 4, 5, 3, 2, 1 };

// chuyen toa do cua quan co thanh ky hieu dang co vua ( E2 A3 cac thu )
// quy uoc don gian, x la so cot - y la so hang
// 
// de chuyen x ve chi so cot => bat dau hang dau tien la 0, ta cong them 'a' hay 97 trong ASCII
// 
// de chuyen y ve chi so hang => phuc tap hon 1 xiu, binh thuong trong co vua hang 1 la hang gan nguoi choi nhat
// nhung trong he toa do, y tang tu tren xuong duoi nen hang 1 se nam o vi tri y lon nhat, vi vay ta phai lay 7 - di roi + '1' hay 49

// => Gia su p(0,0) => A8
std::string toChessNote(Vector2f p)
{
    std::string s = "";
    s += char(p.x / size + 97);
    s += char(7 - p.y / size + 49);
    return s;
}

// chuyen ky hieu dang co vua thanh toa do dang vector 2f de ve quan co len ban co
// vi chess map va do hoa may tinh hieu khac nhau, ta can co ham nay de moi lan di chuyen may tinh se ve chinh xac vi tri cua quan co
Vector2f toCoord(char a, char b)
{
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return Vector2f(x * size, y * size);
}

void move(std::string str)
{   
    Vector2f oldPos = toCoord(str[0], str[1]);
    Vector2f newPos = toCoord(str[2], str[3]);

    // xoa quan co o vi tri newPos ( quan co bi an mat )
    // => lap qua vi tri cua 32 quan co de check tung quan 1 xem quan nao trung newPos thi cut
    for (int i = 0; i < 32; i++)
        if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);

    // di chuyen quan co vua an tu oldPos sang newPos
    for (int i = 0; i < 32; i++)
        if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);

    //castling       //if the king didn't move
    // xu ly truong hop nhap thanh
    if (str == "e1g1") if (position.find("e1") == -1) move("h1f1");
    if (str == "e8g8") if (position.find("e8") == -1) move("h8f8");
    if (str == "e1c1") if (position.find("e1") == -1) move("a1d1");
    if (str == "e8c8") if (position.find("e8") == -1) move("a8d8");
}

void loadPosition()
{
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            int n = board[i][j];
            if (!n) continue;
            int x = abs(n) - 1;
            int y = n > 0 ? 1 : 0;
            f[k].setTextureRect(IntRect(size * x, size * y, size, size));
            f[k].setPosition(size * j, size * i);
            k++;
        }

    // luu lich su di chuyen 
    for (int i = 0; i < position.length(); i += 5)
        move(position.substr(i, 4));
}


int main()
{
    RenderWindow window(VideoMode(900, 900), "The Chess! (press SPACE)");

    /*ConnectToEngine("stockfish.exe");*/


    Texture t1, t2;
    t1.loadFromFile("images/figures.png");
    t2.loadFromFile("images/board.png");

    for (int i = 0; i < 32; i++) f[i].setTexture(t1);
    Sprite sBoard(t2);

    loadPosition();

    bool isMove = false;
    float dx = 0, dy = 0;
    Vector2f oldPos, newPos;
    std::string str;
    int n = 0;

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            ////move back//////
            // cho phep di lai 5 buoc gan nhat bang cach su dung BackSpace
            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::BackSpace)
                {
                    if (position.length() > 6) position.erase(position.length() - 6, 5); loadPosition();
                }

            /////drag and drop///////
            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left)
                    for (int i = 0; i < 32; i++)
                        if (f[i].getGlobalBounds().contains(pos.x, pos.y))
                        {
                            isMove = true; n = i;
                            dx = pos.x - f[i].getPosition().x;
                            dy = pos.y - f[i].getPosition().y;
                            oldPos = f[i].getPosition();
                        }

            if (e.type == Event::MouseButtonReleased)
                if (e.key.code == Mouse::Left)
                {
                    isMove = false;
                    Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);
                    newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));
                    str = toChessNote(oldPos) + toChessNote(newPos);
                    move(str);
                    if (oldPos != newPos) position += str + " ";
                    f[n].setPosition(newPos);
                }
        }

        //comp move
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            /*str = getNextMove(position);*/

            oldPos = toCoord(str[0], str[1]);
            newPos = toCoord(str[2], str[3]);

            for (int i = 0; i < 32; i++) if (f[i].getPosition() == oldPos) n = i;

            /////animation///////
            for (int k = 0; k < 50; k++)
            {
                Vector2f p = newPos - oldPos;
                f[n].move(p.x / 50, p.y / 50);
                window.draw(sBoard);
                for (int i = 0; i < 32; i++) f[i].move(offset);
                for (int i = 0; i < 32; i++) window.draw(f[i]); window.draw(f[n]);
                for (int i = 0; i < 32; i++) f[i].move(-offset);
                window.display();
            }

            move(str);  position += str + " ";
            f[n].setPosition(newPos);
        }

        if (isMove) f[n].setPosition(pos.x - dx, pos.y - dy);

        ////// draw  ///////
        window.clear();
        window.draw(sBoard);
        for (int i = 0; i < 32; i++) f[i].move(offset);
        for (int i = 0; i < 32; i++) window.draw(f[i]); window.draw(f[n]);
        for (int i = 0; i < 32; i++) f[i].move(-offset);
        window.display();
    }

    /*CloseConnection();*/

    return 0;
}