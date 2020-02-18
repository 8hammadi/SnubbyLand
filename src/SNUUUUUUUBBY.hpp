#include <string>
#include <utility>
#include <vector>
#include <SDL2/SDL.h>
#include <thread>

#define SNUBBY_STEP 3
#define SNUBBY_SIZE 15
#define SQUARE_SIZE 20

#define RESTRICTED '#'
#define ALLOWED '.'
#define RETURN '/'

using namespace std;

///////////////////////////////////////////////////////////////////////// Extra Class

class Keys
{
public:
	SDL_Keycode up, left, right, down;
	bool upActivated, leftActivated, rightActivated, downActivated;
	Keys(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right);
};

Keys::Keys(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right)
{
	this->up = up;
	this->left = left;
	this->right = right;
	this->down = down;
	upActivated = false;
	downActivated = false;
	leftActivated = false;
	rightActivated = false;
}

class Snubby
{

public:
	Snubby(vector<vector<char>> const *maps, int x, int y, int keys);	//done
	~Snubby();	//done
	pair<int, int> getPosition();	//done
	string getIcon();		//done
	void setUp(bool b);		//done
	void setDown(bool b);	//done
	void setLeft(bool b);	//done
	void setRight(bool b);	//done
	SDL_Keycode getUp();	//done
	SDL_Keycode getDown();	//done
	SDL_Keycode getLeft();	//done
	SDL_Keycode getRight();	//done

private :
	pair<int, int> position;
	thread *moveThread;
	string icon;
	Keys *keys;
	vector<vector<char>> const *maps;

