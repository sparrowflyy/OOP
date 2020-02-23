#include "Football_factory.hpp"
#include <fstream>
#include <iostream>
void Football_factory::read(std::istream& stream)
{
	std::string buf;
	while (std::getline(stream, buf))							
	{
		Product* product = Product::create(buf);
		int type = product->get_type();
		switch (type)
		{
		case 0: { players.push_back(std::shared_ptr<Player>((dynamic_cast<Player*>(product)))); break; };
		case 1: { teams.push_back(std::shared_ptr<Team>((dynamic_cast<Team*>(product)))); break; };
		case 2: { matches.push_back(std::shared_ptr<Match>((dynamic_cast<Match*>(product)))); break; };
		default: std::cerr << "Unknown product!";
		}
	}																						 
	binding_players();
	binding_teams();
	binding_matches();
}
 void Football_factory::write(std::ostream& stream)
 {
	 for (auto it = players.begin(); it != players.end(); ++it)
	 {
		 stream << (*it)->serialize();
	 }
	 for (auto it = teams.begin(); it != teams.end(); ++it)
	 {
		 stream << (*it)->serialize();
	 }
	 for (auto it = matches.begin(); it != matches.end(); ++it)
	 {
		 stream << (*it)->serialize();
	 }
 }

void Football_factory::read(const std::string& filename)
{
	std::ifstream stream(filename);
	if (stream.is_open()) {
		read(stream);
		stream.close();
	}
	else std::cout << "Couldn't open file!\n";
}
void Football_factory::write(const std::string& filename)
{
	std::ofstream stream(filename);
	if (stream.is_open()) {
		write(stream);
		stream.close();
	}
	else std::cout << "Couldn't create file!\n";
}
void Football_factory::binding_players()
{
	for (auto it_p = players.begin(); it_p != players.end(); ++it_p)
	{
		for (auto it_t = teams.begin(); it_t != teams.end(); ++it_t)
		{
			if ((*it_t)->get_id() == (*it_p)->team_id) (*it_p)->set_team(*it_t);
		}
	}
}

void Football_factory::binding_teams()
{
	for (auto it_t = teams.begin(); it_t != teams.end(); ++it_t)
	{
		for (auto it_p = players.begin(); it_p != players.end(); ++it_p)
		{
			auto it = std::find((*it_t)->players_id.begin(), (*it_t)->players_id.end(), (*it_p)->get_id());
			if (it != (*it_t)->players_id.end()) (*it_t)->add_player(*it_p);
		}
	}
}

void Football_factory::binding_matches()
{
	for (auto it_m = matches.begin(); it_m != matches.end(); ++it_m)
	{
		for (auto it_t = teams.begin(); it_t != teams.end(); ++it_t)
		{
			if ((*it_m)->teamid1 == (*it_t)->get_id()) (*it_m)->set_team_1(*it_t);
			if ((*it_m)->teamid2 == (*it_t)->get_id()) (*it_m)->set_team_2(*it_t);
		}
	}
}


Football_factory::players_iterator Football_factory::find_player(int id)
{
	for (auto it = players.begin();it!=players.end();++it)
	{
		if ((*it)->get_id() == id) return it;
	}
	return players.end();
}
Football_factory::teams_iterator Football_factory::find_team(int id)
{
	for (auto it = teams.begin(); it != teams.end(); ++it)
	{
		if ((*it)->get_id() == id) return it;
	}
	return teams.end();
}

 Football_factory::mathes_iterator Football_factory::find_match(int id)
 {
	 for (auto it = matches.begin(); it != matches.end(); ++it)
	 {
		 if ((*it)->get_id() == id) return it;
	 }
	 return matches.end();
 }

