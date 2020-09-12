#include <gl/glut.h>
#include <stdio.h>
#include <string>
#include "Game.h"
#include "Build.h"
#include "Board.h"
#include "Stick.h"
#include <vector>
#include <fstream>

using namespace Build;

namespace Hanoi
{
	Game::Game(int M) {
		N = 3;
		gameIs = true;

		sticks = new int* [M];
		for (size_t i = 0; i < M; i++)
			sticks[i] = new int[3];

		this->xStep = 0.4f;
		this->M = M;
		this->moves = 0;
		base.push_back(new  Board(0.0f, 0.0f, 0.0f, 1.2f, 0.05f, 0.4f, diffWhite, ambiWhite, specWhite));
		for (size_t i = 0; i < 3; i++)
			base.push_back(new Stick(allocX(i), 0.15f, 0.0f, 0.05f, 0.3f, 0.1f, diffWhite, ambiWhite, specWhite));
		for (size_t i = 0, j = M; i < M; i++, j--)
			base.push_back(new Disk(allocX(0), 0.05f * (j), 0.0f, 0.2f + i * 0.05f, 0.05f, 0.1f, diffLightBlue, ambiLightBlue, specLightBlue, 0.05));

		initialize();
	}

	Game::~Game()
	{
		for (size_t i = 0; i < base.size(); i++)
			delete base[i];
		for (size_t i = 0; i < N; i++)
			delete[]sticks[i];
		delete[]sticks;
	}

	float Game::allocX(int i)
	{
		return  0.4f * i - 0.4f;
	}

	float Game::allocY(int i)
	{
		return  0.05f * i;
	}

	bool Game::moveDisk(int xFrom, int xTo)
	{
		if (xFrom < 0 || xFrom >= 3)
			return false;

		if (xTo < 0 || xTo >= 3)
			return false;

		base[NumOfDisk + 4]->setXCenter(allocX(xTo));

		sticks[NumOfDisk][0] = xTo;
		sticks[NumOfDisk][1] = -1;

		return true;
	}

	void Game::upDisk(int x)
	{
		int y = 0;
		int temp = IfStickHasDisks(x);
		if (temp == 1)
			return;
		for (size_t i = 0; i < N; i++)
		{
			if (x == sticks[i][0]) { NumOfDisk = i; break; }
		}

		if (x < 0 || x >= N)
			return;
		else
		{
			base[NumOfDisk + 4]->setYCenter(0.5);
		}
		
	}

	void Game::downDisk()
	{
		moves++;
		for (int i = 0; i < N; i++)
		{
			if (sticks[i][1] == -1) {

				int t = IfStickHasDisks(sticks[i][0]);
				bool check = false;

				if (t == 1)
					check = true;
				else {
					int* temp = new int[N];

					for (size_t j = 0; j < N; j++)
					{
						if (sticks[j][0] == sticks[i][0] && i != j)
							temp[j] = 1;
						else	temp[j] = -1;
					}
					for (size_t j = 0; j < N; j++)
					{
						if (temp[j] == 1 && j < i) { check = false; break; }
						check = true;
					}
				}

				if (check) {
					base[i + 4]->setYCenter(allocY(IfStickHasDisks(sticks[i][0])));
					sticks[i][1] = IfStickHasDisks(sticks[i][0]) - 1;
					sticks[i][2] = sticks[i][0];
					break;
				}
				else
				{
					base[i + 4]->setYCenter(allocY(IfStickHasDisks(sticks[i][2])));
					base[i + 4]->setXCenter(allocX(sticks[i][2]));
					sticks[i][1] = IfStickHasDisks(sticks[i][0]);
					sticks[i][0] = sticks[i][2];
					break;
				}
			}
		}
	}

	int Game::IfStickHasDisks(int i) {//повертає кількість дисків (на 1 більше)
		int y = 1;
		for (int j = 0; j < N; j++)
		{
			if (sticks[j][0] == i && sticks[j][1] != -1)
				y += 1;
		}
		return y;
	}

	void Game::initialize()
	{
		for (int i = 0, j = N - 1; i < N; i++, j--) {
			sticks[i][0] = 0;
			sticks[i][1] = j;
			sticks[i][2] = 0;
		}
		for (size_t i = 4, j = M; i < base.size(); i++, j--) {
			base[i]->setYCenter(0.05f * (j));
			base[i]->setXCenter(allocX(0));
		}
		int temp = base.size() - 4 - N;//number of not-drawn disks

		if (temp)
			for (size_t i = 3 + N; i != 3; i--)
			{
				base[i]->setYCenter(base[i]->getYCenter() - temp * 0.05f);
			}

		distZ = -1.7;
		angleX = 0;
		angleY = 20;
		time = 0;
		finish = false;
		NumOfDisk = 0;
		moves = 0;
	}

	bool Game::findNearest(int x, int y, int& x1)
	{
		int viewport[4];
		int jMin = -1;
		double mvMatrix[16], projMatrix[16];
		double minDist = 2000;

		for (int j = 0; j < 3; j++)
		{
			double wx = allocX(j);
			double wy = 0.1;
			double wz = 0;

			glGetIntegerv(GL_VIEWPORT, viewport);

			glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
			glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

			double dx, dy, dz;

			gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
			dy = viewport[3] - dy - 1;
			double d = (x - dx) * (x - dx) + (y - dy) * (y - dy);
			if (d < minDist)
			{
				minDist = d;
				jMin = j;
			}

		}
		if (minDist < 1000)
		{
			x1 = jMin;
			return true;
		}
		else
		{
			return false;
		}
	}

