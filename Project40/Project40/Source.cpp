#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <glut.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


char title[] = "SNAKE";
int game = 0;
int windowID;
using namespace std;
GLuint displist;
int dir = RIGHT;
int w = 900;
int h = 664;

signed int direction_x[4]={0,0,-10,10};
signed int direction_y[4]={10,-10,0,0};



struct Position {
	int x;
	int y;
};

struct
{
	int x;
	int y;
} Fruit;

struct
{
	int x;
	int y;
} Bonus1;

struct node
{
	node *next;
	node *pre;
	Position pos;
};

struct Snake
{ 
int leng;
	node *head;
	node *tail;
};

Snake snake;

int in_snake(int x, int y)
{
	node* s = snake.head;
	while (s->next->next != NULL) {
		if (x == s->pos.x && y == s->pos.y) {
			return 1;
		}
		s = s->next;
	}
	return 0;
}

void generate_food() {
	srand(time(NULL));


	while (true)
	{
		Fruit.x = rand() % 400;
		Fruit.y = rand() % 300;
		if ((game == 2 || game == 3)&& !in_snake(Fruit.x, Fruit.y) && Fruit.x % 10 == 0 && Fruit.y % 10 == 0 && Fruit.x > 40 && Fruit.x < 350 && Fruit.y > 40 && Fruit.y < 250) break;
		else
		{
			if (game == 1 && Fruit.x % 10 == 0 && !in_snake(Fruit.x, Fruit.y)&& Fruit.y % 10 == 0 && Fruit.x >= 20 && Fruit.x <= 400 && Fruit.y >= 20 && Fruit.y <= 300) break;
		}
	}
}

void gen_bon(int =0) {
srand(time(NULL));
	while (true) {
		Bonus1.x = rand() % 400;
		Bonus1.y = rand() % 300;
		if (!in_snake(Bonus1.x, Bonus1.y) && Bonus1.x % 10 == 0 && Bonus1.y % 10 == 0 && Bonus1.x > 40 && Bonus1.x < 350 && Bonus1.y > 40 && Bonus1.y < 250 && (Bonus1.x != Fruit.x || Bonus1.y != Fruit.y)) break;
	}

}

void init_snake(int length)
{
	snake.head = (node *)malloc(sizeof(node));											
	snake.head->pre = NULL;									
	snake.head->next = NULL;

	int x = 200;									
	int y = 150;

	snake.head->pos = { x,y };

	node* pre_node = snake.head;						
	node* Node;										

	for (int i = 1; i < length; i++)
	{
		Node=(node*)malloc(sizeof(node));
		Node->pre = pre_node;								
		Node->next = NULL;									
		pre_node->next = Node;															

		Node->pos.x = pre_node->pos.x - 10;				
		Node->pos.y = pre_node->pos.y;						

		pre_node = Node;											

	}

	snake.tail = pre_node;									
	snake.leng = length;		
	
	generate_food();
	if(game==3) gen_bon();
}


