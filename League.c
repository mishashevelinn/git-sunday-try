//
// Created by tal5s on 05/05/2020.
//

#include "Team.h"
#include "Match.h"
#include <stdio.h>
#include <stdlib.h>
#include "League.h"
#include <string.h>

League *LeagueCreate() {
    League *league;
    league = (League *) malloc(sizeof(League));
    if (league == NULL) {
        printf("Failed to allocate %lu bytes\n", sizeof(League));
        exit(1);
    }
    league->teams = (Team **) malloc(sizeof(Team));
    if (league->teams == NULL) {
        printf("Failed to allocate %lu bytes\n", sizeof(Team));
        exit(1);
    }
    league->matches = (Match **) malloc(sizeof(Match));
    if (league->matches == NULL) {
        printf("Failed to allocate %lu bytes\n", sizeof(Match));
        exit(1);
    }

    return league;
}

void LeagueDestroy(League *league) {
    free(league);
    free(league->teams);
    free(league->matches);
}

void read_teams(League *league, const char *file_name) {
    league->teams = NULL;
    league->numTeams = 0;
    char *line = NULL;
    size_t size = 0;
    size_t len = 0;
    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        fprintf(stderr, "error in line %d, failed to open a file\n", __LINE__);
        exit(-1);
    }
    while ((len = getline(&line, &size, fp)) != EOF) {
        line[len - 1] = 0;
        league->teams = (Team **) realloc(league->teams, sizeof(Team)*(league->numTeams));
        league->teams[league->numTeams] = TeamCreate(line);
        league->numTeams++;
    }
}


void read_matches(League *league, const char *file_name) {
    league->matches = NULL;
    league->numMatches = 0;
    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        fprintf(stderr, "error in line %d, failed to open a file\n", __LINE__);
        exit(-1);
    }
    size_t len = 0;
    char ptrH[30];
    char ptrG[30];
    int goalH = -1;
    int goalG = -1;
    while ((len = fscanf(fp, "%s\t%s\t%d\t%d", ptrH, ptrG, &goalH, &goalG)) != EOF) {
        if (len != 4) {
            printf("line %d in file is not in expected format", league->numMatches + 1);
            exit(1);
        }
        league->matches = (Match **) realloc(league->matches, sizeof(Match)*league->numMatches);
        Team *teamH = NULL;
        Team *teamG = NULL;
        for (int i = 0; i < league->numTeams; i++) {
            if (!strcmp((league->teams[i]->TeamName), ptrH)) {
                teamH = league->teams[i];
            } else if (!strcmp((league->teams[i]->TeamName), ptrG)) {
                teamG = league->teams[i];
            }
            if (teamH != NULL && teamG != NULL) {
                break;
            }
        }
        //printf("H: %s, G: %s----> %d:%d\n", teamH->TeamName, teamG->TeamName, goalH, goalG);
        league->matches[league->numMatches] = MatchCreate(teamH, teamG, goalH, goalG);
        //printf("%s\n", league->matches[league->numMatches]->teamHost->TeamName);
        league->numMatches++;
    }
    //printf("%s\n", league->matches[0]->teamHost->TeamName);
}
