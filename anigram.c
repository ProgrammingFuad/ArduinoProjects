/*
        CSCI 2021 programs
        
        anigram program using stacks 
        
         started March 2015

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 6 

char pop(char str[25]);
void push(char str[25], char ch);
void pushFront(char str[25], char ch);
char popFront(char str[25]);
void displayStrings(char left_str[], char right_str[], char bottom[], int count);

void moveCharLeft(char left_str[], char right_str[]);
void moveCharRight(char left_str[], char right_str[]);
void moveCharDown(char left_str[], char bottom_str[]);
void moveCharUp(char left_str[], char bottom_str[]);
void getWords(char startStr[], char endStr[], int which);
int getWordChoice(void);

void eatTheRestOfTheLine();

int main (int argc, const char * argv[]) {
    // insert code here...
	int choice, count = 0;
	
	char right[25] = "\0";
	char left[25];
	char bottom[25] = "\0";
	char target[25];
	
	choice = getWordChoice();
	getWords(left, target, choice);
	
	displayStrings(left, right, bottom, count);
	
	while(strcmp(left, target) != 0){
		scanf("%d", &choice);
		if (choice == 3){
			moveCharRight(left, right);
		}else if (choice == 1){
			moveCharLeft(left, right);
		}else if (choice == 2){
			moveCharDown(left, bottom);
		}else if (choice == 4){
			moveCharUp(left, bottom);
		}
		count++;
		displayStrings(left, right, bottom, count);
    }
	printf("You did it!\n");
   system("pause");
    return 0;
}

char pop(char str[25])
{
	char ch;
	int len = strlen(str);
	if (len == 0){
		ch = 0;
	}else{
		ch = str[len - 1];
		str[len - 1] = '\0';
	}
	return ch;
}

void push(char str[25], char ch)
{
	int len = strlen(str);
	ch = str[len] = ch;
	str[len + 1] = '\0';
}

void pushFront(char str[25], char ch)
{
	int len = strlen(str);
	int i;
	for( i = len+1; i > 0; --i)
	{	
		str[i] = str[i-1];
	}
	
	str[0] = ch;
		
}
	
char popFront(char str[25])
{
	char ch;
	int i, len = strlen(str);
	ch = str[0];
	for( i = 0; i < len; ++i)
	{	
		str[i] = str[i+1];
	}
	
	return ch;
}

void displayStrings(char left_str[], char right_str[], char bottom[], int count)
{
	printf("\n");
	
	printf("%-10s %10s\n", left_str, right_str );
	printf("%-10d %10s\n\n",count, bottom );
}


void moveCharLeft(char left_str[], char right_str[])
{
	char ch = popFront(right_str);
	push(left_str, ch);
}

void moveCharRight(char left_str[], char right_str[])
{
	char ch = pop(left_str);
	pushFront(right_str, ch);
}

void moveCharDown(char left_str[], char bottom_str[])
{
	char ch = pop(left_str);
	pushFront(bottom_str, ch);
}

void moveCharUp(char left_str[], char bottom_str[])
{
	char ch = popFront(bottom_str);
	push(left_str, ch);
}

void getWords(char startStr[], char endStr[], int which)
{  
     if (which == 0 ){
        strncpy(startStr, "resistance", 25);
        strncpy(endStr, "ancestries", 25);
     }else  if (which == 1){
            strncpy(startStr, "listen", 25);
            strncpy(endStr, "silent", 25);
     }else  if (which == 2){
            strncpy(startStr, "admirer", 25);
            strncpy(endStr, "married", 25);
     }else  if (which == 3){
            strncpy(startStr, "angered", 25);
            strncpy(endStr, "enraged", 25);
     }else  if (which == 4){
            strncpy(startStr, "sadder", 25);
            strncpy(endStr, "dreads", 25);
     }else  if (which == 5){
            strncpy(startStr, "orchestra", 25);
            strncpy(endStr, "carthorse", 25);
     }



/*

 …  

 Protectional… Lactoprotein 

 Orchestra… Carthorse 

 Creative… Reactive 

 Deductions… Discounted 

 Listen… Silent 

 Replays… Parsley 

 Players=Parsley 

 Crudities… Diuretics 

 Paternal… Parental 

 Angered… Enraged 

 Discriminator… Doctrinarism 

 Serbia… Rabies 

 Leaf…Flea 

 Elvis Lives 

 Easter…eaters 

 Death = Hated 

 Elvis… Lives 

 Saddam: Maddass 
 */
     
     
}


int getWordChoice(void)
{
    int choice;
    char left[25], correct[25];
    int i;
    do{
        printf("Please choose the word\n");
        for(i = 0; i < MAX_WORDS; i = i +1)
        {
           getWords(left, correct, i);
           printf("%d %s\n", i, left);
        
        }
        scanf("%d", &choice);
        eatTheRestOfTheLine();
    }while(choice < 0 || choice >= MAX_WORDS);
  
    return choice;
}

void eatTheRestOfTheLine()
{
   while(getchar() != '\n')
   {
         ;          
   }  
}
