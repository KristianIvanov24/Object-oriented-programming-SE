#include "Sensor.h"
#include "../Resources.h"

void Sensor::validateID() const
{
	if (ID.length() < resources::constraints::MIN_ID_LEN || ID.length() > resources::constraints::MAX_ID_LEN)
		throw exceptions::InvalidSensorIdException();

	// HW: Add more validations
}

void Sensor::validateTimestamp() const
{
	if (timestamp.length() != resources::constraints::TIMESTAMP_LEN)
		throw exceptions::InvalidTimestampException();
    
    // HW: Add more validations
}

void Sensor::validateHumidity() const
{
	if (humidity > resources::constraints::MAX_HUMIDITY)
		throw exceptions::InvalidHumidityException();
}

void Sensor::validateTemperature() const
{
	if (temperature < resources::constraints::MIN_TEMPERATURE || temperature > resources::constraints::MAX_TEMPERATURE)
		throw exceptions::InvalidTemperatureException();
}

void Sensor::validateData() const
{
	validateID();
	validateTimestamp();
	validateTemperature();
	validateHumidity();
}

Sensor::Sensor() : humidity(0), temperature(0)
{}

std::istream& operator>>(std::istream& is, Sensor& s)
{
	// HW: To be implemented

	return is;
}

std::ostream& operator<<(std::ostream& os, const Sensor& s)
{
	os << s.ID
	   << " at "
	   << s.timestamp
	   << ": Temp="
	   << s.temperature
	   << "C, Humidity="
	   << s.humidity
	   << "%";

	return os;
}