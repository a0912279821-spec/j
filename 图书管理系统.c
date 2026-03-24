#include <stdio.h>
#include<string.h>
#define max 100
void addBook(void);
void listBook(void);
int findBookid(int id);
void searchBook(void);
void deleteBook(void);
void updateBook(void);
void borrowBook(void);
void returnBook(void);
void saveBooksToFile(void);
void loadBooksFromFile(void);
void budgetRecommend(void);
void dfsBuyBook(int index, double sum);
void clearInputBuffer(FILE *stream);
void readLine(FILE *stream, char str[], int size);
typedef struct
{
    int id;//图书编号
    char name[30];//图书名称
    char author[30];//作者
    char publisher[30];//出版社
    double price;//价格
    int total;//总数量
    int stock;//当前库存
    int recommend;
}Book;

Book books[max];
int count=0;//书的数量
double budget;
int chosen[max];

void clearInputBuffer(FILE *stream)
{
    int ch;
    while ((ch = fgetc(stream)) != '\n' && ch != EOF)
    {
    }
}

void readLine(FILE *stream, char str[], int size)
{
    if (fgets(str, size, stream) != NULL)
    {
        str[strcspn(str, "\n")] = '\0';
    }
    else
    {
        str[0] = '\0';
    }
}

void addBook(void)
{
    if (count >= max)
    {
    printf("图书数量已满，无法继续添加\n");
    return;
	}
    printf("请输入图书编号:");
    scanf("%d", &books[count].id);
    clearInputBuffer(stdin);
    if (findBookid(books[count].id) != -1)
	{
    printf("该图书编号已存在，无法重复添加\n");
    return;
	}
    printf("请输入图书名称:");
    readLine(stdin, books[count].name, sizeof(books[count].name));
    printf("请输入作者名称:");
    readLine(stdin, books[count].author, sizeof(books[count].author));
    printf("请输入出版社:");
    readLine(stdin, books[count].publisher, sizeof(books[count].publisher));
    printf("请输入价格:");
    scanf("%lf", &books[count].price);
    printf("请输入图书总量:");
    scanf("%d", &books[count].total);
    printf("是否推荐(1.是 0.否): ");
    scanf("%d", &books[count].recommend);
    books[count].stock = books[count].total;
    count++;
    return;
}
void listBook(void)
{
    if(count == 0)
    {
        printf("当前没有图书信息。\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        printf("编号:%d\n", books[i].id);
        printf("书名:%s\n", books[i].name);
        printf("作者:%s\n", books[i].author);
        printf("出版社:%s\n", books[i].publisher);
        printf("价格:%.2lf\n", books[i].price);
        printf("总数量:%d\n", books[i].total);
        printf("库存:%d\n", books[i].stock);
        if (books[i].recommend == 1)
        printf("推荐状态:推荐\n");
        else
        printf("推荐状态:普通\n");
        printf("-------------------\n");
    }
}

int main()
{
    int choice;
    loadBooksFromFile();
    while (1)
    {
        printf("==== 图书管理系统 ====\n");
        printf("1.添加图书\n");
        printf("2.显示全部图书\n");
        printf("3.查询图书\n");
        printf("4.删除图书\n");
        printf("5.修改图书\n");
        printf("6.借书\n");
        printf("7.还书\n");
        printf("8.预算购书推荐\n");
        printf("0.退出系统\n");
        printf("请输入你的选择:");
        scanf("%d", &choice);
        if (choice == 1)
        {
            addBook();
        }
        else if (choice == 2)
        {
            listBook();
        }
        else if (choice == 3)
        {
            searchBook();
        }
        else if (choice == 4)
        {
            deleteBook();
        }
        else if (choice == 5)
        {
            updateBook();
        }
        else if (choice == 6)
        {
            borrowBook();
        }
        else if (choice == 7)
        {
            returnBook();
        }
        else if (choice == 8)
        {
        budgetRecommend();
        }
       else if (choice == 0)
        {
            saveBooksToFile();
            printf("程序已退出。\n");
            break;
        }
        else
        {
            printf("输入错误，请重新输入。\n");
        }
    }
    return 0;
}
int findBookid(int id)
    {
        for(int i=0;i<count;i++)
        {

            if(books[i].id==id)
            {
                return i;
            }
        }
        return -1;
    }
void searchBook(void)
{
    int id;
    int index;
    printf("请输入要查询的图书编号: ");
    scanf("%d", &id);
    index = findBookid(id);
    if(index == -1)
    printf("未找到图书信息\n");
    else
    {
    printf("编号:%d\n",books[index].id);
    printf("书名:%s\n", books[index].name);
    printf("作者:%s\n", books[index].author);
    printf("出版社:%s\n", books[index].publisher);
    printf("价格:%.2lf\n", books[index].price);
    printf("总数量:%d\n", books[index].total);
    printf("库存:%d\n", books[index].stock);
    }
}
void deleteBook(void)
{
    int id;
    int index;
    printf("请输入想要删除的图书:");
    scanf("%d",&id);
    index = findBookid(id);
    if(index==-1)
    {
    printf("未找到图书信息\n");
    return;
    }
    else
    {
        for(int i=index;i<count-1;i++)
        {
            books[i]=books[i+1];
        }
        count--;
        printf("图书删除成功\n");
    }
}
void updateBook(void)
{
    int id;
    int index;
    printf("请输入要修改的图书:");
    scanf("%d",&id);
    index = findBookid(id);
    if(index==-1)
    {
        printf("未找到图书信息\n");
        return;
    }
    else
    {
    clearInputBuffer(stdin);
    printf("请输入新的图书名称: ");
    readLine(stdin, books[index].name, sizeof(books[index].name));
    printf("请输入新的作者名称: ");
    readLine(stdin, books[index].author, sizeof(books[index].author));
    printf("请输入新的出版社: ");
    readLine(stdin, books[index].publisher, sizeof(books[index].publisher));
    printf("请输入新的价格: ");
    scanf("%lf", &books[index].price);
    printf("请输入新的图书总量: ");
    scanf("%d", &books[index].total);
    books[index].stock = books[index].total;
        printf("图书信息修改成功\n");
    }
}
void borrowBook(void)
{
    int id;
    int index;
    printf("请输入要借阅的图书编号: ");
    scanf("%d", &id);
    index = findBookid(id);
    if (index == -1)
    {
        printf("未找到图书信息\n");
        return;
    }
    if (books[index].stock <= 0)
    {
        printf("库存不足，无法借阅\n");
        return;
    }
    books[index].stock--;
    printf("借书成功，当前库存:%d\n", books[index].stock);
}
void returnBook(void)
{
    int id;
    int index;
    printf("请输入要归还的图书编号: ");
    scanf("%d", &id);
    index = findBookid(id);
    if (index == -1)
    {
        printf("未找到图书信息\n");
        return;
    }

    if (books[index].stock >= books[index].total)
    {
        printf("该图书库存已满，无需归还\n");
        return;
    }
    books[index].stock++;
    printf("还书成功，当前库存:%d\n", books[index].stock);
}
void saveBooksToFile(void)
{
    FILE *fp = fopen("books.txt", "w");
    if (fp == NULL)
    {
        printf("文件打开失败，无法保存数据\n");
        return;
    }

    fprintf(fp, "%d\n", count);

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d\n%s\n%s\n%s\n%.2lf %d %d\n",
                books[i].id,
                books[i].name,
                books[i].author,
                books[i].publisher,
                books[i].price,
                books[i].total,
                books[i].stock);
    }

    fclose(fp);
    printf("图书信息已保存\n");
}
void loadBooksFromFile(void)
{
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL)
    {
        return;
    }
    fscanf(fp, "%d", &count);
    clearInputBuffer(fp);
    for (int i = 0; i < count; i++)
    {
        fscanf(fp, "%d", &books[i].id);
        clearInputBuffer(fp);
        readLine(fp, books[i].name, sizeof(books[i].name));
        readLine(fp, books[i].author, sizeof(books[i].author));
        readLine(fp, books[i].publisher, sizeof(books[i].publisher));
        fscanf(fp, "%lf %d %d",
               &books[i].price,
               &books[i].total,
               &books[i].stock);
        clearInputBuffer(fp);
    }
    fclose(fp);
}
void listRecommendBook(void)
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (books[i].recommend == 1)
        {
            found = 1;
            printf("编号:%d\n", books[i].id);
            printf("书名:%s\n", books[i].name);
            printf("作者:%s\n", books[i].author);
            printf("出版社:%s\n", books[i].publisher);
            printf("价格:%.2lf\n", books[i].price);
            printf("总数量:%d\n", books[i].total);
            printf("库存:%d\n", books[i].stock);
            printf("-------------------\n");
        }
    }
    if (found == 0)
    {
        printf("当前没有推荐图书\n");
    }
}
void dfsBuyBook(int index, double sum)
{
    if(sum>budget)
    return;
    if(index==count)
    {
        printf("找到一种方案\n");
        for(int i=0;i<count;i++)
        {
            if(chosen[i]==1)
            {
                printf("%s\n",books[i].name);
            }
        }           
         printf("总价:%2lf\n",sum);
        printf("--------------------\n");
        return;
    }
    dfsBuyBook(index+1,sum);
    chosen[index]=1;
    dfsBuyBook(index+1,sum+books[index].price);
    chosen[index]=0;
}
void budgetRecommend(void)
{
    printf("请输入预算: ");
    scanf("%lf", &budget);

    for (int i = 0; i < count; i++)
    {
        chosen[i] = 0;
    }

    dfsBuyBook(0, 0);
}
