#ifndef LEVEL
/////////////////////////////////////////////////////////////////////////// Constants
#define LEVEL 1
#define BORDER 3

#define RESTRICTED 0
#define ALLOWED 1
#define RETURN 2

static const int MAP_HEIGHT = 20;
static const int MAP_WIDTH = 20;
static const int SQUARE_SIZE = 30;

static const int RESTRICTED_COLOR[3] = {155, 160, 255};
static const int ALLOWED_COLOR[3] = {155, 160, 180};
static const int RETURN_COLOR[3] = {100, 100, 190};
static const int BORDER_COLOR[3] = {0, 0, 0};

static const int BLUEE_COLOR[3] = {155, 160, 255};
static const int BLUE_COLOR[3] = {155, 160, 180};
static const int GREEN_COLOR[3] = {155, 255, 180};

/////////////////////////////////////////////////////////////////////////// Preprocessors
#include <string>
#include <vector>
#include <utility>
#include <png++/png.hpp>
#include <png++/rgb_pixel.hpp>

using namespace png;
using namespace std;

/////////////////////////////////////////////////////////////////////////// Prototypes
int writeImage(string filename, vector<vector<char>> buffer);     //-1: Error, 0: Sucess
int deleteImage(char* filename);                    //0: Success

/////////////////////////////////////////////////////////////////////////// Functions

int main(){
	vector<vector<char>> v{{RESTRICTED,RESTRICTED,RESTRICTED},{RESTRICTED,ALLOWED,RESTRICTED},
	{RESTRICTED,RESTRICTED,RESTRICTED}};
	writeImage("Test.png",v);
	return 0;
}
int deleteImage(char* filename)
{
	return remove(filename);
}

int writeImage(string filename, vector<vector<char>> buffer)
{
	int unit = SQUARE_SIZE;
	image< rgb_pixel > image(unit * buffer[0].size(), unit * buffer.size());
	int i;
	for (int y = 0; y < image.get_height(); ++y)
	{
		i = 0;
		for (int x = 0; x < image.get_width(); ++x)
		{


			if(buffer[y / unit][x / unit] == RETURN)
				image[y][x] = rgb_pixel(GREEN_COLOR[0], GREEN_COLOR[1], GREEN_COLOR[2]);
			else if(buffer[y / unit][x / unit] == RESTRICTED)
			{
				i = 0;
				if((x + BORDER < image.get_width() && buffer[y / unit][(x + BORDER) / unit] == ALLOWED) ||
						(x - BORDER >= 0 && buffer[y / unit][(x - BORDER) / unit] == ALLOWED) ||
						(y - BORDER >= 0 && buffer[(y - BORDER) / unit][x / unit] == ALLOWED) ||
						(y + BORDER < image.get_height() && buffer[(y + BORDER) / unit][x / unit] == ALLOWED) ||

						(y + BORDER < image.get_height() && x + BORDER < image.get_width() && buffer[(y + BORDER) / unit][(x + BORDER) / unit] == ALLOWED) ||
						(y + BORDER < image.get_height() && x - BORDER >= 0 && buffer[(y + BORDER) / unit][(x - BORDER) / unit] == ALLOWED ) ||
						(y - BORDER >= 0 && x + BORDER < image.get_width() && buffer[(y - BORDER) / unit][(x + BORDER) / unit] == ALLOWED ) ||
						(y - BORDER >= 0 && x - BORDER >= 0 && buffer[(y - BORDER) / unit][(x - BORDER) / unit] == ALLOWED )
				  )
					image[y][x] = rgb_pixel(BORDER_COLOR[0], BORDER_COLOR[1], BORDER_COLOR[2]);
				else
					image[y][x] = rgb_pixel(RESTRICTED_COLOR[0], RESTRICTED_COLOR[1], RESTRICTED_COLOR[2]);

			}
			else if(buffer[y / unit][x / unit] == ALLOWED)
			{
				if(y % unit > unit / 2 )
				{
					if (i == unit)
						i = 0;
					if(i < unit / 2)
						image[y][x] = rgb_pixel(BLUE_COLOR[0], BLUE_COLOR[1], BLUE_COLOR[2]);

					else if(i < unit)
						image[y][x] = rgb_pixel(BLUEE_COLOR[0], BLUEE_COLOR[1], BLUEE_COLOR[2]);

					i++;
				}
				else
				{
					if (i == 0)
						i = unit;
					if(i <= unit / 2)
						image[y][x] = rgb_pixel(BLUE_COLOR[0], BLUE_COLOR[1], BLUE_COLOR[2]);
					else if(i <= unit)
						image[y][x] = rgb_pixel(BLUEE_COLOR[0], BLUEE_COLOR[1], BLUEE_COLOR[2]);
					i--;
				}

			}
		}
	}
	image.write(filename);



	return 0;
}



#endif