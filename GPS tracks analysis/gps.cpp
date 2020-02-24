#include "GPS.hpp"


GPStrack::GPStrack(const char* filename) {
	clear();
	pugi::xml_document doc;
	if (!doc.load_file(filename)) return;
	init(doc);
}
GPStrack::GPStrack(std::istream& stream) {
	clear();
	pugi::xml_document doc;
	if (!doc.load(stream)) return;
	init(doc);
}
void GPStrack::init(pugi::xml_document& doc) {
	pugi::xml_node tools = doc.child("gpx").child("trk").child("trkseg");
	for (pugi::xml_node trkpt : tools.children("trkpt"))
	{
		auto lat = trkpt.attribute("lat").as_double();
		auto lon = trkpt.attribute("lon").as_double();
		std::string time = trkpt.child_value("time");
		auto ele = trkpt.child("ele").text().as_double();
		GeopointEx tmp_point(lat, lon, ele, time.c_str());
		add_point(tmp_point);
	}
	if (points.size())_start_time = points[0].time();
}
GPStrack::GPStrack() {
	clear();
}
void GPStrack::clear()
{
	_movement_time = 0;
	_stops_time = 0;
	_max_speed = 0;
	points.clear();
}
void GPStrack::add_point(GeopointEx& point) {
	if (points.size() == 1) {
		_min_height = points[0].elevation();
		_max_height = points[0].elevation();
		_start_time = points[0].time();
		_end_time = points[0].time();
	}
	{	
		if (point.time() > _end_time)
		{
			_end_time = point.time();
		}

		if (point.elevation() < _min_height)
		{
			_min_height = point.elevation();
		}
		if (point.elevation() > _max_height)
		{
			_max_height = point.elevation();
		}
	}
	if (points.size() >= 1) {
		const GeopointEx& last_point = points.back();
		if (last_point.elevation() > point.elevation())
		{
			_total_descent += fabs(point.elevation() - last_point.elevation());
		}
		else
		{
			_total_climb += fabs(point.elevation() - last_point.elevation());
		}

		double dist = point.distanceTo(last_point);
		_all_distance += fabs(dist);
		double dt = point.time() - last_point.time();
		
		double speed;
		if (dt > .0001) speed = dist / dt;
		else speed = 0;
		if (speed > _max_speed)
			{
				_max_speed = speed;
			}
		if (dist > 0.01 && speed > 0.2345) {
			speed_by_time.push_back({ dt, speed });
		}
		if (speed < 0.2345) _stops_time += dt;
		else _movement_time += dt;
		}
	points.push_back(point);
}

double GPStrack::average_speed(){
	return (_all_distance / (_movement_time - _stops_time));
}
const std::map<const std::string, double>GPStrack::speed_histogram() {
	Histogram speed_hist(speed_by_time);
	return Histogram::get_hist(speed_hist);
}
void GPStrack::print_result(std::ostream& stream) {
	std::map<const std::string, double> hist= speed_histogram();
	stream << "duration: " << int(duration() / 86400) <<" days " << int(duration() / 3600) << " hours "<<int (duration() / 60)- (int(duration() / 3600))*60 << " minutes "<< duration()-60*int(duration()/60) << " seconds\n";
	stream << "all distance: " << all_distance() << " m\n";
	stream << "movement time: " << int(movement_time() / 86400) << " days " << int(movement_time() / 3600) << " hours " << int(movement_time() / 60) - (int(movement_time() / 3600)) * 60 << " minutes " << movement_time() - 60 * int(movement_time() / 60) << " seconds\n";
	stream << "stops time: " << int(stops_time() / 86400) << " days " << int(stops_time() / 3600) << " hours " << int(stops_time() / 60) - (int(stops_time() / 3600)) * 60 << " minutes " << stops_time() - 60 * int(stops_time() / 60) << " seconds\n";
	stream << "average speed: " << average_speed()*3.6 << " km/h\n";
	stream << "max speed: " << max_speed()*3.6 << " km/h\n";
	stream << "min height: " << min_height() << " m\n";
	stream << "max height: " << max_height() << " m\n";
	stream << "total_climb: " << total_climb() << " m\n";
	stream << "total_descent: " << total_descent() << " m\n";
	stream << "\nspeed histogram:\n";
	for (auto it = hist.begin(); it != hist.end(); ++it) {
		std::pair<const std::string, double>& element = *it;
		std::string range = element.first;
		stream << range;
		stream << " m/s : " << int(element.second/60) <<" minutes "<< element.second - 60*(int)(element.second / 60) << " seconds\n";
	}
}