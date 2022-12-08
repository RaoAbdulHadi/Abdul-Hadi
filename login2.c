#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>




struct log_info{
   char name[20],pass[20],uname[20];
   int lev;
}a,b;

char checker[20];
int check;

int check_uname(char *str,int * cnt){
struct log_info var; 
    FILE *search=fopen("login_info.bin","rb");

    if(search== NULL) {
        printf("Error Exist\n");
        exit(0);
        }
        rewind(search);
    while(!(feof(search))){
        if(fread(&var,sizeof(struct log_info),1,search)==NULL)continue;
        puts(var.uname);
        if(strcmp(var.uname,str)==0){
            fclose(search);
//            free(search);
            return 1;
		}
		(*(cnt))++;
		printf("\n\t%d\n",*cnt);
    }
    fclose(search);
    return 0;

}
/*
char* get_string_nospace(){
    int ind=0;char c;
    char *pas1=(char*)malloc(sizeof(char));

            while((c=getche())!=13){

                ind++;
                pas1=(char*)realloc(pas1,ind*sizeof(char));
                pas1[ind-1]=c;
                //  gotoxy(20,20);
                //  printf(" \r");
                //  gotoxy(20,30);
                //  printf("Note donot Enter any character other than Alphabets and  some special characters (%c,%c,%c,%c,%c)",58,59,60,61,62);    

                 if(c==8){
                    ind--;
                    if(ind>0){
                    printf(" \b");
                    pas1=(char*)realloc(pas1,ind*sizeof(char));

                    }else ind=0;
                 }if(c==32)printf("\b");
                }
puts("");
            return pas1;
}

char* assign_id(){

	int i;
    char *id=(char*) calloc(6,sizeof(char));
    do{
    srand(time(NULL));
    for(i=0;i<5;i++){
        id[i]=48+rand()%43;
    }
    id[6]=0;
    }while(check_id(id));
    return id;

    
}
*/
void encrypt_pass(char *arr){
	int i,n = strlen(arr);
  int mb=(n)/2;
puts("\ninencryption");
  //arr=(char*) realloc(arr,(n+4)*sizeof(char));
//puts("\ninencryption");

  for(i=(n+3);i>(mb+3);i--){
     arr[i]=arr[i-4];
  }

puts("\ninencryption");
  arr[mb]='0';
  arr[mb+1]='t';
  arr[mb+2]='k';
  arr[mb+3]='0';
  
puts("The current encrypted stirng : ");puts(arr);
	n = strlen(arr);
    switch(arr[0]){

       case 'a':case 'A':  
       case 'e':case 'E':  
       case 'i':case 'I':  
       case 'o':case 'O':  
       case 'u':case 'U':  
		puts(arr);
            for(i=(n+2)-1;i>1;i--){
               arr[i]=arr[i-2];
            }
            arr[0]='V';
            arr[1]='w';

        break;

        default : 

            arr[n]='C';
            arr[n+1]='n';
            arr[n+2]='s';
            arr[n+3]=0;

        break;    
    }
}

int main(){
	//FILE *ftemp=fopen("login_info.bin","wb");
	//fclose(ftemp);
    char c;
    int cnt=0,pass_cnt=0;
    system("cls");
	printf("\n\n                          WELCOME TO THe PONG GAME\n");
    printf("Sign up or login to enjoy the game \n0- Signup\n1- Login\n2- Play Demo\n\n");
    scanf("%d",&check);
    
    switch(check){

case 0:
	
        fflush(stdin);
    printf("Give the your name : ");
    gets(a.name);
    printf("Give a unique user name with which you will login next time \n");
    gets(a.uname);
    while(check_uname(a.uname,&cnt)){
    	printf("The user name is already present. please choose someother username\n");
    	gets(a.uname);
	}
        do{
        	fflush(stdin);
            printf("give the password you want to create : ");
            gets(checker);
            printf("Renter the password for the sake of confirmation : ");
			gets(a.pass);
			
            if(strcmp(checker,a.pass)==0)break;
            else printf("please Enter the correct password try Again !\n");
        }while(1);

    encrypt_pass(a.pass);
    a.lev=1;
struct log_info var;
 FILE *fw=fopen("login_info.bin","ab");
fwrite(&a,sizeof(struct log_info),1,fw);
 fclose(fw);
 break; 
 	case 1:
 		system("cls");
 		printf("Enter your unique user name: ");
 		fflush(stdin);
 		gets(a.uname);
		cnt=0;
		while(!check_uname(a.uname,&cnt)){
    		printf("The user name is not present. please try again. press 'M' for main menu\n");
    		cnt=0;
    		if(getch()=='M'){
    		return 0;
			}
    		gets(a.uname);
		}
 		FILE *fnew = fopen("login_info.bin","rb");
 		if(fnew == NULL){
 			printf("file not opened\n");
 			exit(0);
		}
		int offset = (cnt)*sizeof(struct log_info);
		fseek(fnew,offset,SEEK_SET);
		fread(&a,sizeof(struct log_info),1,fnew);
		fclose(fnew);
   		printf("\nEnter your password : ");
   		fflush(stdin);
		gets(b.pass);
		encrypt_pass(b.pass);
		
		while(strcmp(b.pass,a.pass)){
			printf("\nYour password is incorrect. Enter your password again. you have %d tries: ",3-pass_cnt);
			gets(b.pass);
			encrypt_pass(b.pass);
			pass_cnt++;
			if(pass_cnt==3){
				printf("You have no tries left\n");
				sleep(2);
				return 0;
			}
		}
		printf("login successful\n");
		
		return 1;
 		break;
	}
}
