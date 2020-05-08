
#include <stdio.h>
#include <stdlib.h>

#include "League.h"


int main() {
    /*    Team* liv = TeamCreate("Liverpool");
    Team*  poel= TeamCreate("HaPoel");
    Team*  milan = TeamCreate("Milan");
    Match* game1 = MatchCreate(poel, liv, 5, 3);
     */

    League *liga1 = LeagueCreate();
    read_teams(liga1, "teams.txt");
    for (int i = 0; i < liga1->numTeams; i++) {
        printf("Team: %s\n", (liga1->teams[i]->TeamName));
    }
    read_matches(liga1, "matches.txt");
    for (int i = 0; i < (liga1->numMatches); i++) {
        printf("Match%d %s against %s - %d:%d\n", i + 1, liga1->matches[i]->teamHost->TeamName,
               liga1->matches[i]->teamGuest->TeamName,
               liga1->matches[i]->goalHost, liga1->matches[i]->goalGuest);
    }
    return 0;
}
