#include <vector>
#include <string>
#include <memory>

#include "Sensor.h"

class SensorManager
{
	std::vector<std::unique_ptr<Sensor>> sensors;

public:
	void loadFromFile(const std::string& inputPath,
					  const std::string& invalidPath);

	void saveProcessed(const std::string& outputPath) const;
};
