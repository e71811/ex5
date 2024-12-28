/// need to write my name here ---------------
/////
/////
/////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Done 4

typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;

void addPlayList();
void  watchPlayList();
void printMenu();
void buildArrayOfPlayLists( Playlist** playlists,int *howManyPlaylists);
void printPlayListMenu(int howManyPlaylists,Playlist** playlists,int menuIndex,char mainMenu[]);


int main() {
    printMenu();
    int menuChoice=0;
    int howManyPlaylists=0;
    char *playListName = NULL;
     Playlist* playlists = NULL;
    scanf("%d", &menuChoice);
    while(menuChoice!=Done)
    {
        switch(menuChoice)
        {
        case 1:{
                char menu[]="Back to main menu\n";
               watchPlayList(menu,howManyPlaylists,&playlists);
                break;
        }
        case 2:
            {

                addPlayList(&playListName,&playlists,&howManyPlaylists);
                break;
            }
        }
        printMenu();
        scanf("%d", &menuChoice);
    }
    printf("Goodbye!");

}




void  watchPlayList(char mainMenu[],int howManyPlaylists,Playlist **playlists)
{
    int choice;
    int menuIndex = howManyPlaylists+1;
  printf("Choose a playlist:\n");
  // i check if there is a playlist available
  if(howManyPlaylists==0)
   {
       printf("1. %s",mainMenu);
   }else
   {
       printPlayListMenu(howManyPlaylists,playlists,menuIndex,mainMenu);
       scanf("%d",&choice);
       while(choice!=6)
       {

           switch(choice)
           {
           case 1:
               {

               }
           case 2:
               {

               }
           case 3:
               {

               }
           case 4:
               {

               }
           case 5:
               {

               }
               default:
               {
                   choice =6;
               }

           }
           scanf("%d",&choice);
   }
       return;
    }
}

void addPlayList( char **playListName, Playlist** playlists,int *howManyPlaylists )
{
    char c = '1';
    int length=0;
    char *tempP=NULL;
    printf("Enter playlist's name:\n");
    // because the buffer might hold \n that i dont want to, so i use getchar()
    getchar();

    // firstly i allocate a one size char slot for the name
    *playListName = malloc(sizeof(char));
    // checks if malloc succeeded
    if (*playListName == NULL) {
        printf("failed to allocate memory");
        return;
    }

    while (c!='\n')
    {
        c=getchar();
        length++;
        tempP= realloc(*playListName,(length+1) * sizeof(char));

        if(tempP==NULL)
        {
            printf("failed to allocate memory");
            free(*playListName);
            playListName=NULL;
            return;
        }

        *playListName= tempP;
        (*playListName)[length-1]=c;
    }
    // Add null terminator
    (*playListName)[length]='\0';
    // i check if the user did add a name if yes the go to build the new array
    if (length > 0) {
        buildArrayOfPlayLists(playlists, howManyPlaylists);

        //set the name in the new playlist
        (*playlists)[*howManyPlaylists - 1].name=malloc(length*sizeof(char));
        if ((*playlists)[*howManyPlaylists - 1].name == NULL) {
            printf("failed to allocate memory for playlist name");
            // Cleanup if name allocation failed
            (*howManyPlaylists)--;
            return;
        }
        strcpy((*playlists)[*howManyPlaylists - 1].name,*playListName);
    }
}

void buildArrayOfPlayLists( Playlist** playlists,int *howManyPlaylists)
{
    Playlist* temp = NULL;
    //update this variable
    (*howManyPlaylists)++;


    temp = realloc(*playlists,*howManyPlaylists * sizeof(Playlist));
    if(temp==NULL)
    {
        printf("failed to allocate memory");
        // if we failed to realloc then we didnt realy add a playlist
        (*howManyPlaylists)--;
        return;
    }
    *playlists=temp;
    // set all the playlist variables to 0/NULL
    (*playlists)[*howManyPlaylists-1].name=NULL;
    (*playlists)[*howManyPlaylists-1].songs=NULL;
    (*playlists)[*howManyPlaylists-1].songsNum=0;

}
void printPlayListMenu(int howManyPlaylists,Playlist** playlists,int menuIndex,char mainMenu[])
{
    // i printf the names of the playlist and at the end print the main menu option
    for (int i = 0; i < howManyPlaylists; i++)
    {
        printf("%d. %s\t\n", i + 1, (*playlists)[i].name);
    }
    printf("%d. %s\t\n",menuIndex,mainMenu);
}






void deleteSong() {

    printf("Song deleted successfully.\n");
}



void playSong() {
    
}



void freeSong() {

}

void freePlaylist() {
    
}





void sortPlaylist() {
    
    printf("sorted\n");
}


void printMenu()
{
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}



