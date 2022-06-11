#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

void textcolor(int fg_color, int bg_color)  //�� �ٲٱ�
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void removeCursor() //Ŀ�� ������
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y) //Ŀ�� ��ǥ �̵�
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

unsigned char getkeypad() //����Ű �Է� ����
{
	unsigned char key;

	key = getch();
	if (key == 224 || key == 0) //���� ���� Ű�� ����Ű���
	{
		key = getch();
		switch (key)
		{
		case 72: //���� ����Ű
			return 72; 
			break;
		case 80: //�Ʒ��� ����Ű
			return 80;
			break;
		}
	}
}

void drawbox(int startx, int starty, int lastx, int lasty) //�ڽ� �׸���
{
	int x;
	int y;

	for (x = startx, y = starty; x <= lastx; x += 2)
	{
		gotoxy(x, y);
		if (x == startx)
		{
			cout << "��";
		}
		else if (x == lastx)
		{
			cout << "��";
		}
		else
		{
			cout << "��";
		}
	}
	for (x = startx, y = lasty; x <= lastx; x += 2)
	{
		gotoxy(x, y);
		if (x == startx)
		{
			cout << "��";
		}
		else if (x == lastx)
		{
			cout << "��";
		}
		else
		{
			cout << "��";
		}
	}
	for (x = startx, y = starty + 1; y <= lasty - 1; y++)
	{
		gotoxy(x, y);
		cout << "��";
	}
	for (x = lastx, y = starty + 1; y <= lasty - 1; y++)
	{
		gotoxy(x, y);
		cout << "��";
	}
}

void drawspace(int startx, int starty, int lastx, int lasty) //��ĭ ä���
{
	int x;
	int y;

	for (x = startx; x <= lastx; x++)
	{
		for (y = starty; y <= lasty; y++)
		{
			gotoxy(x, y);
			cout << " ";
		}
	}
}

class Human //�츮�� ���ΰ�
{
private:
	string name;
	int popular = 0; //�α�(�����ϱ�� �ø�)
	int perpomence = 0; //����(�����ϱ�� �ø�)
	int degree = 0; //����(������� �ø�)
	int tired = 0; //�ǰ���(����ൿ���� �þ)
	int money = 2000; //��(�˹ٷ� �þ, �׸��� �бⰡ ���������� �پ��)

public:
	void lecture() //�����ϱ�
	{
		popular++;
		tired++;
	}
	int getpopular() //���� �α⵵ ����
	{
		return popular;
	}
	void setpopular(int num) //�α⵵ ����
	{
		popular = num;
	}
	void study() //�����ϱ�
	{
		perpomence++;
		tired = tired + 2;
	}
	int getperpomence() //���� ���� ����
	{
		return perpomence;
	}
	void thesis() //������
	{
		degree++;
		tired = tired + 2;
	}
	int getdegree() //���� ���� ����
	{
		return degree;
	}
	void alba() //�Ƹ�����Ʈ
	{
		money = money + 500;
		tired = tired + 3;
	}
	int gettired() //�ǰ��� ����
	{
		return tired;
	}
	void settired(int num) //�ǰ��� ����
	{
		tired = num;
	}
	int getmoney() //�� ����
	{
		return money;
	}
	void setmoney(int num) //�� ����
	{
		money = num;
	}
	void setname() //�̸� ���ϱ�
	{
		cin >> name;
	}
	string getname() //�̸� ����
	{
		return name;
	}
};

class Season //���� �� ���� �б�
{
private:
	int year = 0; //���� �� �� 0 ~ 3
	int semester = 1; //���� �б� 1 ~ 4 

public:
	void increaseyear() //���� �� �� ����
	{
		year++;
	}
	int getyear() //���� �� �� ����
	{
		return year;
	}
	void increasesemester() //���� �б� �� ����
	{
		semester++;
		if (semester == 5) //4�б� �����ϱ� 5�бⰡ ��ٴ°� �б⸦ 1�� �ٲٰ� �� �� �� �÷�����
		{
			semester = 1;
			increaseyear();
		}
	}
	int getsemester() //���� �б� �� ����
	{
		return semester;
	}
};

