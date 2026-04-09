#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for each song node
struct Song {
    char name[50];
    char artist[50];
    float duration;  // in minutes
    struct Song *next;
};

struct Song *head = NULL;
struct Song *currentPlay = NULL; // To keep track for Play Next feature

// Function to create a new song node
struct Song* createSong(char name[], char artist[], float duration) {
    struct Song *newSong = (struct Song*)malloc(sizeof(struct Song));
    strcpy(newSong->name, name);
    strcpy(newSong->artist, artist);
    newSong->duration = duration;
    newSong->next = NULL;
    return newSong;
}

// Add song at end
void addSong() {
    char name[50], artist[50];
    float duration;

    printf("Enter Song Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Artist: ");
    scanf(" %[^\n]", artist);
    printf("Enter Duration (minutes): ");
    scanf("%f", &duration);

    struct Song *newSong = createSong(name, artist, duration);

    if (head == NULL) {
        head = newSong;
        currentPlay = head; // Initialize playing pointer
    } else {
        struct Song *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
    }
    printf("Song Added!\n");
}

// Display all songs
void displayPlaylist() {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    struct Song *temp = head;
    int count = 1;

    printf("\n🎵 Playlist:\n");
    while (temp != NULL) {
        printf("%d. %s - %s (%.2f mins)\n", count, temp->name, temp->artist, temp->duration);
        temp = temp->next;
        count++;
    }
}

// Search for a song by name (Case Insensitive)
void searchSong() {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    char name[50];
    printf("Enter song name to search: ");
    scanf(" %[^\n]", name);

    struct Song *temp = head;
    int found = 0;

    while (temp != NULL) {
        // strcasecmp is used for case-insensitive comparison
        if (strcasecmp(temp->name, name) == 0) {
            printf("Found: %s - %s (%.2f mins)\n", temp->name, temp->artist, temp->duration);
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) printf("Song not found!\n");
}

// Delete a song by name
void deleteSong() {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    char name[50];
    printf("Enter song name to delete: ");
    scanf(" %[^\n]", name);

    struct Song *temp = head, *prev = NULL;

    while (temp != NULL) {
        if (strcasecmp(temp->name, name) == 0) {
            if (prev == NULL) {
                head = temp->next; // Deleting head
            } else {
                prev->next = temp->next;
            }
            
            // Adjust currentPlay if we delete the song it's pointing to
            if (currentPlay == temp) {
                currentPlay = head;
            }

            free(temp);
            printf("Song Deleted!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Song not found!\n");
}

// Count total songs
void countSongs() {
    int count = 0;
    struct Song *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Total Songs in Playlist: %d\n", count);
}

// Play Next Song feature
void playNext() {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }
    if (currentPlay == NULL) {
        currentPlay = head;
    }

    printf("▶️ Now Playing: %s - %s (%.2f mins)\n", currentPlay->name, currentPlay->artist, currentPlay->duration);
    
    // Move to next song for the next time this is called
    currentPlay = currentPlay->next;
    if (currentPlay == NULL) {
        currentPlay = head; // Loop back to start
    }
}

int main() {
    int choice;

    do {
        printf("\n===== 🎧 Music Playlist Manager =====\n");
        printf("1. Add Song\n");
        printf("2. Display Playlist\n");
        printf("3. Search Song\n");
        printf("4. Delete Song\n");
        printf("5. Count Songs\n");
        printf("6. Play Next Song\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addSong(); break;
            case 2: displayPlaylist(); break;
            case 3: searchSong(); break;
            case 4: deleteSong(); break;
            case 5: countSongs(); break;
            case 6: playNext(); break;
            case 7: printf("🚪 Exiting Playlist Manager...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);

    return 0;
}