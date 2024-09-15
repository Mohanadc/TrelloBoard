#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//structs for linked list

typedef struct itemNode{  //linked struct that will contain all the items for a certain name
    char item[50]; //name of the item
    struct itemNode *nextItem;//pointer to the next struct
}itemNode;

typedef struct listNode{
    char name[50];
    struct itemNode *firstItem; // linked to the first item of the certain indivisual
    struct listNode *nextName; // linked to the following name on the board
}listNode;


//function prototypes

void displayBoard(listNode **headNode); //displays the linked list taking in the first node as input
void loadBoard(); //load board from files
void editList(listNode **headNode); //edit an item on a list
void editBoard(listNode **headNode); //edit a list on the board
void saveBoard(listNode **headnode); //saves board to file
void mainMenu(listNode **headNode); //main menu where user can select functions
void ascii(); //prints ascii image when program is ended
listNode *getNewPerson(const char *nameToInput, listNode *headlistNode); //adds a new node to the names linked list taking in the name of the item and the pointer to the first node of the linked list
itemNode *getNewItem(const char *itemToInput, itemNode *headItemNode); // adds a new node to the item linked list taking in the name of the item and the pointer to the first node of the linked list
listNode *sampleBoard();//hard codes values for the sample board so it can be displayed
int checkIfList(char str[], int size); //function that returns 1 if a string is a list and 0 if it isnt


int main(void)
{
  char ans;
  listNode *headNode = NULL;

  printf("Fill board with preset test data? (y/n): ");
    scanf("%c", &ans);
    fflush(stdin);
    if(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N'){
        printf("Invalid answer, please re-enter (y/n): ");
        scanf("%c", &ans);
        fflush(stdin);
    }
    else if(ans == 'y' || ans == 'Y')
        {
            headNode = sampleBoard();
            mainMenu(&headNode);
        }
    else
      {
        mainMenu(NULL);
      }


  puts("End of program\n\n");
  ascii();


  return 0;
}

void mainMenu(listNode **headNode)
{
  //system("cls");
  puts("Menu:\n"
    "1. Display Board\n"
    "2. Load board from a file\n"
    "3. Edit list\n"
    "4. Edit board\n"
    "5. Save board to a file\n"
    "6. Quit\n"
    "Enter your choice (1-6): ");

  char ans =' ';
  unsigned int choice;
  scanf("%u", &choice);
  fflush(stdin);

  while(choice != 6){
    switch(choice){

      case 1:
        if(headNode == NULL)
        {
          printf("\nNo board available to display.");
          printf("\nPress any key to return to main menu.\n");
          fflush(stdin);
          getc(stdin);
          mainMenu(headNode);
        }
        else{
        displayBoard(headNode);
        }

        break;

      case 2:
        if(headNode == NULL)
        {
          loadBoard();
        }
        else
        {
          printf("A board has already been loaded.\nWould you like to replace this board with the one from the file?(y/n)\n");
          scanf("%c", &ans);
          fflush(stdin);

          while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N')
          {
            printf("Invalid answer, please re-enter (y/n): ");
            scanf("%c", &ans);
            fflush(stdin);
          }
          if(ans == 'n' || ans == 'N')
          {
            printf("Type any key to return to the main menu.\n");
            getc(stdin);
            mainMenu(headNode);
          }
          else
          {
            loadBoard();
          }
        }
        break;

      case 3:
        if(headNode == NULL)
        {
          printf("\nNo lists to edit on the board.");
          printf("\nPress any key to return to main menu.\n");
          fflush(stdin);
          getc(stdin);
          mainMenu(headNode);
        }
        else{
          editList(headNode);
        }
        break;

      case 4:
        editBoard(headNode);
        break;

      case 5:
        saveBoard(headNode);
        break;

      default:
        printf("Invalid choice.\n");
        mainMenu(headNode);
        break;
    }
    scanf("%u", &choice);
  }
  if(choice > 6)
  {
    printf("\nInvalid input.");
    printf("\nPress any key to return to main menu.\n");
    fflush(stdin);
    getc(stdin);
    mainMenu(headNode);
  }
  else if(choice == 6)
  {
    ascii();
    exit(0);
  }
}

