#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void swap(pair *xcandidate, pair *ycandidate);
void quicksort(void);
void quicksort_recursion(int low, int high);
int partition(int low, int high);
void lock_pairs(void);
bool cycle(int winner, int loser);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count - 1; k++)
            {
                if ((k > 0) && (ranks[k - 1] == j))
                {
                    break;
                }
                if (i == j)
                {
                    break;
                }
                else if (ranks[k] == i)
                {
                    preferences[i][j]++;
                    break;
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    quicksort();
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool source = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                source = false;
                break;
            }
        }
        if (source == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

// Swaps candidates in the array pairs
void swap(pair *xcandidate, pair *ycandidate)
{
    pair temp = *xcandidate;
    *xcandidate = *ycandidate;
    *ycandidate = temp;
}

// Quick sort algorithm for sorting array pairs
void quicksort()
{
    quicksort_recursion(0, pair_count - 1);
}

// Recursion for quick sort
void quicksort_recursion(int low, int high)
{
    if (low < high)
    {
        int pivot_index = partition(low, high);
        quicksort_recursion(low, pivot_index - 1);
        quicksort_recursion(pivot_index + 1, high);
    }
}

// Partition for divide and conquer aproach
int partition(int low, int high)
{
    int pivot_value = high;
    int iwinner = preferences[pairs[pivot_value].winner][pairs[pivot_value].loser];
    int iloser = preferences[pairs[pivot_value].loser][pairs[pivot_value].winner];
    int ypair = iwinner - iloser;
    int i = low;
    int xpair;
    for (int j = low; j < high; j++)
    {
        int jwinner = preferences[pairs[j].winner][pairs[j].loser];
        int jloser = preferences[pairs[j].loser][pairs[j].winner];
        xpair = jwinner - jloser;
        if (xpair >= ypair)
        {
            swap(&pairs[i], &pairs[j]);
            i++;
        }
    }
    swap(&pairs[i], &pairs[high]);
    return i;
}

bool cycle(int winner, int loser)
{
    if (loser == winner)
    {
        return true;
    }
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[loser][i] == true)
        {
            if (cycle(winner, i))
            {
                return true;
            }
        }
    }
    return false;
}
