#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define TEXT_SIZE 1000
typedef struct {
    char items[MAX][TEXT_SIZE];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, const char *text) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    strcpy(s->items[++(s->top)], text);
}

void pop(Stack *s, char *text) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        text[0] = '\0';
        return;
    }
    strcpy(text, s->items[(s->top)--]);
}

// current text peek
void peek(Stack *s, char *text) {
    if (isEmpty(s)) {
        text[0] = '\0';
        return;
    }
    strcpy(text, s->items[s->top]);
}

int main() {
    Stack undoStack, redoStack;
    char currentText[TEXT_SIZE] = "";
    char tempText[TEXT_SIZE];
    int choice;

    init(&undoStack);
    init(&redoStack);

    while (1) {
        printf("\n--- Undo-Redo Text Editor ---\n");
        printf("1. Type new text\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Show Current Text\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                
                push(&undoStack, currentText);

                printf("Enter new text: ");
                fgets(currentText, TEXT_SIZE, stdin);
                currentText[strcspn(currentText, "\n")] = '\0'; 

                
                init(&redoStack);
                printf("Text updated.\n");
                break;

            case 2:
                if (isEmpty(&undoStack)) {
                    printf("Nothing to undo.\n");
                } else {
                    push(&redoStack, currentText);
                    pop(&undoStack, tempText);
                    strcpy(currentText, tempText);
                    printf("Undo successful.\n");
                }
                break;

            case 3:
                if (isEmpty(&redoStack)) {
                    printf("Nothing to redo.\n");
                } else {
                    push(&undoStack, currentText);
                    pop(&redoStack, tempText);
                    strcpy(currentText, tempText);
                    printf("Redo successful.\n");
                }
                break;

            case 4:
                printf("\nCurrent Text: \"%s\"\n", currentText);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
