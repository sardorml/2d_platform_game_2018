#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#define MAX_NUMBER_OF_ITEMS 3

#include <sstream>

using namespace sf;


float offsetX=0, offsetY=0;
float score = 0;

const int H = 17;
const int W = 150;


String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                    0",
"0                   p                                                                                                                                0",
"0                 iiii                                                                                                                               0",
"0                                                                                                                                                    0",
"0                                                                                                                                                    0",
"0          1e                                                                                                                                        0",
"0         iii                                                                                                                                        0",
"0                                  d                                                                                                                 0",
"0  d              e                                                                                                                                  0",
"0                ii                 c                                                                                                                0",
"0   c                               c                                                                                                                0",
"0   b           1 2 3 4 5 6 7 8 9 * b       f  hh   gh      e    jj   e        g            f          gg         ge              gg                 0",
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo",
"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo",
};


class Menu{
private:
    int selectedItemIndex;
    Font font;
    Text menu[MAX_NUMBER_OF_ITEMS];
public:
    Menu(float width, float height){
        if(!font.loadFromFile("sansation.ttf")){
            // handle
        }
        menu[0].setFont(font);
        menu[0].setColor(Color::Red);
        menu[0].setString("Play");
        menu[0].setPosition(Vector2f(width/2,height/(MAX_NUMBER_OF_ITEMS+1)*1));

        menu[1].setFont(font);
        menu[1].setColor(Color::White);
        menu[1].setString("Options");
        menu[1].setPosition(Vector2f(width/2,height/(MAX_NUMBER_OF_ITEMS+1)*2));

        menu[2].setFont(font);
        menu[2].setColor(Color::White);
        menu[2].setString("Quit");
        menu[2].setPosition(Vector2f(width/2,height/(MAX_NUMBER_OF_ITEMS+1)*3));

    }
    void draw(RenderWindow &window){
        for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
            window.draw(menu[i]);
        }
    }
    void MoveUp(){

    }
    void moveDown(){

    }
};


class PLAYER {

public:

float dx,dy;
FloatRect rect;
bool onGround;
Sprite sprite;
float currentFrame;

    PLAYER(Texture &image)
   {
	sprite.setTexture(image);
	rect = FloatRect(100,180,16,19);

	dx=dy=0.1;
	currentFrame = 0;
   }


   void update(float time)
   {

	 rect.left += dx * time;
     Collision(0);


	 if (!onGround) dy=dy+0.0005*time;
	 rect.top += dy*time;
	 onGround=false;
     Collision(1);


     currentFrame += time * 0.005;
     if (currentFrame > 4) currentFrame -= 4;


    if (dx>0) sprite.setTextureRect(IntRect(16*int(currentFrame),52,16,19));
	if (dx<0) sprite.setTextureRect(IntRect(16*int(currentFrame)+16,52,-16,19));


	 sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	 dx=0;
   }


   void Collision(int num)
{

	for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			 {
				 if ((TileMap[i][j]=='a') || (TileMap[i][j]=='i') || (TileMap[i][j]=='0') || (TileMap[i][j]=='r') || (TileMap[i][j]=='t'))
				                         {
												   if (dy>0 && num==1)
												   { rect.top =   i*16 -  rect.height;  dy=0;   onGround=true; }
											       if (dy<0 && num==1)
												   { rect.top = i*16 + 16;   dy=0;}
												   if (dx>0 && num==0)
												   { rect.left =  j*16 -  rect.width; }
											       if (dx<0 && num==0)
												   { rect.left =  j*16 +16;}
										 }

				 switch(TileMap[i][j]){
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case '*':
                        TileMap[i][j] = ' ';
                        score++;

				 }
			 }

}

};



class ENEMY
{

public:
float dx,dy;
FloatRect rect;
Sprite sprite;
float currentFrame;
bool life;


   void set(Texture &image, int x, int y)
   {
	sprite.setTexture(image);
	rect = FloatRect(x,y,16,16);

    dx=0.05;
	currentFrame = 0;
	life=true;
   }

   void update(float time)
   {
	 rect.left += dx * time;

     Collision();


     currentFrame += time * 0.005;
     if (currentFrame > 2) currentFrame -= 2;

    sprite.setTextureRect(IntRect(16*int(currentFrame),   0, 16,16));
    if (!life) sprite.setTextureRect(IntRect(0, 0, 16,16));


	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

   }


   void Collision()
  {

	for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			 if ((TileMap[i][j]=='P') || (TileMap[i][j]=='0'))
			                           {
                                                    if (dx>0)
												   { rect.left =  j*16 - rect.width; dx*=-1; }
											        else if (dx<0)
												   { rect.left =  j*16 + 16;  dx*=-1; }

										}
  }

};



