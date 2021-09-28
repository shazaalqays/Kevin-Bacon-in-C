#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 100 
#define MARK 5000 

// global queue variables
int r = -1; // rear
int f = 0; // front
int queueCount = 0;

// struct for records
struct Record{
    char name[SIZE], pMovie[SIZE]; // pMovie: parent movie
    struct Record *link, *pActor; // pActor: parent actor
};

// struct for table
struct Table{
    char name[SIZE], info[MARK];
};

// function to initialize lookup table
void init(struct Table *lookUp){
	int i;
	
    for(i=0;i<SIZE;i++)
        strcpy(lookUp[i].name,"");
}

// function to add to lookup table
void addToLookUp(struct Table *lookUp, char *input, char *info){
    int i = 0;
    
    while(strcmp(lookUp[i].name, "")){
        i++;
    }
    
    strcpy(lookUp[i].name, input);
    strcpy(lookUp[i].info, info);
}

// function to search in lookup table
int searchLookUp(struct Table *lookUp, char *input, char *info){
    int i = 0;
    
    while(i < SIZE){
        if(!strcmp(lookUp[i].name, input)){ // if the name in lookup table not equal to the input name
            strcpy(info, lookUp[i].info); // copy the info of lookup table to the info
            return 1;
        }
        i++;
    }
    return 0;
}

// function to get size of movies and actors
void getSize(FILE **fp, int *mSize, int *aSize){
    char filename[5000], ch;
    
    strcpy(filename,"E:\\input-mpaa.txt"); // enterence of file name
    if((*fp = fopen(filename, "r")) == NULL) { // if file is not opened
      perror("File is not opened!");
    }

    while(!feof(*fp)){ // finding number of movies inside the file
        ch = fgetc(*fp);
        if(ch == '\n'){
            *mSize = *mSize+1;
        }
        else if(ch == '/'){
            *aSize = *aSize+1;
        }
    }
    *mSize = *mSize+1;
    rewind(*fp); // rewind: sets the file position to the beginning of the file of the given stream.
}

// function to initialize hash table
void initialize(struct Record *hashTable, int recordNum){
    int i = 0;
    
    while(i<(2*recordNum+1)){
        hashTable[i].link=NULL;
        i++;
    }
}

// function to insert into hash table and returns hash key
int insert(char *name, struct Record *hashTable, int recordNum){
    int key = hash(name,recordNum);
    
    while(hashTable[key].link != NULL && strcmp(hashTable[key].name, name)){ 
        key = (key+17) % (2*recordNum+1); // calculate the hash key
    }
    if(strcmp(hashTable[key].name, name)){   
        strcpy(hashTable[key].name, name);
    }
//    printf("%s\n",hashTable[key].name);
    return key;
}

// funtion to link actors
void addActorLink(struct Record *mList, int mKey, struct Record *aList, int aKey){
    struct Record *ptr,*temp;
    
    temp=(struct Record*)malloc(sizeof(struct Record)); // memory allocation   
    strcpy(temp->name, mList[mKey].name);
    temp->link = NULL;

    ptr = aList[aKey].link;
    if(ptr != NULL){
        while(ptr->link != NULL){
            ptr = ptr->link;
        }
        ptr->link = temp;
    }
    else{
        aList[aKey].link = temp;
    }
}

// function to link movies
void addMovieLink(struct Record *mList, int mKey, struct Record *aList, int aKey){
    struct Record *ptr, *temp;
    
    temp=(struct Record*)malloc(sizeof(struct Record)); // memory allocation
    strcpy(temp->name, aList[aKey].name);
    temp->link = NULL;

    ptr=mList[mKey].link;
    if(ptr != NULL){
        while(ptr->link != NULL){
            ptr = ptr->link;
        }
        ptr->link = temp;
    }
    else{
        mList[mKey].link = temp;
    }
}


// function to load files
void loadValues(FILE **fp, struct Record *mList, int mSize, struct Record *aList, int aSize){
    char line[5000], *movieName, *actorName;
    int movieKey, actorKey;

    initialize(mList,mSize); // initialize hash table for movies          
    initialize(aList,aSize); // initialize hash table for actors

    while(!feof(*fp)){
        fgets(line, sizeof(line), *fp);              
        movieName = strtok(line, "/"); // breaks string line into a series of tokens using the delimiter delim.
        movieKey = insert(movieName, mList, mSize); // insert movie to hash table and returns hash key of the movie inserted
        actorName = strtok(NULL, "/");
        while(actorName != NULL){
            actorKey = insert(actorName, aList, aSize); // insert actor to hash table and returns hash key of the acotr inserted
            addActorLink(mList, movieKey, aList, actorKey); // link actors
            addMovieLink(mList, movieKey, aList, actorKey); // link movies
            actorName = strtok(NULL, "/\n");
        }
    }
    fclose(*fp);
}

