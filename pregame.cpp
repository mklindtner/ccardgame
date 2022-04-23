#ifndef _PREGAME
#define _PREGAME
#include "headers.h"

void pregame_SI(int split_point)
{
    stack_card *stack_left[(CARDSIZE - split_point)];
    stack_card *stack_right[split_point];

    int j = 0;
    for (int i = 0; i < CARDSIZE; i++)
    {
        if (i <= split_point)
        {
            stack_right[i] = stack.cards_ref[i];
        }
        if (i > split_point)
        {
            stack_left[j++] = stack.cards_ref[i];
        }
    }
    // printf("--- fordelt bunker ---\n");
    int l = 0, r = 0, m = 0;
    for (int k = 0; k < CARDSIZE; k++)
    {
        // printf("k: %d\tm: %d\n",k,m);
        if (stack_right[k] != nullptr)
        {        
            stack.cards_ref[m++] = stack_right[r++];
        }
 
        if (stack_left[k] != nullptr)
        {
            stack.cards_ref[m++] = stack_left[l++];
        }
    }
}


void SR_shuffle()
{
    stack_card *stack_sr[CARDSIZE];
    stack_sr[0] = stack.cards_ref[0];
    // printf("---starting loop---\n");
    for (int i = 1; i < CARDSIZE; i++)
    {
        // randomize
        srand(time(NULL));
        // printf("---callign rant---\n");
        int r1 = rand() % i;
        if (r1 < i)
        {
            int j = i;
            stack_card *tmp;
            // printf("---inner forloop---\n");
            for (; j > r1; j--)
            {
                // printf("i: %d\t j:%d\n", i,j);
                stack_sr[j] = stack_sr[j - 1];
            }
            stack_sr[r1] = stack.cards_ref[i];
        }
        else
        {
            stack_sr[r1] = stack.cards_ref[i];
        }
    }

    // printf("---stack_sr---\n");
    for (int k = 0; k < CARDSIZE; k++)
    {
        // printf("val: %d, col: %d\n", stack_sr[k]->card->number, stack_sr[k]->card->color);
        stack.cards_ref[k] = stack_sr[k];
    }
    // printf("---stack_sr finished---\n");
}

void pregame_LD(char *input)
{
    // printf("arg length: %d\n", (int) strlen(pregame_arg));
    if (strlen(pregame_arg) < 1)
    {
        // shuffle_stack();
        pregame_layout(input, false);
    }
    else
    {
        char buff[MAX_LENGTH_FILE];
        FILE *f;
        if(errno_t fo = fopen_s(&f, pregame_arg, "r") != 0)
        {
            sprintf(g_msg, "error reading file");
            return;
        }

        char *reader = nullptr;
        int i = 0;
        // card *head = stack.cards_ref[0]->card;
        do
        {
            fgets(buff, MAX_LENGTH_FILE, f);
            int number = letter_to_int(buff[0]);
            COLOR suit = string_to_color(&buff[1]);
            int index = (suit * 13 + number) - 1;
            card *c = card_definition_list[index];
            stack.cards_ref[i]->card = c;
            i++;
        } while (!feof(f));
        printf("\nout of loop\n");

        fclose(f);
    }
}

void pregame_SD()
{
    if (strlen(pregame_arg) < 1)
    {
        sprintf(pregame_arg, "%s", "cards.txt");
    }

    FILE *f;
    if(fopen_s(&f, pregame_arg, "w+") != 0)
    {
        sprintf(g_msg, "unable to store file\n");
        return;
    }

    for (int i = 0; i < CARDSIZE; i++)
    {
        card *c = stack.cards_ref[i]->card;
        char const *suit = int_to_suit(c->color);
        char const *letter = int_to_letter(c->number);
        if (i == CARDSIZE - 1)
        {
            sprintf(card_tmp, "%s%s", letter, suit);
        }
        else
        {
            sprintf(card_tmp, "%s%s\n", letter, suit);
        }
        fputs(card_tmp, f);
    }

    fclose(f);
}

void pregame_main(char *input)
{
    // pregame, only relevant if pos is 2 long
    //  printf("input is:|%s|\n",input);
    if (strcmp(&input[1], "\0"))
    {
        // cut 2 first letters here
        sprintf(pregame_cmd, "%.2s", input);
        sprintf(pregame_arg, "%s", input + 3);
        // printf("pregame_cmd: |%s|\n", pregame_cmd);
        // printf("pregame_arg: |%s|\n", pregame_arg);

        if (!strcmp(pregame_cmd, "LD"))
        {
            pregame_LD(input);
        }

        if (!strcmp(pregame_cmd, "SD"))
        {
            pregame_SD();
        }

        if (!strcmp(pregame_cmd, "SW"))
        {
            pregame_layout(input, true);
        }

        if (!strcmp(pregame_cmd, "SR"))
        {
            SR_shuffle();
        }

        if (!strcmp(pregame_cmd, "SI"))
        {
            int split_point = -1;
            if (strlen(pregame_arg) < 1)
            {
                srand(time(NULL));
                split_point = rand() % CARDSIZE;
                pregame_SI(split_point);
            }
            else
            {
                split_point = atoi(pregame_arg);
                // sprintf(pregame_arg, "%d", split_point);
                // printf("split_point: %d\tpregame_arg :|%s|\n", split_point,pregame_arg);
                pregame_SI(split_point);
            }
        }

        if(!strcmp(pregame_cmd, "QQ"))
        {
            quit = true;
        }
    }
}

void pregame_layout(char *input, bool show_cards)
{
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    pregame_layout_cards(show_cards);

    printf("\n");
    msg_bottom_left_last_message(input);
    msg_bottom_left_message(g_msg);
    msg_bottom_left_input(empty);
}

void pregame_layout_cards(bool show_cards)
{
    int f = 0;
    for (int i = 0; i < PREGAME_ROWSIZE; i++)
    {

        for (int j = 0; j < COLUMNSIZE; j++)
        {
            if (i * 7 + j < CARDSIZE)
            {
                card *c = stack.cards_ref[i * 7 + j]->card;
                char const *suit = int_to_suit(c->color);
                char const *num = int_to_letter(c->number);
                if (show_cards)
                {
                    printf("%s%s\t", num, suit);
                }
                else
                {
                    printf("[]\t");
                }
            }
        }
        if (i == 0 || i == 2 || i == 4 || i == 6)
        {
            printf("\t\t");
            printf("[]");
            // layout_foundation(f++);
            printf("\tF%d", ++f);
        }

        printf("\n");
    }
}

#endif