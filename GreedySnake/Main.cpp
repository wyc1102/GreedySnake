#include<graphics.h>
#include<conio.h>
#include<vector>
#include<random>
using std::uniform_int_distribution;
using std::mt19937;
using std::random_device;
using std::vector;
class Snake
{
private:
	enum 
	{
		NORTH,WEST,EAST,SOUTH
	}_dir;
	int _lenth;
	struct body
	{
		int _x;
		int _y;
	};
	vector<body> _body;
	bool istouch();
	struct APPLE
	{
		int _xa;
		int _ya;
	}apple;
public:
	Snake();
	~Snake() {};
	void move();
	bool isdeath();
	bool iseat();
	void snakeprint();
	void setdir(int a);
	void randomsetapple();
	bool setapple(int x,int y);
	bool isoverlap(int tempx, int tempy);
	void appleprint();
	void graw();
	int getlenth();
	void printscore();
};
int Snake::getlenth()
{
	return _lenth;
}
void Snake::graw()
{
	_lenth++;
	body temp = _body[_body.size() - 1];
	move();
	_body.push_back(temp);
}
void Snake::appleprint()
{
	setfillcolor(RED);
	solidcircle(apple._xa,apple._ya, 5);
}
bool Snake::isoverlap(int tempx,int tempy)
{
	for (int i = 0; i < _body.size(); i++)
	{
		if (_body[i]._x == tempx && _body[i]._y == tempy)
		{
			return true;
		}
	}
	return false;
}
void Snake::randomsetapple()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrubx(1, 50);
	uniform_int_distribution<> distruby(1, 40);
	bool flag = true;
	int tempx = distrubx(gen);
	int tempy = distruby(gen);
	while (isoverlap(tempx, tempy))
	{
		int tempx = distrubx(gen);
		int tempy = distruby(gen);
	}
	apple._xa = tempx * 10 + 5;
	apple._ya = tempy * 10 + 5;
}
bool Snake::setapple(int x,int y)
{
	for (int i = 0; i < _body.size(); i++)
	{
		if (_body[i]._x == x && _body[i]._y == y)
		{
			return false;
		}
	}
	apple._xa = x;
	apple._ya = y;
	return true;
}
bool Snake::iseat()
{
	if (_body[0]._x == apple._xa && _body[0]._y == apple._ya)
	{
		return true;
	}
	else return false;
}
Snake::Snake()
{
	_body.clear();
	_lenth = 1;
	body temp;
	temp._x = 255;
	temp._y = 205;
	_body.push_back(temp);
	_dir = EAST;
	apple._xa = 0;
	apple._ya = 0;
}
bool Snake::istouch()
{
	for (int i = 1; i < _body.size(); i++)
	{
		if (_body[0]._x == _body[i]._x && _body[0]._y == _body[i]._y)
		{
			return true;
		}
	}
	return false;
}
void Snake::move()
{
	for (auto i = _body.size() - 1; i > 0; i--)
	{
		_body[i]._x = _body[i - 1]._x;
		_body[i]._y = _body[i - 1]._y;
	}
	switch (_dir)
	{
	case NORTH:
		_body[0]._y -= 10;
		break;
	case WEST:
		_body[0]._x -= 10;
		break;
	case EAST:
		_body[0]._x += 10;
		break;
	case SOUTH:
		_body[0]._y += 10;
		break;
	}
}
void Snake::snakeprint()
{
	setfillcolor(RGB(0, 204, 0));
	for (int i = 0; i < _body.size(); i++)
	{
		solidcircle(_body[i]._x,_body[i]._y,5);
	}
}
void Snake::setdir(int a)
{
	switch (a)
	{
	case 0:
		if (_dir != SOUTH)
		{
			_dir = NORTH; break;
		}
	case 1:if (_dir != WEST)
		{
			_dir = EAST; break;
		}
	case 2:if (_dir != EAST)
		{
			_dir = WEST; break;
		}
	case 3:if (_dir != NORTH)
		{
			_dir = SOUTH; break;
		}
	}
}
bool Snake::isdeath()
{
	if (_body[0]._x <= 10 || _body[0]._x >= 510)
	{
		return true;
	}
	else if (_body[0]._y <= 10 || _body[0]._y >= 410)
	{
		return true;
	}
	else if(istouch())
	{
		return true;
	}
	return false;
}
void Snake::printscore()
{
	TCHAR num[20];
	_stprintf_s(num, _T("%d"), _lenth);
	TCHAR s[] = _T("Scores:");
	settextcolor(BLACK);
	outtextxy(520, 210, s);
	outtextxy(570, 210, num);
}
void gameover()
{
	BeginBatchDraw();
	cleardevice();
	TCHAR message[] = _T("Game over");
	settextcolor(BLACK);
	outtextxy(260, 210, message);
	FlushBatchDraw();
	EndBatchDraw();
	_getch();
}
void gamestart()
{
	initgraph(640, 480);
	setbkcolor(RGB(204, 255, 255));
	cleardevice();
	setlinecolor(RGB(51, 0, 0));
	line(10, 10, 510, 10);
	line(10, 10, 10, 410);
	line(510, 10, 510, 410);
	line(10, 410, 510, 410);
	setfillcolor(RGB(0, 204, 0));
	solidcircle(255, 205, 5);
}
void wallprint()
{
	setlinecolor(RGB(51, 0, 0));
	line(10, 10, 510, 10);
	line(10, 10, 10, 410);
	line(510, 10, 510, 410);
	line(10, 410, 510, 410);
}
void gamedraw(Snake a)
{
	bool flag = true;
	BeginBatchDraw();
	a.randomsetapple();
	//a.setapple(15, 15);
	while (1)
	{
		if (_kbhit())
		{
			char hit = _getch();
			switch (hit)
			{
			case 'w':
			case 'W':
				a.setdir(0); break;
			case 'a':
			case 'A':
				a.setdir(2); break;
			case 's':
			case 'S':
				a.setdir(3); break;
			case 'd':
			case 'D':
				a.setdir(1); break;
			}
		}
		cleardevice();
		if (flag)
		{
			a.move();
		}
		flag = true;
		a.snakeprint();
		wallprint();
		a.appleprint();
		a.printscore();
		FlushBatchDraw();
		if (a.isdeath())
		{
			EndBatchDraw();
			Sleep(200);
			gameover();
			return;
		}
		if (a.iseat())
		{
			flag = false;
			a.graw();
			a.randomsetapple();
		}
		Sleep(100);
	}
	EndBatchDraw();
}
int main()
{
	Snake snake;
	gamestart();
	_getch();
	gamedraw(snake);
	_getch();
}
//initgraph(960, 720);
//setbkcolor(RGB(204, 255, 255));
//cleardevice();
//setlinecolor(RGB(51, 0, 0));
//line(10, 10, 170, 10);
//setfillcolor(RGB(0, 204, 0));
//solidcircle(320, 240, 5);
//setfillcolor(RED);
//solidcircle(320, 300, 5);
//_getch();
//255,205
//260,210