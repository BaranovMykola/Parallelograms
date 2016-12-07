#pragma once
#include <exception>
#include <fstream>
#include <algorithm>
#include "Lego.h"
#include <memory>

enum PICE{LEFT, TOP, RIGHT, BOTTOM};
const int sides = 4;

using namespace std;

class Parallelogram
{
public:
	Parallelogram();
	Parallelogram(Lego, Lego, Lego, Lego);
	Parallelogram(const Parallelogram&);
	explicit Parallelogram(bool);
	~Parallelogram()=default;
	unsigned short getPredominantColor()const;
	void getState()const;
	void tryMonohrome();
	friend ostream& operator<<(ostream&, const Parallelogram&);
	friend istream& operator>>(istream&, Parallelogram&);
	Parallelogram& operator=(const Parallelogram&);
	bool getType()const;
	Lego getPiece(unsigned short)const;
	unsigned int getResistibility()const;

private:
	Lego piece[4];
	class BaseState;
	unsigned int resistibility;
	friend class BaseState;
	class BaseState
	{
	public:
		virtual ~BaseState() = default;
		virtual void printState(ostream&)const = 0;
		virtual void getMonochrome(Parallelogram&)const = 0;
		virtual bool isMonochrome()const = 0;
	};
	class Monochrome : public BaseState
	{
	public:
		void printState(ostream& stream)const
		{
			stream << "Monochorme parallelogram";
		}
		void getMonochrome(Parallelogram&)const
		{
            throw "Sharpe is already monochrome";
		}
		bool isMonochrome()const
		{
			return true;
		}
	};
	class Random : public BaseState
	{
	public:
		void printState(ostream& stream)const
		{
			stream << "Random parallelogram";
		}
		void getMonochrome(Parallelogram& _object)const
		{
			if (_object.isMonochrome())
			{
				_object.current.reset();
				_object.current = make_unique<Monochrome>(Monochrome());
			}
		}
		bool isMonochrome()const
		{
			return false;
		}
	};

	unique_ptr<BaseState> current;

	bool isMonochrome()const;
	void trySides()const;
};