class Event //Ư�� ���� ������ �ߵ��ϴ� �̺�Ʈ
{
public:
	int dorest = 0; //�б⸦ ���� �̺�Ʈ���� ���°����� �����ϸ� 1�̵ǰ� �� �бⰡ ��ŵ�Ǹ� �Ƿε��� 0���� ����� ���� 1000���� ����
	int dowork = 0; //�б⸦ �� ���µ� ���� �̺�Ʈ���� ���� ����� �����ϸ� 1�̵ǰ� �� �бⰡ ��ŵ�Ǹ� ���� 3000���� ����

	void rest(Human &h)
	{
		int select = 1;
		unsigned char key = 1;

		drawspace(0, 0, 50, 24);
		textcolor(3, 0);
		drawbox(0, 0, 50, 11);
		gotoxy(2, 4);
		textcolor(12, 0);
		cout << "���� �ʹ� ���̰� �ǰ��ϴ�.";
		gotoxy(2, 6);
		cout << "�̹� �б�� ���� ���鼭 ������ �߽�����?";
		textcolor(3, 0);
		drawbox(0, 12, 50, 24);
		while (kbhit() == 1) getch(); //�Լ��� ���۵ɶ� �����ִ� ���ڸ� ������ �ؿ� while���� ����� ����ǰ� �ϱ� ����.
		while (key != 13) //���� ������ ����
		{
			if (kbhit() == 1)
			{
				key = getkeypad();
				if (key == 72)
				{
					select = 1;
				}
				else if (key == 80)
				{
					select = 2;
				}
			}
			if (select == 1)
			{
				gotoxy(2, 16);
				textcolor(11, 0);
				cout << "�ƴ�, ������ ���ð��� ����.";
				textcolor(15, 0);
				gotoxy(2, 20);
				cout << "�׷�, �̷��� ���������� ���� ��ġ�� ���ž�.";
			}
			else if (select == 2)
			{
				gotoxy(2, 16);
				cout << "�ƴ�, ������ ���ð��� ����.";
				gotoxy(2, 20);
				textcolor(11, 0);
				cout << "�׷�, �̷��� ���������� ���� ��ġ�� ���ž�.";
				textcolor(15, 0);
			}
		}
		if (select == 2) //2�� ����
		{
			h.settired(0);
			h.setmoney(h.getmoney() + 1000);
			dorest = 1;
		}
		drawspace(0, 0, 50, 24);
	}
	void work(Human &h)
	{
		int select = 1;
		unsigned char key = 1;

		drawspace(0, 0, 50, 24);
		textcolor(3, 0);
		drawbox(0, 0, 50, 11);
		gotoxy(2, 4);
		textcolor(12, 0);
		cout << "���� �� ������ ��Ȱ�� �Ұ����ϴ�.";
		gotoxy(2, 6);
		cout << "�̹� �б�� ���鼭 �����⿡ �����ұ�?";
		textcolor(3, 0);
		drawbox(0, 12, 50, 24);
		while (kbhit() == 1) getch(); //�Լ��� ���۵ɶ� �����ִ� ���ڸ� ������ �ؿ� while���� ����� ����ǰ� �ϱ� ����.
		while (key != 13) //���� ������ ����
		{
			if (kbhit() == 1)
			{
				key = getkeypad();
				if (key == 72)
				{
					select = 1;
				}
				else if (key == 80)
				{
					select = 2;
				}
			}		
			if (select == 1)
			{
				gotoxy(2, 16);
				textcolor(11, 0);
				cout << "�ƴ�, �����Դ� �ð��� ������.";
				gotoxy(2, 17);
				cout << "�ֺ� ����鿡�� ������ ��û����.";
				textcolor(15, 0);
				gotoxy(2, 20);
				cout << "�׷�, �����԰� �����帮��";
				gotoxy(2, 21);
				cout << "�̹� �б�� ��Ȱ�� �����°Ϳ� ��������.";
			}
			else if (select == 2)
			{
				gotoxy(2, 16);
				cout << "�ƴ�, �����Դ� �ð��� ������.";
				gotoxy(2, 17);
				cout << "�ֺ� ����鿡�� ������ ��û����.";
				gotoxy(2, 20);
				textcolor(11, 0);
				cout << "�׷�, �����԰� �����帮��";
				gotoxy(2, 21);
				cout << "�̹� �б�� ��Ȱ�� �����°Ϳ� ��������.";
				textcolor(15, 0);
			}
		}
		if (select == 1) //1�� ����
		{
			h.setpopular(h.getpopular() - 5);
			if (h.getpopular() < 0)
			{
				h.setpopular(0);
			}
			h.setmoney(3000);
		}
		if (select == 2) //2�� ����
		{
			h.setmoney(3000);
			h.settired(h.gettired() - 10);
			if (h.gettired() < 0)
			{
				h.settired(0);
			}
			dowork = 1;
		}
		drawspace(0, 0, 50, 24);
	}
};

