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
        int N, M;//M Ч максимальна к≥льк≥сть диск≥в; N Ч к≥льк≥сть диск≥в на пол≥ гри
        vector<Base*> base;

        int button;           // кнопка миш≥ (-1 - не натиснута, 0 - л≥ва, 2 - права)
        float angleX, angleY;
        float mouseX, mouseY;
        float width, height;
        float distZ;
        int NumOfDisk, NumOfPrevPlace;
        bool finish;
        bool gameIs; //game == true
                    // records == false
        int** sticks;       // масив диск≥в, €к≥ перебувають на стрижн€х
                                  //[стрижень, на € кому знаходитьс€ диск][0]
                                   //[номер, €кий диск зверху][1]
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