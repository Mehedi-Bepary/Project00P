#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <dos.h>
#include<fstream>
using namespace std;
#define MAXSNAKESIZE 100
#define MAXFRAMEX 119
#define MAXFRAMEY 29
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
int n=100;
void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if(size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

class cart
{
protected:
		int x;
		int y;
	    //constructor without agrument
		cart(){
			x = y = 10;
		}
		//constructor with agruments
		//use of this pointer
		cart(int x, int y){
			this -> x = x;
			this -> y = y;
		}
		void Setcart(int x, int y){
			this -> x = x;
			this -> y = y;
		}
};
class Point: virtual public cart
{
public:

    Point(){
			x = y = 10;
		}
		//constructor with agruments
		//use of this pointer
		Point(int x, int y){
			this -> x = x;
			this -> y = y;
		}
		void SetPoint(int x, int y){
			this -> x = x;
			this -> y = y;
		}

        int GetX(){
			return x;
		}
		int GetY(){
			return y;
		}
		void MoveUp(){
			y--;
			if( y < 0 )
				y = MAXFRAMEY;
		}
		void MoveDown(){
			y++;
			if( y > MAXFRAMEY )
				y = 0;
		}
		void MoveLeft(){
			x--;
			if( x < 0 )
				x = MAXFRAMEX;
		}
		void MoveRight(){
			x++;
			if( x > MAXFRAMEX )
				x = 0;
		}
		void Erase(){
			gotoxy(x,y);
			cout<<" ";
		}
		void CopyPos(Point * p){
			p->x = x;
			p->y = y;
		}
		int IsEqual(Point * p){
			if( p->x == x && p->y ==y )
				return 1;
			return 0;
		}
		void Debug(){
			cout<<"("<<x<<","<<y<<") ";
		}
		void Draw(char ch='O'){
			gotoxy(x,y);
			cout<<ch;
		}
		friend class poison;
};

class food:virtual public cart
{
public:
    virtual void Draw(char ch='O')=0;
};

class fruit:public food
{
public:

    void Draw(char ch='#'){
			gotoxy(x,y);
			cout<<ch;
		}

};

class poison: public Point, public food
{
  public:
      void Draw(char ch='$'){
			gotoxy(x,y);
			cout<<ch;
		}

};

void endScreen();

class snake
{
	private:
		Point * cell[MAXSNAKESIZE]; // array of points to represent snake
		int size; // current size of snake
		char dir; // current direction of snake
		Point fruit;
		int state; // bool representing state of snake : living, dead
		int started;
		poison p;
		int blink;// fruit blinking
		int blink1;
		int score;
	public:
	    int a;
		snake(){
			size = 1; // default size
			cell[0] = new Point(20,20); // 20,20 is default position
			for( int i=1; i<MAXSNAKESIZE; i++){
				cell[i] = NULL;
			}
			fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY);
			state = 0;
			a=0;
			started = 0;
		}
		void AddCell(int x, int y){
			cell[size++] = new Point(x,y);
		}
		void deletecell()
		{
		    if(size==1)
              a=1;
            else
		    delete cell[--size];
		}
		void TurnUp(){
			if( dir!='s' )
			dir = 'w'; // w is control key for turning upward
		}
		void TurnDown(){
			if( dir!='w' )
			dir = 's'; // w is control key for turning downward
		}
		void TurnLeft(){
			if( dir!='d' )
			dir = 'a'; // w is control key for turning left
		}
		void TurnRight(){
			if( dir!='a' )
			dir = 'd'; // w is control key for turning right
		}
		void WelcomeScreen(){
			SetConsoleTextAttribute(console,14);
			cout<<"\n               /^\\/^\\                                             ";
			cout<<"\n              *_0__*0 **                                              ";
			cout<<"\n             **   **   **                                          ";
			cout<<"\n Hello Master***    *    *                                  ";
			cout<<"\n   ~~~~~~~~~~~~~~~~~*    *                *                     ";
			cout<<"\n                 **     *                  **                   ";
			cout<<"\n                   *     *                  ***               ";
			cout<<"\n                  *      *                    ****                 ";
			cout<<"\n                 *     *                       ****              ";
			cout<<"\n               *      *                         ** **            ";
			cout<<"\n              *     *                            **  **          ";
			cout<<"\n            *     *             *****             **   **        ";
			cout<<"\n           *     *           *-~      **           **   **          ";
			cout<<"\n          *      *         *    ****_    ***        **    **          ";
			cout<<"\n           *      **____**    _*~    ~-_    *******       **          ";
			cout<<"\n             ***           **~          ~-_       _     ***   - Mehedi Ayman -";
			cout<<"\n                 ***********-~                ~-****-~               ";
			cout<<"\n              M  I D  G  A  R D              S  E R P E N T       ";
		}
		int SelfCollision(){
			for(int i=1; i<size; i++)
				if( cell[0]->IsEqual(cell[i]) )
					return 1;
			return 0;
		}
		void Move(){
			// Clear screen
			system("cls");

			if( state == 0 ){
				if( !started ){
					WelcomeScreen();
					cout<<"\n\nPress any key to start";
					getch();
					started = 1;
					state = 1;
					score=0;
				}else{
					cout<<"\nGame Over";
					cout<<"\nPress any key to start";
					getch();
					state = 1;
					size = 1;
				}
			}

			// making snake body follow its head
			for(int i=size-1; i>0; i--){
				cell[i-1]->CopyPos(cell[i]);
			}

			// turning snake's head
			//because rest of body copies the path of head
			switch(dir){
				case 'w':
					cell[0]->MoveUp();
					break;
				case 's':
					cell[0]->MoveDown();
					break;
				case 'a':
					cell[0]->MoveLeft();
					break;
				case 'd':
					cell[0]->MoveRight();
					break;
			}

			if( SelfCollision() )
				state = 0;




			// Collision with fruit
			if( fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()){
				AddCell(0,0);
				fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY);
				score+=10;
			}
			//collision with poison
            if( p.GetX() == cell[0]->GetX() && p.GetY() == cell[0]->GetY()){
				deletecell();
				p.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY);
			}
			//drawing snake
			for(int i=0; i<size; i++)
				cell[i]->Draw();

			SetConsoleTextAttribute(console,242);
			if( !blink )
				fruit.Draw('#');
			blink = !blink;
            //poison generating
			if( !blink1 )
                p.Draw('$');
			blink1 = !blink1;
			SetConsoleTextAttribute(console,252);

			Sleep(n);
		}
		friend void record(snake,string);
};
void record(snake s,string name)
{
    //use of file management
    ofstream outf;
    outf.open("record.txt",ios::app);
    outf<<"\n"<<name<<"\t\tscore="<<s.score<<"\t\t";
    (n>75)?outf<<"level-1":((n==75)?outf<<"level-2":outf<<"level-3\n");
    outf.close();
    cout<<"\n\b SNAKE DIED\n";
    cout<<"score ="<<s.score<<endl;
}
void level(string name)
{
    cout<<"Welcome to Midgard Serpent"<<","<<name<<endl;
    cout<<"CHOOSE YOUR LEVEL\n\t\t01:EASY\n\t\t02:MEDIUM\n\t\t03:HARD\n";
    int x;
    cin>>x;
    if(x==3)
        n=5;
    else if(x==2)
        n=75;
    else if(x==1)
        n=100;


}
void endScreen(){
			SetConsoleTextAttribute(console,14);
			cout<<"\n               /^\\/^\\                                             ";
			cout<<"\n              *_X__*X **                                              ";
			cout<<"\nYOU LOSE!!   **   **   **                                          ";
			cout<<"\n      Master ***    *    *                                  ";
			cout<<"\n   ~~~~~~~~~~~~~~~~~*    *                *                     ";
			cout<<"\n                 **     *                  **                   ";
			cout<<"\n                   *     *                  ***               ";
			cout<<"\n                  *      *                    ****                 ";
			cout<<"\n                 *     *                       ****              ";
			cout<<"\n               *      *                         ** **            ";
			cout<<"\n              *     *                            **  **          ";
			cout<<"\n            *     *             *****             **   **        ";
			cout<<"\n           *     *           *-~      **           **   **          ";
			cout<<"\n          *      *         *    ****_    ***        **    **          ";
			cout<<"\n           *      **____**    _*~    ~-_    *******       **          ";
			cout<<"\n             ***           **~          ~-_       _     ***   - Mehedi Ayman -";
			cout<<"\n                ***********-~                ~-****-~               ";
			cout<<"\n              M  I D  G  A  R D              S  E R P E N T       ";
			exit(1);
		}
int main()
{
    string name;
    cout<<"ENTER YOUR NAME:\n";
    getline(cin,name);
    setcursor(0,0);

    srand( (unsigned)time(NULL));
	snake s;
	fruit f;
	poison p;
	 level(name);
	char op = 'l';
	do{
        p.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY);
        if(s.a)
          {
            record(s,name);
            endScreen();
          }
		if(kbhit()){
			op = getch();
		}
		switch(op){
			case 'w':
			case 'W':
				s.TurnUp();
				break;

			case 's':
			case 'S':
				s.TurnDown();
				break;

			case 'a':
			case 'A':
				s.TurnLeft();
				break;

			case 'd':
			case 'D':
				s.TurnRight();
				break;
		}
		s.Move();
	}while(op != 'e');
	return 0;

}