void delayprint(string text, int delay, int x, int y) //õõ�� ����ϱ�
{
	int i;
	int length = text.length();

	gotoxy(x, y);
	for (i = 0; i < length; i += 2)
	{
		cout << text[i] << text[i + 1];
		Sleep(delay);
	}
}

void intro() //���� ���� �պκ� �ΰ� ������ �Լ�
{
	textcolor(7, 0);
	gotoxy(1, 8); cout << "�����    �����         ����           ��            �� ��           ��";
	gotoxy(1, 9); cout << "��      ��  ��      ��     ��      ��         ���        ��� ��        ��";
	gotoxy(1, 10); cout << "��       �� ��       ��  ��          ��       ��  ��    ��  �� ��      ��";
	gotoxy(1, 11); cout << "��       �� ��       �� ��            ��      ��   ��  ��   �� ��    ��";
	textcolor(8, 0);
	gotoxy(1, 12); cout << "��      ��  ��      ��  ��            ��      ��    ���    �� ����";
	textcolor(7, 0);
	gotoxy(1, 13); cout << "�����    �����    ��            ��      ��     ��     �� ��   ��";
	gotoxy(1, 14); cout << "��          ��  ��       ��          ��       ��            �� ��     ��";
	gotoxy(1, 15); cout << "��          ��    ��       ��      ��         ��            �� ��       ��";
	gotoxy(1, 16); cout << "��          ��      ��       ����           ��            �� ��         ��";
	textcolor(13, 0);
	gotoxy(29, 20);
	cout << "PRESS ENTER TO START";
	textcolor(15, 0);
	getchar(); //���� ������ ����
}

void prologue(Human &h) //������ ���ѷα�
{
	drawbox(0, 0, 78, 15);
	gotoxy(70, 14); cout << "(ENTER)";
	delayprint("�ȳ��ϼ��� ������.", 20, 2, 1);
	getchar();
	delayprint("�̹� ��ǥ ��̷Ӱ� ������ϴ�.", 20, 2, 3);
	getchar();
	delayprint("�а��� �Ÿ��̽� ������ ���п� ��ǻ�� ������ �̷��� ���� ������ �����ϴ�.", 20, 2, 5);
	getchar();
	delayprint("��... �׸��� ���� ��, ����� ������ �о����ϴ�.", 20, 2, 7);
	getchar();
	delayprint("���ͺ並 �ϰ��� �� �ܽŵ��� ������, ���� �б��� ������ ��������", 20, 2, 9);
	delayprint("�׺е鿡�� ���԰� �Ҽ��� ���� ������ �ֽø� �����ϰڽ��ϴ�.", 20, 2, 10);
	getchar(); //�̸� ���ϴ°����� �Ѿ

	drawspace(2, 1, 76, 14);
	gotoxy(2, 6); cout << "�Ҽ� : �Ѽ����б�"; //�Ҽ��� �Ѽ����б��ϱ� ���ٲ�, ��� �̺κ��� �ʿ� ���µ�, �� ������ ���Ἲ ������ ����.
	gotoxy(2, 5); cout << "�̸� : ";
	gotoxy(9, 5); h.setname();
	getchar();

	drawspace(2, 1, 76, 14);
	gotoxy(70, 14); cout << "(ENTER)";
	delayprint("...(�ߺ�����! �ߺ�����!)", 20, 2, 1);
	getchar();
	delayprint("���� ������ �������� ���� õ��, �������� ���� �ֺ�... ���̾���.", 20, 2, 3);
	getchar();
	delayprint("�ƹ����� �����ϴ� ����� �������� ������ ���� ���̵� ����̴�.", 20, 2, 5);
	getchar();
	delayprint("���� ���� ������� �����ϴ� ������ ���п����̰�,", 20, 2, 7);
	delayprint("����� �������� �����μ� �Ǹ��� ������ ��ǥ�� �ϴ� ���� ��ġ�� û���̴�.", 20, 2, 8);
	getchar();
	delayprint("������ �־��� �ð��� �뷫 4��.", 20, 2, 10);
	getchar();
	delayprint("������ 4�Ⱓ, �Ϸ��Ϸ縦 ��� ��ƾ� ���� �̷� �� ������?", 20, 2, 12);
	getchar();
}

