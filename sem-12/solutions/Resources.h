namespace resources
{
	namespace exception_strings
	{
		static constexpr char invalid_sensor_id[] =
			"Invalid sensor ID!";

		static constexpr char invalid_sensor_timestamp[] =
			"Invalid timestamp!";

		static constexpr char invalid_sensor_temperature[] =
			"Invalid temperature!";

		static constexpr char invalid_sensor_humidity[] =
			"Invalid humidity!";

		static constexpr char invalid_line_format[] =
			"Invalid line format!";

		static constexpr char file_open[] =
			"Cannot open file!";
	}

    namespace constraints
    {
        static unsigned MIN_ID_LEN = 4;
        static unsigned MAX_ID_LEN = 8;
        static unsigned TIMESTAMP_LEN = 19;
        static unsigned MAX_HUMIDITY = 100;
        static double MIN_TEMPERATURE = -50.0;
        static double MAX_TEMPERATURE = 100.0;
    }
}