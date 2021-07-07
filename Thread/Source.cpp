#include<iostream>
#include<thread>
using namespace std; 
using namespace std::literals::chrono_literals;

bool stop = false;

void Hello()
{
	while (!stop)
	{
		cout << "+";
		std::this_thread::sleep_for(1s);
	}
}
void World()
{
	while (!stop)
	{
		cout << "-";
		std::this_thread::sleep_for(1s);
	}
}

void main()
{
	std::thread thread_hello(Hello);
	std::thread thread_world(World);

	std::cin.get(); //Ожидание Ентера
	stop = true;

	thread_world.join();
	thread_hello.join();
}