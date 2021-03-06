#include "ScoreList.h"



ScoreList::ScoreList()
{
	
}

bool ScoreList::add(unsigned long score)
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.
{
	if (score > 100 || m_seq.size() == DEFAULT_MAX_ITEMS) {
		return false;
	}
	else {
		m_seq.insert(score);
		return true;
	}
}

bool ScoreList::remove(unsigned long score)
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
{
	int result = m_seq.find(score);
	if (result == -1) {
		return false;
	}
	else {
		m_seq.erase(result);
		return true;
	}
}

int ScoreList::size() const  // Return the number of scores in the list.
{
	return m_seq.size();
}

unsigned long ScoreList::minimum() const
// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.
{
	if (m_seq.size() == 0) {
		return NO_SCORE;
	}
	else {
		unsigned long result;
		m_seq.get(0, result);
		return result;
	}
}

unsigned long ScoreList::maximum() const
// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
{
	if (m_seq.size() == 0) {
		return NO_SCORE;
	}
	else {
		unsigned long result;
		m_seq.get(m_seq.size() - 1, result);
		return result;
	}
}
