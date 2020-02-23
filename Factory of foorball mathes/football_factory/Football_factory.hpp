#pragma once
#include <string>
#include <vector>
#include "Player.hpp"
#include "Team.hpp"
#include "Match.hpp"

class Football_factory
{
public:
	using players_iterator = std::vector<std::shared_ptr<Player>>::const_iterator;
	using teams_iterator = std::vector<std::shared_ptr<Team>>::const_iterator;
	using mathes_iterator = std::vector<std::shared_ptr<Match>>::const_iterator;
	

	void read(const std::string& filename);
	void read(std::istream& stream);
	void write(const std::string& filename);
	void write(std::ostream& stream);
	
	auto players_begin() { return players.begin(); }
	auto teams_begin() { return teams.begin(); }
	auto mathes_begin() { return matches.begin(); }
	
	auto players_end() { return players.end(); }
	auto teams_end() { return teams.end(); }
	auto mathes_end() { return matches.end(); }
	
	players_iterator find_player(int id);
	teams_iterator find_team(int id);
	mathes_iterator find_match(int id);

private:
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::shared_ptr<Team>> teams;
	std::vector<std::shared_ptr<Match>> matches;
	void binding_players();
	void binding_teams();
	void binding_matches();
};


