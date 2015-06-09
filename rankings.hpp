// Philip
#ifndef __rankings_h_
#define __rankings_h_

struct Match {
  Match(const std::string name1, int score1, const std::string name2, int score2);
  std::string team1Name;
  std::string team2Name;
  int team1Score;
  int team2Score;
};

class Team {
  std::string name_;
  int wins_, losses_, ties_;
public:
  Team(const std::string name);
  std::string name();
  void win();
  void lose();
  void tie();
  std::string toString();
  bool operator==(Team other) {
    bool isEqual = (name_ == other.name());
    return isEqual;
  };
};

class League {
  std::vector<Team> teams_;
  int winPoints_;
  int losePoints_;
  int tiePoints_;
public:
  League();
  League(const int winPoints, const int losePoints, const int tiePoints);
  void addTeam(const std::string teamName);
  Team *getTeam(const std::string teamName);
  Team *ensureTeam(const std::string teamName);
  size_t totalTeams() const noexcept;
  bool recordMatch(const Match match);
  std::vector<Team>* teams();
  bool populateLeague(std::istream &input_stream, League *league);
};

#endif
