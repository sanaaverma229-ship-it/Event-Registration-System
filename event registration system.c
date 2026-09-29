#include <stdio.h>
#include <string.h>

#define MAX 5
#define WAIT 5

char mainQueue[MAX][20];
int front1 = -1, rear1 = -1;

char waitQueue[WAIT][20];
int front2 = -1, rear2 = -1;

void registerUser(char name[]) {

    if (rear1 == MAX - 1) {
        if (rear2 == WAIT - 1) {
            printf("Both Event and Waiting List Full!\n");
        }
        else
        {
            if (front2 == -1) front2 = 0;
            strcpy(waitQueue[++rear2], name);
            printf("%s added to Waiting List!\n", name);
        }
    } 
    else
    {
        if (front1 == -1) front1 = 0;
        strcpy(mainQueue[++rear1], name);
        printf("%s Registered Successfully!\n", name);
    }
}

void cancel() {
    if (front1 == -1) {
        printf("No registrations!\n");
        return;
    }

    printf("Cancelled: %s\n", mainQueue[front1]);
    front1++;

    if (front1 > rear1) {
        front1 = rear1 = -1;
    }

    if (front2 != -1) {
        if (rear1 == -1) front1 = 0;

        strcpy(mainQueue[++rear1], waitQueue[front2]);
        printf("Moved from waiting: %s\n", waitQueue[front2]);

        front2++;
        if (front2 > rear2)
            front2 = rear2 = -1;
    }
}

void display() {
    int i;

    printf("\n--- Registered Participants ---\n");
    if (front1 == -1)
        printf("None\n");
    else {
        for (i = front1; i <= rear1; i++)
            printf("%s\n", mainQueue[i]);
    }

    printf("\n--- Waiting List ---\n");
    if (front2 == -1)
        printf("None\n");
    else {
        for (i = front2; i <= rear2; i++)
            printf("%s\n", waitQueue[i]);
    }
}

int main() {
    int choice;
    char name[20];

    while (1) {
        printf("\n1. Register\n2. Cancel\n3. Display\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter Name: ");
            scanf("%s", name);
            registerUser(name);
            break;

        case 2:
            cancel();
            break;

        case 3:
            display();
            break;

        case 4:
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}