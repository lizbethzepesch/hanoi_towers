#ifndef Game_  
#define Game_
#include "Disk.h"
#include "Base.h"
#include <vector>
using namespace std;
namespace Hanoi
{

    class Game
    {
        int N, M;//M � ����������� ������� �����; N � ������� ����� �� ��� ���
        vector<Base*> base;

        int button;           // ������ ���� (-1 - �� ���������, 0 - ���, 2 - �����)
        float angleX, angleY;
        float mouseX, mouseY;
        float width, height;
        float distZ;
        int NumOfDisk, NumOfPrevPlace;
        bool finish;
        bool gameIs; //game == true
                    // records == false
        int** sticks;       // ����� �����, �� ����������� �� ��������
                                  //[��������, �� � ���� ����������� ����][0]
                                   //[�����, ���� ���� ������][1]
        float xStep;
        int time;
        int moves;
        int xFrom, yFrom;
        int xTo, yTo;
    public:
        Game(int N);
        ~Game();
        void draw();
        void on_size(int width, int height);
        void on_mouse(int button, int state, int x, int y);
        void on_motion(int x, int y);
        void on_special(int key, int x, int y);
        void on_timer(int value);
        void getTime();
    private:
        void initialize();

        bool moveDisk(int xFrom, int xTo);
        void upDisk(int x);
        bool findNearest(int x, int z, int& x1);
        float allocX(int i);
        float allocY(int i);
        void downDisk();
        int IfStickHasDisks(int i);
        void showRecords();
    };

}

#endif