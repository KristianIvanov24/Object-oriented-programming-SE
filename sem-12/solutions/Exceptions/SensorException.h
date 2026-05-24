#include <stdexcept>
#include <string>

#include "../Resources.h"

namespace exceptions
{
	class SensorException : public std::invalid_argument
	{
	public:
		SensorException(const std::string& msg)
			: std::invalid_argument(msg)
		{
		}
	};

	class InvalidSensorIdException : public SensorException
	{
	public:
		InvalidSensorIdException()
			: SensorException(resources::exception_strings::invalid_sensor_id)
		{
		}
	};

	class InvalidTimestampException : public SensorException
	{
	public:
		InvalidTimestampException()
			: SensorException(resources::exception_strings::invalid_sensor_timestamp)
		{
		}
	};

	class InvalidTemperatureException : public SensorException
	{
	public:
		InvalidTemperatureException()
			: SensorException(resources::exception_strings::invalid_sensor_temperature)
		{
		}
	};

	class InvalidHumidityException : public SensorException
	{
	public:
		InvalidHumidityException()
			: SensorException(resources::exception_strings::invalid_sensor_humidity)
		{
		}
	};

	class InvalidLineFormatException : public SensorException
	{
	public:
		InvalidLineFormatException()
			: SensorException(resources::exception_strings::invalid_line_format)
		{
		}
	};
}
