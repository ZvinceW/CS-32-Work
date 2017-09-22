#include <stack>
#include <string>
#include <iostream>

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
	Coord start(sr, sc);
	Coord end(er, ec);
	maze[sr][sc] = '0';
	Coord current = start;
	maze[current.r()][current.c()] = '0';      //make current location as visited
	if (current.r() == er && current.c() == ec)   // the current location is the end location
	{
		return true;
	}
	if (maze[current.r() - 1][current.c()] == '.') //moving NORTH
	{
		if (pathExists(maze, nRows, nCols, current.r() - 1, current.c(), er, ec))
		{
			return true;
		}
	}
	if (maze[current.r()][current.c() + 1] == '.') //moving EAST
	{
		if (pathExists(maze, nRows, nCols, current.r(), current.c() + 1, er, ec))
		{
			return true;
		}
	}
	if (maze[current.r() + 1][current.c()] == '.') //moving SOUTH
	{
		if (pathExists(maze, nRows, nCols, current.r() + 1, current.c(), er, ec))
		{
			return true;
		}
	}
	if (maze[current.r()][current.c() - 1] == '.') //moving WEST
	{
		if (pathExists(maze, nRows, nCols, current.r(), current.c() - 1, er, ec))
		{
			return true;
		}
	}
	return false;
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
