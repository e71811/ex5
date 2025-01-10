/******************
Name:ilay hefgot
ID:212398648
Assignment:ex5
*******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLOSE_PROGRAM 4
#define RETURN_MENU 6
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

void addPlayList(char **playListName, Playlist** playlists,int *howManyPlaylists);
void  watchPlayList(char mainMenu[],int howManyPlaylists,Playlist **playLists,char **songDetail);
void printMenu();
void buildArrayOfPlayLists( Playlist** playlists,int *howManyPlaylists);
void printPlayListMenu(int howManyPlaylists,Playlist** playlists,int menuIndex,char mainMenu[]);
void  printPlayListOptions();
void getInfoAboutSong(Playlist **playLists,char **songDetail,int playListChoice);
void buildArrayOfSongs( int playListChoice,Playlist **playlists);
char* getString();
void sort(int choice,int playListChoice,Playlist **playlist);
void sortByYear(int playListChoice,Playlist **playList);
void sortAlphabetically(int playListChoice,Playlist **playList);
void sortByStreamAscending(int playListChoice,Playlist **playList);
void sortByStreamDescending(int playListChoice,Playlist **playList);
void sortPlaylist();
void deleteSong(int songDelete,Playlist **playlist,int playListChoice);
void removePlayList(int *howManyPlaylists,Playlist **playLists,char menu[]);
void freeAll(int *howManyPlaylists,Playlist **playLists);
int main() {
    printMenu();
    int menuChoice=0;
    int howManyPlaylists=0;
    char *playListName = NULL;
    char *songDetail = NULL;
     Playlist* playlists = NULL;
    scanf("%d", &menuChoice);
    //main menu switch cases
    while(menuChoice!=CLOSE_PROGRAM)
    {
        switch(menuChoice)
        {
        case 1:{
                char menu[]="Back to main menu\n";
                watchPlayList(menu,howManyPlaylists,&playlists,&songDetail);
                break;
        }
        case 2:
            {
                addPlayList(&playListName,&playlists,&howManyPlaylists);
                break;
            }
        case 3:
            {
                char menu[]="Back to main menu\n";
                removePlayList(&howManyPlaylists,&playlists,menu);
                break;
            }

        }
        printMenu();
        scanf("%d", &menuChoice);
    }
    freeAll(&howManyPlaylists,&playlists);
    printf("Goodbye!\n");

}

void watchPlayList(char mainMenu[],int howManyPlaylists,Playlist **playLists,char **songDetail)
{
    int songChoice;
    int menuChoice;
    int playListChoice;
    int menuIndex = howManyPlaylists+1;
    printf("Choose a playlist:\n");
    printPlayListMenu(howManyPlaylists, playLists, menuIndex, mainMenu);

    scanf("%d",&playListChoice);
    // if the user types back to the main menu i want to exit the function
    while(playListChoice!=menuIndex)
    {
        if(playListChoice > 0 && playListChoice <= howManyPlaylists)
        {
            printf("playlist %s:\n", (*playLists)[playListChoice-1].name);
            printPlayListOptions();
            scanf("%d",&menuChoice);

            while(menuChoice!=RETURN_MENU)
            {
                switch(menuChoice)
                {
                    case 1:
                    {
                        // i check if there is a song in the playlist
                        if((*playLists)[playListChoice-1].songsNum==0)
                        {
                            printf("choose a song to play, or 0 to quit:\n");
                            int c=0;
                            scanf("%d",&c);
                            c=0;
                            break;
                        }
                        else
                        {
                            int x=1;
                            Song **temp=(*playLists)[playListChoice-1].songs;
                            while (x<=(*playLists)[playListChoice-1].songsNum)
                            {
                                printf("%d. Title: %s\n   Artist: %s\n   Released: %d\n   Streams: %d\n",
                                    x,temp[x-1]->title,temp[x-1]->artist,temp[x-1]->year,temp[x-1]->streams);
                                x++;
                            }
                            printf("\nchoose a song to play, or 0 to quit:\n");
                            scanf("%d",&songChoice);
                            while(songChoice!=0)
                            {
                                printf("Now playing %s:\n",(*playLists)[playListChoice-1].
                                    songs[songChoice-1]->title);
                                printf("$ %s $\n\n",(*playLists)[playListChoice-1].songs[songChoice-1]->lyrics);
                                (*playLists)[playListChoice-1].songs[songChoice-1]->streams=
                                (*playLists)[playListChoice-1].songs[songChoice-1]->streams+1;
                                printf("choose a song to play, or 0 to quit:\n");

                                scanf("%d",&songChoice);
                            }
                            break;
                        }
                    }
                    case 2:
                    {
                        getInfoAboutSong(playLists,songDetail,playListChoice);
                        break;
                    }
                    case 3:
                    {
                        int x=1;
                        Song **temp=(*playLists)[playListChoice-1].songs;
                        int songDelete;
                        while (x<=(*playLists)[playListChoice-1].songsNum)
                        {
                            printf("%d. Title: %s\n   Artist: %s\n   Released: %d\n   Streams: %d\n",x
                                ,temp[x-1]->title,temp[x-1]->artist,temp[x-1]->year,temp[x-1]->streams);
                            x++;
                        }
                        printf("choose a song to delete, or 0 to quit:\n");
                        scanf("%d",&songDelete);
                        if(songDelete==0)
                        {
                            break;
                        }
                        deleteSong(songDelete,playLists,playListChoice);
                        break;
                    }
                    case 4:
                    {
                        int choice;
                        printf("choose:\n1. sort by year\n2. sort by streams - ascending order\n"
                            "3. sort by streams - descending order\n4. sort alphabetically\n");
                        scanf("%d",&choice);
                        sort(choice,playListChoice,playLists);
                        sortPlaylist();
                        break;
                    }
                    case 5:
                    {
                        int i=0;
                        while(i<(*playLists)[playListChoice-1].songsNum)
                        {
                            printf("Now playing %s:\n",(*playLists)[playListChoice-1].songs[i]->title);
                            printf("$ %s $\n",(*playLists)[playListChoice-1].songs[i]->lyrics);
                            (*playLists)[playListChoice-1].songs[i]->streams=
                              (*playLists)[playListChoice-1].songs[i]->streams+1;
                            i++;

                        }
                        break;
                    }
                    case 6:
                    {
                        return;
                    }
                }
                printPlayListOptions();
                scanf("%d",&menuChoice);
            }
        }
        else
        {
            printf("Invalid playlist choice\n");
        }

        printf("Choose a playlist:\n");
        printPlayListMenu(howManyPlaylists, playLists, menuIndex, mainMenu);
        scanf("%d",&playListChoice);
    }
}
void getInfoAboutSong(Playlist **playLists,char **songDetail,int playListChoice)
{
    printf("Enter song's details\nTitle:\n");
    // clear the buffer
    getchar();
    *songDetail = getString();
    if (*songDetail == NULL) {
        printf("malloc failed");
        exit(1);
    }
    buildArrayOfSongs(playListChoice,playLists);
    // create a playlist pointer which points to the specific playlist place
    Playlist *playlist = *playLists + (playListChoice - 1);
    // create a song pointer which points to the playlist song array
    Song *newSong = playlist->songs[playlist->songsNum - 1];
    newSong->title = *songDetail;
    printf("Artist:\n");
    *songDetail = getString();
    if (*songDetail == NULL) {
        printf("malloc failed");
        exit(1);
    }
    newSong->artist = *songDetail;
    printf("Year of release:\n");
    // beacause the year is a int i dont want to use getstring function
    int year;
    if (scanf("%d", &year) != 1) {
        printf("wrong input\n");
        return;
    }
    getchar(); // clean buffer after year input
    newSong->year = year;
    printf("Lyrics:\n");
    *songDetail = getString();
    if (*songDetail == NULL) {
        printf("malloc failed");
        exit(1);
    }
    newSong->lyrics = *songDetail;
    newSong->streams = 0; // Initialize streams to 0 because still no one watched it

}
void sort(int choice,int playListChoice,Playlist **playlist)
{
    // sort by year
    if(choice==1)
    {
      sortByYear(  playListChoice-1,playlist);
        return;
    }
    // sort by streams - ascending order
    if(choice==2)
    {
      sortByStreamAscending(  playListChoice-1,playlist);
        return;
    }
    //  sort by streams - ascending order
    if(choice==3)
    {
        sortByStreamDescending( playListChoice-1,playlist);
        return;
    }
    // sort alphabetically
    if(choice==4)
    {
        sortAlphabetically( playListChoice-1,playlist);
        return;
    }
    // in case an invalid option were chosen do the default sort
    sortAlphabetically( playListChoice-1,playlist);

}
void sortByYear(int playListChoice,Playlist **playList)
{
    // pointer that points to the array of pointers
    Song **songs = (*playList)[playListChoice].songs;
    for (int i = 0; i <  (*playList)[playListChoice].songsNum; i++) {
        for (int j = 0; j < (*playList)[playListChoice].songsNum - i - 1; j++) {
            if (songs[j]->year > songs[j + 1]->year) {
                Song *temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
        }

    }
}
void sortByStreamAscending( int playListChoice,Playlist **playList )
{
    // pointer that points to the array of pointers
    Song **songs = (*playList)[playListChoice].songs;
    for (int i = 0; i <  (*playList)[playListChoice].songsNum; i++) {
        for (int j = 0; j < (*playList)[playListChoice].songsNum - i - 1; j++) {
            if (songs[j]->streams > songs[j + 1]->streams) {
                Song *temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
        }

    }
}
void sortByStreamDescending( int playListChoice,Playlist **playList )
{
    // pointer that points to the array of pointers
    Song **songs = (*playList)[playListChoice].songs;
    for (int i = 0; i <  (*playList)[playListChoice].songsNum; i++) {
        for (int j = 0; j < (*playList)[playListChoice].songsNum - i - 1; j++) {
            if (songs[j]->streams < songs[j + 1]->streams) {
                Song *temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
        }

    }
}
void sortAlphabetically( int playListChoice,Playlist **playList )
{
    // pointer that points to the array of pointers
    Song **songs = (*playList)[playListChoice].songs;
    for (int i = 0; i <  (*playList)[playListChoice].songsNum; i++) {
        for (int j = 0; j < (*playList)[playListChoice].songsNum - i - 1; j++) {
            //strcmp compares between 2 strings and checks who has the bigger value by asci values
            if (strcmp(songs[j]->title, songs[j + 1]->title) > 0) {
                Song *temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
        }
    }
}
void addPlayList( char **playListName, Playlist** playlists,int *howManyPlaylists )
{
    char c ;
    int length=0;
    char *tempP=NULL;
    printf("Enter playlist's name:\n");
    // because the buffer might hold \n that i dont want to, so i use getchar()
    getchar();

    // firstly i allocate a one size char slot for the name
    *playListName = malloc(sizeof(char));
    // checks if malloc succeeded
    if (*playListName == NULL) {
        printf("malloc failed");
        exit(1);
    }

    while ((c=getchar()) !='\n'&& c !='\r')
    {
        length++;
        tempP= realloc(*playListName,(length+1) * sizeof(char));

        if(tempP==NULL)
        {
            free(*playListName);
            *playListName=NULL;
            printf("malloc failed");
            exit(1);
        }

        *playListName= tempP;
        (*playListName)[length-1]=c;
    }
    // Add null terminator
    (*playListName)[length]='\0';
    // i check if the user did add a name if yes then go to build the new array
    if (length > 0) {
        buildArrayOfPlayLists(playlists, howManyPlaylists);

        //set the name in the new playlist (the plus one to the length is because i need room for \0)
        (*playlists)[*howManyPlaylists - 1].name=malloc((length+1)*sizeof(char));
        if ((*playlists)[*howManyPlaylists - 1].name == NULL) {
            // Cleanup if name allocation failed
            (*howManyPlaylists)--;
            printf("malloc failed");
            exit(1);
        }
        strcpy((*playlists)[*howManyPlaylists - 1].name,*playListName);

    }
    //after playlistname is used free it
    free(*playListName);
}
void buildArrayOfPlayLists( Playlist** playlists,int *howManyPlaylists)
{
    Playlist *temp = NULL;
    //update this variable
    (*howManyPlaylists)++;


    temp = realloc(*playlists,*howManyPlaylists * sizeof(Playlist));
    if(temp==NULL)
    {
        // if we failed to realloc then we didnt really add a playlist
        (*howManyPlaylists)--;
        printf("malloc failed");
        exit(1);
    }
    *playlists=temp;
    // set all the playlist variables to 0/NULL
    (*playlists)[*howManyPlaylists-1].name=NULL;
    (*playlists)[*howManyPlaylists-1].songs=NULL;
    (*playlists)[*howManyPlaylists-1].songsNum=0;

}
void buildArrayOfSongs(int playListChoice,Playlist **playlists)
{
    //update how much songs to the specific playlist
    (*playlists)[playListChoice-1].songsNum=  (*playlists)[playListChoice-1].songsNum+1;
    //reallocate a new array of songs for the specific playlist
    Song **temp = realloc((*playlists)[playListChoice-1].songs,
        (*playlists)[playListChoice-1].songsNum * sizeof(Song*));
    if(temp==NULL)
    {
        // if we failed to reallocate then we didn't really add a song
        (*playlists)[playListChoice-1].songsNum= (*playlists)[playListChoice-1].songsNum-1;
        printf("malloc failed");
        exit(1);
    }
    // after a successful creation of a song i create a array of song pointers
   (*playlists)[playListChoice-1].songs=temp;
   //i allocate song worth of data in the specific place in the array
   (*playlists)[playListChoice-1].songs[(*playlists)[playListChoice-1].songsNum-1]=malloc(sizeof(Song));
    // check if malloc failed
    if ((*playlists)[playListChoice - 1].songs[(*playlists)[playListChoice-1].songsNum-1] == NULL) {
        printf("malloc failed");
        (*playlists)[playListChoice - 1].songsNum--;
        // this will remove all we did above if we malloc failed
        (*playlists)[playListChoice - 1].songs = realloc(
           (*playlists)[playListChoice - 1].songs,
           (*playlists)[playListChoice - 1].songsNum * sizeof(Song *));
    }
}
void printPlayListMenu(int howManyPlaylists,Playlist** playlists,int menuIndex,char mainMenu[])
{

    // i check if there is a playlist available
    if(howManyPlaylists==0)
    {
        printf("\t1. %s",mainMenu);

    }else
    {
        // i printf the names of the playlist and at the end print the main menu option
        for (int i = 0; i < howManyPlaylists; i++)
        {
            printf("\t%d. %s\n", i + 1, (*playlists)[i].name);
        }
        printf("\t%d. %s",menuIndex,mainMenu);



    }

}
void  printPlayListOptions()
{
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. exit\n");
}
void deleteSong(int songDelete,Playlist **playlist,int playListChoice)
{
   //i get access to the specific song array
    Song **songs = (*playlist)[playListChoice-1].songs;
    int numSongs = (*playlist)[playListChoice-1].songsNum;


    Song *songToDelete = songs[songDelete-1];
    free(songToDelete->title);
    free(songToDelete->artist);
    free(songToDelete->lyrics);
    free(songToDelete);

    // move all the songs pointers one slot left
    for (int i = songDelete-1; i < numSongs-1; i++) {
        songs[i] = songs[i+1];
    }

    // update number of songs for the specific playlist
    (*playlist)[playListChoice-1].songsNum--;

    // because now i have array with one slot empty i want to make a smaller array
    Song **newSongs = realloc(songs, sizeof(Song*) * (numSongs-1));
    if (newSongs == NULL && numSongs-1 != 0) {
        printf("malloc failed");
        exit(1);
    }
    (*playlist)[playListChoice-1].songs = newSongs;
    printf("Song deleted successfully.\n");
}
void removePlayList(int *howManyPlaylists,Playlist **playLists,char mainMenu[])
{
    int menuIndex = (*howManyPlaylists)+1;
    int deletePlayList;
    printf("Choose a playlist:\n");
    printPlayListMenu(*howManyPlaylists, playLists, menuIndex, mainMenu);
    scanf("%d",&deletePlayList);

    // i check if the user typed back to main menu
    if(deletePlayList==menuIndex)
    {
        return;
    }

    // because the user will choose between 1 - infinite and not from 0
    deletePlayList--;
    if((*playLists)[deletePlayList].songsNum>0)
    {
        int numberOfSongs = (*playLists)[deletePlayList].songsNum;
        // for loop that will free each individual song struct
        for (int i=0;i<numberOfSongs;i++)
        {
            free((*playLists)[deletePlayList].songs[i]->title);
            free((*playLists)[deletePlayList].songs[i]->artist);
            free((*playLists)[deletePlayList].songs[i]->lyrics);
            //after freeing all the variables of the song i can now free the song itself
            free((*playLists)[deletePlayList].songs[i]);
        }
        // free the songs array and playlist name
        free((*playLists)[deletePlayList].songs);
        free((*playLists)[deletePlayList].name);


    }else
    {
        //because the user hasn't added a single song to this playlist i want to only free the name of playlist
        free((*playLists)[deletePlayList].name);

    }
    // now i need to move all the playlists in the array one slot left
    for(int i = deletePlayList; i < *howManyPlaylists - 1; i++) {
        (*playLists)[i] = (*playLists)[i + 1];
    }
    // one less playlist
    (*howManyPlaylists)--;
    // now i realloc the size of the array because it has one slot empty
    Playlist *temp = realloc(*playLists, (*howManyPlaylists ) * sizeof(Playlist));
    if (temp == NULL && *howManyPlaylists > 0) {
        printf("malloc failed");
        exit(1);
    }
     *playLists = temp;

    printf("Playlist deleted.\n");
}
void freeAll(int *howManyPlaylists,Playlist **playLists)
{
    // for loop which goes on all the playlists and free all the songs in the songs array including the array
    for (int i=0;i<*howManyPlaylists;i++)
    {
        int numberOfSongs = (*playLists)[i].songsNum;
        // for loop that will free each individual song struct
        for (int j=0;j<numberOfSongs;j++)
        {
            free((*playLists)[i].songs[j]->title);
            free((*playLists)[i].songs[j]->artist);
            free((*playLists)[i].songs[j]->lyrics);
            //after freeing all the variables of the song i can now free the song itself
            free((*playLists)[i].songs[j]);
        }
        // free the songs array and playlist name
        free((*playLists)[i].songs);
        free((*playLists)[i].name);

    }
    //after i freed all the playlist variables i can free the array of playlists
    free(*playLists);

}
void sortPlaylist() {

    printf("sorted\n");
}
void printMenu()
{
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}
char* getString()
{
    char c ;
    int length=0;
    char *tempP=NULL;
    // firstly i allocate a one size char slot for the name
    char *songDetail = malloc(sizeof(char));
    // checks if malloc succeeded
    if (songDetail == NULL) {
        printf("malloc failed");
        exit(1);
    }

    c = getchar(); // Read the first character
    if (c != '\n' && c != '\r')
    {
        // If it's not just an empty line
        length = 1;
        // Store the first character
        songDetail[0] = c;
    }
    while ((c=getchar()) !='\n'&& c !='\r')
    {
        length++;
        tempP= realloc(songDetail,(length+1) * sizeof(char));
        if(tempP==NULL)
        {
            free(songDetail);
            printf("malloc failed");
            exit(1);
        }
        songDetail= tempP;
        //insert the char to it specific place in the char array
        songDetail[length-1]=c;
    }
    // Add null terminator
    songDetail[length]='\0';
    return songDetail;
}