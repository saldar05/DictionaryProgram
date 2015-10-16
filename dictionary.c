/****************************************************************************
 * dictionary.c
 *
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>

 
typedef struct Node {    

     char word[LENGTH+1];  

     struct Node *Next;    

 }
 Node;

 typedef struct hash_table_t{
    int size;       /* the size of the table */
  struct  Node **table; /* the table elements */
} hash_table_t;
 
  
  
  
FILE* inptr ;
hash_table_t *hashtable=NULL;
Node* Head=NULL;
int sizeOfDictionary=0;
int count2=0;
unsigned int hash( char str[])
{
//SparkNotes Editors. “SparkNote on Hash Tables.” SparkNotes.com. SparkNotes LLC. n.d.. Web. 14 Mar. 2013.

 
    unsigned int hashval;
    
    /* we start our hash out at 0 */
    hashval = 0;

   
     
    for(; *str != '\0'; str++) 
    hashval = *str + (hashval << 5) - hashval;

    /* we then return the hash value mod the hashtable size so that it will
     * fit into the necessary range
     */
    return hashval % hashtable->size;
}
hash_table_t  *create_hash_table(int size)


//SparkNotes Editors. “SparkNote on Hash Tables.” SparkNotes.com. SparkNotes LLC. n.d.. Web. 14 Mar. 2013.
{
if (size<1) 
{
   
    return NULL; 
    
}
  
hashtable = malloc(sizeof(hash_table_t));
   
if (hashtable == NULL) 
{
  
return NULL;
        
}
   
 hashtable->table= malloc(size * sizeof(struct Node *) )  ;
  
if (hashtable->table== NULL)
{
  return NULL;
}
for(int i=0; i<size; i++) 
{ 
  hashtable->table[i]=NULL;
  hashtable->size =size;
   
}
   
       
    
   
 return hashtable;
   


}
bool check(const char* word)
  {
 
 /**
 * Returns true if word is in dictionary else false.
 */
 int i=0;
 char DuplicateArray[LENGTH+1];
 Node* NodePointer=NULL;
 unsigned int hashval=0;
DuplicateArray[LENGTH] = '\0';
 strcpy(DuplicateArray, word);
int r=strlen(DuplicateArray);
       
   while ( DuplicateArray[i] != '\0')
      {
    
    
    
     
     
     
      DuplicateArray[i] = tolower(DuplicateArray[i]);    
      
   
      i++;
      
      }
      hashval=hash(DuplicateArray);
      int j=0;
       
  for (NodePointer=hashtable->table[hashval];NodePointer !=NULL;NodePointer=NodePointer->Next)

    {
       
     
      j=memcmp(DuplicateArray,NodePointer->word,2);

  
      if (j==0)
       
        { 
          for (int i=0;i<r;i++)
          {
           if(ispunct(DuplicateArray[i]))
           {
            return false;
           }
          }
           return true;
         
          
         }
        
        }
        return false;
      }
      
    

   
   
  

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
Node* TempNode=NULL;
Node* new_node=NULL;
Node* Head=NULL;
char buffer[LENGTH+1];
unsigned int hashval;
int j=0;
int update_counter=0;
inptr= fopen(dictionary, "r");
int count=0; 
int thirdcounter=0;
if (inptr == NULL)
    {
        printf("Could not open dictionary file");
        printf("\n");
        return 0;
    } 
  
  
  
for ( ;; )     
{        

  int ch = fgetc(inptr);      
  if ( ch == EOF )    //determines how many words are in the file        
     {           
    
      break;        
    
     }        
  if (isalpha(ch) || isdigit(ch) || ispunct(ch))        
     {           
      update_counter = 1;          
     }         
  if (isspace(ch) && update_counter )      
     {           
     count++;           
   update_counter = 0;       
     }     
}
  if (update_counter) 
    {
	count++;
    } 
   
   
sizeOfDictionary=count;
rewind(inptr);
    
   
    
 
   
hashtable=create_hash_table(sizeOfDictionary);



      
  
  while(fgets(buffer,sizeof(buffer),inptr)!=NULL)
   {
      
     
     
     
    if(Head==NULL)
    {   int sizevalue=strlen(buffer);
        if(buffer[sizevalue-1]=='\n')
        {
          buffer[sizevalue-1]='\0';
        } 
        count2=count2+1;  
       
        hashval = hash(buffer);
        Head = malloc(sizeof(Node));
        strncpy(&Head->word[j],&buffer[j],sizevalue); 
        Head->Next = hashtable->table[hashval];

        hashtable->table[hashval]=Head;
        Head=Head->Next;

        TempNode =  Head; 
    }
    else 
    {
        
        int sizevalue=strlen(buffer);
         if(buffer[sizevalue-1]=='\n')
        {
          buffer[sizevalue-1]='\0';
        } 
        
        
        
        new_node = malloc(sizeof(Node));
        hashval = hash(buffer);
        
        memcpy(&new_node->word[j],&buffer[j],sizevalue);
        thirdcounter=thirdcounter+1;
        new_node->Next = hashtable->table[hashval];
        hashtable->table[hashval]=new_node;
        TempNode=new_node->Next;
             
    } 
  
/*   free(TempNode);*/
/*   free(new_node);   */
    
   }


return true;

/*for(int i=0;i<thirdcounter;i++)*/
/*{*/
/* free(new_node);*/
/* free(TempNode);*/
/*}*/

}



  
               
               
       
   
  

/*  Returns number of words in dictionary if loaded else 0 if not yet loaded.*/
/* */
unsigned int size(void)
{
 if(sizeOfDictionary>0)
    {
    return sizeOfDictionary;
    }
    
    return 0;
}









/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{


for (int i=0;i<sizeOfDictionary;i++)
  {
   free(hashtable->table[i]);
   hashtable->table[i]=NULL;
  }


 for(int i=0;i<count2;i++)
  {
   free(Head);
  } 
free(hashtable->table);
free(hashtable);
fclose(inptr);

Head=NULL;
hashtable=NULL;





if(Head==NULL && hashtable==NULL)
{
  return true;
 
}
 
    return false;
}
