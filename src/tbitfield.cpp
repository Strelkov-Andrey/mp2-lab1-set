// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{

	if (len >= 0)
	{
		int size = sizeof(int) * 8;
		BitLen = len;
		MemLen = (len + size - 1) / size;
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
	{
		throw logic_error("Negative len");
	}



}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	if (bf.BitLen >= 0)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	else
	{
		throw logic_error("Negative len");
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{

	int shift = 0, size = sizeof(int) * 8;
	while (size != 1)
	{
		size /= 2;
		shift++;
	}
	return n >> shift;


}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{

	return 1 << (n & (sizeof(int) * 8 - 1));


}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{

	return BitLen;

}

void TBitField::SetBit(const int n) // установить бит
{

	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
	{
		throw logic_error("Negative or Too large index");
	}


}

void TBitField::ClrBit(const int n) // очистить бит
{

	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
	{
		throw logic_error("Negative or Too large index");
	}


}

int TBitField::GetBit(const int n) const // получить значение бита
{

	if ((n > -1) && (n < BitLen))
	{
		if (pMem[GetMemIndex(n)] & GetMemMask(n))
			return 1;
		else
			return 0;

	}
	else
	{
		throw logic_error("Negative or Too large index");
	}


}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{

	if (this == &bf)
		return *this;

	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
		pMem[GetMemIndex(i)] = bf.pMem[i];

	return *this;


}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (this == &bf)
		return 1;
	if (BitLen != bf.BitLen)
		return 0;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				return 0;
			}
	return 1;


}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{

	int size = sizeof(int) * 8;
	if (BitLen != bf.BitLen)
		return 0;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				return 1;
			}
	return 0;


}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > BitLen)
		len = bf.BitLen;
	TBitField t(len);
	
	for (int i = 0; i < bf.MemLen; i++)
	{
		t.pMem[i] = pMem[i] | bf.pMem[i];
	}
	
	return t;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{


	int len = BitLen;
	if (bf.BitLen > BitLen)
		len = bf.BitLen;
	TBitField t(len);
	for (int i = 0; i < bf.MemLen; i++)
	{
		t.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return t;


}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField t(BitLen);
	for (int i = 0; i < MemLen - 1; i++)
	{
		t.pMem[i] = ~pMem[i];
	}
	int k = BitLen % (8 * sizeof(TELEM));
	int shift = sizeof(TELEM) * 8 * (MemLen - 1);
	for (int i = 0; i < k; i++)
	{
		if (GetBit(i + shift) == 1) t.ClrBit(i + shift);
		else t.SetBit(i + shift);
	}
	
	return t;


}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{

	int i, n = 0;
	while (1)
	{
		istr >> i;
		if (i == 1)
			bf.ClrBit(n);
		if (i == 0)
			bf.SetBit(n);
		else
			break;
		n++;
	}
	return istr;


}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{

	for (int i = 0; i < bf.GetLength(); i++)
	{
		ostr << bf.pMem[i];
	}
	return ostr;
}
