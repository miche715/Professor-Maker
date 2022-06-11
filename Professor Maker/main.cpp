#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

void textcolor(int fg_color, int bg_color)  //색 바꾸기
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void removeCursor() //커서 가리기
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y) //커서 좌표 이동
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

unsigned char getkeypad() //방향키 입력 제어
{
	unsigned char key;

	key = getch();
	if (key == 224 || key == 0) //만약 누른 키가 방향키라면
	{
		key = getch();
		switch (key)
		{
		case 72: //위쪽 방향키
			return 72; 
			break;
		case 80: //아래쪽 방향키
			return 80;
			break;
		}
	}
}

void drawbox(int startx, int starty, int lastx, int lasty) //박스 그리기
{
	int x;
	int y;

	for (x = startx, y = starty; x <= lastx; x += 2)
	{
		gotoxy(x, y);
		if (x == startx)
		{
			cout << "┏";
		}
		else if (x == lastx)
		{
			cout << "┓";
		}
		else
		{
			cout << "━";
		}
	}
	for (x = startx, y = lasty; x <= lastx; x += 2)
	{
		gotoxy(x, y);
		if (x == startx)
		{
			cout << "┗";
		}
		else if (x == lastx)
		{
			cout << "┛";
		}
		else
		{
			cout << "━";
		}
	}
	for (x = startx, y = starty + 1; y <= lasty - 1; y++)
	{
		gotoxy(x, y);
		cout << "┃";
	}
	for (x = lastx, y = starty + 1; y <= lasty - 1; y++)
	{
		gotoxy(x, y);
		cout << "┃";
	}
}

void drawspace(int startx, int starty, int lastx, int lasty) //빈칸 채우기
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

class Human //우리의 주인공
{
private:
	string name;
	int popular = 0; //인기(수업하기로 늘림)
	int perpomence = 0; //성과(연구하기로 늘림)
	int degree = 0; //학위(논문쓰기로 늘림)
	int tired = 0; //피곤함(모든행동으로 늘어남)
	int money = 2000; //돈(알바로 늘어남, 그리고 분기가 지날때마다 줄어듬)

public:
	void lecture() //수업하기
	{
		popular++;
		tired++;
	}
	int getpopular() //현재 인기도 리턴
	{
		return popular;
	}
	void setpopular(int num) //인기도 조정
	{
		popular = num;
	}
	void study() //연구하기
	{
		perpomence++;
		tired = tired + 2;
	}
	int getperpomence() //현재 성과 리턴
	{
		return perpomence;
	}
	void thesis() //논문쓰기
	{
		degree++;
		tired = tired + 2;
	}
	int getdegree() //현재 학위 리턴
	{
		return degree;
	}
	void alba() //아르바이트
	{
		money = money + 500;
		tired = tired + 3;
	}
	int gettired() //피곤함 리턴
	{
		return tired;
	}
	void settired(int num) //피곤함 조정
	{
		tired = num;
	}
	int getmoney() //돈 리턴
	{
		return money;
	}
	void setmoney(int num) //돈 조정
	{
		money = num;
	}
	void setname() //이름 정하기
	{
		cin >> name;
	}
	string getname() //이름 리턴
	{
		return name;
	}
};

class Season //지난 년 수와 분기
{
private:
	int year = 0; //지난 년 수 0 ~ 3
	int semester = 1; //현재 분기 1 ~ 4 

public:
	void increaseyear() //지난 년 수 증가
	{
		year++;
	}
	int getyear() //지난 년 수 리턴
	{
		return year;
	}
	void increasesemester() //현재 분기 수 증가
	{
		semester++;
		if (semester == 5) //4분기 까지니까 5분기가 됬다는건 분기를 1로 바꾸고 년 수 를 올려야함
		{
			semester = 1;
			increaseyear();
		}
	}
	int getsemester() //현재 분기 수 리턴
	{
		return semester;
	}
};

