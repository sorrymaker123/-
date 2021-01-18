#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Book{
    char ISBN[40];  
    int id;         
    char name[30];  
    char author[20];  
    double price;  
    struct Book *next;  
}Book_s;
Book* head = NULL;  
Book* end = NULL;   
int id = 0;     
void show();
void keyDown(); 
void addBook(); 
void del();
int find(char ISBN[]);
void seek();
void change();
void print();
void save_Information();
void delete_Files();
void read();
int main(void){
    system("color 00"); 
    read();
    while (1){
        show();
        keyDown();
        system("cls");}
    return 0;
}
void show(){
   printf("***********************\n");
   printf("******图书管理系统*******\n");
   printf("*******1.添加书籍********\n");
   printf("*******2.删除书籍********\n");
   printf("*******3.查找书籍********\n");
   printf("******4.更改书籍信息******\n");
   printf("*****5.打印所有书籍*******\n");
   printf("*******6.退出系统********\n");
}
void keyDown(){
int select;//选择
printf("请选择：");
scanf("%d",&select);
    switch (select) {
        case 1:
            //添加书籍
            printf("********添加书籍*********\n");
            addBook();
            save_Information();
            system("pause");
            break;
        case 2:
            //删除书籍
            printf("********删除书籍*********\n");
            del();
            delete_Files();
            system("pause");
            break;
        case 3:
            //查找书籍
            printf("********查找书籍*********\n");
            //seek_Book_ISBN();
            seek();
            system("pause");
            break;
        case 4:
            //更改书籍
            printf("*******更改书籍信息*******\n");
//            change_Information_id();
            change();
            save_Information();
            system("pause");
            break;
        case 5:
            //打印所有书籍
            printf("*****5.打印所有书籍*******\n");
            print();
            system("pause");
            break;
        case 6:
            //退出
            printf("********退出系统*********\n");
            system("pause");
            exit(0);
        default:
            printf("请正确输入....\n");
            system("pause");
            break;}}
void addBook(){
    Book_s* p = NULL; 
    p = (Book_s*)(malloc(sizeof(Book_s)));
    if (!p){
        printf("内存申请失败");
        return;}
    printf("请输入要录入书籍的id：");
    scanf("%s",p->ISBN);
    if(find(p->ISBN)){
        printf("对不起，您输入的id值在系统中已经存在了，抱歉\n");
        free(p);
        return;}
    printf("请输入要录入书籍的作者：");
    scanf("%s",p->author);
    printf("请输入要录入书籍的书名(不带书名号)：");
    scanf("%s",p->name);
    printf("请输入要录入书籍的价格：");
    scanf("%lf",&p->price);
    p->next = NULL;     
    p->id = ++id;      
    if (head == NULL || end == NULL){
        head = p;
        end = p;} else{end->next =p;end = p;}}
void del(){
    char select;
    Book_s *p = NULL;
    if (head == NULL){
        printf("无法删除\n");
        return;
    }
    printf("请选择编号：");
    getchar();
    scanf("%c",&select);
    if (select == 'n' || select == 'N'){
        printf("正在退出\n");
        return; }
    while (head){
        p = head;
        head = head->next;  
        free(p);       } 
    printf("清除成功\n");
}
int find(char *ISBN){
    int status = 0; 
    if (head == NULL){
        return 0;  }
    Book_s* p = head;
    while (p){
        if (strcmp(p->ISBN,ISBN) == 0){     
            status = 1;
            return status;}
        p = p->next;  }return 0;}
void seek(){
    int num;
    Book_s* p = NULL;
    if (head == NULL){
        printf("无法执行该操作\n");
        return; }
    p = head;
    printf("请输入该书在系统中的编号:");
    getchar();
    scanf("%d",&num);
    while (p){
        if (p->id == num){
            printf("id值：%s\t系统编号：%d\t书名：《%s》\t作者：%s\t价格：%.2lf元\n", p->ISBN,p->id, p->name,p->author,p->price);
           return; }                
        else{p = p->next;  } }
         printf("对不起，系统中没有录入该信息。\n");}          
  void change(){
    char n[40];
    Book_s* p = NULL;
    if (head == NULL){
        printf("无法执行该操作\n");
        return;   }
    p = head;
    printf("请输入更改书籍的id值：");
    getchar();
    scanf("%s",n);
    while (p) {
        if (strcmp(p->ISBN,n) == 0) {
            printf("id值：%s\t系统编号：%d\t书名：《%s》\t作者：%s\t价格：%.2lf元\n",p->ISBN, p->id,p->name, p->author,p->price);
            printf("更改过后的价格：");       
            getchar();  
            scanf("%lf", &p->price);
            printf("修改成功\n");
            return;} else {p = p->next;}}
printf("对不起，系统中没有录入该信息。\n");}
void print(){
    Book_s* p = NULL;
    if (head == NULL){
        printf("无法执行该操作\n");
        return; }
    p = head;
    while (p){
        printf("id值：%s\t系统编号：%d\t书名：《%s》\t作者：%s\t价格：%.2lf元\n",p->ISBN,p->id,p->name,p->author,p->price);
        p=p->next;}}    
  void save_Information(){
    FILE *p = NULL;
    Book_s* p2 = NULL;
    if ((p = fopen("database.txt","a")) == NULL){
        printf("文件出错，程序退出!\n");
        exit(-1);  }
    p2 = head;
    while (p2){
        fwrite(p2, sizeof(Book_s),1,p);
        p2 = p2->next;  }
 fclose(p);}             
void delete_Files(){
    int status;
    status = remove("database.txt");
    if (status == 0){
        printf("删除成功\n");  } else{
        printf("删除成功，请尝试再次删除\n"); }}              
               
               
       


void read(){
    FILE * file = NULL;
    Book_s *p;
    if ((file = fopen("database.txt","a")) == 0){
        printf("文件读取失败\n");
        exit(-1); }
    while(!feof(file)){
        p = (Book*)(malloc(sizeof(Book)));
        fread(p,sizeof(Book),1,file); 
        if (p->id == 0){
            free(p);
            break;  }
        if (head == NULL || end == NULL){
            head = p;
            end = p;
    } else{
    end->next = p;
    end = p; }
    id = p->id;  }
    fclose(file);
}