void ending1(Human &h) //���� 1��(�����伭)(������)
{
	drawbox(0, 0, 78, 20);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("�ȳ��ϼ��� ������.", 20, 2, 1);
	getchar();
	delayprint("�̹� ��ǥ ��̷Ӱ� ������ϴ�.", 20, 2, 3);
	getchar();
	delayprint("�а��� �Ÿ��̽� ������ ���п� ��ǻ�� ������ �̷��� ���� ������ �����ϴ�.", 20, 2, 5);
	getchar();
	delayprint("��... �׸��� ���� ��, ����� ������ �о����ϴ�.", 20, 2, 7);
	getchar();
	delayprint("���ͺ並 �ϰ��� �� �ܽŵ��� ������, ���� �б��� ������ ��������", 20, 2, 9);
	delayprint("�׺е鿡�� ���԰� �Ҽ��� ���� ������ �ֽø� �����ϰڽ��ϴ�.", 20, 2, 10);
	getchar();

	drawspace(2, 1, 76, 19);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("�� �̸��� ", 20, 2, 1);
	delayprint(h.getname(), 20, 12, 1);
	cout << ".";
	getchar();
	delayprint("��ǻ�� ���� �ڻ����� �Ѽ����б� �����Դϴ�.", 20, 2, 3);
	getchar();
	delayprint("���� ���� �̷�� �´�.", 20, 2, 5);
	getchar();
	delayprint("�ʼ����� �پ��� ���� ���� �̷� ���̴�.", 20, 2, 7);
	getchar();
	delayprint("���� ����... �ٴ� ���� �ƴ϶�, �̷�� ���� ���̴�.", 20, 2, 9);
	getchar();
	textcolor(12, 0);
	delayprint("ED NO.1 �����伭", 200, 2, 19);
}

void ending2() //���� 2��(�������� ����)
{
	drawbox(0, 0, 78, 20);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("�л�1 : �� ���ʿ� �� ������ ��� �����ϳ�?", 20, 2, 1);
	getchar();
	delayprint("�л�2 : ��... �� ����. �״��� ȣ���� �Ȱ��ٰ� �����ϴµ�.", 20, 2, 3);
	getchar();
	delayprint("�л�1 : �� ��Ҹ��� �ʹ� ũ��. �鸮�ھ�.", 20, 2, 5);
	getchar();
	delayprint("...�̹� �� ��ȴ�.", 20, 2, 7);
	getchar();
	delayprint("���� ����, �ΰ����踦 ������ ���鼭���� �������ؼ� ������ �Ǿ���.", 20, 2, 9);
	getchar();
	delayprint("������ ����. �� ȸ�ǰ���... ���� �޲پ��� ������� ���� �ٸ��Ͱ���.", 20, 2, 11);
	getchar();
	delayprint("�׷����� ���� �� �Ӹ��ӿ� �������� �Ѹ����?", 20, 2, 13);
	getchar();
	delayprint("��. �Ͽ��� ����͵���... �� ���� ������ ��� ���ߴµ�.", 20, 2, 15);
	getchar();
	textcolor(12, 0);
	delayprint("ED NO.2 �������� ����", 200, 2, 19);
}

