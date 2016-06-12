/*
   CSCI 2021
   Multiplication table generator 
   for any base
    finish the function
   printMultTable
   Fuad Mohamoud
*/

#include <stdio.h>
#include <stdlib.h>

char convertToChar(int i, int base);
void printNumber(int i, int base, int field_width, int char_count);
void printMultTable(int base);



int main()
{
    int i = 59;
    int base;
    /*
    printf("...");
    printNumber(i, 10, 4, 0);
    printf("...");
    putchar('\n');
     printNumber(i, 12, 4, 0);
    putchar('\n');
     printNumber(i, 20, 4, 0);
    putchar('\n');
    */
    
    printf("This program will print a multiplication base for any base 2 to 36\n");
    printf("What base would you like to use?\n");
    scanf("%d", &base);
    if (base >= 2 && base <= 36){
       printMultTable(base);
    }else{
       printf("invalid base\n");   
    }
    
    system("pause");
    return 0;  
}
/*
  i < base
*/
char convertToChar(int i, int base)
{
    char answer;
    
    if ( i < 10){
      answer = i + '0';   
     }else{
        answer = i + 'A' - 10;       
     }
     return answer;
}

void printNumber(int i, int base, int field_width, int char_count)
{
    char ch;
    char_count++;
    if (i < base){
          int k;
         ch = convertToChar(i, base);
         //see if we need to pad it with spaces
         for(k = char_count; k < field_width; ++k)
         {
              putchar(' '); 
         } 
          
    }else{
        int r = i % base;
        ch = convertToChar(r, base);
        
        i = i /base;  
        printNumber(i, base, field_width, char_count);
        
    } 
    
    printf("%c", ch);
}


void printMultTable(int base)
{
     
int i,j;
int k;
    for(i = 1; i < base; ++i)
    
    {
      for(j = 1; j < base; ++j){
       k=i*j;
        printNumber( k, base, 4, 0);
      }
     printf("\n\n");
    }
    printf("\n\n");
     printf("\n\n");

}