class Event //특정 조건 만족시 발동하는 이벤트
{
public:
	int dorest = 0; //분기를 쉬는 이벤트에서 쉬는것으로 결정하면 1이되고 그 분기가 스킵되며 피로도를 0으로 만들고 돈을 1000원을 더함
	int dowork = 0; //분기를 돈 버는데 쓰는 이벤트에서 돈을 벌기로 결정하면 1이되고 그 분기가 스킵되며 돈을 3000으로 만듬

	void rest(Human &h)
	{
		int select = 1;
		unsigned char key = 1;

		drawspace(0, 0, 50, 24);
		textcolor(3, 0);
		drawbox(0, 0, 50, 11);
		gotoxy(2, 4);
		textcolor(12, 0);
		cout << "몸이 너무 무겁고 피곤하다.";
		gotoxy(2, 6);
		cout << "이번 분기는 몸을 쉬면서 마음을 추스를까?";
		textcolor(3, 0);
		drawbox(0, 12, 50, 24);
		while (kbhit() == 1) getch(); //함수가 시작될때 남아있는 문자를 제거해 밑에 while문이 제대로 실행되게 하기 위함.
		while (key != 13) //엔터 누르면 종료
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
				cout << "아니, 나에게 쉴시간은 없어.";
				textcolor(15, 0);
				gotoxy(2, 20);
				cout << "그래, 이럴때 쉬지않으면 몸을 망치고 말거야.";
			}
			else if (select == 2)
			{
				gotoxy(2, 16);
				cout << "아니, 나에게 쉴시간은 없어.";
				gotoxy(2, 20);
				textcolor(11, 0);
				cout << "그래, 이럴때 쉬지않으면 몸을 망치고 말거야.";
				textcolor(15, 0);
			}
		}
		if (select == 2) //2번 선택
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
		cout << "돈이 다 떨어져 생활이 불가능하다.";
		gotoxy(2, 6);
		cout << "이번 분기는 쉬면서 돈벌기에 전념할까?";
		textcolor(3, 0);
		drawbox(0, 12, 50, 24);
		while (kbhit() == 1) getch(); //함수가 시작될때 남아있는 문자를 제거해 밑에 while문이 제대로 실행되게 하기 위함.
		while (key != 13) //엔터 누르면 종료
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
				cout << "아니, 나에게는 시간이 부족해.";
				gotoxy(2, 17);
				cout << "주변 사람들에게 도움을 요청하자.";
				textcolor(15, 0);
				gotoxy(2, 20);
				cout << "그래, 교수님게 말씀드리고";
				gotoxy(2, 21);
				cout << "이번 분기는 생활비를 모으는것에 집중하자.";
			}
			else if (select == 2)
			{
				gotoxy(2, 16);
				cout << "아니, 나에게는 시간이 부족해.";
				gotoxy(2, 17);
				cout << "주변 사람들에게 도움을 요청하자.";
				gotoxy(2, 20);
				textcolor(11, 0);
				cout << "그래, 교수님게 말씀드리고";
				gotoxy(2, 21);
				cout << "이번 분기는 생활비를 모으는것에 집중하자.";
				textcolor(15, 0);
			}
		}
		if (select == 1) //1번 선택
		{
			h.setpopular(h.getpopular() - 5);
			if (h.getpopular() < 0)
			{
				h.setpopular(0);
			}
			h.setmoney(3000);
		}
		if (select == 2) //2번 선택
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

void delayprint(string text, int delay, int x, int y) //천천히 출력하기
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

void intro() //게임 제일 앞부분 로고 나오는 함수
{
	textcolor(7, 0);
	gotoxy(1, 8); cout << "■■■■    ■■■■         ■■■           ■            ■ ■           ■";
	gotoxy(1, 9); cout << "■      ■  ■      ■     ■      ■         ■■        ■■ ■        ■";
	gotoxy(1, 10); cout << "■       ■ ■       ■  ■          ■       ■  ■    ■  ■ ■      ■";
	gotoxy(1, 11); cout << "■       ■ ■       ■ ■            ■      ■   ■  ■   ■ ■    ■";
	textcolor(8, 0);
	gotoxy(1, 12); cout << "■      ■  ■      ■  ■            ■      ■    ■■    ■ ■■■";
	textcolor(7, 0);
	gotoxy(1, 13); cout << "■■■■    ■■■■    ■            ■      ■     ■     ■ ■   ■";
	gotoxy(1, 14); cout << "■          ■  ■       ■          ■       ■            ■ ■     ■";
	gotoxy(1, 15); cout << "■          ■    ■       ■      ■         ■            ■ ■       ■";
	gotoxy(1, 16); cout << "■          ■      ■       ■■■           ■            ■ ■         ■";
	textcolor(13, 0);
	gotoxy(29, 20);
	cout << "PRESS ENTER TO START";
	textcolor(15, 0);
	getchar(); //엔터 누르면 시작
}

