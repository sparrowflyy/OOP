#include "Match.hpp"
#include <sstream>
#include <iostream>

const std::string Match::product_type = "match";

std::string& Match::serialize() const
{
	std::stringstream data;
	data << product_type<<" "<< match_id << " " << date << " " << location << " " << result << " " << teamid1 << " " << teamid2 << "\n";
	std::string* buf = new std::string(data.str());
	return *buf;
}
 void Match::set_team_1(std::shared_ptr<Team> _team1)
 {
	  team1 = _team1; 
 }

void Match::set_team_2(std::shared_ptr<Team> _team2)
{
	team2 = _team2;
}
 int Match::get_id() const
 {
	 return match_id; 
 }



Match::Match(std::string& str)
{
	std::istringstream stream(str);		 //type id date location result team1_id team2_id  
	std::string buf;
	stream >> buf;
	try
	{
		if (buf != product_type) throw buf;
		stream >> match_id;
		stream >> date;
		stream >> location;
		stream >> result;
		stream >> teamid1;
		stream >> teamid2;
		team1 = nullptr;
		team2 = nullptr;
	}
	catch (std::string& type)
	{
		std::cout << "Wrong type of Product: " << type << std::endl;

	}
}