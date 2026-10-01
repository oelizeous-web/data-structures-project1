#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 10
#define MAX_UNITS 10

// 1. Data Structures
typedef struct {
    char name[32];
    int votes;
} CandidateVote;

typedef struct {
    CandidateVote candidates[MAX_CANDIDATES];
    int candidate_count;
} Tally;

// 2. The Complete Hierarchy (Bottom to Top)
typedef struct {
    Tally tally;
} PollingStation;

typedef struct {
    PollingStation stations[MAX_UNITS];
    int count;
} Subcounty;

typedef struct {
    Subcounty subcounties[MAX_UNITS];
    int count;
} District;

typedef struct {
    District districts[MAX_UNITS];
    int count;
} Country;


// 3. Divide and Conquer Logic
// Merges two Tally arrays manually
Tally merge_tallies(Tally left, Tally right) {
    Tally combined = left; // Start with everything from the left half
    
    // Add or merge right half into combined
    for (int i = 0; i < right.candidate_count; i++) {
        int found = 0;
        
        // Search if candidate already exists in the combined array
        for (int j = 0; j < combined.candidate_count; j++) {
            if (strcmp(combined.candidates[j].name, right.candidates[i].name) == 0) {
                combined.candidates[j].votes += right.candidates[i].votes;
                found = 1;
                break;
            }
        }
        
        // If new, append to the end of the array
        if (!found && combined.candidate_count < MAX_CANDIDATES) {
            combined.candidates[combined.candidate_count] = right.candidates[i];
            combined.candidate_count++;
        }
    }
    return combined;
}

// Recursively splits an array of tallies
Tally aggregate_tallies(Tally* tallies, int left, int right) {
    // CONQUER Phase: Base Case
    if (left == right) {
        return tallies[left];
    }
    
    // DIVIDE Phase
    int mid = left + (right - left) / 2;
    Tally left_tally = aggregate_tallies(tallies, left, mid);
    Tally right_tally = aggregate_tallies(tallies, mid + 1, right);
    
    // COMBINE Phase
    return merge_tallies(left_tally, right_tally);
}

// 4. Cascade Helpers: Bottom-up Aggregation
Tally process_subcounty(Subcounty sc) {
    if (sc.count == 0) { Tally empty = {0}; return empty; }
    
    Tally tallies[MAX_UNITS];
    for(int i = 0; i < sc.count; i++) {
        tallies[i] = sc.stations[i].tally;
    }
    return aggregate_tallies(tallies, 0, sc.count - 1);
}

Tally process_district(District d) {
    if (d.count == 0) { Tally empty = {0}; return empty; }
    
    Tally tallies[MAX_UNITS];
    for(int i = 0; i < d.count; i++) {
        tallies[i] = process_subcounty(d.subcounties[i]);
    }
    return aggregate_tallies(tallies, 0, d.count - 1);
}

// The National Tally Centre level
Tally process_country(Country c) {
    if (c.count == 0) { Tally empty = {0}; return empty; }
    
    Tally tallies[MAX_UNITS];
    for(int i = 0; i < c.count; i++) {
        tallies[i] = process_district(c.districts[i]);
    }
    return aggregate_tallies(tallies, 0, c.count - 1);
}

// Helper function to populate votes
Tally create_tally(int count, const char* name1, int vote1, const char* name2, int vote2) {
    Tally t = {0};
    t.candidate_count = count;
    strcpy(t.candidates[0].name, name1); t.candidates[0].votes = vote1;
    strcpy(t.candidates[1].name, name2); t.candidates[1].votes = vote2;
    return t;
}

int main() {
    // --- DISTRICT 1 ---
    PollingStation ps1 = { .tally = create_tally(2, "Candidate A", 150, "Candidate B", 80) };
    PollingStation ps2 = { .tally = create_tally(2, "Candidate A", 90, "Candidate B", 110) };
    
    Subcounty sc1 = {0};
    sc1.stations[0] = ps1;
    sc1.stations[1] = ps2;
    sc1.count = 2;
    
    District district1 = {0};
    district1.subcounties[0] = sc1;
    district1.count = 1;

    // --- DISTRICT 2 ---
    PollingStation ps3 = { .tally = create_tally(2, "Candidate A", 200, "Candidate B", 300) };
    
    Subcounty sc2 = {0};
    sc2.stations[0] = ps3;
    sc2.count = 1;
    
    District district2 = {0};
    district2.subcounties[0] = sc2;
    district2.count = 1;

    // --- TOP LEVEL: COUNTRY ---
    Country country = {0};
    country.districts[0] = district1;
    country.districts[1] = district2;
    country.count = 2;

    // Process everything from the top down
    Tally national_tally = process_country(country);
    
    // Output Final National Results
    printf("National Final Results:\n");
    for(int i = 0; i < national_tally.candidate_count; i++) {
        printf("%s: %d\n", national_tally.candidates[i].name, national_tally.candidates[i].votes);
    }
    
    return 0;
}