void prologue(Human &h) //게임의 프롤로그
{
	drawbox(0, 0, 78, 15);
	gotoxy(70, 14); cout << "(ENTER)";
	delayprint("안녕하세요 교수님.", 20, 2, 1);
	getchar();
	delayprint("이번 발표 흥미롭게 들었습니다.", 20, 2, 3);
	getchar();
	delayprint("학계의 거목이신 교수님 덕분에 컴퓨터 공학의 미래가 더욱 밝은것 같습니다.", 20, 2, 5);
	getchar();
	delayprint("아... 그리고 저번 논문, 상당히 감명깊게 읽었습니다.", 20, 2, 7);
	getchar();
	delayprint("인터뷰를 하고자 온 외신들이 많은데, 저희 학교의 위상을 높히고자", 20, 2, 9);
	delayprint("그분들에게 성함과 소속을 직접 말씀해 주시면 감사하겠습니다.", 20, 2, 10);
	getchar(); //이름 정하는곳으로 넘어감

	drawspace(2, 1, 76, 14);
	gotoxy(2, 6); cout << "소속 : 한성대학교"; //소속은 한성대학교니까 못바꿈, 사실 이부분은 필요 없는데, 위 대사와의 연결성 때문에 넣음.
	gotoxy(2, 5); cout << "이름 : ";
	gotoxy(9, 5); h.setname();
	getchar();

	drawspace(2, 1, 76, 14);
	gotoxy(70, 14); cout << "(ENTER)";
	delayprint("...(삐비비비비빅! 삐비비비비빅!)", 20, 2, 1);
	getchar();
	delayprint("손을 뻗으면 닿을듯한 낮은 천장, 정돈되지 않은 주변... 꿈이었다.", 20, 2, 3);
	getchar();
	delayprint("아무래도 존경하는 현희원 교수님의 강연을 보다 잠이든 모양이다.", 20, 2, 5);
	getchar();
	delayprint("나는 많은 사람들이 기피하는 퀴퀴한 대학원생이고,", 20, 2, 7);
	delayprint("현희원 교수님의 조교로서 훌륭한 교수를 목표로 하는 열정 넘치는 청년이다.", 20, 2, 8);
	getchar();
	delayprint("나에게 주어진 시간은 대략 4년.", 20, 2, 10);
	getchar();
	delayprint("앞으로 4년간, 하루하루를 어떻게 살아야 꿈을 이룰 수 있을까?", 20, 2, 12);
	getchar();
}

void ending1(Human &h) //엔딩 1번(프로페서)(진엔딩)
{
	drawbox(0, 0, 78, 20);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("안녕하세요 교수님.", 20, 2, 1);
	getchar();
	delayprint("이번 발표 흥미롭게 들었습니다.", 20, 2, 3);
	getchar();
	delayprint("학계의 거목이신 교수님 덕분에 컴퓨터 공학의 미래가 더욱 밝은것 같습니다.", 20, 2, 5);
	getchar();
	delayprint("아... 그리고 저번 논문, 상당히 감명깊게 읽었습니다.", 20, 2, 7);
	getchar();
	delayprint("인터뷰를 하고자 온 외신들이 많은데, 저희 학교의 위상을 높히고자", 20, 2, 9);
	delayprint("그분들에게 성함과 소속을 직접 말씀해 주시면 감사하겠습니다.", 20, 2, 10);
	getchar();

	drawspace(2, 1, 76, 19);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("제 이름은 ", 20, 2, 1);
	delayprint(h.getname(), 20, 12, 1);
	cout << ".";
	getchar();
	delayprint("컴퓨터 공학 박사이자 한성대학교 교수입니다.", 20, 2, 3);
	getchar();
	delayprint("나는 꿈을 이루어 냈다.", 20, 2, 5);
	getchar();
	delayprint("십수년전 꾸었던 꿈을 드디어 이루어낸 것이다.", 20, 2, 7);
	getchar();
	delayprint("역시 꿈은... 꾸는 것이 아니라, 이루어 내는 것이다.", 20, 2, 9);
	getchar();
	textcolor(12, 0);
	delayprint("ED NO.1 프로페서", 200, 2, 19);
}

