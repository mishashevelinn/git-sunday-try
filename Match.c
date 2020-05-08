//
// Created by tal5s on 05/05/2020.
//

#include "Team.h"
#include "Match.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Match * MatchCreate(Team* teamH, Team* teamG, int goalH, int goalG){
    Match *match;
    match = (Match *) malloc(sizeof(Match));
    if(match == NULL) {
        printf("Failed to allocate %lu bytes\n", sizeof(Match));
        exit(1);
    }
    match->teamHost = teamH;
    match->teamGuest = teamG;
    match->goalGuest = goalG;
    match->goalHost = goalH;
    return match;

}

void MatchDestroy(Match * match){
    free(match);
}

bool team_participated(Match *match, Team *team) {
    return (team==match->teamGuest || team == match->teamHost);
}

bool match_tied(Match* match){
    return match->goalGuest==match->goalHost;
}
bool team_won(Match* match, Team* team){ //TODO Check the logic here!!!
    if(!team_participated(match, team)){
        printf("Error in file %s, line %d\n", __FILE__, __LINE__);
        printf("Team %s has not participated in match\n", team->TeamName);
        exit(-1);
    }
    if(match->teamHost.){//comparing structs not goals! and return false when true
        return true;
    }
    else if(match->goalHost>match->goalGuest){
        return team == match->teamGuest;
    }
    return false;
}

bool team_lost(Match* match, Team* team) {
    if (!team_participated(match, team)) {
        printf("Error in file %s, line %d\n", __FILE__, __LINE__);
        printf("Team %s has not participated in match\n", team->TeamName);
        exit(-1);
    }
    return (!match_tied(match) && !team_won(match, team));

}
int GF(Match* match, Team* team){
    if (!team_participated(match, team)) {
        printf("Error in file %s, line %d\n", __FILE__, __LINE__);
        printf("Team %s has not participated in match\n", team->TeamName);
        exit(-1);
    }
    return (match->teamGuest == team) ? match->goalGuest : match->goalHost;

}
int GA(Match* match, Team* team){
    if (!team_participated(match, team)) {
        printf("Error in file %s, line %d\n", __FILE__, __LINE__);
        printf("Team %s has not participated in match\n", team->TeamName);
        exit(-1);
    }
    return (match->teamGuest == team) ?  match->goalHost : match->goalGuest;


}