//function 1 - finished
void displayBoard(listNode **headNode)
{
  //system("cls");
  listNode *nodeToPrint = (*headNode);


 while(nodeToPrint != NULL)
  {
    printf("\n%s:", nodeToPrint->name);       // printing the name of the node

     itemNode *temp = nodeToPrint->firstItem; //setting temp value = to the pointer of the first node of the item linked list
     while(temp != NULL)                      // while there is a node in the item linked list this will continue to print it
     {
       printf("\n\t%s",temp->item);
       temp = temp->nextItem;
     }

    nodeToPrint = nodeToPrint->nextName;     // cycling throught the linked list
  }
 printf("\n\nPress any key to return to main menu.\n");
 fflush(stdin);
 getc(stdin);
 mainMenu(headNode); // returns to main menu
}

//function 3 - unfinished
void editList(listNode** headNode)
{
    unsigned int option; //user's chosen option from the menu
    char toEdit_list[50]; //user input of list to be edited
    listNode *tempListNode = (*headNode); //tempListNode initialised to the node inputed
    char ans; //for y/n questions

    //system("cls");

    printf("Enter the name of the list to edit or press enter to cancel: ");
    fgets(toEdit_list, sizeof(toEdit_list), stdin);
    toEdit_list[strcspn(toEdit_list, "\n")] = '\0'; //remove new line

    while (tempListNode != NULL && strcmp(tempListNode->name, toEdit_list) != 0) {
        tempListNode = tempListNode->nextName;
    }
    if(tempListNode == NULL){
        printf("\nNo list found.\n");
        printf("Press any key to return to main menu.\n");
        fflush(stdin);
        getc(stdin);
        mainMenu(headNode); //returns to main menu if no list found or inputted
    }

    //system("cls");

    printf("Selected list: %s\n\n", *tempListNode);

    puts("Options:\n"
      "1. Edit an item\n"
      "2. Add a new item\n"
      "3. Delete an item\n"
      "4. Return to main menu\n"
      "Enter your option (1-4): ");

    scanf("%u", &option);
    fflush(stdin);

    itemNode *tempItemNode = tempListNode->firstItem; //tempItemNode initialised to first item of the node inputted
    char itemName[50];
    char newName[50];

    while(option != 4){
        switch(option){
            case 1: //edit
                printf("Enter the name of the item to edit: \n");
                fgets(itemName, sizeof(itemName), stdin);
                itemName[strcspn(itemName, "\n")] = '\0'; //remove the new line

                while (tempItemNode != NULL && strcmp(tempItemNode->item, itemName) != 0) {
                    tempItemNode = tempItemNode->nextItem;
                }

                if(tempItemNode != NULL){
                    printf("\nSelected item: %s\n", tempItemNode->item);
                    printf("\nEnter new name for item '%s': \n", itemName);
                    fgets(newName, sizeof(newName), stdin);
                    newName[strcspn(newName, "\n")] = '\0';
                    strcpy(tempItemNode->item, newName); //replaces old item name with new name

                    printf("\nItem name changed successfully.\n");
                    printf("\nPress any key to return to main menu.\n");
                    fflush(stdin);
                    getc(stdin);
                    editList(headNode);
                }
                else{
                    printf("\nError locating inputed name.\n");
                    printf("\nPress any key to return to main menu.\n");
                    fflush(stdin);
                    getc(stdin);
                    editList(headNode);
                }
                break;

            case 2: //add
                printf("\nEnter the name of the new item: \n");
                fgets(itemName, sizeof(itemName), stdin);
                itemName[strcspn(itemName, "\n")] = '\0'; //remove the new line

                itemNode *headItemNode = tempItemNode;
                itemNode *currNode = headItemNode;
                currNode = getNewItem(itemName, headItemNode); //adds new item
                currNode = currNode->nextItem; //moves to next node so more items can be added

                printf("\nWould you like to add another item? (y/n): ");
                scanf("%c", &ans);
                fflush(stdin);

                if(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N'){
                   printf("\nInvalid answer, please re-enter (y/n): ");
                   scanf("%c", &ans);
                   printf("\n");
                   fflush(stdin);
                }

                while(ans == 'y' || ans == 'Y'){
                    printf("\nEnter the name of the new item: \n");
                    fgets(itemName, sizeof(itemName), stdin);
                    itemName[strcspn(itemName, "\n")] = '\0'; //remove the new line

                    currNode = getNewItem(itemName, headItemNode);
                    currNode = currNode->nextItem;

                    printf("\nWould you like to add another item? (y/n):\n");
                    scanf("%c", &ans);
                    fflush(stdin);

                    if(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N'){
                        printf("\nInvalid answer, please re-enter (y/n): ");
                        scanf("%c", &ans);
                        printf("\n");
                        fflush(stdin);
                    }
                }
                if(ans =='n' || ans == 'N'){
                    sleep(1);
                    editList(headNode);
                }
                break;

            case 3: //delete - input and loop works? first item is not deleted
                printf("\nEnter the name of the item to delete: ");
                fgets(itemName, sizeof(itemName), stdin);
                itemName[strcspn(itemName, "\n")] = '\0'; //remove the new line

                int match = 0;
                itemNode *currNode_Del = tempItemNode;
                tempItemNode = currNode_Del->nextItem;

                if(strcmp(currNode_Del->item, itemName) == 0){ //item to be deleted is the first node
                  if(currNode_Del->nextItem != NULL)
                    tempListNode->firstItem = currNode_Del->nextItem;

                    else
                      tempListNode->firstItem = NULL;

                  printf("\n\nItem deleted successfully.\n\n");
                  printf("\nPress any key to return to main menu.\n");
                  getchar();
                  match = 1;
                  editList(headNode);
                }
                else{
                  while(tempItemNode != NULL){ //while the next node is not null
                    if(strcmp(tempItemNode->item, itemName) == 0){ //if the next node is the node to be deleted
                      if(tempItemNode->nextItem != NULL){ //if there is a node after the one we want to delete
                        currNode_Del->nextItem = tempItemNode->nextItem;
                      }
                      currNode_Del = currNode_Del->nextItem;
                      tempItemNode = currNode_Del->nextItem;
                    }
                  }
                }

                if(match == 0){ //if node to be deleted was not found
                    printf("\nItem could not be found.\n");
                    printf("\nPress any key to return to main menu.\n");
                    getc(stdin);
                }

                editList(headNode);
                break;

            default: //invalid input
                puts("Invalid option, please re-enter.\n");

                break;
      }
      scanf("%u", &option);
      printf("\n\n");
    }
    if(option == 4){
      mainMenu(headNode);
    }
    else{
      puts("Invalid option, please re-enter.\n");
      mainMenu(headNode);
    }
}

