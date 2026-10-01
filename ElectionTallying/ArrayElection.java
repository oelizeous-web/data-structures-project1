package DCandGreedy.ElectionTallying;
public class ArrayElection {

    static final int MAX_CANDIDATES = 10;
    static final int MAX_UNITS = 100;

    // 1. Data Structures
    static class CandidateVote {
        String name;
        int votes;

        CandidateVote(String name, int votes) {
            this.name = name;
            this.votes = votes;
        }
    }

    static class Tally {
        CandidateVote[] candidates = new CandidateVote[MAX_CANDIDATES];
        int candidateCount = 0;

        void addVote(String name, int votes) {
            candidates[candidateCount++] = new CandidateVote(name, votes);
        }
    }

    // 2. The Complete Hierarchy: Polling Station -> Subcounty -> District -> Country
    static class PollingStation {
        Tally tally = new Tally();
    }

    static class Subcounty {
        PollingStation[] stations = new PollingStation[MAX_UNITS];
        int count = 0;
        void addStation(PollingStation ps) { stations[count++] = ps; }
    }

    static class District {
        Subcounty[] subcounties = new Subcounty[MAX_UNITS];
        int count = 0;
        void addSubcounty(Subcounty sc) { subcounties[count++] = sc; }
    }

    // Country is back! It holds the districts.
    static class Country {
        District[] districts = new District[MAX_UNITS];
        int count = 0;
        void addDistrict(District d) { districts[count++] = d; }
    }

    // 3. Divide and Conquer Logic
    static Tally aggregateTallies(Tally[] tallies, int left, int right) {
        if (left == right) {
            return tallies[left];
        }

        int mid = left + (right - left) / 2;
        Tally leftTally = aggregateTallies(tallies, left, mid);
        Tally rightTally = aggregateTallies(tallies, mid + 1, right);

        return mergeTallies(leftTally, rightTally);
    }

    static Tally mergeTallies(Tally left, Tally right) {
        Tally combined = new Tally();

        for (int i = 0; i < left.candidateCount; i++) {
            combined.addVote(left.candidates[i].name, left.candidates[i].votes);
        }

        for (int i = 0; i < right.candidateCount; i++) {
            boolean found = false;
            for (int j = 0; j < combined.candidateCount; j++) {
                if (combined.candidates[j].name.equals(right.candidates[i].name)) {
                    combined.candidates[j].votes += right.candidates[i].votes;
                    found = true;
                    break;
                }
            }
            if (!found && combined.candidateCount < MAX_CANDIDATES) {
                combined.addVote(right.candidates[i].name, right.candidates[i].votes);
            }
        }
        return combined;
    }

    // 4. Cascade Helpers: Bottom-up Aggregation
    static Tally processSubcounty(Subcounty sc) {
        Tally[] tallies = new Tally[sc.count];
        for (int i = 0; i < sc.count; i++) tallies[i] = sc.stations[i].tally;
        return aggregateTallies(tallies, 0, sc.count - 1);
    }

    static Tally processDistrict(District d) {
        Tally[] tallies = new Tally[d.count];
        for (int i = 0; i < d.count; i++) tallies[i] = processSubcounty(d.subcounties[i]);
        return aggregateTallies(tallies, 0, d.count - 1);
    }

    // The National Tally Centre level
    static Tally processCountry(Country c) {
        if (c.count == 0) return new Tally();
        Tally[] tallies = new Tally[c.count];
        for (int i = 0; i < c.count; i++) tallies[i] = processDistrict(c.districts[i]);
        return aggregateTallies(tallies, 0, c.count - 1);
    }

    public static void main(String[] args) {
        // --- DISTRICT 1 ---
        PollingStation ps1 = new PollingStation();
        ps1.tally.addVote("Candidate A", 150);
        ps1.tally.addVote("Candidate B", 80);

        PollingStation ps2 = new PollingStation();
        ps2.tally.addVote("Candidate A", 90);
        ps2.tally.addVote("Candidate B", 110);

        Subcounty sc1 = new Subcounty();
        sc1.addStation(ps1);
        sc1.addStation(ps2);

        District district1 = new District();
        district1.addSubcounty(sc1);

        // --- DISTRICT 2 ---
        PollingStation ps3 = new PollingStation();
        ps3.tally.addVote("Candidate A", 200);
        ps3.tally.addVote("Candidate B", 300);

        Subcounty sc2 = new Subcounty();
        sc2.addStation(ps3);

        District district2 = new District();
        district2.addSubcounty(sc2);

        // --- TOP LEVEL: COUNTRY ---
        Country country = new Country();
        country.addDistrict(district1);
        country.addDistrict(district2);

        // Process everything from the top down
        Tally nationalTally = processCountry(country);

        // Output Final National Results
        System.out.println("National Final Results:");
        for (int i = 0; i < nationalTally.candidateCount; i++) {
            System.out.println(nationalTally.candidates[i].name + ": " + nationalTally.candidates[i].votes);
        }
    }
}
