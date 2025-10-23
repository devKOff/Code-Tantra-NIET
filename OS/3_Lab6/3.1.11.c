#include <stdio.h>
#include <stdlib.h> // For exit()

// Define the number of philosophers
#define N 5

// Define the states
enum {
    THINKING,
    HUNGRY,
    EATING
} philosopher_state[N];

// 0 = Free, 1 = Taken
int chopstick_state[N];

/**
 * @brief Prints the main menu (without the "Enter choice" prompt).
 */
void print_menu_choices() {
    printf("Choices:\n");
    printf("1. Philosopher hungry\n");
    printf("2. Philosopher puts down chopsticks\n");
    printf("3. Exit\n");
}

/**
 * @brief Prints the current status of all philosophers and chopsticks.
 */
void print_current_state() {
    // Print philosopher states
    printf("States:\n");
    for (int i = 0; i < N; i++) {
        printf("Philosopher %d: ", i);
        if (philosopher_state[i] == EATING) {
            printf("Eating\n");
        } else if (philosopher_state[i] == HUNGRY) {
            printf("Hungry\n");
        } else {
            printf("Thinking\n");
        }
    }

    // Print chopstick states
    printf("Chopsticks:\n");
    for (int i = 0; i < N; i++) {
        printf("Chopstick %d: ", i);
        if (chopstick_state[i] == 1) { // 1 = Taken
            printf("Taken\n");
        } else { // 0 = Free
            printf("Free\n");
        }
    }
}

/**
 * @brief Logic for when a philosopher becomes hungry.
 * They will immediately try to eat if possible.
 */
void philosopher_hungry() {
    int p;
    printf("Which philosopher (0-4) is hungry: ");
    scanf("%d", &p);

    // Validate input
    if (p < 0 || p >= N) {
        printf("Invalid philosopher number.\n");
        return;
    }

    printf("Philosopher %d is now hungry\n", p);
    philosopher_state[p] = HUNGRY;

    // Define left and right chopsticks
    int left_chopstick = p;
    int right_chopstick = (p + 1) % N;

    // Check if both chopsticks are free
    if (chopstick_state[left_chopstick] == 0 && chopstick_state[right_chopstick] == 0) {
        // Yes, can eat!
        philosopher_state[p] = EATING;
        chopstick_state[left_chopstick] = 1; // Take
        chopstick_state[right_chopstick] = 1; // Take
        printf("Philosopher %d starts eating\n", p);
    } else {
        // No, cannot eat
        printf("Philosopher %d cannot eat now\n", p);
    }
}

/**
 * @brief Logic for when a philosopher puts down their chopsticks.
 */
void philosopher_put_down() {
    int p;
    printf("Which philosopher (0-4) puts down chopsticks: ");
    scanf("%d", &p);

    // Validate input
    if (p < 0 || p >= N) {
        printf("Invalid philosopher number.\n");
        return;
    }

    if (philosopher_state[p] == EATING) {
        philosopher_state[p] = THINKING;

        int left_chopstick = p;
        int right_chopstick = (p + 1) % N;

        // Free both chopsticks
        chopstick_state[left_chopstick] = 0; // Free
        chopstick_state[right_chopstick] = 0; // Free

        printf("Philosopher %d stops eating and starts thinking\n", p);
    } else {
        // Handle cases where the philosopher wasn't eating
        if(philosopher_state[p] == HUNGRY) {
            printf("Philosopher %d is hungry, not eating.\n", p);
        } else {
             printf("Philosopher %d is thinking, not eating.\n", p);
        }
    }
}


int main() {
    int choice;

    // Initialize all philosophers to THINKING
    // and all chopsticks to 0 (Free)
    for (int i = 0; i < N; i++) {
        philosopher_state[i] = THINKING;
        chopstick_state[i] = 0; // 0 = Free
    }

    // --- THIS IS THE FIX ---
    // Print the menu choices only ONCE, before the loop.
    print_menu_choices();

    while (1) {
        // Print the prompt *inside* the loop
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                philosopher_hungry();
                print_current_state(); // Print state after action
                break;
            case 2:
                philosopher_put_down();
                print_current_state(); // Print state after action
                break;
            case 3:
                exit(0); // Exit the program
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }
    // -----------------------

    return 0;
}