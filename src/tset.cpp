// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"



TSet::TSet(int mp) : BitField(mp), MaxPower(mp)

{
}

// конструктор копирования

TSet::TSet(const TSet& s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;

}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength())
{}


TSet::operator TBitField()
{

	this->BitField;
	return *this;

}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{

	return MaxPower;


}

int TSet::IsMember(const int Elem) const // элемент множества?
{

	return BitField.GetBit(Elem);

}

void TSet::InsElem(const int Elem) // включение элемента множества
{

	BitField.SetBit(Elem);

}

void TSet::DelElem(const int Elem) // исключение элемента множества
{


	BitField.ClrBit(Elem);


}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;


}

int TSet::operator==(const TSet& s) const // сравнение
{
	if (MaxPower != s.MaxPower)
	{
		throw logic_error ("Different MaxPower");
	}
	else
	{
		if (BitField == s.BitField)
			return 1;
		else
			return 0;

	}
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	if (MaxPower != s.MaxPower)
	{
		throw logic_error("Different MaxPower");
	}
	else 
	{
		if (BitField != s.BitField)
			return 0;
		else
			return 1;
	}
}

TSet TSet::operator+(const TSet& s) // объединение
{


	return BitField | s.BitField;



}

TSet TSet::operator+(const int Elem) // объединение с элементом
{


	BitField.SetBit(Elem);
	return BitField;


}

TSet TSet::operator-(const int Elem) // разность с элементом
{

	BitField.ClrBit(Elem);
	return BitField;
}


TSet TSet::operator*(const TSet& s) // пересечение
{
	return BitField & s.BitField;


}



TSet TSet::operator~(void) // дополнение
{

	return ~BitField;
}


// перегрузка ввода/вывода
istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i = 0, n;
	char c;
	istr >> c;
	while (c != '}')
	{
		istr >> n >> c;
		s.BitField.GetBit(n);
	}
	return istr;
}
ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "{ ";
	for (int i = 0; i < s.MaxPower; i++)
	{
		if (s.BitField.GetBit(i))
			ostr << i << " ";
	}
	ostr << " } ";
	return ostr;
}
// перегрузка ввода/вывода
TSet TSet::create_fib(int mp)
{
	TSet fib(mp);
	int prevElem = 1;
	int curElem = 1;
	int nxtElem;
	for (int i = 0; i < mp; i++)
	{
		nxtElem = curElem + prevElem;
		prevElem = curElem;
		curElem = nxtElem;
		if ((nxtElem % 2) == 0) fib.InsElem(nxtElem);
	}
	return fib;
}

void TSet::WriteFile(TSet& bf)
{
	ofstream fout;
	fout.open("");
	fout << bf;
	fout.close();
}
void TSet::ReadFile(TSet& bf)
{
	ifstream fin;
	fin >> bf;
	fin.close();
}