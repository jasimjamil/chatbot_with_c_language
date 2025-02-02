#include <stdio.h>
#include <string.h>
#include <stdlib.h>// file 

#define MAX_LINE 256
#define MAX_QA 100


void searchAnswer(char *question);// pointer
void addNewQuestion(char *question);

char *dataFile = "data.txt";

int main(int argc, char *argv[]) {
    // Check if user input is passed as an argument
    if (argc < 2) {
        printf("Error: No question provided.\n");
        return 1;
    }

    char *question = argv[1]; // Get user input from command-line argument

    searchAnswer(question); // Process the input

    return 0;
}

// Function to search for an answer in the text file
void searchAnswer(char *question) {
    FILE *file = fopen(dataFile, "r");
    if (file == NULL) {
        printf("Error: Could not open data file.\n");
        return;
    }

    char line[MAX_LINE];
    char storedQuestion[MAX_LINE];
    char answer[MAX_LINE];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {//loops
        // Parse the line into question and answer
        sscanf(line, "%[^|]|%[^\n]", storedQuestion, answer);//input 

        if (strcmp(storedQuestion, question) == 0) {
            printf("%s\n", answer); // Print the answer
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Chatbot: I don't know the answer. Would you like to teach me? (yes/no): ");
        char response[10];
        fgets(response, sizeof(response), stdin);
        response[strcspn(response, "\n")] = 0;

        if (strcmp(response, "yes") == 0) {
            addNewQuestion(question);
        } else {
            printf("Chatbot: Alright! Let me know if you have more questions.\n");
        }
    }
}

// Function to add a new question-answer pair to the file
void addNewQuestion(char *question) {
    char answer[MAX_LINE];
    printf("Chatbot: Please enter the answer for '%s': ", question);
    fgets(answer, sizeof(answer), stdin);
    answer[strcspn(answer, "\n")] = 0; // Remove trailing newline

    FILE *file = fopen(dataFile, "a");
    if (file == NULL) {
        printf("Error: Could not open data file to save new question.\n");
        return;
    }

    fprintf(file, "%s|%s\n", question, answer);
    fclose(file);

    printf("Chatbot: Got it! I learned something new.\n");
}