void ending2() //엔딩 2번(고지식한 교수)
{
	drawbox(0, 0, 78, 20);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("학생1 : 야 저쪽에 저 교수님 어떻게 생각하냐?", 20, 2, 1);
	getchar();
	delayprint("학생2 : 어... 난 별로. 그다지 호감이 안간다고 생각하는데.", 20, 2, 3);
	getchar();
	delayprint("학생1 : 야 목소리가 너무 크다. 들리겠어.", 20, 2, 5);
	getchar();
	delayprint("...이미 다 들렸다.", 20, 2, 7);
	getchar();
	delayprint("젊은 시절, 인간관계를 포기해 가면서까지 열심히해서 교수가 되었다.", 20, 2, 9);
	getchar();
	delayprint("하지만 뭘까. 이 회의감은... 내가 꿈꾸었던 모습과는 많이 다른것같다.", 20, 2, 11);
	getchar();
	delayprint("그럼에도 지금 내 머리속에 떠오르는 한마디는?", 20, 2, 13);
	getchar();
	delayprint("쯧. 하여간 요즘것들은... 나 때는 저런거 상상도 못했는데.", 20, 2, 15);
	getchar();
	textcolor(12, 0);
	delayprint("ED NO.2 고지식한 교수", 200, 2, 19);
}

void ending3() //엔딩 3번(인사이더)
{
	drawbox(0, 0, 78, 20);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("나는 무엇을 하기 위해 대학원에 들어왔었나.", 20, 2, 1);
	getchar();
	delayprint("훌륭한 교수가 되기 위함이 아니었던가.", 20, 2, 3);
	getchar();
	delayprint("하지만, 지금은...", 20, 2, 5);
	getchar();
	delayprint("친구 : 야 뭐해. 빨리 건배 안하고.", 20, 2, 7);
	getchar();
	delayprint("나 : 미안 미안. 자, 오늘 마시고 죽자!", 20, 2, 9);
	getchar();
	delayprint("하지만 지금 무엇을 하던 뭐가 중요한가.", 20, 2, 11);
	getchar();
	delayprint("그저 인생에 한번밖에 없는 청춘을 즐기면 되는것 아니겠는가?", 20, 2, 13);
	getchar();
	textcolor(12, 0);
	delayprint("ED NO.3 인사이더", 200, 2, 19);
}

void ending4() //엔딩 4번(펼치지 못한 날개)
{
	drawbox(0, 0, 78, 20);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("...(삐비비비비빅! 삐비비비비빅!)", 20, 2, 1);
	getchar();
	delayprint("손을 뻗으면 닿을듯한 낮은 천장, 정돈되지 않은 주변... 나가봐야겠다.", 20, 2, 3);
	getchar();
	delayprint("대학원시절, 갑작스런 아버지의 사망으로인해", 20, 2, 5);
	delayprint("활동은 거의 하지 못한채 생계를 유지하기 위해 일을 할 수밖에 없었다.", 20, 2, 6);
	getchar();
	delayprint("십수년이 지난 지금, 일용직 사무소에서 코딩 노가다를 하고있다.", 20, 2, 8);
	getchar();
	delayprint("어쩔 수 없다. 가족들을 부양해야 하니까.", 20, 2, 10);
	getchar();
	delayprint("어쩔 수 없는 것이다...", 20, 2, 12);
	getchar();
	textcolor(12, 0);
	delayprint("ED NO.4 펼치지 못한 날개", 200, 2, 19);
}

