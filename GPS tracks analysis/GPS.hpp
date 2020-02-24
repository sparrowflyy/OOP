#pragma once
#include <ctime>
#include <map>
#include <vector>
#include "xmlparser/geopoint.h"
#include "xmlparser/GeopointEx.h"
#include "xmlparser/pugixml/pugixml.hpp"
#include "xmlparser/pugixml/pugiconfig.hpp"
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <istream>
#include <fstream>
typedef double speed;
typedef double min_speed;
typedef double max_speed;
typedef time_t _time;
#define SPEED_SEGMENT 6

class GPStrack
{
private:
	std::vector<GeopointEx> points;
	std::vector<std::pair<double,speed>> speed_by_time;

	time_t _start_time, _end_time, _movement_time, _stops_time; 
																
	double _max_speed;
	double _min_height, _max_height;
	double _total_climb, _total_descent;
	double _all_distance;

public:
	GPStrack(const char* filename);
	GPStrack(std::istream& stream);
	GPStrack();
	~GPStrack() = default;
	void print_result(std::ostream& stream);
	void add_point(GeopointEx& point);
	double all_distance() { return _all_distance; }
	double total_climb() { return _total_climb; }
	double total_descent() { return _total_descent; }
	double max_height() { return _max_height; }
	double min_height() { return _min_height; }
	double max_speed() { return _max_speed; }
	time_t duration() { return (_end_time - _start_time); }
	time_t movement_time() { return _movement_time; }
	time_t stops_time() { return _stops_time; }
	double average_speed();
	void clear();
	const std::map<const std::string, double> speed_histogram();
	void init(pugi::xml_document& doc);
};
class Histogram {
public:
	Histogram() {};
	Histogram(std::vector<std::pair< double, speed>>& book);
	~Histogram()=default;

	static const std::map<const std::string, double> get_hist(const Histogram& hist);
	const std::string get_range(speed v);
	void add_el(const std::pair< double, speed>& element);
private:
	std::map<const std::string, double> vocab;
};


