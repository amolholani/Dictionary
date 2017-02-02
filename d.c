/*
	dictionary using binary search tree and hashing
*/	


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
typedef struct data {
	char word[30];
	char meaning[128];
} data;
*/
typedef struct dict {
	char word[30];
	int syn;
	char syno[4][30];
	char meaning[128];
	struct dict *left;
	struct dict *right;
}dict;

dict *dictionary[26];

int strcmpi(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}

void pattern(){
	printf("			.------..------..------..------..------..------..------..------..------..------.  \n");
	printf("			|D.--. ||I.--. ||C.--. ||T.--. ||I.--. ||O.--. ||N.--. ||A.--. ||R.--. ||Y.--. |  \n");	
	printf("			| :/\\: || (\\/) || :/\\: || :/\\: || (\\/) || :/\\: || :(): || (\\/) || :(): || (\\/) |  \n");
	printf("			| (__) || :\\/: || :\\/: || (__) || :\\/: || :\\/: || ()() || :\\/: || ()() || :\\/: |  \n");
	printf("			| '--'D|| '--'I|| '--'C|| '--'T|| '--'I|| '--'O|| '--'N|| '--'A|| '--'R|| '--'Y|  \n");
	printf("			`------'`------'`------'`------'`------'`------'`------'`------'`------'`------'  \n");	
}

void insert (dict *root, dict *new_node)
{
	
 	 if (root == NULL){
  		root = new_node;
		return;
	
 	 }

 	 int compare_value = strcmpi (new_node->word, root->word);

 	 if (compare_value == 0)
  	 {
  		  //printf("word already present\n");
  		  return;
 	 }

  	if (compare_value < 0)
   	{
     		if (root->left != NULL)
      		{
            		insert (root->left, new_node);
     		}
     		else
      		{         
       			root->left = new_node;
          	return;
      		}
   	}
  	else
  	{
      		if (root->right != NULL) 
      		{
      			insert (root->right, new_node);
      		}
      		else
      		{
          		root->right = new_node;
          		return;
     		}
   	}
}

int find_word(dict *dictionary, char word[])
{
 	if (!word || !dictionary)
  	{
    		printf("\t\t ###  Word NOT found11  ###\n");
    		return 0;
  	}

  	int compare_value = strcmpi (word, dictionary->word);

  	if (compare_value == 0)
  	{
  	  	printf("Word \t\t\t\t Meaning\n");
  	  	printf("%s \t\t\t\t%s\n", word, dictionary->meaning);
  	  	return 1;    	
  	}
  	
  	else if (compare_value < 0)
  	{
  		  return find_word (dictionary->left, word);
  	}
  	else 
  	{
  	 	 return find_word (dictionary->right, word);
  	}
}

int n = 1;
int advance_suggest(dict *dictionary, char *word) {
	float x = 0, y, z;
	int i, j;
	float k;
	float matched = 0;
	float missmatched = 0;
	if(dictionary == NULL)
		return 0;	
	y = strlen(word);
	
	for(j = 0; j < dictionary->syn; j++) {
		z = 0;
		x = 0;
		while(dictionary->syno[j][i] != '\0') {
			i++;
			x++;
		}
		if(x > y) {
			for (i = 0; i < y; i++) {
				if(dictionary->syno[j][i] == word[i]) 
					matched++;
			}
		}
		
		else {
			for (i = 0; i < x; i++) {
				if(dictionary->syno[j][i] == word[i]) 
					matched++;
			}
		}



		z = matched / x;
		if(z >= 0.50) {
			printf("%s\t%s\n", dictionary->syno[j], dictionary->word);
			n++;
		}
	}
		advance_suggest(dictionary->left, word);
		printf("\n");
		advance_suggest(dictionary->right, word);

	
	return 0;
}
	
int suggestion_1(dict *dictionary, char *word) {
	
	float x, y, z;
	int i, j;
	float k;
	float matched = 0;
	float missmatched = 0;
	if(dictionary == NULL)
		return 0;	
	x = strlen(dictionary->word);
	y = strlen(word);
	
	if(dictionary) {
		if(x > y) {
			for (i = 0; i < y; i++) {
				if(dictionary->word[i] == word[i]) 
					matched++;
			}
		}
		
		else {
			for (j = 0; j < x; j++) {
				if(dictionary->word[j] == word[j]) 
					matched++;
			}
		}



		z = matched / x;
		if(z >= 0.50) {
			printf("%d\t%s\n", n, dictionary->word);
			n++;
		}
	}
		suggestion_1(dictionary->left, word);
		printf("\n");
		suggestion_1(dictionary->right, word);

	
	return 0;
}

