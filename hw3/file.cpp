#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here

class File
{
public:
	File(string name)
	{
		m_name = name;
	}
	string name() const  //return name string
	{
		return m_name;
	}
	virtual void redisplay() const
	{
		cout << "refresh the screen";
	}
	virtual void open() const = 0; //prints the open message
	virtual ~File() //prints the deleting message
	{
		return;
	}

private:
	string m_name;
};

class TextMsg : public File
{
public:
	TextMsg(string name) :
		File(name)
	{

	}
	virtual void open() const
	{
		cout << "open test message";
	}
	virtual ~TextMsg()
	{
		cout << "Destroying " << name() << ", a text message" << endl;
	}
};

class Picture : public File
{
public:
	Picture(string name) :
		File(name)
	{

	}
	virtual void open() const
	{
		cout << "show picture";
	}
	virtual ~Picture()
	{
		cout << "Destroying the picture " << name() << endl;
	}
};

class Video : public File
{
public:
	Video(string name, int length):
		File(name)
	{
		m_length = length;
	}
	virtual void open() const
	{
		cout << "play " << m_length << " second video";
	}
	virtual void redisplay() const
	{
		cout << "replay video";
	}
	virtual ~Video()
	{
		cout << "Destroying " << name() << ", a video" << endl;
	}
private:
	int m_length;
};

void openAndRedisplay(const File* f)
{
	cout << f->name() << ": ";
	f->open();
	cout << endl << "Redisplay: ";
	f->redisplay();
	cout << endl;
}

int main()
{
	File* files[4];
	files[0] = new TextMsg("fromFred.txt");
	// Videos have a name and running time
	files[1] = new Video("goblin.mpg", 3780);
	files[2] = new Picture("kitten.jpg");
	files[3] = new Picture("baby.jpg");

	for (int k = 0; k < 4; k++)
		openAndRedisplay(files[k]);

	// Clean up the files before exiting
	cout << "Cleaning up." << endl;
	for (int k = 0; k < 4; k++)
		delete files[k];
}