// hashing function
int hash(char name[SIZE], int recordNum){
    int i = 0, adrs = 0;

    while(i < strlen(name)){
    	adrs = adrs + name[i]*26*i;
    	i++;
	}
    adrs = adrs % (2*recordNum+1); // calculate the address
    return adrs;
}

// function to get hash key
int getKey(char name[SIZE], struct Record *hashTable, int recordNum){
    int key = hash(name,recordNum);
    
    while(strcmp(name,hashTable[key].name)){
        key = (key+17) % (2*recordNum+1);
    }
    return key;
}


// function to get actor number
int getNumber(struct Record *aList, int aSize){
    int i = 0, actorNum = 0;
    
    while(i < (2*aSize+1)){
        if(aList[i].link != NULL){
            actorNum++;
        }
        i++;
    }
    return actorNum;
}

// function to initialize the queue for BFS
void initQueue(struct Record *queue, int *visited, int aSize){
    int i;
    
    for(i=0; i<(2*aSize+1); i++){
        visited[i] = 0;
    }
}

// function to check if queue is empty
int isQueueEmpty() {
    if(queueCount == 0)
        return 1;
    else
        return 0;
}

// function to insert actors into the queue
void insertQueue(struct Record *queue, struct Record actor){
    queue[++r] = actor; // insert to rear ( to the end )
    queueCount++;
}

// function to remove a record from the queue
struct Record removeQueue(struct Record *queue) {
   queueCount--;
   return queue[f++]; // remove from front (from the beginning)
}

// function to find bacon number 
void findBaconNumber(struct Record *queue, int *visited, struct Record *movieList, int movieSize, struct Record *actorList, int actorSize, int actorNumber, int baconKey){
    int i, key, parentKey, counter = 0, baconNumber = 0, distanceToBacon[14];
    struct Record *ptrMovie,*ptrActor, actor;
    
    for(i=0; i<14; i++) // initializing array
        distanceToBacon[i] = 0;

    initQueue(queue, visited, actorSize); // initializing the queue

    // BFS 
    insertQueue(queue, actorList[baconKey]);  //insert an actor to the queue
    visited[baconKey] = 1;               // mark the actor 
    strcpy(actorList[baconKey].pMovie, "NULL"); 
    while((!isQueueEmpty()) && (baconNumber < 13)){  // while the queue is not empty and the bacon number less than 13     
        actor = removeQueue(queue); // take an actor from the queue off
        parentKey = getKey(actor.name, actorList, actorSize); // get the key of the actor which we took it off
        baconNumber = visited[parentKey]; 
        ptrMovie = actor.link; // add a link
        while(ptrMovie != NULL){ // while array of movies is not empty
            key = getKey(ptrMovie->name, movieList, movieSize); // get movie key
            ptrActor = movieList[key].link; // link the movie to the actor
            while(ptrActor != NULL){ // while array of actors is not empty
                key = getKey(ptrActor->name, actorList, actorSize); // get the actor key
                if(visited[key] == 0){ // if the array of visited at key cell equal 0
                    actorList[key].pActor = &actorList[parentKey]; // add the address of parent key to the actors list
                    strcpy(actorList[key].pMovie, ptrMovie->name); // copy the movie name
                    insertQueue(queue, actorList[key]); // enter the actor into the queue
                    visited[key] = baconNumber+1; // increase the label 
                    distanceToBacon[baconNumber]++; // increase the distance between bacon and the actor
                }
                ptrActor = ptrActor->link; // link the actor
            }
            ptrMovie = ptrMovie->link; // link the movie
        }
    }
    i = 0;
    while(i<13){
        counter = counter + distanceToBacon[i]; //finds distance
        i++;
    }
    printf("\nNumber of actors which are infinite far away from bacon:%d\n", (actorNumber-counter-1));
}

// function to search for an actor
int findActor(char name[SIZE],struct Record *hashTable, int recordNum){
    int key = hash(name,recordNum);
//    printf("\n error2");
//	printf("\n%d\n", hashTable[key].link);
	if( hashTable[key].link == NULL ){
		return -1;
	}
    while(strcmp(name, hashTable[key].name) && hashTable[key].link != NULL ){
        key = (key+17) % (2*recordNum+1);
//        printf("\n%d\n", key);
    }
//    printf("%d",hashTable[key].link);
//    printf("\n error3");
    if(hashTable[key].link == NULL){
//    	printf("\n error4");
    	return ;
	}
        
    else{
//    	printf("\n error5");
    	return key;
	}
        
}