void findElement_this(char *str){
	if(!str){
		printf("\t\t ### Enter valid word  ###\n");
		return;
	}
	printf("%s\n", str);
	if(!find_word(dictionary[str[0] - 'a'], str)){
		printf("word NOT found\n");
	}
	return;
}
void initialize(){
	FILE *fp;
	fp = fopen("dictinory.txt", "a+");
	dict *temp;
	temp = (dict *) malloc (sizeof (dict));	  
        
         while(fread(temp, sizeof(dict), 1, fp) == 1) 
	{			
		 if(dictionary[temp->word[0] - 'a'] == NULL)
                 {
                         dictionary[temp->word[0] - 'a'] = temp;
                  }
                  else {
                       	insert(dictionary[temp->word[0] - 'a'], temp);
                  }
			
	}
	fclose(fp);
        
}

int main(){
	system("clear");		
	int ch, z = 0; 	
        char str[30];
        dict *temp, a;
        
        int i = 26, ji, tmp = 0, k;
       	
        while(i < 26){
        	dictionary[i] = NULL;
        }
        
        initialize();
	FILE *fp;
	fp = fopen("dictinory.txt", "a+");
	
	initialize();
        while (1) {
		pattern();
                printf("\n\t\t1 INSERTION \t\t2. SEARCH \t\t3.EXIT \n");
                //printf("3. Searching\t4. Traversal\n");
                //printf("5. Exit\nEnter ur choice:");
                scanf("%d", &ch);
                getchar();
		 
		         
                switch (ch) {
                        case 1:
                        	temp = (dict *) malloc (sizeof (dict));	  
         	 		temp->left = NULL;
          			temp->right = NULL;
          			
                                printf("Word to insert:- ");
                                fgets(temp->word, 30, stdin);
                                
                                z = 0, tmp = 0;
                                
                                while(temp->word[z] != '\n'){
                                	if(temp->word[z] >= 'A' && temp->word[z] <= 'Z'){
                                		temp->word[z] = temp->word[z] + 32;
                                	}
                                	z++;
                             	}
                                
                                printf("Meaning:- ");
                                fgets(temp->meaning, 128, stdin);
                                
                                printf("Enter number of synonym (MAX 4)\n");
				scanf("%d", &(temp->syn));
				getchar();
                                
                                for(ji = 0; ji < temp->syn; ji++) {
					fgets(temp->syno[ji], 30, stdin);
				}
                                
                                while(fread(&a, sizeof(dict), 1, fp) == 1) 
				{			
					
					if(!strcmp(temp->word, a.word)) 
					{
						printf("\t*** input error ** :- word alredy present\n");
						tmp = 1;
						break;
					}			
				}	
				fseek(fp, 0, 2);

				if(tmp != 1)					/* enroll if previously not present */
				{
					printf("\t*****student enrolled sucessfully*******\n");
					fwrite(temp, sizeof(dict), 1, fp);
				}
                               
                               
                                if(dictionary[temp->word[0] - 'a'] == NULL)
                                {
                                	dictionary[temp->word[0] - 'a'] = temp;
                                }
                                else {
                                	insert(dictionary[temp->word[0] - 'a'], temp);
                                }
                                
                                
                                fclose(fp);
                                fp = fopen("dictinory.txt", "a+");
                                
                                
                                //insert_this(w);
                                //printf(" ---  %s  ----\n", dictionary[temp->word[0] - 'a']->word);
				system("clear");
                                break;
                       /* case 2:
                                printf("Enter the word to delete:");
                                fgets(str, 30, stdin);
                                //deleteNode(str);
                                break;*/
                        case 2:
                                printf("Enter the search word:");
                                
                                fgets(str, 30, stdin);
                                z = 0;
                                while(str[z] != '\n'){
                                	if(str[z] >= 'A' && str[z] <= 'Z'){
                                		str[z] = str[z] + 32;
                                	}
                                	z++;
                             	}
                                system("clear");
                                
				//pattern();
				
                                findElement_this(str );
                                
                                printf("suggestions : \n");
                                suggestion_1(dictionary[str[0] - 'a'], str);
                                                                
				printf("press 1 : main menu\t\t2 : exit\n");
				scanf("%d", &ji);
				if(ji == 1){
					system("clear");                                	
					break;					
				}
				else if(ji == 3) {
					printf("advance suggestion : \n");
					for(k = 0; k < 26; k++) {
						advance_suggest(dictionary[k], str);
					}
					system("clear");
					break;
				}
				else {
					fclose(fp);
					exit(0);
				}	
                       
                        case 3:
                        	fclose(fp);
                                exit(0);
                        default:
                                printf("You have entered wrong option\n");
                                break;
                }
        }
        return 0;
}
