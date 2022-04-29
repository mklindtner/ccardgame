#include <stdio.h>
#include "headers.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

char const *empty = "";
char const *header = "C1\tC2\tC3\tC4\tC5\tC6\tC7";
char const *sSPADE = "S";
char const *sHEARTS = "H";
char const *sDIAMONDS = "D";
char const *sCLOVER = "C";
char const *KING = "K";
char const *QUEEN = "Q";
char const *JACK = "J";
char const *TEN = "T";
char const *ACE = "A";

char *letter = (char *)malloc(sizeof(char)*2);
char *g_msg = (char *)malloc(sizeof(char)*100);
char *pregame_cmd = (char *)malloc(sizeof(char)*3);
char *pregame_arg = (char *)malloc(sizeof(char)*MAX_INPUT_SZ-2);
char *card_tmp = (char *)malloc(sizeof(char)*3);

card **card_definition_list = (card **)malloc(sizeof(card *)*CARDSIZE);
sfoundations *fonds = (sfoundations *)malloc(sizeof(sfoundations));
scolumns *cols = (scolumns *)malloc(sizeof(scolumns));
stack_card **cards_ref = (stack_card **)malloc(sizeof(stack_card)*CARDSIZE);
sstack stack = {cards_ref};
scolumns *copycols = (scolumns *)malloc(sizeof(scolumns));

char quit = false;
char quit_game = false;

int main()
{
    card **cards = generate_cards(0);
    // shuffle_stack();
    generate_columns();
    initialize_columns();
    start_turn();
    char firsttime = true;
    char *input = (char *)malloc(sizeof(char) * 40);

    sprintf(g_msg, "");
    sprintf(input, "");
    // sprintf(empty, "");

    start_layout_table(input);
    while (1)
    {
        // system("clear");
        if(quit_game == true)
        {
            start_layout_table(input);
            quit_game = false;
        }
        sprintf(g_msg, "");

        fgets(input, MAX_INPUT_SZ, stdin);
        char *pos = strstr(input, "->");
        cut_space(input);

        pregame_main(input);
        if(quit == true)
        {
            break;
        }

        // play mode
        if (!strcmp(input, "P"))
        {
            while (1)
            {
                layout_tableau();
                msg_bottom_left_last_message(input);
                msg_bottom_left_message(g_msg);
                msg_bottom_left_input(empty);
                sprintf(g_msg, "");

                fgets(input, MAX_INPUT_SZ, stdin);
                char *pos = strstr(input, "->");
                cut_space(input);

                if (!strcmp(input, "Q"))
                {
                    quit_game = true;
                    break;
                }
                if (pos)
                {
                    //['C1:A1']
                    char **c = split_move(input, pos);
                    // printf("lhs: |%s|\t rhs:|%s|\n", c[0], c[1]);
                    printf("--------------------\n");
                    move_col_card(c);
                }
            }
        }
    }

    return 0;
}

void cut_space(char *input)
{
    // printf("input before cut: |%s|\n", input);
    if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
    {
        input[strlen(input) - 1] = '\0';
    }
    // printf("input after cut: |%s|\n", input);
}
#pragma clang diagnostic pop