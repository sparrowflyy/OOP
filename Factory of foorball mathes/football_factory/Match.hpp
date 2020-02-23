#pragma once
#include "Product.hpp"
#include "Team.hpp"
class Match : public Product
{
public:
	Match(std::string& str);
	int get_id() const;
	std::string& serialize() const;
	bool operator==(const Match& another) const
	{
		return match_id == another.match_id && date == another.date && location == another.location && result == another.result && teamid1==another.teamid1 && teamid2==another.teamid2;
	}
	int get_type() const { return 2; };
	
	std::string get_location() const { return location; };
	std::string get_date() const { return date; };
	std::string get_result() const { return result; };
	std::shared_ptr<Team> get_team_first() const { return team1; };
	std::shared_ptr<Team> get_team_second() const { return team2; };

	void set_team_1(std::shared_ptr<Team> _team1);
	void set_team_2(std::shared_ptr<Team> _team2);
	static const std::string product_type;
	int teamid1;
	int teamid2;
private:
	int match_id;
	std::string date;
	std::string location;
	std::shared_ptr<Team> team1;
	std::shared_ptr<Team> team2;
	std::string result;

};