	void Game::draw()
	{
		char text[256];

		if (finish)
			sprintf_s(text, "you win! press F1 to restart the game or escape for exit.  your time: %d sec.", time);
		else
			sprintf_s(text, "Time: %d sec. | F1 - restart | ESC - exit | F2-5 - change number of disk | F6 - records", time);

		glViewport(0, 0, width, height);

		glClearColor(0.7, 0.6, 0.3, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, 1, 0, 1, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(0.9, 1.0, 1.0);
		writeText(GLUT_BITMAP_HELVETICA_18, text, 0.01, 0.95);
		sprintf_s(text, "moves: %d", moves);
		writeText(GLUT_BITMAP_HELVETICA_18, text, 0.01, 0.90);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(60, width / height, 1, 100);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0, 0, distZ);

		glRotatef(angleX, 0.0f, 1.0f, 0.0f);
		glRotatef(angleY, 1.0f, 0.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_LIGHTING);

		glEnable(GL_LIGHT0);

		for (int i = 0; i < 4 + N; i++)
			base[i]->draw();

		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glFlush();
		glutSwapBuffers();
	}

	void Game::on_size(int width, int height)
	{
		this->width = width;
		if (height == 0)
			height = 1;
		this->height = height;
	}

	void Game::on_mouse(int button, int state, int x, int y)
	{

		mouseX = x;
		mouseY = y;
		if ((state == GLUT_UP))
		{
			downDisk();
			int check = false;
			for (size_t i = 0, j = N - 1; i < N; i++, j--)
			{
				if (sticks[i][0] == 2 && sticks[i][1] == j)
					check = true;
				else { check = false; break; }
			}
			if (check)
			{
				getTime();
				finish = true;

			}
			this->button = -1;
			return;
		}
		this->button = button;
		if (finish)
			return;
		if (button == 0 && findNearest(x, y, xFrom))
			upDisk(xFrom);
	}

	void Game::on_motion(int x, int y)
	{
		switch (button)
		{
		case 0:
			if (finish)
				break;
			if (findNearest(x, y, xTo))
			{
				moveDisk(xFrom, xTo);
				xFrom = xTo;
			}
			break;
		}
	}

	void Game::on_special(int key, int x, int y)
	{
		switch (key) {
		case GLUT_KEY_UP:
			angleY += 3;
			break;
		case GLUT_KEY_DOWN:
			angleY -= 3;
			break;
		case GLUT_KEY_F2:
			N = 2;
			gameIs = true;
			Game::draw();
			Game::initialize();
			break;
		case GLUT_KEY_F1:
			gameIs = true;
			Game::initialize();
			break;
		case GLUT_KEY_LEFT:
			angleX -= 3;
			break;
		case GLUT_KEY_RIGHT:
			angleX += 3;
			break;
		case GLUT_KEY_F3:
			N = 3;
			gameIs = true;
			Game::draw();
			Game::initialize();
			break;
		case GLUT_KEY_F4:
			N = 4;
			gameIs = true;
			Game::draw();
			Game::initialize();
			break;
		case GLUT_KEY_F5:
			N = 5;
			gameIs = true;
			Game::draw();
			Game::initialize();
			break;
		case GLUT_KEY_F6:
			gameIs = false;
			Game::showRecords();
			break;
		}
	}

	int tick = 0;
	void Game::on_timer(int value)
	{
		tick++;
		if (tick >= 40)
		{
			if (!finish)
				time++;
			tick = 0;
		}
		if (gameIs)
			draw();
		else showRecords();
	}

	void Game::getTime() {
		ofstream fout;
		fout.open("time.txt", ios::app);
		fout <<  N << "|";
		fout << moves << "|";
		fout <<  time << "|"<< endl;
		fout.close();
	}

	void Game::showRecords() {
		const int len = 7, wi = 3, l1 = 50 ,l2 = 30;
		int s[len][wi];
		char t[l1], r[l1], u[l2];
		int x, y, st;
		char z;
		for (size_t i = 1; i < len; i++)
			for (size_t j = 0; j < wi; j++)
				s[i][j] = 0;
		
		for (size_t i = 2; i < len; i++)
				s[i][0] = i;


		fstream inOut;
		inOut.open("time.txt", ios::in);
		for (;;)	if (!inOut.eof()) {
				inOut >> x >> z >> y >> z >> st >> z;
				if (s[x][1]==0 || (s[x][0]==x && s[x][1] > y)) 
					s[x][0] = x,	
					s[x][1] = y,	
					s[x][2] = st;
			}	else break;
	
		sprintf_s(t, "Your best results: (F1 to play)");
		glViewport(0, 0, width, height);
		glClearColor(0.7, 0.6, 0.3, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, 1, 0, 1, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(0.9, 1.0, 1.0);
		writeText(GLUT_BITMAP_HELVETICA_18, t, 0.01, 0.95);
	float y1 = 0.035, y2 = 0.95;
		
		for (size_t i = 2; i < len-1; i++)
		{
			if (s[i][1]!=0) {
				y2 -= y1;
				sprintf_s(t, "Disks: %d", s[i][0]);
				writeText(GLUT_BITMAP_HELVETICA_18, t, 0.01, y2);
				y2 -= y1;
				sprintf_s(r, "Moves: %d", s[i][1]);
				writeText(GLUT_BITMAP_HELVETICA_18, r, 0.01, y2);
				y2 -= y1;
				sprintf_s(r, "Time: %d", s[i][2]);
				writeText(GLUT_BITMAP_HELVETICA_18, r, 0.01, y2);
				y2 -= 2 * y1;
			}
			else {
				y2 -= y1;
				sprintf_s(r, "You have no played games with %d disks!", s[i][0]);
				writeText(GLUT_BITMAP_HELVETICA_18, r, 0.01, y2);
				y2 -= 2 * y1;
			}

		}
		
		glPopMatrix();

		glFlush();
		glutSwapBuffers();
		inOut.close();
	}

}