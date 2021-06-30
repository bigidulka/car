#include<iostream>
#include<conio.h>
using namespace std;

const unsigned int default_tank_volume = 60;
const unsigned int min_fuel_level = 5;
const unsigned int default_engine_consumption = 8;

class Tank
{
	unsigned int volume;
	double fuel_level;
	unsigned int min_level;
public:
	unsigned int get_volume()const
	{
		return volume;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	unsigned int get_min_level()const
	{
		return min_level;
	}
	void set_fuel_level(double fuel)
	{
		if (fuel < 0)return;
		if (this->fuel_level + fuel < volume) fuel_level += fuel;
		else fuel_level = volume;
	}
	explicit Tank(int volume):volume(volume >= 40 && volume <=120?volume:default_engine_consumption)
	{
		/*if (volume >= 40 && volume <= 120) this->volume = volume;
		else this->volume = 60;*/
		this->volume = volume >= 40 && volume <= 120 ? volume : default_tank_volume;
		fuel_level = 0;
		min_level = min_fuel_level;
		cout << "TankIsReady:\t" << this << endl;
	}
	~Tank()
	{
		cout << "TankIsOver:\t" << this << endl;
	}
	void info()const
	{
		cout << "Volume:\t " << volume << endl;
		cout << "Fuel:\t ";
		if (fuel_level < 10)cout << 0;
		cout << fuel_level << endl;
		cout << "MinValue:";
		if (min_level < 10)cout << 0;
		cout << min_level << endl;
	}
};

class Engine
{
	unsigned int volume;
	unsigned int power;
	double consumption;
	double consumption_per_second;

	bool started;
public:
	double get_consumption()const
	{
		return consumption;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	explicit Engine(double consumption)
	{
		/*if (consumption >= 4 && consumption <= 25) this->consumption = consumption;
		else consumption = 8;*/
		this->consumption = consumption >= 4 && consumption <= 25 ? consumption : default_engine_consumption;
		this->consumption_per_second = consumption * 5e-5;
		started = false;
		cout << "EngineIsReady:\t" << this << endl;
	}
	bool is_started()const
	{
		return started;
	}
	void start()
	{
		started = true;
	}
	void stop()
	{
		started = false;
	}
	~Engine()
	{
		cout << "EngineIsOver:\t" << this << endl;
	}
	void info()const
	{
		cout << "Consumption:\t" << consumption << endl;
		cout << "ConsumptionPerSec:\t" << consumption_per_second << endl;
	};
};

class Car
{
	Engine engine;
	Tank tank;
	const unsigned int MAX_SPEED;
	unsigned int speed;
	bool driver_inside;
public:
	/*Car(const Engine& engine, const Tank& tank) :engine(engine), tank(tank)
	{
		cout << "CarIsReady:\t" << this << endl;
	}*/
	Car(double consumption, unsigned int volume, const unsigned int MAX_SPEED):engine(consumption), tank(volume), MAX_SPEED(MAX_SPEED >= 90&&MAX_SPEED<=400?MAX_SPEED:250), speed(0)
	{
		driver_inside = false;
		cout << "CarIsReady:\t" << this << endl;
	}
	~Car()
	{
		cout << "CarIsOver:\t" << this << endl;
	}
	void get_in()
	{
		driver_inside = true;
	}
	void get_out()
	{
		driver_inside = false;
	}
	bool is_driver_inside()const
	{
		return driver_inside;
	}
	void fill(unsigned int fuel)
	{
		tank.set_fuel_level(fuel);
	}

	void start()
	{
		engine.start();
	}
	void stop()
	{
		engine.stop();
	}

	void display()const
	{
		cout << "Engine is:\t" << (engine.is_started() ? "Started" : "Stoped") << endl;
		cout << "Fuel level:\t" << tank.get_fuel_level() << endl;
		if (tank.get_fuel_level() < tank.get_min_level()) cout << "LOW FUEL" << endl;
		cout << "Speed:" << speed << "\t";
		cout << "MaxSpeed: " << MAX_SPEED << endl;
	}

	void info()const
	{
		cout << "Engine:\t"; engine.info();
		cout << "Tank:\n"; tank.info();
		cout << "Engine is:\t" << (engine.is_started() ? "Started" : "Stoped") << endl;
		cout << "Speed:\t" << speed << "km/h\n";
		cout << "MaxSpeed:\t" << MAX_SPEED << endl;
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK
#define Escape 27
#define Enter 13

void main()
{
	setlocale(0, "Rus");
#ifdef TANK_CHECK
	Tank tank(35);
	tank.info();
	cout << "\n----------------------------\n";
	tank.set_fuel_level(30);
	tank.info();
	cout << "\n----------------------------\n";
	tank.set_fuel_level(40);
	tank.info();
#endif // TANK_CHECK
#ifdef ENGINE_CHECK
	Engine engine(10);
	engine.info();
#endif // ENGINE_CHECK

	Car car(10, 80, 220);
	//car.info();

	cout << "Press Enter to get in" << endl;
	cout << "Press F to fill the car" << endl;

	char key;
	do
	{
		key = _getch();
		switch (key)
		{
		case 'F':
		case 'f':
			system("cls");
			unsigned int fuel;
			cout << "Введите объем топлива: "; cin >> fuel; cout << endl;
			car.fill(fuel);
			break;
		case 'S' :
		case 's' :
			if (car.is_driver_inside()) car.start();
		case Enter: 
			if (car.is_driver_inside())
			{
				system("cls"); car.get_out();
			}
			else
			{
				system("cls"); car.get_in(); break;
			}
		case Escape: system("cls"); cout << "Get out" << endl; break;
		}
		if(car.is_driver_inside())car.display();
	} while (key != Escape);
}