int main()
{

    RenderWindow window(VideoMode(1200, 750), "SFML works!",Style::Fullscreen);
    Vector2u wSize = window.getSize();
    int newH = (400*wSize.y)/wSize.x;
    int displace = (newH - 250)/(-2);
    window.setView(View(FloatRect(0,displace,450,newH)));

    // Menu

    Menu menu(window.getSize().x,window.getSize().y);

	Texture tileSet;
	tileSet.loadFromFile("tileset.png");

	Texture foodTileSet;
	foodTileSet.loadFromFile("food.png");

	Texture tt;
	tt.loadFromFile("player.png");

	//Text
	Font font;
	font.loadFromFile("sansation.ttf");

	Text mytext("Hello!",font,25);

	mytext.setColor(Color(0,0,0));
	mytext.setPosition(10,10);


	PLAYER p(tt);
	ENEMY  enemy;
	enemy.set(foodTileSet,48*16,13*16);


	Sprite tile(tileSet);
	Sprite foodTile(foodTileSet);

	SoundBuffer buffer;
	buffer.loadFromFile("Jump.ogg");
	Sound sound(buffer);

    Music music;
    music.openFromFile("pickle_rick.ogg");
    music.play();

	Clock clock;

	//window.setSize(Vector2u(1600, 1000));
	//window.setPosition(Vector2i(0, 0));


    window.clear(Color(107,140,255));
    menu.draw(window);
    while (window.isOpen())
    {

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;

		if (time > 20) time = 20;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Left))    p.dx=-0.1;

	    if (Keyboard::isKeyPressed(Keyboard::Right))    p.dx=0.1;

	    if (Keyboard::isKeyPressed(Keyboard::Up))	if (p.onGround) { p.dy=-0.27; p.onGround=false;  sound.play();}

	    if (Keyboard::isKeyPressed(Keyboard::A))    p.dx=-0.1;

	    if (Keyboard::isKeyPressed(Keyboard::D))    p.dx=0.1;

	    if (Keyboard::isKeyPressed(Keyboard::W))	if (p.onGround) { p.dy=-0.27; p.onGround=false;  sound.play();}



		 p.update(time);
		 enemy.update(time);


		 if  (p.rect.intersects( enemy.rect ) )
		 {
			 if (enemy.life) {
			 if (p.dy>0) { enemy.dx=0; p.dy=-0.2; enemy.life=false;}
			 else {p.sprite.setColor(Color::Red); window.close();}
			 }
		 }


		 if (p.rect.left>200) offsetX = p.rect.left-200;




		 window.clear(Color(107,140,255));

		 for (int i=0; i<H; i++)
			 for (int j=0; j<W; j++)
			  {
				if (TileMap[i][j]=='a')  tile.setTextureRect( IntRect(16,16,16,16) );
				if (TileMap[i][j]=='b')  tile.setTextureRect( IntRect(16,128,16,16) );
				if (TileMap[i][j]=='c')  tile.setTextureRect( IntRect(32,128,16,16) );
				if (TileMap[i][j]=='d')  tile.setTextureRect( IntRect(0,144,48,32) );
				if (TileMap[i][j]=='i')  tile.setTextureRect( IntRect(0,0,16,16) );
				if (TileMap[i][j]=='e')  tile.setTextureRect( IntRect(0,128,16,16) );
				if (TileMap[i][j]=='f')  tile.setTextureRect( IntRect(64,112,16,16) );
				if (TileMap[i][j]=='g')  tile.setTextureRect( IntRect(48,144,16,16) );
				if (TileMap[i][j]=='h')  tile.setTextureRect( IntRect(48,128,16,16) );
				if (TileMap[i][j]=='j')  tile.setTextureRect( IntRect(48,160,16,16) );
				if (TileMap[i][j]=='o')  tile.setTextureRect( IntRect(5,23,16,16) );

                // Clear
				if ((TileMap[i][j]==' ') || (TileMap[i][j]=='0')) continue;

		        switch(TileMap[i][j]){
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'i':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'j':
                case 'o':
                    tile.setPosition(j*16-offsetX,i*16 - offsetY) ;
                    window.draw(tile);
                    break;

		        }

		        //food
                if (TileMap[i][j]=='1')foodTile.setTextureRect( IntRect(0,0,16,16) ); // bread
                if (TileMap[i][j]=='2')foodTile.setTextureRect( IntRect(0,32,16,16) ); // egg
                if (TileMap[i][j]=='3')foodTile.setTextureRect( IntRect(0,64,16,16) ); // apple
                if (TileMap[i][j]=='4')foodTile.setTextureRect( IntRect(16,64,16,16) ); //strawberry
                if (TileMap[i][j]=='5')foodTile.setTextureRect( IntRect(32,64,16,16) ); //peach
                if (TileMap[i][j]=='6')foodTile.setTextureRect( IntRect(48,64,16,16) ); //avacado
                if (TileMap[i][j]=='7')foodTile.setTextureRect( IntRect(16,48,16,16) ); //meat
                if (TileMap[i][j]=='8')foodTile.setTextureRect( IntRect(48,48,16,16) ); //baklajan
                if (TileMap[i][j]=='9')foodTile.setTextureRect( IntRect(64,48,16,16) ); //chili
                if (TileMap[i][j]=='*')foodTile.setTextureRect( IntRect(112,16,16,16) ); //chili

                switch(TileMap[i][j]){
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '*':
                        foodTile.setPosition(j*16-offsetX,i*16 - offsetY) ;
                        window.draw(foodTile);
                        break;
                }
		     }

        std::ostringstream ss;    // score text
        ss<< score;
        mytext.setString( "Score: " + ss.str() );
        window.draw(mytext);


		window.draw(p.sprite);
	    window.draw(enemy.sprite);

		window.display();
    }

    return 0;
}