void Sdisplay()
{
	glPointSize(20);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	if (game == 2 || game == 3)
	{
		glColor3f(0.5, 0.1, 0);
		for (int i = 20; i < 380; i++) glVertex2f(i, 20);
		for (int i = 20; i < 280; i++) glVertex2f(20, i);
		for (int i = 20; i < 380; i++) glVertex2f(i, 280);
		for (int i = 20; i < 280; i++) glVertex2f(380, i);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glColor3f(0, 1, 0);

	for (node* Node = snake.head; Node != NULL; Node = Node->next)
	{
		glVertex2f(Node->pos.x - 10, Node->pos.y - 10);

	}
	
	glColor3f(1, 0.3, 0);
	glVertex2f(Fruit.x - 10, Fruit.y - 10);

	glClear(GL_COLOR_BUFFER_BIT);

	if (game == 3)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(Bonus1.x - 10, Bonus1.y - 10);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	glEnd();
	glFlush();
	glutSwapBuffers();

}




void eat_bon() {


	node* p;
		node* Node = (node*)malloc(sizeof(node));				
		Node->pos.x = Bonus1.x + direction_x[dir];									
		Node->pos.y = Bonus1.y; +direction_y[dir];

		Node->next = snake.head;								
		snake.head->pre = Node;
		Node->pre = NULL;

		snake.head = Node;										
		snake.leng++;

		node* end1=(node*)malloc (sizeof(node));
		end1->pos.x=snake.head->pos.x + direction_x[dir];
		end1->pos.y=snake.head->pos.y + direction_y[dir];
		end1->next = snake.head;								
		snake.head->pre = end1;
		end1->pre = NULL;

		snake.head = end1;										
		snake.leng++;
		node* end2 = (node*)malloc(sizeof(node));
		end2->pos.x = snake.head->pos.x + direction_x[dir];
		end2->pos.y = snake.head->pos.y + direction_y[dir];
		end2->next = snake.head;								
		snake.head->pre = end2;
		end2->pre = NULL;

		snake.head = end2;										
		snake.leng++;
		if (snake.leng == 100)
		{
			MessageBox(NULL, "Ты выиграл! :)", "Win", MB_OK);
			exit(0);
		}
	Bonus1.x = Bonus1.y = 0;
}

void change_dir(int key, int x, int y) {
	if (GetAsyncKeyState(VK_ESCAPE)) exit(0);
	switch (key)
	{
	case GLUT_KEY_UP:
		if (dir != DOWN)
		{
			dir = UP;
		}
		break;
	case GLUT_KEY_DOWN:
		if (dir!= UP)
		{
			dir = DOWN;
		}
		break;
	case GLUT_KEY_LEFT:
		if (dir != RIGHT)
		{
			dir = LEFT;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (dir != LEFT)
		{
			dir = RIGHT;

		}
	default:
		break;
	}

}
void snake_move()
{


	if ((snake.head->pos.x <= 30 || snake.head->pos.y <= 30 || snake.head->pos.x >= 390 || snake.head->pos.y >= 290) && (game != 1))
	{
		/*end = clock() * 1000 / CLOCKS_PER_SEC;;
		printf("\nReal time for sorting %i(ms)\n", (end - start));*/
		MessageBox(NULL, "Вы проиграли! Не выходите за границы поля", "End of the game", MB_OK);
		exit(0);
	}
	else
	{
	
			 
				if (snake.head->pos.x <= 200) snake.head->pos.x += 390;
		
			
				if (snake.head->pos.x >= 410) snake.head->pos.x -= 390;
			
			
				if (snake.head->pos.y <= 200) snake.head->pos.y += 290;
		
			
				if (snake.head->pos.y >= 310)snake.head->pos.y -= 290;
			
		

	}
	node* head = snake.head;
	snake.tail->pos.x = head->pos.x + direction_x[dir];		
	snake.tail->pos.y = head->pos.y + direction_y[dir];


	node* new_tail = snake.tail->pre;
	new_tail->next = NULL;									   


	snake.tail->pre = NULL;
	snake.tail->next = head;
	snake.head->pre = snake.tail;								

	snake.head = snake.tail;									
	snake.tail = new_tail;								        


}



int is_died()
{
if(snake.head!=0 && in_snake(snake.tail->pos.x, snake.tail->pos.y)){
MessageBox(NULL, "Вы врезались в себя :(", "End of the game", MB_OK);
exit(0);
}
}



int eat_food() {
	node* Node = (node*)malloc(sizeof(node));				
	Node->pos.x =Fruit.x ;									
	Node->pos.y = Fruit.y;

	Node->next = snake.head;								
	snake.head->pre = Node;
	Node->pre = NULL;

	snake.head = Node;										
	snake.leng++;
	if (snake.leng == 100)
	{
		MessageBox(NULL, "Ты выиграл! :)", "Win", MB_OK);
		exit(0);
	}
}

void onTimer(int =0 ) {

Sdisplay();
snake_move();
node* s = snake.head;
if (s->pos.x == Fruit.x && s->pos.y == Fruit.y){
	eat_food();
	generate_food();
}
if (s->pos.x == Bonus1.x && s->pos.y == Bonus1.y) {
eat_bon();
glutTimerFunc(30000, gen_bon, 0);
}
		is_died();
	   if(game!=3) glutTimerFunc(100,onTimer,0);
	   else {
	   glutTimerFunc(50, onTimer, 0);
	   }
}




void drawText(float x, float y, const char text[], int j) {
	int len = strlen(text);
	glColor3f(0.0, 0.0, 0.0);
	if (j == 1) {
		glRasterPos2i(x, y);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	if (j == 2) {
		glRasterPos2i(x, y);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);  //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}

	if (j == 3) {
		void *font = GLUT_STROKE_ROMAN; //один из предварительно определены шрифтов в GLUT
		glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(0.4f, 0.3f, 25.0f);
		for (int i = 0; i < len; i++)
			glutStrokeCharacter(font, text[i]);
		glPopMatrix();
	}
}


void Modes() {


	if (game == 1) {
		printf("1\n");
		Sleep(800);
		glClearColor(0.0, 0.0, 0, 0.0);
		glViewport(0, 0, w, h);
		gluOrtho2D(0, 400, 0, 300);
		glutDisplayFunc(Sdisplay);
		glutSpecialFunc(change_dir);
		init_snake(3);
		onTimer();
		glutMainLoop();

	}
	if (game == 2) {
		printf("2\n");
		Sleep(800);
		glClearColor(0.0, 0.0, 0, 0.0);
		glViewport(0, 0, w, h);
		gluOrtho2D(0, 400, 0, 300);

		glutDisplayFunc(Sdisplay);
		glutSpecialFunc(change_dir);
		init_snake(3);
		onTimer();
		

		glutMainLoop();
	}
	if (game == 3) {
		printf("3\n");
		Sleep(800);
		glClearColor(0.0, 0.0, 0, 0.0);
		glViewport(0, 0, w, h);
		gluOrtho2D(0, 400, 0, 300);

		glutDisplayFunc(Sdisplay);
		glutSpecialFunc(change_dir);
		init_snake(3);
		onTimer();


		glutMainLoop();
	}
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glutSwapBuffers();

}

void orthogonalStart(void) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1536, 0, 864);
	glMatrixMode(GL_MODELVIEW);
}

void orthogonalEnd(void) {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
	if (key == 49) {
		game = 1;
		init_snake(3);
		Modes();
		glutMainLoop();
	}
	else if (key == 50) {
		game = 2;
		init_snake(3);
		Modes();
		glutMainLoop();

	}
	else if (key == 51) {
		game = 3;
		init_snake(3);
		Modes();
		glutMainLoop();
	}
	printf("%i %c\n", key, key);
}

void displayMenu(void) {
	glClearColor((float)255 / 255.0, (float)255 / 255.0, (float)255 / 255.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	orthogonalStart();
	displist = glGenLists(1);
	glNewList(displist, GL_COMPILE);
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);

	drawText(678, 730, "SNAKE", 3);
	drawText(679, 730, "SNAKE", 3);
	drawText(678, 731, "SNAKE", 3);
	drawText(679, 731, "SNAKE", 3);
	drawText(680, 730, "SNAKE", 3);
	drawText(680, 731, "SNAKE", 3);

	int shift = 0;
	for (int i = 0; i < 3; i++) {
		glBegin(GL_QUADS);
		glColor3f((float)230 / 255.0, (float)230 / 255.0, (float)230 / 255.0);

		glVertex2f(568, 350 + shift); //нижний левый угол
		glVertex2f(568, 250 + shift); //верхний левый угол
		glVertex2f(968, 250 + shift); //верхний правый угол
		glVertex2f(968, 350 + shift); //нижний правый угол
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		if (i == 2) {
			glRasterPos2i(728, 300); //set position to top corner to print EDIT 
			drawText(720, 300 + shift, "level 1", 2);
		}
		if (i == 1) {
			drawText(720, 300 + shift, "level 2", 2);
		}
		if (i == 0) {
			drawText(720, 300 + shift, "level 3", 2);
		}
		glPopMatrix();
		shift += 130;
		glFlush();
	}
	glEndList();
	glCallList(displist);
	orthogonalEnd();
	glutSwapBuffers();
	glLoadIdentity();
	glFlush();
}

int main(int argc, char **argv) {
	//start = clock() * 1000 / CLOCKS_PER_SEC
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(80, 80);
	windowID = glutCreateWindow(title);
	glutDisplayFunc(displayMenu);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}