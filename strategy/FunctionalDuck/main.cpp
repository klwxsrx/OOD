#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;


typedef std::function<void()> FlyBehaviorFunction;

FlyBehaviorFunction MakeWithWingsFlyBehavior()
{
	return[flyCounter = 0]() mutable { cout << "I'm flying with wings!! Number: " << ++flyCounter << endl; };
}

FlyBehaviorFunction MakeNoWayFlyBehavior()
{
	return []() {};
}



typedef std::function<void()> QuackBehaviorFunction;

QuackBehaviorFunction MakeQuackQuackBehavior()
{
	return []() { cout << "Quack Quack!!!" << endl; };
}

QuackBehaviorFunction MakeSqueekQuackBehavior()
{
	return []() { cout << "Squeek!!!" << endl; };
}

QuackBehaviorFunction MakeMuteQuackBehavior()
{
	return []() {};
}



typedef std::function<void()> DanceBehaviorFunction;

DanceBehaviorFunction MakeWaltzDanceBehavior()
{
	return []() { cout << "I'm dancing waltz!!!" << endl; };
}

DanceBehaviorFunction MakeMinuetDanceBehavior()
{
	return []() { cout << "I'm dancing minuet!!!" << endl; };
}

DanceBehaviorFunction MakeNoWayDanceBehavior()
{
	return []() { cout << "Dancing? No way!!!" << endl; };
}



class Duck
{
public:
	Duck(FlyBehaviorFunction&& flyBehavior, QuackBehaviorFunction&& quackBehavior, DanceBehaviorFunction&& danceBehavior)
		: m_quackBehavior(move(quackBehavior))
		, m_danceBehavior(move(danceBehavior))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(move(flyBehavior));
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	virtual void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(FlyBehaviorFunction&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehaviorFunction m_flyBehavior;
	QuackBehaviorFunction m_quackBehavior;
	DanceBehaviorFunction m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(MakeWithWingsFlyBehavior(), MakeQuackQuackBehavior(), MakeWaltzDanceBehavior())
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(MakeWithWingsFlyBehavior(), MakeQuackQuackBehavior(), MakeMinuetDanceBehavior())
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DeckoyDuck : public Duck
{
public:
	DeckoyDuck()
		: Duck(MakeNoWayFlyBehavior(), MakeMuteQuackBehavior(), MakeNoWayDanceBehavior())
	{
	}
	void Display() const override
	{
		cout << "I'm deckoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(MakeNoWayFlyBehavior(), MakeSqueekQuackBehavior(), MakeNoWayDanceBehavior())
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(MakeNoWayFlyBehavior(), MakeQuackQuackBehavior(), MakeNoWayDanceBehavior())
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Fly();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

void main()
{
	MallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(MakeWithWingsFlyBehavior());
	PlayWithDuck(modelDuck);
}
