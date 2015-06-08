#include <iostream>
#include <vector>
#include <regex>
#include "rankings.hpp"

Match::Match(const std::string name1, int score1, const std::string name2, int score2):
  team1Name{name1},
  team1Score{score1},
  team2Name{name2},
  team2Score{score2} {}

League::League() { League(3, 0, 1); }

League::League(const int winPoints, const int losePoints, const int tiePoints):
  winPoints_{winPoints},
  losePoints_{losePoints},
  tiePoints_{tiePoints},
  teams_() {}

std::vector<Team>* League::teams() { return &teams_; }

Team* League::ensureTeam(const std::string teamName) {
  Team *team = getTeam(teamName);

  if (team) return team;

  addTeam(teamName);
  team = getTeam(teamName);

  if (team) return team;

  return NULL;
}

bool League::recordMatch(const Match match) {
  Team *team1 = ensureTeam(match.team1Name);
  Team *team2 = ensureTeam(match.team2Name);

  if (!(team1 && team2)) return false;

  if (match.team1Score == match.team2Score) {
    team1->tie();
    team2->tie();
  } else if (match.team1Score > match.team2Score) {
    team1->win();
    team2->lose();
  } else {
    team1->lose();
    team2->win();
  }

  return true;
}

void League::addTeam(const std::string teamName) {
  teams_.push_back(Team(teamName));
}

size_t League::totalTeams() const noexcept {
  return teams_.size();
}

Team* League::getTeam(const std::string name) {
  size_t size = teams_.size();

  for (int i = 0; i < size; ++i)
    if (teams_[i].name() == name) return & teams_[i];

  return 0;
}

Team::Team(std::string name):
  name_{name},
  ties_{0},
  losses_{0},
  wins_{0} {}

std::string Team::name() { return name_; }

void Team::win() { ++wins_; }
void Team::lose() { ++losses_; }
void Team::tie() { ++ties_; }

std::string Team::toString() {
  return "<Teamname: " + name_ +
    ", wins: " + std::to_string(wins_) +
    ", losses: " + std::to_string(losses_) +
    ", ties: " + std::to_string(ties_) + ">";
}

bool populateLeague(std::istream &input_stream, League *league) {
  std::string line = std::string();
  std::regex lineSplitter("([\\s\\w]+)\\s+(\\d+),\\s([\\s\\w]+)\\s+(\\d+)");
  std::smatch re_match;
  int rc;

  while (std::getline(input_stream, line)) {
    std::regex_search(line, re_match, lineSplitter);
    rc = league->recordMatch(Match(re_match.str(1),
                              atoi(re_match.str(2).c_str()),
                              re_match.str(3),
                              atoi(re_match.str(4).c_str())));
  }

  return true;
}

void printLeague(std::ostream &output_stream, League *league) {
  std::vector<Team>* teams = league->teams();
  size_t team_count = teams->size();

  for (int i = 0; i < team_count; ++i)
    std::cout << (teams->at(i)).toString() << std::endl;
}

int main() {
  League *mls = new League(3, 0, 1);

  if (!populateLeague(std::cin, mls)) {
    std::cerr << "Error populating league with input" << std::endl;
    return 1;
  }

  printLeague(std::cout, mls);
  delete mls;

  return 0;
}