void ending3() //���� 3��(�λ��̴�)
{
	drawbox(0, 0, 78, 20);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("���� ������ �ϱ� ���� ���п��� ���Ծ���.", 20, 2, 1);
	getchar();
	delayprint("�Ǹ��� ������ �Ǳ� ������ �ƴϾ�����.", 20, 2, 3);
	getchar();
	delayprint("������, ������...", 20, 2, 5);
	getchar();
	delayprint("ģ�� : �� ����. ���� �ǹ� ���ϰ�.", 20, 2, 7);
	getchar();
	delayprint("�� : �̾� �̾�. ��, ���� ���ð� ����!", 20, 2, 9);
	getchar();
	delayprint("������ ���� ������ �ϴ� ���� �߿��Ѱ�.", 20, 2, 11);
	getchar();
	delayprint("���� �λ��� �ѹ��ۿ� ���� û���� ���� �Ǵ°� �ƴϰڴ°�?", 20, 2, 13);
	getchar();
	textcolor(12, 0);
	delayprint("ED NO.3 �λ��̴�", 200, 2, 19);
}

void ending4() //���� 4��(��ġ�� ���� ����)
{
	drawbox(0, 0, 78, 20);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("...(�ߺ�����! �ߺ�����!)", 20, 2, 1);
	getchar();
	delayprint("���� ������ �������� ���� õ��, �������� ���� �ֺ�... �������߰ڴ�.", 20, 2, 3);
	getchar();
	delayprint("���п�����, ���۽��� �ƹ����� �����������", 20, 2, 5);
	delayprint("Ȱ���� ���� ���� ����ä ���踦 �����ϱ� ���� ���� �� ���ۿ� ������.", 20, 2, 6);
	getchar();
	delayprint("�ʼ����� ���� ����, �Ͽ��� �繫�ҿ��� �ڵ� �밡�ٸ� �ϰ��ִ�.", 20, 2, 8);
	getchar();
	delayprint("��¿ �� ����. �������� �ξ��ؾ� �ϴϱ�.", 20, 2, 10);
	getchar();
	delayprint("��¿ �� ���� ���̴�...", 20, 2, 12);
	getchar();
	textcolor(12, 0);
	delayprint("ED NO.4 ��ġ�� ���� ����", 200, 2, 19);
}

void ending5() //���� 5��(������� ������)
{
	drawbox(0, 0, 78, 20);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("���ǹ��� ��ħ, ���ǹ��� �, ���ǹ��� �����.", 20, 2, 1);
	getchar();
	delayprint("������� ���� �Ϸ�� ���ǹ��ϰ�, ���̰����� ������� ����á��.", 20, 2, 3);
	getchar();
	delayprint("�����ε� �ѽ��ϴ� �����, ���õ� ��������� ���� �����δ�.", 20, 2, 5);
	getchar();
	delayprint("�Ƹ� ���� �����ߴ� ��� ������ ó�� �Ǵ°�", 20, 2, 7);
	delayprint("���������� �Ұ����ϴ� �������� ���ĺ��� �ε��ϴ�.", 20, 2, 8);
	getchar();
	delayprint("�������κ��� 10����, �� �� �ϰ� ������?", 20, 2, 10);
	getchar();
	delayprint("������ �ȴ�.", 20, 2, 12);
	getchar();
	delayprint("������ ���� �߸��� ����� ������� �������� ������ ������ ����� �ִ�.", 20, 2, 14);
	getchar();
	textcolor(12, 0);
	delayprint("ED NO.5 ������� ������", 200, 2, 19);
}

void schedule(int key, int x, int y) //Ű����, �װͿ� ���� ��ǥ���� �޾� ������ ����Ѵ�.
{
	textcolor(14, 0);
	if (key == 49) //1
	{
		gotoxy(x, y);
		cout << "�����ϱ�";
	}
	else if (key == 50) //2
	{
		gotoxy(x, y);
		cout << "�����ϱ�";
	}
	else if (key == 51) //3
	{
		gotoxy(x, y);
		cout << "������";
	}
	else if (key == 52) //4
	{
		gotoxy(x, y);
		cout << "�˹ٰ���";
	}
	textcolor(15, 0);
}