	void moveSnubby();	//done
	int moveUp();		//done
	int moveDown();		//done
	int moveLeft();		//done
	int moveRight();	//done
	int changePosition(int x, int y);	//done

};
///////////////////////////////////////////////////////////////////////// Constructor & Destructor
Snubby::~Snubby()
{
	delete moveThread;
	delete keys;
}
Snubby::Snubby(vector<vector<char>> const *maps, int x, int y, int keys)
{
	if(!maps)
		throw invalid_argument("Invalid MAP pointer!");
	this -> maps = maps;
	switch(keys)
	{
	case 0:
		this->keys = new Keys(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);
		break;
	case 1:
		this->keys = new Keys(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
		break;
	default:
		throw invalid_argument("Invalid KEYS value!");
		break;
	}
	position = make_pair(x, y);
	moveThread = new thread(&Snubby::moveSnubby);
}

///////////////////////////////////////////////////////////////////////// Functions
//////					Thread
void Snubby::moveSnubby()
{
	while(1)
	{
		if(this->keys->upActivated)
			this->moveUp();
		if(this->keys->downActivated)
			this->moveDown();
		if(this->keys->leftActivated)
			this->moveLeft();
		if(this->keys->rightActivated)
			this->moveRight();
		SDL_Delay(1000 / 60);
	}

}
int Snubby::moveUp()
{
	return changePosition(get<0>(position), get<1>(position) - SNUBBY_STEP);
}
int Snubby::moveDown()
{
	return changePosition(get<0>(position), get<1>(position) + SNUBBY_STEP);
}
int Snubby::moveLeft()
{
	return changePosition(get<0>(position) - SNUBBY_STEP, get<1>(position));
}
int Snubby::moveRight()
{
	return changePosition(get<0>(position) + SNUBBY_STEP, get<1>(position));
}

int Snubby::changePosition(int x, int y)
{
	vector<vector<char>> map = maps[0];
	int w = map[0].size(), h = map.size();
	int squareSize = SQUARE_SIZE;
	//printf("---------------------- %i : %i\n",x,y );

	//Snubby Out Of Range
	if(x <= 0 || x + SNUBBY_SIZE >= map[0].size() * squareSize)
		return -1;
	if(y <= 0 || y + SNUBBY_SIZE >= map.size() * squareSize)
		return -1;

	//Check if at least one snubby's corner is in the restricted zone!left-top,right-bot,rigth-top,left_bot & middle of each segment
	if(map[y / squareSize][x / squareSize] == RESTRICTED ||
			map[(SNUBBY_SIZE + y) / squareSize][(SNUBBY_SIZE + x ) / squareSize] == RESTRICTED ||
			map[ y / squareSize][(SNUBBY_SIZE + x ) / squareSize] == RESTRICTED ||
			map[(SNUBBY_SIZE + y) / squareSize][x / squareSize] == RESTRICTED ||

			map[(2 * y + SNUBBY_SIZE) / 2 / squareSize][x / squareSize] == RESTRICTED ||
			map[(SNUBBY_SIZE + y) / squareSize][(SNUBBY_SIZE + 2 * x ) / 2 / squareSize] == RESTRICTED ||
			map[ y / squareSize][(SNUBBY_SIZE + 2 * x ) / 2 / squareSize] == RESTRICTED ||
			map[(SNUBBY_SIZE + 2 * y) / 2 / squareSize][(x + SNUBBY_SIZE) / squareSize] == RESTRICTED
	  )
	{
		//If STEP is too large and gets to RESTRICTED zone! change "STEP" to fit the available area
		int diff = 1;   //Difference between current pos and frontier

		// If Move Left
		if(get<0>(position) > x )
		{
			while(get<0>(position) - diff >= 0
					&& map[y / squareSize][(get<0>(position) - diff) / squareSize] != RESTRICTED
					&& map[(y + SNUBBY_SIZE) / squareSize][(get<0>(position) - diff) / squareSize] != RESTRICTED
					&& map[(y + SNUBBY_SIZE / 2) / squareSize][(get<0>(position) - diff) / squareSize] != RESTRICTED)
				diff++;
			return changePosition(get<0>(position) - diff + 1, y);

		}// If Move Right
		else if(get<0>(position) < x )
		{
			while(get<0>(position) + diff + SNUBBY_SIZE < w * squareSize
					&& map[y / squareSize][(get<0>(position) + diff + SNUBBY_SIZE) / squareSize] != RESTRICTED
					&& map[(y + SNUBBY_SIZE) / squareSize][(get<0>(position) + diff + SNUBBY_SIZE) / squareSize] != RESTRICTED
					&& map[(y + SNUBBY_SIZE  / 2) / squareSize][(get<0>(position) + diff + SNUBBY_SIZE) / squareSize] != RESTRICTED)
				diff++;
			return changePosition(get<0>(position) + diff - 1, y);

		}// If Move Down
		else if(get<1>(position) < y )
		{
			while( get<1>(position) + diff + SNUBBY_SIZE < h * squareSize
					&& map[(get<1>(position) + diff + SNUBBY_SIZE) / squareSize][x / squareSize] != RESTRICTED
					&& map[(get<1>(position) + diff + SNUBBY_SIZE) / squareSize][(x + SNUBBY_SIZE) / squareSize] != RESTRICTED
					&& map[(get<1>(position) + diff + SNUBBY_SIZE) / squareSize][(x + SNUBBY_SIZE  / 2 ) / squareSize] != RESTRICTED)
				diff++;
			return changePosition(x, get<1>(position) + diff - 1);
		}// If Move Up
		else if(get<1>(position) > y )
		{
			while( get<1>(position) - diff >= 0
					&& map[(get<1>(position) - diff) / squareSize][x / squareSize] != RESTRICTED
					&& map[(get<1>(position) - diff) / squareSize][(x + SNUBBY_SIZE) / squareSize] != RESTRICTED
					&& map[(get<1>(position) - diff) / squareSize][(x + SNUBBY_SIZE  / 2 ) / squareSize] != RESTRICTED)
				diff++;
			return changePosition(x, get<1>(position) - diff + 1);
		}
		else return -1;

	}
	// new Position is legitimate
	get<0>(position) = x;
	get<1>(position) = y;

	//Check if all snubby's corners are all in the return zone!left-top,right-bot,rigth-top,left_bot
	if(map[y / squareSize][x / squareSize] == RETURN &&
			map[(SNUBBY_SIZE + y) / squareSize][(SNUBBY_SIZE + x ) / squareSize] == RETURN &&
			map[ y / squareSize][(SNUBBY_SIZE + x ) / squareSize] == RETURN &&
			map[(SNUBBY_SIZE + y) / squareSize][x / squareSize] == RETURN
	  )
	{
		//TODO: Many Position for the same RETURN Zone!!!!
		;
	}
	else
	{
		;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////// Setters

void Snubby::setUp(bool b)
{
	keys->upActivated = b;
}
void Snubby::setDown(bool b)
{
	keys->downActivated = b;
}
void Snubby::setLeft(bool b)
{
	keys->leftActivated = b;
}
void Snubby::setRight(bool b)
{
	keys->rightActivated = b;
}

///////////////////////////////////////////////////////////////////////// Getters

SDL_Keycode Snubby::getUp()
{
	return keys->up;
}
SDL_Keycode Snubby::getDown()
{
	return keys->down;
}
SDL_Keycode Snubby::getLeft()
{
	return keys->left;
}
SDL_Keycode Snubby::getRight()
{
	return keys->right;
}
string Snubby::getIcon()
{
	return icon;
}

pair<int, int> Snubby::getPosition()
{
	return position;
}
