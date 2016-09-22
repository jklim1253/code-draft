#include <iostream>
#include <string>
#include "INIHelper.hpp"
using namespace std;

class Sensor {
private :
	std::string name;
	int price;
	double resolution;
	std::string corp;

public :
	void save() {
		helper.useFile("Setting.ini");
		{
			helper.useSection("Sensor");
			{
				helper.SetValue("name", "K63 basic sensor");
				helper.SetValue("price", 1500);
				helper.SetValue("resolution", 5412.01);
				helper.SetValue("corp", "apple, inc");
			}
			helper.useSection("Servo");
			{
				helper.SetValue("nam", "Servo default");
				helper.SetValue("price", 2400);
				helper.SetValue("speed", 1.152);
				helper.SetValue("corp", "lenovo");
			}
		}

	}
	void load() {
		helper.useFile("Setting.ini");
		{
			helper.useSection("Sensor");
			{
				name = helper.GetValue<std::string>("name");
				price = helper.GetValue("price", 0);
				resolution = helper.GetValue("resolution", 0.0);
				corp = helper.GetValue("corp", std::string("none"));
				name = helper.GetValue<std::string>("names");
				price = helper.GetValue<int>("prices");

				std::cout << "name : " << name << std::endl;
				std::cout << "price : " << price << std::endl;
				std::cout << "resolution : " << resolution << std::endl;
				std::cout << "corp : " << corp << std::endl;
			}
		}

	}
private :
	INIHelper helper;
};
int main(void) {

	try {
		Sensor sensor;
		sensor.save();
		sensor.load();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}