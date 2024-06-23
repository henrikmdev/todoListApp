#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TASK_LENGTH 256

void addTask(char *tasks[], int *taskCount);
void viewTasks(char *tasks[], int taskCount, int completed[]);
void markTaskComplete(int completed[], int taskCount);
void deleteTask(char *tasks[], int *taskCount, int completed[]);

int main() {
    char *tasks[MAX_TASKS];
    int completed[MAX_TASKS] = {0};
    int taskCount = 0;
    int choice;

    while (1) {
        printf("\nTo-Do List Menu:\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task as Complete\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount, completed);
                break;
            case 3:
                markTaskComplete(completed, taskCount);
                break;
            case 4:
                deleteTask(tasks, &taskCount, completed);
                break;
            case 5:
                // Free allocated memory before exiting
                for (int i = 0; i < taskCount; i++) {
                    free(tasks[i]);
                }
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void addTask(char *tasks[], int *taskCount) {
    if (*taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    char task[MAX_TASK_LENGTH];
    printf("Enter the task: ");
    fgets(task, MAX_TASK_LENGTH, stdin);
    task[strcspn(task, "\n")] = '\0'; // Remove newline character

    tasks[*taskCount] = (char *)malloc(strlen(task) + 1);
    strcpy(tasks[*taskCount], task);
    (*taskCount)++;
    printf("Task added.\n");
}

void viewTasks(char *tasks[], int taskCount, int completed[]) {
    if (taskCount == 0) {
        printf("No tasks to display.\n");
        return;
    }

    printf("\nTo-Do List:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s [%s]\n", i + 1, tasks[i], completed[i] ? "Completed" : "Not Completed");
    }
}

void markTaskComplete(int completed[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks to mark.\n");
        return;
    }

    int taskNum;
    printf("Enter the task number to mark as complete: ");
    scanf("%d", &taskNum);
    getchar(); // Consume the newline character

    if (taskNum < 1 || taskNum > taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    completed[taskNum - 1] = 1;
    printf("Task marked as complete.\n");
}

void deleteTask(char *tasks[], int *taskCount, int completed[]) {
    if (*taskCount == 0) {
        printf("No tasks to delete.\n");
        return;
    }

    int taskNum;
    printf("Enter the task number to delete: ");
    scanf("%d", &taskNum);
    getchar(); // Consume the newline character

    if (taskNum < 1 || taskNum > *taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    // Shift the tasks and completed statuses to the left
    for (int i = taskNum - 1; i < *taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
        completed[i] = completed[i + 1];
    }

    // Free the memory allocated for the last task
    free(tasks[*taskCount - 1]);

    // Decrement the task count
    (*taskCount)--;

    printf("Task deleted.\n");
}
