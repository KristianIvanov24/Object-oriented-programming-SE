#include <string>
#include <iostream>

class Sensor
{
	std::string ID;
	std::string timestamp;
	unsigned humidity;
	double temperature;

	void validateID() const;
	void validateTimestamp() const;
	void validateHumidity() const;
	void validateTemperature() const;
	void validateData() const;

public:
	Sensor();

	friend std::istream& operator>>(std::istream& is, Sensor& s);
	friend std::ostream& operator<<(std::ostream& os, const Sensor& s);
};