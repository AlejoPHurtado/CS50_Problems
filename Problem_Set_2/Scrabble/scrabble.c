#import <cs50.h>
#import <ctype.h>
#import <stdio.h>

int player_score(string word);

int main(void)
{

    string word_player1 = get_string("Player1: ");
    string word_player2 = get_string("Player2: ");

    int player1_score = player_score(word_player1);
    int player2_score = player_score(word_player2);

    if (player1_score > player2_score)
        printf("Player 1 wins!\n");
    else if (player1_score < player2_score)
        printf("Player 2 wins!\n");
    else if (player1_score == player2_score)
        printf("Tie!\n");
    else
        printf("Game error.\n");
}

int player_score(string word)
{
    int i = 0;
    int score = 0;

    while (word[i] != '\0')
    {
        char letter = toupper(word[i]);
        int nletter = (int) letter;

        if ((nletter > 64) && (nletter < 91))
        {
            switch (nletter)
            {
                case 75:
                    score += 5;
                    break;
                case 90:
                case 81:
                    score += 10;
                    break;
                case 88:
                case 74:
                    score += 8;
                    break;
                case 68:
                case 71:
                    score += 2;
                    break;
                case 70:
                case 72:
                case 86:
                case 87:
                    score += 4;
                    break;
                case 66:
                case 67:
                case 77:
                case 80:
                    score += 3;
                    break;
                default:
                    score += 1;
            }
        }
        i++;
    }
    return score;
}