int main()
{
	Human h;
	Season s;
	Event e;
	int gameover = 0; //1�̵Ǹ� ���� ����. ���� �б��� ���ǿ����� ������ ����.
	int key1, key2, key3, key4; //�������� �Է��ϱ� ���� Ű

	removeCursor();
	intro();
	system("cls");
	prologue(h);
	system("cls");

	while (gameover == 0) //������ ������ �ʾ����� ��� �ݺ�.
	{
		if (h.gettired() >= 20) //�Ƿε��� ������ rest()�̺�Ʈ ����
		{
			e.rest(h);
		}
		if (h.getmoney() <= 0) //���� ������ work()�̺�Ʈ ����
		{
			e.work(h);
		}

		textcolor(3, 0);
		drawbox(0, 0, 50, 4); //������ �ֺ�
		drawbox(0, 5, 50, 18); //������ ����
		drawbox(0, 19, 50, 24); //���� ����
		drawbox(52, 0, 78, 21); //�ൿ �α�
		drawbox(2, 1, 12, 3); //������1
		drawbox(14, 1, 24, 3); //������2
		drawbox(26, 1, 36, 3); //������3
		drawbox(38, 1, 48, 3); //������4
		textcolor(15, 0);
		drawspace(2, 20, 48, 23); //����â �����
		drawbox(2, 6, 16, 8);
		gotoxy(4, 7);
		cout << "(1)�����ϱ�";
		gotoxy(20, 6);
		cout << "�����ϱ� : �α� ����";
		drawbox(2, 9, 16, 11);
		gotoxy(4, 10);
		cout << "(2)�����ϱ�";
		gotoxy(20, 9);
		cout << "�����ϱ� : ���� ����";
		drawbox(2, 12, 16, 14);
		gotoxy(4, 13);
		cout << "(3)������";
		gotoxy(20, 12);
		cout << "������ : ���� ����";
		drawbox(2, 15, 16, 17);
		gotoxy(4, 16);
		cout << "(4)�˹ٰ���";
		gotoxy(20, 15);
		cout << "�˹ٰ��� : �� ����";
		gotoxy(20, 17);
		cout << "����ൿ : �Ƿε� ����";
		gotoxy(2, 20);
		cout << "�α� : " << h.getpopular();
		gotoxy(20, 20);
		cout << "���� : " << h.getperpomence();
		gotoxy(38, 20);
		cout << "���� : " << h.getdegree();
		gotoxy(2, 22);
		cout << "�Ƿε� : " << h.gettired();
		gotoxy(20, 22);
		cout << "�� : " << h.getmoney();
		gotoxy(52, 22);
		cout << "�Ҽ� : �Ѽ����б�";
		gotoxy(52, 23);
		cout << "�̸� : " << h.getname();
		gotoxy(52, 24);
		textcolor(10, 0);
		cout << "[" << s.getyear() << "]" << "��° " << "[" << s.getsemester() << "]" << "�б�";
		gotoxy(4, 2);
		textcolor(6, 0);
		cout << "1st_Act";
		gotoxy(16, 2);
		cout << "2nd_Act";
		gotoxy(28, 2);
		cout << "3rd_Act";
		gotoxy(40, 2);
		cout << "4th_Act";
		textcolor(15, 0);

		if (e.dorest != 1 && e.dowork != 1) //���� �Ǵ� ���Ѵٸ� ���������� ���� �Ѿ��.
		{
			do
			{
				key1 = getch();
			} while (key1 <= 48 || key1 >= 53); //�ϴ� 1�� �����ϰ� 1, 2, 3, 4�� �ƴϸ� �ݺ�.
			schedule(key1, 4, 2); //�Է¹��� ���ڿ� ��ǥ���� �Ѱ� �� ���ڿ� �����ϴ� �ൿ�� ���.
			do
			{
				key2 = getch();
			} while (key2 <= 48 || key2 >= 53); 
			schedule(key2, 16, 2); 
			do
			{
				key3 = getch();
			} while (key3 <= 48 || key3 >= 53); 
			schedule(key3, 28, 2); 
			do
			{
				key4 = getch();
			} while (key4 <= 48 || key4 >= 53);
			schedule(key4, 40, 2); 

			getchar(); //������ �� ������ ����
			drawspace(4, 2, 10, 2); //������1 �����
			drawspace(16, 2, 22, 2); //������2 �����
			drawspace(28, 2, 34, 2); //������3 �����
			drawspace(40, 2, 46, 2); //������4 �����
			drawspace(54, 1, 77, 20); //�α�â �����
			if (h.gettired() < 20) textcolor(1, 0); //���� ������ �Ķ���
			else if (h.gettired() >= 20) textcolor(4, 0); //�ǰ��ؼ� ����� �������� ������
			if (key1 == 49)
			{
				if (h.gettired() < 20)
				{
					h.lecture();
					gotoxy(54, 1);
					cout << "������ ���� �Ͽ���.";
				}
				else if (h.gettired() >= 20) //�ǰ��� ���¸�, �ƹ��͵� �ö��� ����.
				{
					gotoxy(54, 1);
					cout << "�Ƿζ����� ��������";
					gotoxy(54, 2);
					cout << "Ⱦ�������� �ߴ�.";
				}
			}
			else if (key1 == 50)
			{
				if (h.gettired() < 20)
				{
					h.study();
					gotoxy(54, 1);
					cout << "������ ������ �־���.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 1);
					cout << "�Ƿζ����� ������";
					gotoxy(54, 2);
					cout << "�տ� ������ �ʴ´�.";
				}
			}
			else if (key1 == 51)
			{
				if (h.gettired() < 20)
				{
					h.thesis();
					gotoxy(54, 1);
					cout << "���� ������� ����.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 1);
					cout << "�Ƿζ����� ����";
					gotoxy(54, 2);
					cout << "���� ������ �ʴ´�.";
				}
			}
			else if (key1 == 52)
			{
				if (h.gettired() < 20)
				{
					h.alba();
					gotoxy(54, 1);
					cout << "������ �˹ٸ� ���ƴ�.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 1);
					cout << "�Ƿζ����� �˹���";
					gotoxy(54, 2);
					cout << "��� �Ĺ��ȴ�.";
				}
			}
			if (h.gettired() < 20) textcolor(1, 0);
			else if (h.gettired() >= 20) textcolor(4, 0);
			if (key2 == 49)
			{
				if (h.gettired() < 20)
				{
					h.lecture();
					gotoxy(54, 4);
					cout << "������ ���� �Ͽ���.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 4);
					cout << "�Ƿζ����� ��������";
					gotoxy(54, 5);
					cout << "Ⱦ�������� �ߴ�.";
				}
			}
			else if (key2 == 50)
			{
				if (h.gettired() < 20)
				{
					h.study();
					gotoxy(54, 4);
					cout << "������ ������ �־���.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 4);
					cout << "�Ƿζ����� ������";
					gotoxy(54, 5);
					cout << "�տ� ������ �ʴ´�.";
				}
			}
			else if (key2 == 51)
			{
				if (h.gettired() < 20)
				{
					h.thesis();
					gotoxy(54, 4);
					cout << "���� ������� ����.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 4);
					cout << "�Ƿζ����� ����";
					gotoxy(54, 5);
					cout << "���� ������ �ʴ´�.";
				}
			}
			else if (key2 == 52)
			{
				if (h.gettired() < 20)
				{
					h.alba();
					gotoxy(54, 4);
					cout << "������ �˹ٸ� ���ƴ�.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 4);
					cout << "�Ƿζ����� �˹���";
					gotoxy(54, 5);
					cout << "��� �Ĺ��ȴ�.";
				}
			}
			if (h.gettired() < 20) textcolor(1, 0);
			else if (h.gettired() >= 20) textcolor(4, 0);
			if (key3 == 49)
			{
				if (h.gettired() < 20)
				{
					h.lecture();
					gotoxy(54, 7);
					cout << "������ ���� �Ͽ���.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 7);
					cout << "�Ƿζ����� ��������";
					gotoxy(54, 8);
					cout << "Ⱦ�������� �ߴ�.";
				}
			}
			else if (key3 == 50)
			{
				if (h.gettired() < 20)
				{
					h.study();
					gotoxy(54, 7);
					cout << "������ ������ �־���.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 7);
					cout << "�Ƿζ����� ������";
					gotoxy(54, 8);
					cout << "�տ� ������ �ʴ´�.";
				}
			}
			else if (key3 == 51)
			{
				if (h.gettired() < 20)
				{
					h.thesis();
					gotoxy(54, 7);
					cout << "���� ������� ����.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 7);
					cout << "�Ƿζ����� ����";
					gotoxy(54, 8);
					cout << "���� ������ �ʴ´�.";
				}
			}
			else if (key3 == 52)
			{
				if (h.gettired() < 20)
				{
					h.alba();
					gotoxy(54, 7);
					cout << "������ �˹ٸ� ���ƴ�.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 7);
					cout << "�Ƿζ����� �˹���";
					gotoxy(54, 8);
					cout << "��� �Ĺ��ȴ�.";
				}
			}
			if (h.gettired() < 20) textcolor(1, 0);
			else if (h.gettired() >= 20) textcolor(4, 0);
			if (key4 == 49)
			{
				if (h.gettired() < 20)
				{
					h.lecture();
					gotoxy(54, 10);
					cout << "������ ���� �Ͽ���.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 10);
					cout << "�Ƿζ����� ��������";
					gotoxy(54, 11);
					cout << "Ⱦ�������� �ߴ�.";
				}
			}
			else if (key4 == 50)
			{
				if (h.gettired() < 20)
				{
					h.study();
					gotoxy(54, 10);
					cout << "������ ������ �־���.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 10);
					cout << "�Ƿζ����� ������";
					gotoxy(54, 11);
					cout << "�տ� ������ �ʴ´�.";
				}
			}
			else if (key4 == 51)
			{
				if (h.gettired() < 20)
				{
					h.thesis();
					gotoxy(54, 10);
					cout << "���� ������� ����.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 10);
					cout << "�Ƿζ����� ����";
					gotoxy(54, 11);
					cout << "���� ������ �ʴ´�.";
				}
			}
			else if (key4 == 52)
			{
				if (h.gettired() < 20)
				{
					h.alba();
					gotoxy(54, 10);
					cout << "������ �˹ٸ� ���ƴ�.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 10);
					cout << "�Ƿζ����� �˹���";
					gotoxy(54, 11);
					cout << "��� �Ĺ��ȴ�.";
				}
			}
			textcolor(15, 0);
			h.setmoney(h.getmoney() - 1000); //�� �бⰡ ������ �� 1000�� ��
		}
		e.dorest = 0;
		e.dowork = 0;
		s.increasesemester(); //�б� ����

		if (s.getyear() == 4) //3��° 4�бⰡ ���ε� 4��°�� ��ٴ°� ������ �����ٴ� ����
		{
			gameover = 1;
		}
	}
	system("cls");
	if (h.getpopular() >= 13 && h.getperpomence() >= 15 && h.getdegree() >= 14) //���� 1��(������)
	{
		ending1(h);
	}
	else if (h.getpopular() < 13 && h.getperpomence() >= 13 && h.getdegree() >= 13) //���� 2��
	{
		ending2();
	}
	else if (h.getpopular() >= 40 && h.getperpomence() < 3 && h.getdegree() < 3) //���� 3��
	{
		ending3();
	}
	else if (h.getpopular() < 3 && h.getperpomence() < 3 && h.getdegree() < 3 && h.getmoney() >= 12000) //���� 4��
	{
		ending4();
	}
	else //���� 5��
	{
		ending5();
	}
	gotoxy(70, 19); 
	cout << "       "; //������ �Ʒ�(ENTER)�����.
	gotoxy(2, 22);
	textcolor(13, 0);
	cout << "PRESS ENTER TO EXIT";
	getchar();

	return 0;
}