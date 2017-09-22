#include <iostream>
#include "History.h"

using namespace std;

//History implementation

History::History(int nRows, int nCols) {
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			m_gridHist[i][j] = '.';
		}
	}
	m_row = nRows;
	m_col = nCols;
}

bool History::record(int r, int c)
{
	if (r > m_row || c > m_col) {
		return false;
	}
	if (m_gridHist[r - 1][c - 1] == '.') {
		m_gridHist[r - 1][c - 1] = 'A';
	}
	else if (m_gridHist[r - 1][c - 1] >= 'A' && m_gridHist[r][c] <= 'Z') {
		m_gridHist[r - 1][c - 1]++;
	}
	else {
		m_gridHist[r - 1][c - 1] = 'Z';
	}
	return true;
}

void History::display() const
{
	//something to do with clearScreen() ???
	clearScreen();
	for (int r = 0; r < m_row; r++)
	{
		for (int c = 0; c < m_col; c++)
			cout << m_gridHist[r][c];
		cout << endl;
	}
	cout << endl;
}
