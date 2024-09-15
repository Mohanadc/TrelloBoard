#include <stdio.h>
#include <stdlib.h>

//function prototypes
void testData(List** board);
void mainMenu();
void ascii();

void displayBoard(List* list);
void editList(List* list);
void saveBoard(List* list);

//structs
typedef struct item {
    char item[50]; //name of item
    struct item *next; //pointer to next item
} Item;

typedef struct list{
    char name[50];
    struct item *firstItem; //pointer to first item
    struct name *next; //pointer to next struct
} List;

int main(void)
{
    List* board = malloc(sizeof(List));
    char ans;
    printf("Fill board with preset test data? (y/n): ");
    scanf("%c", &ans);
    if(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N'){
        printf("Invalid answer, please re-enter (y/n): ");
        scanf("%c", &ans);
    }
    else{
        if(ans == 'y' || ans == 'Y'){
            testData(&board);
        }
    }

    mainMenu();
    unsigned int choice;
    scanf("%u", &choice);

    while(choice != 6){
        switch(choice){

            case 1:
                displayBoard();
                break;

            case 2:
                //loadBoard();
                printf("This function has not been implemented yet.\n");
                break;

            case 3:
                editList();
                break;

            case 4:
                //editBoard();
                printf("This function has not been implemented yet.\n");
                break;

            case 5:
                saveBoard();
                break;

            default:
                printf("Invalid choice.\n");
                mainMenu();
                break;
        }
        scanf("%u", &choice);
    }

    puts("End of program\n\n");
    ascii();

    return 0;
}

//displays instructions for main menu
void mainMenu()
{
    puts("Menu:\n"
      "1. Display Board\n"
      "2. Load board from a file\n"
      "3. Edit list\n"
      "4. Edit board\n"
      "5. Save board to a file\n"
      "6. Quit\n"
      "Enter your choice (1-5): ");
}

//preset list
void testData(List** board)
{
    List* list1 = malloc(sizeof(List));
    strcpy(list1->name, "Abey:");
    list1->next = NULL;

    Item* item1_1 = malloc(sizeof(Item));
    strcpy(item1_1->name, "Oculus Pro");
    Item* item1_2 = malloc(sizeof(Item));
    strcpy(item1_2->name, "Oculus Quest 1");
    item1_2->next = NULL;

    list1->firstItem = item1_1;
    item1_1->next = item1_2;


    List* list2 = malloc(sizeof(List));
    strcpy(list2->name, "Dante:");
    list2->next = list1;

    Item* item2_1 = malloc(sizeof(Item));
    strcpy(item2_1->name, "Oculus Quest 1");
    item2_1->next = NULL;
    Item* item2_2 = malloc(sizeof(Item));
    strcpy(item2_2->name, "3070 RTX");
    item2_2->next = NULL;

    list2->firstItem = item2_1;
    item2_1->next = item2_2;


    List* list3 = malloc(sizeof(List));
    strcpy(list3->name, "Tim:");
    list3->next = list2;

    Item* item3_1 = malloc(sizeof(Item));
    strcpy(item3_1->name, "Oculus Quest 2");
    list3->firstItem = item3_1;
    item3_1->next = NULL;
    List* list4 = malloc(sizeof(List));
    strcpy(list4->name, "Nick:");
    Item* item4_1 = malloc(sizeof(Item));
    strcpy(item4_1->name, "3070 RTX");
    item4_1->next = NULL;

    list4->firstItem = item4_1;
    list4->next = list3;


    list1->prev = list2;
    list2->prev = list3;
    list3->prev = list4;
    list4->prev = NULL;
    *board = list4;
}

//prints ascii art
void ascii(void)
{
    puts("                     ,, \n"
         "  /\\ _,,_/\\         / / \n"
         " /  .   .  \\        | | \n"
         " |  > ^ <  |,,.,_.,/ / \n"
         "  \\          \\ \\ \\ \\/ \n"
         "  /                 \\ \n"
         "  |   _    ______   / \n"
         "  |  |\\   |  \\  \\   \\ \n"
         "  \\../ \\../   \\..\\../ \n");
}

//prints out the data
void displayBoard(List* list)
{
    List* curr = list;
    while(curr != NULL){
        printf("%s:\n", curr->name);
        Item* item = curr->firstItem;

        while(item != NULL){
            printf("\t%s\n", item);
            item = item->next;
        }
        curr = curr->next;
    }
}

//loads board from

//edit, add or delete an item on a list
void editList(List** list)
{
  char toEdit_list[50];
  unsigned int option;

  printf("Enter the name of the list to edit: ");
  fgets(toEdit, 50, stdin);
  printf("\n\n");

  for(List* curr = &list; curr != NULL; curr = curr->next){
      if(strcmp(curr->name, toEdit) == 0) {
          break;
      }
      else{
          continue;
      }
  }

  printf("Selected list: %s", *curr);

  puts("Options:\n"
    "1. Edit an item\n"
    "2. Add a new item\n"
    "3. Delete an itemt\n"
    "4. Return to main menu\n"
    "Enter your option (1-4): ");

  scanf("%u", &option);
  printf("\n\n");

  while(option != 4){
     switch(option){
        case 1: //edit
            char toEdit_item[50];

            printf("Enter the name of the item to edit: ");
            scanf("%s", &tempItem);
            printf("\n\n");

            printf("Enter new name for item: ");
            scanf("%s", &tempItem);
            printf("\n\n");
            break;

        case 2: //add
            char newItem[50];

             printf("Enter the name of the new item: ");
             fgets(newItem, 50, stdin);
             printf("\n\n");

             insertItem_end(&curr, newItem);
             break;

         case 3: //delete
             char toDelete[50];

             printf("Enter the name of the item to delete: ");
             fgets(toDelete, 50, stdin);
             printf("\n\n");


         default:
             printf("Invalid option, please re-enter.\n");
    }

    scanf("%u", &option);
    printf("\n\n");
  }
}

//writes board to file
void saveBoard(List* list)
{
    FILE* file;
    char filename[50];
    printf("Enter filename :");
    fgets(filename, 50, stdin);
    printf("\n\n");

    file = fopen(filename, "w");
    if(file == NULL){
        printf("File not found.\n");
        return;
    }

    List* curr = list;
    while(curr != NULL){
      fprintf("%s:\n", curr->name);
      Item* item = curr->firstItem;

      while(item != NULL){
          fprintf("\t%s\n", item);
          item = item->next;
      }

      curr = curr->next;
    }

    fclose(file);

    printf("\nSave completed.\n");
}

void insertItem_end(List** list, char newItem [])
{
    List* listPtr = malloc(sizeof(List));
    if(listPtr == NULL){
        printf("Function error 1.\n");
        return;
    }
    Item* newItem = malloc(sizeof(Item));
    if(newItem == NULL){
        printf("Function error 2.\n");
        return;
    }


}
