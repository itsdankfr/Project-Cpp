## Demo 1: Chess game
### basic function in SFML:
Vector2

![image](https://github.com/user-attachments/assets/f39b9b7e-e194-4eb9-ac9f-d0e62f6f15a5)

Texture and Sprite

![image](https://github.com/user-attachments/assets/4a582070-19af-4f6b-a0cf-d585a2edf092)

![image](https://github.com/user-attachments/assets/d24a95bd-3712-4519-a815-e6f8fa16c6c3)

```cpp
#include <SFML/Graphics.hpp>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

int squareSize = 56;                          // kích thước ô cờ
Vector2f offset(28,28);                 // Offset của mỗi quân cờ
bool isBotTurn = false;

Sprite f[32];                           // mảng lưu hình ảnh 32 quân cờ
string position="";                // các nước di chuyển của ván đấu

// Stockfish process handles
STARTUPINFOA sti = {0};
PROCESS_INFORMATION pi = {0};
HANDLE pipin_w, pipin_r, pipout_w, pipout_r;

// Chess board layout with initial positions
int board[8][8] = 
    {-1,-2,-3,-4,-5,-3,-2,-1,
     -6,-6,-6,-6,-6,-6,-6,-6,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      6, 6, 6, 6, 6, 6, 6, 6,
      1, 2, 3, 4, 5, 3, 2, 1};

// chuyển vị trí quân cờ từ dạng vector2f sang kí hiệu cờ vua đại số (algebraic notation)
string toChessNote(Vector2f p)
{
  string s = "";
  s += char(p.x/squareSize + 'a');              // Column
  s += char(8 - p.y/squareSize + '0');            // Row
  return s;
}

// chuyển từ algebraic notation sang vị trí quân cờ dạng vector2f (ngược lại hàm bên trên)
Vector2f toCoord(char a,char b)
{
   int x = int(a) - 'a';                 // Column
   int y = 8 - int(b) + '0';                 // Row
   return Vector2f(x*squareSize,y*squareSize);
}

void moveCastling(string str)
{
    Vector2f oldPos = toCoord(str[0],str[1]); // gán giá trị cũ của quân cờ trước khi bị di chuyển vào oldPos
    Vector2f newPos = toCoord(str[2],str[3]); // gán giá trị mới của quân cờ sau khi bị di chuyển vào newPos

    // xóa hình ảnh của quân cờ bị ăn bằng cách đưa nó ra vị trí -100 -100 (ẩn quân cờ khỏi window)
    for(int i = 0; i < 32; i++)
        if (f[i].getPosition() == newPos) 
            f[i].setPosition(-100,-100);
        
    // dịch chuyển vị trí của quân cờ
    for(int i = 0; i < 32; i++)
        if (f[i].getPosition() == oldPos) 
            f[i].setPosition(newPos);
}

// di chuyển quân cờ
void move(string str)
{
    Vector2f oldPos = toCoord(str[0],str[1]); // gán giá trị cũ của quân cờ trước khi bị di chuyển vào oldPos
    Vector2f newPos = toCoord(str[2],str[3]); // gán giá trị mới của quân cờ sau khi bị di chuyển vào newPos

    // xóa hình ảnh của quân cờ bị ăn bằng cách đưa nó ra vị trí -100 -100 (ẩn quân cờ khỏi window)
    for(int i = 0; i < 32; i++)
        if (f[i].getPosition() == newPos) 
            f[i].setPosition(-100,-100);
        
    // dịch chuyển vị trí của quân cờ
    for(int i = 0; i < 32; i++)
        if (f[i].getPosition() == oldPos) 
            f[i].setPosition(newPos);

    // Handle castling
    if (str == "e1g1" && position.find("e1") == -1) moveCastling("h1f1");
    if (str == "e8g8" && position.find("e8") == -1) moveCastling("h8f8");
    if (str == "e1c1" && position.find("e1") == -1) moveCastling("a1d1");
    if (str == "e8c8" && position.find("e8") == -1) moveCastling("a8d8");

}


// load hình ảnh của các quân cờ trong trò chơi
void loadPosition()
{
    int k = 0;               //stores the Sprite objects for each chess piece.
    for(int i =0 ; i < 8; i++)
        for(int j = 0; j < 8; j++)
        {
            int n = board[i][j];
            if (!n) continue;                  
            // nếu board = 0, nghĩa là vị trí trống không có quân cờ
            int x = abs(n) - 1;                  
            // gán loại quân cờ cho từng vị trí (ví dụ ở vị trí 1 là quân xe, 2 là quân mã)
            int y = n > 0 ? 1 : 0;                   
            // gán quân cờ trắng đen, nếu mang giá trị dương thì màu trắng, và ngược lại
            f[k].setTextureRect( IntRect(squareSize*x,squareSize*y,squareSize,squareSize) );
            // hàm setTextureRect chọn từng phần hình ảnh trong t1 (hình ảnh các quân cờ)
            // hàm IntRect sau đó tạo ra một hình vuông, lấy phần ảnh quân cờ thích hợp dựa trên x và y cho từng quân cờ
            f[k].setPosition(squareSize*j,squareSize*i); 
            // đặt hình ảnh quân cờ vào vị trí đúng trên bàn cờ
            k++;
        }

    // Apply moves in position string
    for(int i = 0; i < position.length(); i += 5)
        move(position.substr(i,4));
}

void ConnectToEngine(const char* path) {
    SECURITY_ATTRIBUTES sats = { sizeof(sats), NULL, TRUE };
    CreatePipe(&pipout_r, &pipout_w, &sats, 0);
    CreatePipe(&pipin_r, &pipin_w, &sats, 0);

    sti.cb = sizeof(sti);
    sti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    sti.wShowWindow = SW_HIDE;
    sti.hStdInput = pipin_r;
    sti.hStdOutput = pipout_w;
    sti.hStdError = pipout_w;

    if (!CreateProcessA(path, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &sti, &pi)) {
        DWORD error = GetLastError();  // Capture the error code
        cerr << "Failed to start Stockfish. Error code: " << error << endl;
        exit(1);
    }
}


string getNextMove(const string& position) {
    string command = "position startpos moves " + position + "\ngo\n";
    DWORD writ, read, available;
    BYTE buffer[2048];
    string output;

    WriteFile(pipin_w, command.c_str(), command.length(), &writ, NULL);

    // Wait for Stockfish response
    while (true) {
        Sleep(50);  // Short delay to allow Stockfish to process

        PeekNamedPipe(pipout_r, NULL, 0, NULL, &available, NULL);
        if (available > 0) {
            ZeroMemory(buffer, sizeof(buffer));
            ReadFile(pipout_r, buffer, sizeof(buffer) - 1, &read, NULL);
            buffer[read] = 0;
            output += (char*)buffer;

            size_t n = output.find("bestmove");
            if (n != string::npos) {
                return output.substr(n + 9, 4);
            }
        }
    }
    return "error";
}

void CloseConnection() {
    WriteFile(pipin_w, "quit\n", 5, NULL, NULL);
    CloseHandle(pipin_w);
    CloseHandle(pipin_r);
    CloseHandle(pipout_w);
    CloseHandle(pipout_r);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main()
{
    RenderWindow window(VideoMode(504, 504), "CHESS GAME");
    ConnectToEngine("C:\\Users\\ADMIN\\OneDrive\\Documents\\C++ project\\code\\stockfish.exe");
 // Relative path in the same directory


    Texture t1, t2;
    t1.loadFromFile("code/images/figures.png"); 
    t2.loadFromFile("code/images/board.png");

    // gán t1 cho toàn bộ mảng hình ảnh quân cờ f[i], sau đó mới chỉnh sửa lại texture sao cho các hình ảnh quân cờ hợp lí ở hàm loadPosition
    for(int i = 0; i < 32; i++) f[i].setTexture(t1);
    Sprite sBoard(t2);                         

    loadPosition();      

    bool isMove = false;
    float dx = 0, dy = 0;
    Vector2f oldPos, newPos;
    string str;
    int n = 0;

    while (window.isOpen()) // bắt toàn bộ event e
    {
        Vector2i pos = Mouse::getPosition(window) - Vector2i(offset); // vị trí trỏ chuột
        // lấy vị trí con trỏ chuột, cần phải trừ đi offset thì vị trí của chuột mới chính xác ở trên bàn cờ

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) // exit
                window.close();

            // đi lại nước trước, check nút backspace
            if (e.type == Event::KeyPressed && e.key.code == Keyboard::BackSpace)
            {
                if (position.length() > 6) // xóa string di chuyển, ví dụ 
                    position.erase(position.length() - 6, 5); 
                loadPosition(); // update bàn cờ
            }

            // người chơi di chuyển các quân cờ bằng các ấn giữ chuột trái
            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
                for(int i = 0; i < 32; i++)
                    if (f[i].getGlobalBounds().contains(pos.x,pos.y)) 
                    // kiểm tra người chơi chọn quân cờ gì, và chọn quân cờ đó để di chuyển
                    {
                        isMove = true; 
                        // một quân cờ nào đó đang di chuyển, đang bị drag
                        n = i; 
                        // n mang giá trị của quân cờ được chọn trong 32 quân cờ
                        dx = pos.x - f[i].getPosition().x;
                        dy = pos.y - f[i].getPosition().y;
                        // vị trí của hỉnh ảnh quân cờ, sao cho khi drag quân cờ thì hình ảnh quân cờ "dính" vào con trỏ chuột một cách hợp lí
                        oldPos = f[i].getPosition();
                        // lưu lại vị trí cũ của quân cờ cho các hành động sau
                    }

            if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left)
            {
                isMove = false;      // quân cờ ngừng bị drag
                Vector2f p = f[n].getPosition() + Vector2f(squareSize/2, squareSize/2); // vector2f của vị trí quân cờ
                // cần phải cộng thêm để lấy vị trí trung tâm của quân cờ, do hàm getPosition trả về tọa độ góc trên bên trái của ảnh quân cờ 
                newPos = Vector2f(squareSize*int(p.x/squareSize), squareSize*int(p.y/squareSize));
                // tính toán vị trí sao cho khi quân cờ được đặt xuống, thì vị trí mới của quân cờ nằm trên các ô cờ (có thể hiểu là làm tròn vị trí mới của quân cờ để quân cờ snap vào đúng ô cờ)
                str = toChessNote(oldPos) + toChessNote(newPos);
                move(str); 
                if (oldPos != newPos) position += str + " "; // ví dụ, position có thể là "e2e4 d7d5 "
                f[n].setPosition(newPos);                   
            }                       
        }

        // Stockfish move// Computer move (bot move) when space is pressed
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            str = getNextMove(position);
                    
            oldPos = toCoord(str[0], str[1]);
            newPos = toCoord(str[2], str[3]);
            
            // Find the piece that needs to move
            for (int i = 0; i < 32; i++) 
                if (f[i].getPosition() == oldPos) 
                    n = i;
            
            ///// Animation loop for bot's move /////
            for (int k = 0; k < 50; k++)
            {
                // Move piece incrementally towards new position
                Vector2f p = newPos - oldPos;
                f[n].move(p.x / 50, p.y / 50); 

                window.clear();            // Clear the window for a fresh frame
                window.draw(sBoard);       // Draw the board first

                // Offset and draw each piece
                for (int i = 0; i < 32; i++) f[i].move(offset);
                for (int i = 0; i < 32; i++) window.draw(f[i]); 
                for (int i = 0; i < 32; i++) f[i].move(-offset);

                window.display();          // Display the current frame
            }

            // Finalize the piece's position after animation completes
            move(str);                     // Update the board state logically
            position += str + " ";         // Append move to position string
            f[n].setPosition(newPos);      // Set the piece to its final position
        }

        // Update piece position while dragging
        if (isMove) 
            f[n].setPosition(pos.x - dx, pos.y - dy);

        ////// Draw section for the board and pieces //////

        window.clear();                     // Clear the window
        window.draw(sBoard);                // Draw the board

        // Apply offset and draw all pieces in their final positions
        for (int i = 0; i < 32; i++) f[i].move(offset);
        for (int i = 0; i < 32; i++) window.draw(f[i]); 
        for (int i = 0; i < 32; i++) f[i].move(-offset);

        window.display();                   // Display everything on the window
    }

    CloseConnection();
    return 0;
}

```
