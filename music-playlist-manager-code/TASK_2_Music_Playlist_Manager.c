#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song {
    char name[50];
    char artist[50];
    float duration;
    struct Song *next;
};

struct Song *head = NULL;
struct Song *currentPlay = NULL;

void clearBuffer() {
    while (getchar() != '\n');
}

struct Song* createSong(char name[], char artist[], float duration) {
    struct Song *newSong = (struct Song*)malloc(sizeof(struct Song));
    if (!newSong) return NULL;

    strncpy(newSong->name, name, 49);
    newSong->name[49] = '\0';

    strncpy(newSong->artist, artist, 49);
    newSong->artist[49] = '\0';

    newSong->duration = duration;
    newSong->next = NULL;

    return newSong;
}

void addSong() {
    char name[50], artist[50];
    float duration;

    printf("Enter Song Name: ");
    if (scanf(" %49[^\n]", name) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    printf("Enter Artist: ");
    if (scanf(" %49[^\n]", artist) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    printf("Enter Duration: ");
    if (scanf("%f", &duration) != 1 || duration <= 0) {
        printf("Invalid duration!\n");
        clearBuffer();
        return;
    }

    struct Song *newSong = createSong(name, artist, duration);
    if (!newSong) return;

    if (head == NULL) {
        head = newSong;
        currentPlay = head;
    } else {
        struct Song *temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newSong;
    }

    printf("Song added!\n");
}

void displayPlaylist() {
    struct Song *temp = head;
    int i = 1;

    if (!temp) {
        printf("Playlist is empty.\n");
        return;
    }

    printf("\nPlaylist:\n");
    while (temp != NULL) {
        printf("%c %d. %s - %s (%.2f mins)\n",
               (temp == currentPlay) ? '>' : ' ',
               i++, temp->name, temp->artist, temp->duration);
        temp = temp->next;
    }
}

void deleteSong() {
    char name[50];
    struct Song *temp = head, *prev = NULL;

    if (!head) {
        printf("Playlist is empty.\n");
        return;
    }

    printf("Enter song name to delete: ");
    if (scanf(" %49[^\n]", name) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {

            if (currentPlay == temp) {
                currentPlay = temp->next;
                if (currentPlay == NULL) currentPlay = head;
            }

            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);

            if (head == NULL) currentPlay = NULL;

            printf("Song deleted!\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("Song not found.\n");
}

void playNext() {
    if (!head) {
        printf("Playlist is empty.\n");
        return;
    }

    if (!currentPlay) currentPlay = head;

    printf("Now Playing: %s - %s\n",
           currentPlay->name, currentPlay->artist);

    currentPlay = currentPlay->next;
    if (!currentPlay) currentPlay = head;
}

void freePlaylist() {
    struct Song *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int choice;

    do {
        printf("\n--- Playlist Manager ---\n");
        printf("1. Add\n2. Display\n3. Delete\n4. Play Next\n5. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1: addSong(); break;
            case 2: displayPlaylist(); break;
            case 3: deleteSong(); break;
            case 4: playNext(); break;
            case 5:
                freePlaylist();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }

    } while (choice != 5);

    return 0;
}
