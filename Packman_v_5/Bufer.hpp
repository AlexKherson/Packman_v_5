#ifndef BUFER_H
#define BUFER_H

template<typename T> 
class Bufer
{
public:
	Bufer(const int sizeX,const int sizeY);
	~Bufer();

	void setBufer(const int x, const int y, const T value);
	
	void clear();

	T getElement(const int x, const int posy) const;
private:
	
	void initBufer(char **tmp);
	void initBufer(int **tmp);
private:
	int sizeX;
	int sizeY;

	
	T **bufer;
};

#endif


template<typename T>
Bufer<T>::Bufer(const int sizeX, const int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	bufer = new T *[sizeX];
	for (int i = 0; i < sizeX; i++)
		bufer[i] = new T[sizeY];

	initBufer(bufer);
}

template<typename T>
Bufer<T>::~Bufer()
{
	for (int i = 0; i < sizeX; i++)
		delete[] bufer[i];
	delete[]bufer;
}

template<typename T>
void Bufer<T>::setBufer(const int x, const int y, const T value)
{
	bufer[x][y] = value;
}


template<typename T>
void Bufer<T>::clear()
{
	initBufer(bufer);
}

template<typename T>
T Bufer<T>::getElement(const int x, const int y) const
{
	return bufer[x][y];
}

template<typename T>
void Bufer<T>::initBufer(char ** tmp)
{
	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++)
			tmp[i][j] = '0';
			
}

template<typename T>
void Bufer<T>::initBufer(int ** tmp)
{
	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++)
			tmp[i][j] = 0;

		
}
