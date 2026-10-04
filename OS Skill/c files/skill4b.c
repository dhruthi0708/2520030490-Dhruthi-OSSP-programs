#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 200
#define MAX_TOKENS 50
#define MAX_LENGTH 50

struct Node
{
    char value[MAX_LENGTH];
    struct Node *left;
    struct Node *right;
};

struct Node *create_node(char *value)
{
    struct Node *node = malloc(sizeof(struct Node));

    if (node == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(node->value, value);
    node->left = NULL;
    node->right = NULL;

    return node;
}

void print_tree(struct Node *root, int level)
{
    if (root == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("  ");

    printf("|-- %s\n", root->value);

    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}

void free_tree(struct Node *root)
{
    if (root == NULL)
        return;

    free_tree(root->left);
    free_tree(root->right);

    free(root);
}

int tokenize(char *input, char tokens[][MAX_LENGTH])
{
    int count = 0;
    int i = 0;

    while (input[i] != '\0')
    {
        while (isspace(input[i]))
            i++;

        if (input[i] == '\0')
            break;

        if (count >= MAX_TOKENS)
            return -1;

        int j = 0;

        while (input[i] != '\0' &&
               !isspace(input[i]) &&
               input[i] != '|')
        {
            if (j < MAX_LENGTH - 1)
                tokens[count][j++] = input[i];

            i++;
        }

        tokens[count][j] = '\0';

        if (j > 0)
            count++;

        if (input[i] == '|')
        {
            if (count >= MAX_TOKENS)
                return -1;

            strcpy(tokens[count], "|");
            count++;
            i++;
        }
    }

    return count;
}

int validate_syntax(char tokens[][MAX_LENGTH], int count)
{
    if (count == 0)
        return 0;

    /* Command cannot start with pipe */
    if (strcmp(tokens[0], "|") == 0)
    {
        printf("Syntax Error: Command cannot start with '|'.\n");
        return 0;
    }

    /* Command cannot end with pipe */
    if (strcmp(tokens[count - 1], "|") == 0)
    {
        printf("Syntax Error: Command cannot end with '|'.\n");
        return 0;
    }

    /* Two pipes cannot occur together */
    for (int i = 0; i < count - 1; i++)
    {
        if (strcmp(tokens[i], "|") == 0 &&
            strcmp(tokens[i + 1], "|") == 0)
        {
            printf("Syntax Error: Consecutive pipes found.\n");
            return 0;
        }
    }

    return 1;
}

int main()
{
    char input[MAX_INPUT];
    char tokens[MAX_TOKENS][MAX_LENGTH];

    printf("===== Simple Command Parser =====\n");
    printf("Enter command: ");

    fgets(input, MAX_INPUT, stdin);

    input[strcspn(input, "\n")] = '\0';

    /* Handle empty command */
    if (strlen(input) == 0)
    {
        printf("Empty command. Nothing to parse.\n");
        return 0;
    }

    int count = tokenize(input, tokens);

    if (count == -1)
    {
        printf("Error: Too many tokens.\n");
        return 1;
    }

    printf("\nTokens:\n");

    for (int i = 0; i < count; i++)
        printf("%d: %s\n", i + 1, tokens[i]);

    /* Validate syntax */
    if (!validate_syntax(tokens, count))
    {
        printf("Parsing failed.\n");
        return 1;
    }

    printf("\nSyntax is valid.\n");

    /* Create execution structure */
    struct Node *root = create_node("COMMAND");

    struct Node *current = root;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(tokens[i], "|") == 0)
        {
            struct Node *pipe_node = create_node("PIPE");

            pipe_node->left = current;
            root = pipe_node;
            current = root;
        }
        else
        {
            if (current->left == NULL)
                current->left = create_node(tokens[i]);
            else if (current->right == NULL)
                current->right = create_node(tokens[i]);
        }
    }

    printf("\n===== Parse / Execution Tree =====\n");

    print_tree(root, 0);

    printf("\nExecution structure generated successfully.\n");

    /* Release memory */
    free_tree(root);

    return 0;
}
