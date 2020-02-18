#define COIN_ICON "./images/coin.png"
#define COIN_SIZE 10

#include <utility>

using namespace std;

class Coin
{
public:
	Coin(int x, int y);
	pair<int, int> getPostion();
	bool isTaken();
	void take();

private:
	pair<int, int> position;
	bool taken;

};

Coin::Coin(int x, int y)
{
	position = make_pair(x, y);
	taken = false;
}

pair<int, int> Coin::getPostion()
{
	return position;
}
bool Coin::isTaken()
{
	return taken;
}
void Coin::take()
{
	taken = true;
}