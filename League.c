//
// Created by tal5s on 05/05/2020.
//

#include "Team.h"
#include "Match.h"
#include <stdbool.h>
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
    return league;
}

void LeagueDestroy(League *league) {
    free(league);
}

void read_teams(League *league, const char *file_name) {
    league->teams = NULL;
    league->numTeams = 0;
    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        fprintf(stderr, "error in line %d, failed to open a file\n", __LINE__);
        exit(-1);
    }
    char *line = NULL;
    size_t size = 0;
    size_t len = 0;

    while ((len = getline(&line, &size, fp)) != EOF) {
        line[len - 1] = 0;
        league->teams = (Team **) realloc(league->teams, sizeof(Team)*league->numTeams);
        league->teams[league->numTeams] = TeamCreate(line);
        league->numTeams++;
    }
    league->numTeams--;
    fclose(fp);
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
    printf("OK1, ptrH: %s, ptrG: %s, goalH: %d, goalG: %d\n", ptrH, ptrG, goalH, goalG);
    while ((len = fscanf(fp, "%s\t%s\t%d\t%d", ptrH, ptrG, &goalH, &goalG)) != EOF) {
        printf("Try NO%d, return value from scan: %d\n", league->numMatches + 1, len);
        if (len != 4) {
            printf("line %d in file is not in expected format", league->numMatches + 1);
            exit(1);
        }

        printf("OK2, ptrH: %s, ptrG: %s, goalH: %d, goalG: %d\n", ptrH, ptrG, goalH, goalG);
        league->matches = (Match **) realloc(league->matches, sizeof(Match));
        Team *teamH = NULL;
        Team *teamG = NULL;
        for (int i = 0; i < league->numTeams; i++) {
            printf("OK3, ptrH: %s, ptrG: %s, goalH: %d, goalG: %d\n", ptrH, ptrG, goalH, goalG);
            if (!strcmp((league->teams[i]->TeamName), ptrH)) {
                teamH = league->teams[i];
                printf("OK4, %d\n", i);
            } else if (!strcmp((league->teams[i]->TeamName), ptrG)) {
                teamG = league->teams[i];
                printf("OK5, %d\n", i);
            }
            if (teamH != NULL && teamG != NULL) {
                printf("OK6, %d\n", i);
                break;
            }
        }
        printf("H: %s, G: %s----> %d:%d\n", teamH->TeamName, teamG->TeamName, goalH, goalG);
        league->matches[league->numMatches] = MatchCreate(teamH, teamG, goalH, goalG);
        printf("%s\n", league->matches[league->numMatches]->teamHost->TeamName);
        league->numMatches++;
    }
    fclose(fp);
    printf("%s\n", league->matches[0]->teamHost->TeamName);
}
