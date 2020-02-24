#include "gtest/gtest.h"
#include "..//GPS tracks/GPS.hpp"

const char* few_points = 
"<?xml version='1.0' encoding='UTF-8' standalone='no' ?>													   \n"
"<gpx>																										   \n"
"<trk>																										   \n"
"<trkseg>																									   \n"
"<trkpt lat='45.012423' lon='41.951237'><time>2014-11-16T10:11:00.2Z</time><ele>579.0</ele></trkpt>			   \n"
"<trkpt lat='45.012347' lon='41.950698'><time>2014-11-16T10:11:38.3Z</time><ele>579.7</ele></trkpt>			   \n"
"<trkpt lat='45.012308' lon='41.950497'><time>2014-11-16T10:11:39.998Z</time><ele>579.7</ele></trkpt>		   \n"
"<trkpt lat='45.012395' lon='41.950166'><time>2014-11-16T10:11:43.999Z</time><ele>580.6</ele></trkpt>		   \n"
"<trkpt lat='45.012613' lon='41.94977'><time>2014-11-16T10:11:49.1Z</time><ele>581.3</ele></trkpt>			   \n"
"<trkpt lat='45.012949' lon='41.949405'><time>2014-11-16T10:11:54.997Z</time><ele>583.0</ele></trkpt>		   \n"
"<trkpt lat='45.013071' lon='41.949525'><time>2014-11-16T10:11:56Z</time><ele>582.2</ele></trkpt>			   \n"
"<trkpt lat='45.013108' lon='41.949994'><time>2014-11-16T10:12:00.999Z</time><ele>580.0</ele></trkpt>		   \n"
"	</trkseg>																								   \n"
"</trk>																										   \n"
"</gpx>																										   \n"
;

const char* smooth_flight = "<?xml version='1.0' encoding='UTF-8' standalone='no' ?>													   \n"
"<gpx>																										   \n"
"<trk>																										   \n"
"<trkseg>																									   \n"
"<trkpt lat='0' lon='0'><time>2014-11-16T10:11:00.2Z</time><ele>600.0</ele></trkpt>							   \n"			
"<trkpt lat='0' lon='0'><time>2014-11-16T10:12:00.3Z</time><ele>660.0</ele></trkpt>								\n"			
"<trkpt lat='0' lon='0'><time>2014-11-16T10:13:00.998Z</time><ele>720.7</ele></trkpt>		   \n"							
"<trkpt lat='0' lon='0'><time>2014-11-16T10:14:00.999Z</time><ele>780.6</ele></trkpt>		   \n"							
"<trkpt lat='0' lon='0'><time>2014-11-16T10:15:00.1Z</time><ele>840</ele></trkpt>			   \n"							
"<trkpt lat='0' lon='0'><time>2014-11-16T10:16:00.997Z</time><ele>900.0</ele></trkpt>		   \n"							
"<trkpt lat='0' lon='0'><time>2014-11-16T10:17:00Z</time><ele>960</ele></trkpt>				   \n"							
"<trkpt lat='0' lon='0'><time>2014-11-16T10:18:00.999Z</time><ele>1020</ele></trkpt>		   \n"							
"	</trkseg>																								   \n"			
"</trk>																										   \n"			
"</gpx>																										   \n"
;
const char* rapid_flight = "<?xml version='1.0' encoding='UTF-8' standalone='no' ?>													   \n"
"<gpx>																										   \n"
"<trk>																										   \n"
"<trkseg>																									   \n"
"<trkpt lat='0' lon='0'><time>2014-11-16T10:11:00.2Z</time><ele>600.0</ele></trkpt>			   \n"
"<trkpt lat='0' lon='0'><time>2014-11-16T10:12:00.3Z</time><ele>660.0</ele></trkpt>			   \n"
"<trkpt lat='0' lon='0'><time>2014-11-16T10:13:00.998Z</time><ele>780.0</ele></trkpt>		   \n"
"<trkpt lat='0' lon='0'><time>2014-11-16T10:14:00.999Z</time><ele>960.0</ele></trkpt>		   \n"
"<trkpt lat='0' lon='0'><time>2014-11-16T10:15:00.1Z</time><ele>1200</ele></trkpt>			   \n"
"<trkpt lat='0' lon='0'><time>2014-11-16T10:16:00.997Z</time><ele>1500.0</ele></trkpt>		   \n"
"<trkpt lat='0' lon='0'><time>2014-11-16T10:17:00Z</time><ele>1860</ele></trkpt>				   \n"
"<trkpt lat='0' lon='0'><time>2014-11-16T10:18:00.999Z</time><ele>2280</ele></trkpt>		   \n"
"	</trkseg>																								   \n"
"</trk>																										   \n"
"</gpx>																										   \n"
;
std::istringstream ss(few_points);
std::istringstream fly(smooth_flight);
std::istringstream rapid_fly(rapid_flight);
GPStrack test(ss);
GPStrack flying(fly);
GPStrack fast_flying(rapid_fly);

TEST(gps, time_test){
	EXPECT_EQ(test.duration(), 60);
}

TEST(gps, max_height_test) {
	EXPECT_EQ(test.max_height(), 583);
}

TEST(gps, min_height_test) {
	EXPECT_EQ(test.min_height(), 579);
}

TEST(gps, total_climb) {
	EXPECT_EQ(flying.total_climb(), 420);
}
TEST(gps, descent_test) {
	EXPECT_EQ(flying.total_descent(), 0);
}

TEST(gps, distance_test) {
	EXPECT_EQ(flying.all_distance(),420);
}
TEST(gps, stops_time_test) {
	EXPECT_EQ(flying.stops_time(), 0);
}
TEST(gps, average_speed_test) {
	EXPECT_EQ(flying.average_speed(), 1);		 //1 ms
}

////ускор€юща€с€ 
TEST(gps, max_speed_test) {
	EXPECT_EQ(fast_flying.max_speed(), 7);
}
TEST(gps, speed_hist_test) {
	auto hist = fast_flying.speed_histogram();
	const std::map<const std::string, double> result = { {"0-2",60},{"2-4",120},{"4-6",120},{"6-8",120} };
	EXPECT_EQ(result,hist);
}