// function to find the link between bacon and the actor
void findLink(int *visited, char input[SIZE], struct Record *movieList, int movieSize, struct Record *actorList, int actorSize, int baconKey, char *info){
    struct Record *ptr;
    char baconNumber[3];
    int key = findActor(input, actorList, actorSize);
//    printf("\n error6");
    strcat(info, "Bacon number of the entered actor:\n");
//    printf("\n  %d\n", key);
    if(key != -1){
        
        itoa(visited[key]-1, baconNumber, 10); // itoa: converts int data type to string data type
        strcat(info, baconNumber); // strcat: appends the string pointed to by src to the end of the string pointed to by dest.
//      printf("%s",info);
//		printf("%d",baconNumber);
        strcat(info, "\n\n");
        ptr = actorList[key].pActor;

        strcat(info, "Actors: ");
        strcat(info, input);
//      printf("%s",info);
//		printf("%s",input);
        strcat(info, " - ");
        strcat(info, ptr->name);
//      printf("%s",info);
//		printf("%s",ptr->name);
        strcat(info, "\n");

        strcat(info, "Movie:     ");
        strcat(info, actorList[key].pMovie);
//      printf("%s",info);
//		printf("%s",actorList[key].pMovie);
        strcat(info, "\n\n");

        while(ptr->pActor != NULL){
            strcat(info, "Actors: ");
            strcat(info, ptr->name);
            strcat(info, " - ");
            strcat(info, ptr->pActor->name);
            strcat(info, "\n");

            strcat(info, "Movie:     ");
            strcat(info, ptr->pMovie);
            strcat(info, "\n\n");

            ptr = ptr->pActor;
        }
    }
    else{
        strcat(info, "\nActor not in the same sub network!\n\nBacon number: infinite\n");
    }
}


//////////////// MAIN FUNCTION ///////////////////
int main(){
	
    FILE *fp; 
    int aNumber, i, baconKey, mSize=0, aSize=0, exit=0, *visited, *p1, *p2;
    char input[SIZE], info[MARK]=""; 
    struct Record *mList, *aList, *queue; 
    struct Table *lookUp;
    
    p1 = &mSize; 
	p2 = &aSize;

//	fp = fopen("E:\input-mpaa.txt","r");
//	char tmo;
//	int ii=0;
//	char kk[20];
//	while((tmo =getc(fp))!= EOF){
//		kk[ii] = tmo;
//		ii = (ii+1)%2;
//	}
//	int t =0;
//	for(t=0;t<20;t++){
//		printf("%c ", kk[ii]);
//		ii = (ii +1)%20;
//	}

    getSize(&fp, p1, p2); // to find the actor and film number
    printf("Actor size: %d\n\nMovie size: %d\n", aSize, mSize);
    printf("\n");


    // allocate memory for movie list and actor list //
    mList = (struct Record*) malloc ((2*mSize+1)*sizeof(struct Record)); // allocate memory for films
    aList = (struct Record*) malloc ((2*aSize+1)*sizeof(struct Record)); // allocate memory for actors

    loadValues(&fp, mList, mSize, aList, aSize); // loading into hash table

    aNumber = getNumber(aList, aSize); // find number of actors
    printf("Number of actors:%d\n", aNumber);
    baconKey = getKey("Bacon, Kevin", aList, aSize);

    // allocate memory for the queue, visited array  //
    queue = (struct Record*)malloc(aNumber*sizeof(struct Record)); // allocate memory for queue
    visited = (int*)malloc((2*aSize+1)*sizeof(int)); // allocate memory for visited array
    lookUp = (struct Table*) malloc (100*sizeof(struct Table)); // allocate memory for look up table

    init(lookUp); // initialize look up table

    // find the bacon length for each actor
    findBaconNumber(queue, visited, mList, mSize, aList, aSize, aNumber, baconKey);

    while(exit==0){
        printf("\nEnter a name of actor: ");
        scanf("\n %[^\t\n]s", &input);
        printf("\nInput: %s\n", input);
        
        if(searchLookUp(lookUp, input, info) != 0 ){
        	printf("Information was read from table: %s %s\n", lookUp->name, lookUp->info);
        }
        else{
            findLink(visited, input, mList, mSize, aList, aSize, baconKey, info); // finds the path between bacon and the actor
            addToLookUp(lookUp, input, info); // adding to look up table
//            printf("error1");
        }
        printf("%s ", info);
        strcpy(info, "");      
        printf("\nDo you want to continue?\nIf yes press 0 otherwise press 1\t");
        scanf("%d", &exit);
    }

    // free the memory // 
    free(mList);
    free(aList);
    free(queue);
    free(visited);

    return 0;
}
