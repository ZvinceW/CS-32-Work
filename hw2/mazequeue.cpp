#include <queue>
#include <iostream>
#include <string>

using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
	queue<Coord> coordQueue;
	Coord start(sr, sc);
	Coord end(er, ec);
	coordQueue.push(start);
	maze[sr][sc] = '0';
	while (!coordQueue.empty())
	{
		Coord current = coordQueue.front(); //save the current coord

		//cout << current.r() << ", " << current.c() << endl; //debugging

		coordQueue.pop();       //pop the current coord
		maze[current.r()][current.c()] = '0';      //make current location as visited
		if (current.r() == er && current.c() == ec)   // the current location is the end location
		{
			return true;
		}
		if (maze[current.r() - 1][current.c()] == '.') //moving NORTH
		{
			Coord new1(current.r() - 1, current.c());
			coordQueue.push(new1);
			maze[current.r() - 1][current.c()] = '0';
		}
		if (maze[current.r()][current.c() + 1] == '.') //moving EAST
		{
			Coord new1(current.r(), current.c() + 1);
			coordQueue.push(new1);
			maze[current.r()][current.c() + 1] = '0';
		}
		if (maze[current.r() + 1][current.c()] == '.') //moving SOUTH
		{
			Coord new1(current.r() + 1, current.c());
			coordQueue.push(new1);
			maze[current.r() + 1][current.c()] = '0';
		}
		if (maze[current.r()][current.c() - 1] == '.') //moving WEST
		{
			Coord new1(current.r(), current.c() - 1);
			coordQueue.push(new1);
			maze[current.r()][current.c() - 1] = '0';
		}
	}
	return false;  //return false if the path never reached end point
}

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X........X",
		"XX.X.XXXXX",
		"X..X.X...X",
		"X..X...X.X",
		"XXXX.XXX.X",
		"X.X....XXX",
		"X..XX.XX.X",
		"X...X....X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 6, 4, 1, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}