void ending5() //엔딩 5번(무기력한 나날들)
{
	drawbox(0, 0, 78, 20);
	gotoxy(70, 19); cout << "(ENTER)";
	delayprint("무의미한 아침, 무의미한 등교, 무의미한 스펙업.", 20, 2, 1);
	getchar();
	delayprint("어느샌가 나의 하루는 무의미하고, 무미건조한 느낌들로 가득찼다.", 20, 2, 3);
	getchar();
	delayprint("스스로도 한심하다 여기며, 오늘도 기계적으로 몸을 움직인다.", 20, 2, 5);
	getchar();
	delayprint("아마 내가 존경했던 어느 교수님 처럼 되는걸", 20, 2, 7);
	delayprint("직감적으로 불가능하다 느꼈던때 이후부터 인듯하다.", 20, 2, 8);
	getchar();
	delayprint("지금으로부터 10년후, 난 뭘 하고 있을까?", 20, 2, 10);
	getchar();
	delayprint("걱정이 된다.", 20, 2, 12);
	getchar();
	delayprint("하지만 나의 발목을 붙잡는 무기력이 걱정조차 귀찮은 것으로 만들고 있다.", 20, 2, 14);
	getchar();
	textcolor(12, 0);
	delayprint("ED NO.5 무기력한 나날들", 200, 2, 19);
}

void schedule(int key, int x, int y) //키값과, 그것에 따른 좌표값을 받아 할일을 출력한다.
{
	textcolor(14, 0);
	if (key == 49) //1
	{
		gotoxy(x, y);
		cout << "수업하기";
	}
	else if (key == 50) //2
	{
		gotoxy(x, y);
		cout << "연구하기";
	}
	else if (key == 51) //3
	{
		gotoxy(x, y);
		cout << "논문쓰기";
	}
	else if (key == 52) //4
	{
		gotoxy(x, y);
		cout << "알바가기";
	}
	textcolor(15, 0);
}