//function 4 - finished
void editBoard(listNode **headNode)
{
    unsigned int option;
    char tempStr[50]; //temporary string to read user input
    listNode *tempNode = (*headNode); //tempNode initialised to the node inputed
    char ans;

    //system("cls");

    puts("Options:\n"
      "1. Edit the name of a list\n"
      "2. Add a new list\n"
      "3. Delete a list\n"
      "4. Return to main menu\n"
      "Enter your option (1-4): ");

    scanf("%u", &option);
    fflush(stdin);

    while(option != 4){
      switch(option){

        case 1:
            printf("Enter the name of the list to edit: \n");
            fgets(tempStr, sizeof(tempStr), stdin);
            tempStr[strcspn(tempStr, "\n")] = '\0'; //remove the new line

            while (tempNode != NULL && strcmp(tempNode->name, tempStr) != 0) { //while the name doesn tmatch and the node isnt null loop to the next node
                tempNode = tempNode->nextName;
            }

            if (tempNode != NULL) { //if it is not null change the name
                printf("\nEnter new name for list '%s': \n", tempNode);
                fgets(tempNode->name, sizeof(tempNode->name), stdin);
                tempNode->name[strcspn(tempNode->name, "\n")] = '\0'; //remove the new line

                printf("\nList name changed successfully.\n");
                printf("\nPress any key to return to main menu.\n");
                fflush(stdin);
                getc(stdin);
                editBoard(headNode);
            } else { // otherwise the name does not exist and return to the editboard menu
                printf("\nError locating inputed name.\n");
                printf("\nPress any key to return to main menu.\n");
                fflush(stdin);
                getc(stdin);
                editBoard(headNode);
            }
            break;

        case 2:
          printf("\nEnter the name of the list you would like to add:\n");
          fgets(tempStr, sizeof(tempStr), stdin);
          tempStr[strcspn(tempStr, "\n")] = '\0'; //remove the new line

          tempNode  = getNewPerson(tempStr, (*headNode)); //creates a new node with the name inputed

          printf("\nWould you like to add items to this list? (y/n):\n");//prompts user if they want to add items to inputed lists
          scanf("%c", &ans);
          fflush(stdin);

          if(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N'){ //invalid input handling
              printf("\nInvalid answer, please re-enter (y/n): ");
              scanf("%c", &ans);
              fflush(stdin);
          }
          else if(ans == 'y' || ans == 'Y')
              {
                printf("\nEnter the name of the item you would like to add: \n");
                fgets(tempStr, sizeof(tempStr), stdin);
                tempStr[strcspn(tempStr, "\n")] = '\0'; //remove the new line

                itemNode *headItemNode = getNewItem(tempStr, NULL); //creating new item node
                itemNode *currNode = headItemNode;
                tempNode->firstItem = headItemNode; //setting the first item of the node to the item node

                currNode = currNode->nextItem;

                printf("\nWould you like to add another item?(y/n)\n");
                scanf("%c", &ans);
                fflush(stdin);

                  if(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N') // invalid input handling
                    {
                        printf("\nInvalid answer, please re-enter (y/n): ");
                        scanf("%c", &ans);
                        fflush(stdin);
                    }

                    while(ans == 'y' || ans == 'Y')
                      {
                        printf("\nEnter the name of the item you would like to add: \n");
                        fgets(tempStr, sizeof(tempStr), stdin);
                        tempStr[strcspn(tempStr, "\n")] = '\0'; //remove the new line

                        currNode = getNewItem(tempStr, headItemNode); //adding the new item
                        currNode = currNode->nextItem;

                        printf("\nWould you like to add another item?(y/n)\n");
                        scanf("%c", &ans);
                        fflush(stdin);

                          if(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N')
                            {
                                printf("Invalid answer, please re-enter (y/n): ");//invalid input handling
                                scanf("%c", &ans);
                                fflush(stdin);
                            }
                      }
                    if(ans =='n' || ans == 'N')
                     {
                        printf("Returning to menu...");
                        sleep(1);
                        editBoard(headNode); //returning to editboard menu
                     }

              }
          break;

        case 3:
          printf("Enter the name of the list to delete: ");
          fgets(tempStr, sizeof(tempStr), stdin);
          tempStr[strcspn(tempStr, "\n")] = '\0'; //remove the new line

          int match = 0;//variable to track if a list has been deleted
          listNode *currNode = tempNode;
          tempNode = currNode->nextName;

          if (strcmp(currNode->name,tempStr) == 0) //if the first node is the list you want to delete
           {
              (*headNode) = (*headNode)->nextName;
              printf("\n\n DELETED SUCCESSFULLY\n\n");
              printf("\nPress any key to return to main menu.\n");
              getchar();
              match = 1;
           }
        else {
              while (tempNode != NULL) //while the next node is not null
              {
                  if (strcmp(tempNode->name, tempStr) == 0) { //if the following node is the node to delete
                      if (tempNode->nextName != NULL) // if there is a node after the node we want to delete
                      {
                          currNode->nextName = tempNode->nextName;
                      }
                      else
                      {
                          currNode->nextName = NULL; //if there is no node set it to null
                      }
                      printf("\n\n DELETED SUCCESSFULLY\n\n");
                      printf("\nPress any key to return to main menu.\n");
                      getc(stdin);
                      match = 1;
                      break;
                  }
                  currNode = currNode->nextName;
                  tempNode = currNode->nextName;
              }
            }

          if (match == 0) {
              printf("\nError locating inputed list.\n");
              printf("\nPress any key to return to main menu.\n");
              getc(stdin);
              editList(headNode);
          }

          editList(headNode); ///gooes back to the editboard functoin

          break;


        default:
          puts("Invalid option.\n");

          puts("Options:\n"
            "1. Edit the name of a list\n"
            "2. Add a new list\n"
            "3. Delete a list\n"
            "4. Return to main menu\n"
            "Enter your option (1-4): ");
             break;
      }
      scanf("%u", &option);
      fflush(stdin);
    }

    if(option == 4)
    mainMenu(headNode);
}

//function 2 - finished
void loadBoard()
{
  FILE *fPtr; // file pointer
  char fileName[50]; // used to get the file name from the user
  char tempStr[50]; //used to read values from the file
  int firstNameCheck = 0; // variable to check if the current name is the first name in the list.
  int prevNodeItemCheck = 0; //variable that checks if the previous node was an item
  listNode *tempListNode = NULL;
  itemNode *tempItemNode = NULL;
  listNode *headNode = NULL;
  itemNode *headItemNode = NULL;

  printf("Enter the name of the file you want to load:\n");
  fgets(fileName, sizeof(fileName), stdin);
  fileName[strcspn(fileName, "\n")] = '\0'; //remove the new line

  fPtr = fopen(fileName, "r");
  if(fPtr == NULL){ //if the file could not be opened display an error message and return to main menu
    printf("\nFile could not be opened.\nPress any key to return to main menu.\n");
    getc(stdin);
    mainMenu(&headNode);
    exit(1);
  } else { //else load from the file
     while(!feof(fPtr))
    {
       memset(tempStr, '\0', sizeof(tempStr));//resets the string values
      fgets(tempStr, 50, fPtr);
      int i = 0;

      if(checkIfList(tempStr, sizeof(tempStr)) == 0){ //if the first character is a tab that means that the line is an item
       for (i = 0; tempStr[i+1] != '\0'; i++)
       {
          tempStr[i] = tempStr[i+1];//removes the \t at the beginning of an item
          if(tempStr[i] == '\n')
          tempStr[i] = '\0';

       }

        tempStr[i] = '\0'; //sets the last charcter to null

        if(prevNodeItemCheck == 0){ //if the previous line read was a list
          prevNodeItemCheck = 1;

          headItemNode = getNewItem(tempStr, NULL); //head item node is set to a new item node
          tempListNode->firstItem = headItemNode; //the current list nodes first item is set to the new head item node

        } else {
          tempItemNode = getNewItem(tempStr, headItemNode);
        }

      } else { //otherwise it will be the list name
         while(tempStr[i] != '\0'){
            if(tempStr[i] == ':')
            tempStr[i] = '\0'; //removing the semi coloun

            if(tempStr[i] == '\n')
            tempStr[i] = '\0';

            i++;
         }
        tempListNode = getNewPerson(tempStr, headNode); //adding a new node to the linked list

         if(!firstNameCheck){
         headNode = tempListNode; //if itsthe first name set the headnode pointer to that name
         firstNameCheck = 1;}

         prevNodeItemCheck = 0;
         headItemNode == NULL;
       }

    }
    fclose(fPtr);
    printf("\n\t BOARD SUCCESSFULLY LOADED\n\nPress any key to return to main menu.\n");
    getc(stdin);
    mainMenu(&headNode); // returns to main menu
  }

}

//function 5 - finished
void saveBoard(listNode **headNode)
{
    //system("cls");

    FILE* file; //file pointer
    char filename[50]; //user input to name the file

    printf("Enter filename (if this filename already exists its contents will be overwritten): \n");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    file = fopen(filename, "wb"); //creates or overwrites filename
    if(file == NULL){
        printf("\nError creating file.\n"); //error handling for if the file was not created
        printf("\nPress any key to return to main menu.\n");
        fflush(stdin);
        getc(stdin);
        mainMenu(headNode); //returns to main menu
    }
    else{
        printf("\n%s created, saving board to file ...\n", filename);
    }

    listNode *nodeToSave = (*headNode); //initialises node to the inputted node

    while(nodeToSave != NULL){
        fprintf(file, "%s:\n", nodeToSave->name); //prints name of list

        itemNode *temp = nodeToSave->firstItem; //pointer to the first item of the list
        while(temp != NULL){
            if(temp->nextItem == NULL && nodeToSave->nextName == NULL){ //for last item of last list so file has no empty line
                fprintf(file, "\t%s", temp->item); //prints last item of list
                temp = temp->nextItem; //moves to next item node to end while loop
            }
            else{
                fprintf(file, "\t%s\n", temp->item); //prints items of list
                temp = temp->nextItem; //moves to next item node to print next item/list name
            }
        }
        nodeToSave = nodeToSave->nextName; //moves to next list once all items of a list printed
    }
    fclose(file); //closes file
    printf("\nCurrent board saved to %s.\n", filename);
    printf("\nPress any key to return to main menu.\n");
    fflush(stdin);
    getc(stdin);
    mainMenu(headNode); //returns to main menu
}

//function to add a new person to a the board - semi-finished
listNode *getNewPerson(const char *nameToInput, listNode *headlistNode)
{
    listNode *newPerson = NULL; //initialising pointer for the new person
    listNode *temp = headlistNode; //temp struct to add nodes to the end of the linked list

    newPerson = malloc(sizeof(listNode)); //allocating memory for the new person
    newPerson->firstItem = NULL; // setting the first item pointer to null
    newPerson->nextName = NULL; // setting the nextname to null

    strcpy(newPerson->name, nameToInput); // setting the name string in the struct to the name inputed

    if(headlistNode == NULL)
    return newPerson;

    while(temp->nextName != NULL) //while we are not at the end of the linked list cycle to the next name in the list
    temp = temp->nextName;

    if(temp->nextName == NULL) //fi we reach the end of the linked list add the new person
    temp->nextName = newPerson;


    return newPerson; // returning the pointer to the struct
}

//function to add a new item to a name - semi-finished
itemNode *getNewItem(const char *itemToInput, itemNode *headItemNode)
{
    itemNode *newItem = NULL; //initialising pointer for the new utem
    itemNode *temp = headItemNode; //temp struct to add nodes to the end of the linked list

    newItem = malloc(sizeof(itemNode)); //allocating memory for the new item
    newItem->nextItem = NULL; // setting the next item to null

    strcpy(newItem->item, itemToInput); // setting the name string in the struct to the name inputed

    if(headItemNode == NULL)// if there are no previous nodes return the new node
    return newItem;

    while(temp->nextItem != NULL) //while we are not at the end of the linked list cycle to the next name in the list
    temp = temp->nextItem;

    if(temp->nextItem == NULL) //fi we reach the end of the linked list add the new person
    temp->nextItem = newItem;

    return newItem; // returning the pointer to the first node
}

//function which returns a pointer to the first node for the sample board and hard codes a linked list -unfinished
listNode *sampleBoard()
{
   listNode *headNode = getNewPerson("Nick", NULL);
   headNode->firstItem = getNewItem("3070 RTX", NULL);

   listNode *templistNode = getNewPerson("Tim", headNode);
   templistNode->firstItem = getNewItem("Oculus Quest 2", NULL);

   templistNode = getNewPerson("Dante", headNode);
   templistNode->firstItem = getNewItem("Oculus Quest 1", NULL);
   itemNode *tempItemNode = getNewItem("3070 RTX", templistNode->firstItem);

   templistNode = getNewPerson("Abey", headNode);
   templistNode->firstItem = getNewItem("Oculus Pro", NULL);
   tempItemNode = getNewItem("Oculus Quest 1", templistNode->firstItem);

   return headNode;
}

int checkIfList(char str[], int size)
{
  for(int i = 0;i < size; i++)
  {
    if(str[i] == ':')
    return 1;
  }
  return 0;
}

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
       "  \\,,/ \\../   \\..\\../ \n");
}