int main()
{
	Human h;
	Season s;
	Event e;
	int gameover = 0; //1이되면 게임 오버. 엔딩 분기의 조건에따라 엔딩을 본다.
	int key1, key2, key3, key4; //스케쥴을 입력하기 위한 키

	removeCursor();
	intro();
	system("cls");
	prologue(h);
	system("cls");

	while (gameover == 0) //게임이 끝나지 않았으면 계속 반복.
	{
		if (h.gettired() >= 20) //피로도가 많으면 rest()이벤트 시작
		{
			e.rest(h);
		}
		if (h.getmoney() <= 0) //돈이 없으면 work()이벤트 시작
		{
			e.work(h);
		}

		textcolor(3, 0);
		drawbox(0, 0, 50, 4); //스케쥴 주변
		drawbox(0, 5, 50, 18); //스케쥴 선택
		drawbox(0, 19, 50, 24); //현재 상태
		drawbox(52, 0, 78, 21); //행동 로그
		drawbox(2, 1, 12, 3); //스케쥴1
		drawbox(14, 1, 24, 3); //스케쥴2
		drawbox(26, 1, 36, 3); //스케쥴3
		drawbox(38, 1, 48, 3); //스케쥴4
		textcolor(15, 0);
		drawspace(2, 20, 48, 23); //상태창 비워줌
		drawbox(2, 6, 16, 8);
		gotoxy(4, 7);
		cout << "(1)수업하기";
		gotoxy(20, 6);
		cout << "수업하기 : 인기 증가";
		drawbox(2, 9, 16, 11);
		gotoxy(4, 10);
		cout << "(2)연구하기";
		gotoxy(20, 9);
		cout << "연구하기 : 성과 증가";
		drawbox(2, 12, 16, 14);
		gotoxy(4, 13);
		cout << "(3)논문쓰기";
		gotoxy(20, 12);
		cout << "논문쓰기 : 학위 증가";
		drawbox(2, 15, 16, 17);
		gotoxy(4, 16);
		cout << "(4)알바가기";
		gotoxy(20, 15);
		cout << "알바가기 : 돈 증가";
		gotoxy(20, 17);
		cout << "모든행동 : 피로도 증가";
		gotoxy(2, 20);
		cout << "인기 : " << h.getpopular();
		gotoxy(20, 20);
		cout << "성과 : " << h.getperpomence();
		gotoxy(38, 20);
		cout << "학위 : " << h.getdegree();
		gotoxy(2, 22);
		cout << "피로도 : " << h.gettired();
		gotoxy(20, 22);
		cout << "돈 : " << h.getmoney();
		gotoxy(52, 22);
		cout << "소속 : 한성대학교";
		gotoxy(52, 23);
		cout << "이름 : " << h.getname();
		gotoxy(52, 24);
		textcolor(10, 0);
		cout << "[" << s.getyear() << "]" << "년째 " << "[" << s.getsemester() << "]" << "분기";
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

		if (e.dorest != 1 && e.dowork != 1) //쉰다 또는 일한다를 선택했으면 여긴 넘어간다.
		{
			do
			{
				key1 = getch();
			} while (key1 <= 48 || key1 >= 53); //일단 1번 실행하고 1, 2, 3, 4가 아니면 반복.
			schedule(key1, 4, 2); //입력받은 숫자와 좌표값을 넘겨 그 숫자에 대응하는 행동을 출력.
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

			getchar(); //스케쥴 다 쳤으면 엔터
			drawspace(4, 2, 10, 2); //스케쥴1 비워줌
			drawspace(16, 2, 22, 2); //스케쥴2 비워줌
			drawspace(28, 2, 34, 2); //스케쥴3 비워줌
			drawspace(40, 2, 46, 2); //스케쥴4 비워줌
			drawspace(54, 1, 77, 20); //로그창 비워줌
			if (h.gettired() < 20) textcolor(1, 0); //별일 없으면 파란색
			else if (h.gettired() >= 20) textcolor(4, 0); //피곤해서 제대로 못했으면 빨간색
			if (key1 == 49)
			{
				if (h.gettired() < 20)
				{
					h.lecture();
					gotoxy(54, 1);
					cout << "수업을 진행 하였다.";
				}
				else if (h.gettired() >= 20) //피곤한 상태면, 아무것도 올라가지 않음.
				{
					gotoxy(54, 1);
					cout << "피로때문에 수업에서";
					gotoxy(54, 2);
					cout << "횡설수설을 했다.";
				}
			}
			else if (key1 == 50)
			{
				if (h.gettired() < 20)
				{
					h.study();
					gotoxy(54, 1);
					cout << "연구가 진전이 있었다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 1);
					cout << "피로때문에 연구가";
					gotoxy(54, 2);
					cout << "손에 잡히지 않는다.";
				}
			}
			else if (key1 == 51)
			{
				if (h.gettired() < 20)
				{
					h.thesis();
					gotoxy(54, 1);
					cout << "논문을 어느정도 썻다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 1);
					cout << "피로때문에 논문이";
					gotoxy(54, 2);
					cout << "눈에 들어오지 않는다.";
				}
			}
			else if (key1 == 52)
			{
				if (h.gettired() < 20)
				{
					h.alba();
					gotoxy(54, 1);
					cout << "무사히 알바를 마쳤다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 1);
					cout << "피로때문에 알바중";
					gotoxy(54, 2);
					cout << "사고를 쳐버렸다.";
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
					cout << "수업을 진행 하였다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 4);
					cout << "피로때문에 수업에서";
					gotoxy(54, 5);
					cout << "횡설수설을 했다.";
				}
			}
			else if (key2 == 50)
			{
				if (h.gettired() < 20)
				{
					h.study();
					gotoxy(54, 4);
					cout << "연구가 진전이 있었다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 4);
					cout << "피로때문에 연구가";
					gotoxy(54, 5);
					cout << "손에 잡히지 않는다.";
				}
			}
			else if (key2 == 51)
			{
				if (h.gettired() < 20)
				{
					h.thesis();
					gotoxy(54, 4);
					cout << "논문을 어느정도 썻다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 4);
					cout << "피로때문에 논문이";
					gotoxy(54, 5);
					cout << "눈에 들어오지 않는다.";
				}
			}
			else if (key2 == 52)
			{
				if (h.gettired() < 20)
				{
					h.alba();
					gotoxy(54, 4);
					cout << "무사히 알바를 마쳤다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 4);
					cout << "피로때문에 알바중";
					gotoxy(54, 5);
					cout << "사고를 쳐버렸다.";
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
					cout << "수업을 진행 하였다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 7);
					cout << "피로때문에 수업에서";
					gotoxy(54, 8);
					cout << "횡설수설을 했다.";
				}
			}
			else if (key3 == 50)
			{
				if (h.gettired() < 20)
				{
					h.study();
					gotoxy(54, 7);
					cout << "연구가 진전이 있었다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 7);
					cout << "피로때문에 연구가";
					gotoxy(54, 8);
					cout << "손에 잡히지 않는다.";
				}
			}
			else if (key3 == 51)
			{
				if (h.gettired() < 20)
				{
					h.thesis();
					gotoxy(54, 7);
					cout << "논문을 어느정도 썻다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 7);
					cout << "피로때문에 논문이";
					gotoxy(54, 8);
					cout << "눈에 들어오지 않는다.";
				}
			}
			else if (key3 == 52)
			{
				if (h.gettired() < 20)
				{
					h.alba();
					gotoxy(54, 7);
					cout << "무사히 알바를 마쳤다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 7);
					cout << "피로때문에 알바중";
					gotoxy(54, 8);
					cout << "사고를 쳐버렸다.";
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
					cout << "수업을 진행 하였다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 10);
					cout << "피로때문에 수업에서";
					gotoxy(54, 11);
					cout << "횡설수설을 했다.";
				}
			}
			else if (key4 == 50)
			{
				if (h.gettired() < 20)
				{
					h.study();
					gotoxy(54, 10);
					cout << "연구가 진전이 있었다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 10);
					cout << "피로때문에 연구가";
					gotoxy(54, 11);
					cout << "손에 잡히지 않는다.";
				}
			}
			else if (key4 == 51)
			{
				if (h.gettired() < 20)
				{
					h.thesis();
					gotoxy(54, 10);
					cout << "논문을 어느정도 썻다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 10);
					cout << "피로때문에 논문이";
					gotoxy(54, 11);
					cout << "눈에 들어오지 않는다.";
				}
			}
			else if (key4 == 52)
			{
				if (h.gettired() < 20)
				{
					h.alba();
					gotoxy(54, 10);
					cout << "무사히 알바를 마쳤다.";
				}
				else if (h.gettired() >= 20)
				{
					gotoxy(54, 10);
					cout << "피로때문에 알바중";
					gotoxy(54, 11);
					cout << "사고를 쳐버렸다.";
				}
			}
			textcolor(15, 0);
			h.setmoney(h.getmoney() - 1000); //한 분기가 지나면 돈 1000을 씀
		}
		e.dorest = 0;
		e.dowork = 0;
		s.increasesemester(); //분기 증가

		if (s.getyear() == 4) //3년째 4분기가 끝인데 4년째가 됬다는건 게임이 끝났다는 뜻임
		{
			gameover = 1;
		}
	}
	system("cls");
	if (h.getpopular() >= 13 && h.getperpomence() >= 15 && h.getdegree() >= 14) //엔딩 1번(진엔딩)
	{
		ending1(h);
	}
	else if (h.getpopular() < 13 && h.getperpomence() >= 13 && h.getdegree() >= 13) //엔딩 2번
	{
		ending2();
	}
	else if (h.getpopular() >= 40 && h.getperpomence() < 3 && h.getdegree() < 3) //엔딩 3번
	{
		ending3();
	}
	else if (h.getpopular() < 3 && h.getperpomence() < 3 && h.getdegree() < 3 && h.getmoney() >= 12000) //엔딩 4번
	{
		ending4();
	}
	else //엔딩 5번
	{
		ending5();
	}
	gotoxy(70, 19); 
	cout << "       "; //오른쪽 아래(ENTER)지우기.
	gotoxy(2, 22);
	textcolor(13, 0);
	cout << "PRESS ENTER TO EXIT";
	getchar();

	return 0;
}