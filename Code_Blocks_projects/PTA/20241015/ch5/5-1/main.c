/*
5-1 变长动态数组
Score 20
Author 陈浩川
Organization 厦门大学

在C/C++中，原生数组的空间大小是静态的。例如，声明int a[10]之后，数组a的大小就已经固定为10，因此在使用时，常常以数据量的上限作为数组的长度，比如最多有可能要保存100,000个元素时，可以创建一个长度为106的数组。这样做的显著缺点就是，当实际数据量较小时，会造成大量的空间浪费。更合理的方法是因地制宜地对数组空间进行动态分配。这里给出一种最简单的动态数组管理策略：

    使用用户分配的一段连续的内存空间表示数组；
    初始时，数组的容量为16；
    (扩展) 当插入元素时，如果空间已满，将数组容量增加至原有的2倍，也就是将原有的空间释放，分配一个大小为原有大小2倍的内存空间，并将原来的元素复制到新的空间中，例如原来的空间大小为16，现在增加到32；
    (压缩) 删除数组中元素后，如果剩余元素的数量小于容量的1/4（向下取整）且数组的容量大于16时，删除掉原有的空间，分配一个为原有容量一半的新的内存空间，并将原来的元素复制到新的空间中，例如原来的容量为64，但是删除元素后，数组中只有15个元素，那么将容量压缩到32。

根据以上策略，实现下面的接口。这些接口以C++中容器std::vector为蓝本，接口的具体功能请看函数前的注释。通过实现这些接口，你或许能够受到一些关于面向对象编程(OOP)的启发。
动态数组类型定义:

typedef int Elem;


typedef enum bool

{

    false,

    true

} bool;


typedef struct DynamicArray

{

    size_t capacity;   // 数组的容量，初始值和最小值均为16u

    size_t size;       // 数组中元素的个数

    Elem* data;     // 用于保存数组中元素的内存空间

} DynamicArray;

函数接口定义：

// 创建数组，初始容量为16。

DynamicArray* DynamicArray_new();


// 本题中，在位置pos前插入元素*v，也就是*v插入后，它是数组中的第pos个元素，下标从0开始。

// 注意，插入后的数组可能发生容量的倍增，假设内存分配总是合法的，不需要针对内存不足抛出异常。

// 例如：

//      1. pos = 10  ，表示在第10个元素前插入元素*v，插入后它前面有10个元素，原来的第10个元素在它后面

//      2. pos = 0   ，表示在数组的起始位置插入元素*v

//      3. pos = size，表示在数组的末尾插入元素*v

void DynamicArray_insert(DynamicArray* this, size_t pos, const Elem* v);


// 删除位置pos的元素，可以假定pos总是合法的，即pos=0,1,...,size - 1，删除后的数组不应该有空档。

// 注意，删除数组元素可能会导致容量变更。

// 例如：

//     size = 6, 数组中的元素为0,1,2,3,4,5。删除了pos=3的元素3之后，数组的元素变为0,1,2,4,5，size=5，数组第3个元素为4

Elem DynamicArray_erase(DynamicArray* this, size_t pos);


// 获取位置为pos的元素，假设pos总是合法的。

Elem DynamicArray_get(const DynamicArray* this, size_t pos);


// 将位置为pos的元素设置为*v，假设pos总是合法的。

void DynamicArray_set(DynamicArray* this, size_t pos, const Elem* v);


// 返回数组的容量。

size_t DynamicArray_capacity(const DynamicArray* this);


// 返回数组的元素个数。

size_t DynamicArray_size(const DynamicArray* this);


// 返回数组元素是否为空，为空则返回true，否则返回false。

bool DynamicArray_empty(const DynamicArray* this);


// 重设数组元素个数为new_size，注意，容量可能因此发生变更。

// 新的数组元素个数如果比原来的数组更多，将原有数组的元素复制到新数组对应位置即可。

// 新的数组元素个数如果比原来的数组更少，超出的部分截断即可。

// 例如：

//    1. 原数组为0,1,2,3,4,5，新数组大小为4，那么新数组变为0,1,2,3，size=4

//    2. 原数组为0,1,2,3，新数组大小为6，那么数组变为0,1,2,3,?,?，size=6，其中?表示任意值，即这些多出的元素

//       不需要初始化

void DynamicArray_resize(DynamicArray* this, size_t new_size);


// 删除数组。不要忘记释放原有数组的空间，否则会造成内存泄漏。

void DynamicArray_delete(DynamicArray* this);

裁判测试程序样例：

int main()

{

    char line[100];

    DynamicArray* arr = NULL;

    size_t size;

    size_t pos;

    Elem v;


    while (gets(line))

    {

        switch (line[0])

        {

        case 'C': // 创建数组

            arr = DynamicArray_new();

            break;

        case 'D': // 删除数组

            DynamicArray_delete(arr);

            arr = NULL;

            break;

        case 'R': // resize

            sscanf(line + 2, "%lu", &size);

            DynamicArray_resize(arr, size);

            break;

        case 'c': // 输出capacity

            printf("%lu\n", DynamicArray_capacity(arr));

            break;

        case 's': // 输出size

            printf("%lu\n", DynamicArray_size(arr));

            break;

        case 'i': // 插入元素

            sscanf(line + 2, "%lu %d", &pos, &v);

            DynamicArray_insert(arr, pos, &v);

            break;

        case 'd': // 删除元素并输出

            sscanf(line + 2, "%lu", &pos);

            printf("%d\n", DynamicArray_erase(arr, pos));

            break;

        case 'G': // get元素并输出

            sscanf(line + 2, "%lu", &pos);

            printf("%d\n", DynamicArray_get(arr, pos));

            break;

        case 'S': // set元素

            sscanf(line + 2, "%lu %d", &pos, &v);

            DynamicArray_set(arr, pos, &v);

            break;

        case 'e': // 输出数组是否为empty

            printf("%s\n", DynamicArray_empty(arr) == true ? "true" : "false");

            break;

        default:

            break;

        }

    }


    return 0;

}


/* 请在这里填写答案 */
/*

输入输出介绍：

输入输出均由裁判程序完成，作答时通常不需要关注。

以下为裁判程序的输入输出介绍，以单个字母表示命令，它们是大小写敏感的，随后跟随若干个参数，命令列表如下：
命令 	含义 	示例 	示例含义
C 	创建数组 	C
D 	删除数组 	D
R $0 	重设数组元素个数为$0 	R 20 	重设数组元素个数为20
c 	输出数组容量capacity 	c
s 	输出数组元素个数size 	s
i 01 	在位置0前插入元素1 	i 10 5 	在第10个位置前插入5
d $0 	删除位置$0的元素并输出 	d 10 	删除位置为10的元素并输出
G $0 	获取位置$0的元素并输出 	G 5 	获取位置为5的元素并输出
S 01 	将位置0的元素赋值为1 	S 5 10 	将数组位置为5的元素设为10
e 	输出数组是否为空，为空输出true，反之输出false 	e

更具体的信息请参考裁判测试程序样例。

可以保证，同一时间，程序中至多只有一个被创建的数组。在创建数组(C)后，每一个操作均在刚刚创建的数组中进行。当数组被删除且没有新的数组被创建时，不会有除创建(C)外的指令。
输入样例：

C
R 10
s
c
S 9 10
i 0 -1
G 0
G 10
d 0
G 9
e
c
R 20
s
c
R 60
s
c
R 5
s
c
D

输出格式：

10
16
-1
10
-1
10
false
16
20
32
60
64
5
16

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
10 MB
*/

#include <stdio.h>
#include <stdlib.h>

/*
动态数组类型定义:
*/
typedef int Elem;

typedef enum bool
{
    false,
    true
} bool;

typedef struct DynamicArray
{
    size_t capacity;   // 数组的容量，初始值和最小值均为16u
    size_t size;       // 数组中元素的个数
    Elem* data;     // 用于保存数组中元素的内存空间
} DynamicArray;

/*
函数接口定义：
*/
// 创建数组，初始容量为16。
DynamicArray* DynamicArray_new();

// 本题中，在位置pos前插入元素*v，也就是*v插入后，它是数组中的第pos个元素，下标从0开始。
// 注意，插入后的数组可能发生容量的倍增，假设内存分配总是合法的，不需要针对内存不足抛出异常。
// 例如：
//      1. pos = 10  ，表示在第10个元素前插入元素*v，插入后它前面有10个元素，原来的第10个元素在它后面
//      2. pos = 0   ，表示在数组的起始位置插入元素*v
//      3. pos = size，表示在数组的末尾插入元素*v
void DynamicArray_insert(DynamicArray* this, size_t pos, const Elem* v);

// 删除位置pos的元素，可以假定pos总是合法的，即pos=0,1,...,size - 1，删除后的数组不应该有空档。
// 注意，删除数组元素可能会导致容量变更。
// 例如：
//     size = 6, 数组中的元素为0,1,2,3,4,5。删除了pos=3的元素3之后，数组的元素变为0,1,2,4,5，size=5，数组第3个元素为4
Elem DynamicArray_erase(DynamicArray* this, size_t pos);

// 获取位置为pos的元素，假设pos总是合法的。
Elem DynamicArray_get(const DynamicArray* this, size_t pos);

// 将位置为pos的元素设置为*v，假设pos总是合法的。
void DynamicArray_set(DynamicArray* this, size_t pos, const Elem* v);

// 返回数组的容量。
size_t DynamicArray_capacity(const DynamicArray* this);

// 返回数组的元素个数。
size_t DynamicArray_size(const DynamicArray* this);

// 返回数组元素是否为空，为空则返回true，否则返回false。
bool DynamicArray_empty(const DynamicArray* this);

// 重设数组元素个数为new_size，注意，容量可能因此发生变更。
// 新的数组元素个数如果比原来的数组更多，将原有数组的元素复制到新数组对应位置即可。
// 新的数组元素个数如果比原来的数组更少，超出的部分截断即可。
// 例如：
//    1. 原数组为0,1,2,3,4,5，新数组大小为4，那么新数组变为0,1,2,3，size=4
//    2. 原数组为0,1,2,3，新数组大小为6，那么数组变为0,1,2,3,?,?，size=6，其中?表示任意值，即这些多出的元素
//       不需要初始化
void DynamicArray_resize(DynamicArray* this, size_t new_size);

// 删除数组。不要忘记释放原有数组的空间，否则会造成内存泄漏。
void DynamicArray_delete(DynamicArray* this);

/*
裁判测试程序样例：
*/
int main()
{
    char line[100];
    DynamicArray* arr = NULL;
    size_t size;
    size_t pos;
    Elem v;

    while (gets(line))
    {
        switch (line[0])
        {
        case 'C': // 创建数组
            arr = DynamicArray_new();
            break;
        case 'D': // 删除数组
            DynamicArray_delete(arr);
            arr = NULL;
            break;
        case 'R': // resize
            sscanf(line + 2, "%lu", &size);
            DynamicArray_resize(arr, size);
            break;
        case 'c': // 输出capacity
            printf("%lu\n", DynamicArray_capacity(arr));
            break;
        case 's': // 输出size
            printf("%lu\n", DynamicArray_size(arr));
            break;
        case 'i': // 插入元素
            sscanf(line + 2, "%lu %d", &pos, &v);
            DynamicArray_insert(arr, pos, &v);
            break;
        case 'd': // 删除元素并输出
            sscanf(line + 2, "%lu", &pos);
            printf("%d\n", DynamicArray_erase(arr, pos));
            break;
        case 'G': // get元素并输出
            sscanf(line + 2, "%lu", &pos);
            printf("%d\n", DynamicArray_get(arr, pos));
            break;
        case 'S': // set元素
            sscanf(line + 2, "%lu %d", &pos, &v);
            DynamicArray_set(arr, pos, &v);
            break;
        case 'e': // 输出数组是否为empty
            printf("%s\n", DynamicArray_empty(arr) == true ? "true" : "false");
            break;
        default:
            break;
        }
    }

    return 0;
}

/* 请在这里填写答案 */
#define dft_cap 16u
// 创建数组，初始容量为16。
DynamicArray* DynamicArray_new()
{
    DynamicArray *DA=malloc(sizeof(DynamicArray));
    DA->capacity=dft_cap,DA->size=0u,DA->data=NULL;
    return DA;
}

// 本题中，在位置pos前插入元素*v，也就是*v插入后，它是数组中的第pos个元素，下标从0开始。
// 注意，插入后的数组可能发生容量的倍增，假设内存分配总是合法的，不需要针对内存不足抛出异常。
// 例如：
//      1. pos = 10  ，表示在第10个元素前插入元素*v，插入后它前面有10个元素，原来的第10个元素在它后面
//      2. pos = 0   ，表示在数组的起始位置插入元素*v
//      3. pos = size，表示在数组的末尾插入元素*v
void DynamicArray_insert(DynamicArray* this, size_t pos, const Elem* v)
{
    if(this&&(pos<=(this->size))&&v)
    {
        ++(this->size);
        if((this->size)>(this->capacity))
        {
            if(this->data)
            {
                (this->capacity)<<=1;
                Elem *Data=malloc((this->capacity)*sizeof(Elem));
                size_t idx=0u;
                for(Elem *p=Data,*q=(this->data); (idx=p-Data)<(this->size); ++p)
                    if(idx==pos)
                        *p=*v;
                    else
                        *p=*q++;
                free(this->data),this->data=Data;
            }
        }
        else
        {
            if(!(this->data))
                this->data=malloc((this->capacity)*sizeof(Elem));
            Elem tmp=(this->data)[pos];
            (this->data)[pos]=*v;
            for(Elem *p=(this->data)+pos+1; p-(this->data)<(this->size); ++p)
            {
                *p^=tmp;
                tmp^=*p;
                *p^=tmp;
            }
        }
    }
}

// 删除位置pos的元素，可以假定pos总是合法的，即pos=0,1,...,size - 1，删除后的数组不应该有空档。
// 注意，删除数组元素可能会导致容量变更。
// 例如：
//     size = 6, 数组中的元素为0,1,2,3,4,5。删除了pos=3的元素3之后，数组的元素变为0,1,2,4,5，size=5，数组第3个元素为4
Elem DynamicArray_erase(DynamicArray* this, size_t pos)
{
    Elem res;
    if(this&&(pos<(this->size))&&(this->data))
    {
        --(this->size),res=(this->data)[pos];
        if(((this->capacity)>dft_cap)&&((this->size)<(this->capacity)>>2))
        {
            (this->capacity)>>=1;
            Elem *Data=malloc((this->capacity)*sizeof(Elem));
            size_t idx=0u;
            for(Elem *p=Data,*q=(this->data); (idx=p-Data)<(this->size); ++p)
                if(idx==pos)
                    ++q;
                else
                    *p=*q++;
            free(this->data),this->data=Data;
        }
        else if(!(this->size))
            free(this->data),this->data=NULL;
        else
            for(Elem *p=(this->data)+pos+1; p-(this->data)<=(this->size); ++p)
                *(p-1)=*p;
    }
    return res;
}

// 获取位置为pos的元素，假设pos总是合法的。
Elem DynamicArray_get(const DynamicArray* this, size_t pos)
{
    Elem res;
    if(this&&(pos<(this->size))&&(this->data))
        res=(this->data)[pos];
    return res;
}

// 将位置为pos的元素设置为*v，假设pos总是合法的。
void DynamicArray_set(DynamicArray* this, size_t pos, const Elem* v)
{
    if(this&&(pos<(this->size))&&(this->data))
        (this->data)[pos]=*v;
}

// 返回数组的容量。
size_t DynamicArray_capacity(const DynamicArray* this)
{
    if(this)
        return this->capacity;
    else
        return 0u;
}

// 返回数组的元素个数。
size_t DynamicArray_size(const DynamicArray* this)
{
    if(this)
        return this->size;
    else
        return 0u;
}

// 返回数组元素是否为空，为空则返回true，否则返回false。
bool DynamicArray_empty(const DynamicArray* this)
{
    if(!this||(this->size)||(this->data))
        return false;
    else
        return true;
}

// 重设数组元素个数为new_size，注意，容量可能因此发生变更。
// 新的数组元素个数如果比原来的数组更多，将原有数组的元素复制到新数组对应位置即可。
// 新的数组元素个数如果比原来的数组更少，超出的部分截断即可。
// 例如：
//    1. 原数组为0,1,2,3,4,5，新数组大小为4，那么新数组变为0,1,2,3，size=4
//    2. 原数组为0,1,2,3，新数组大小为6，那么数组变为0,1,2,3,?,?，size=6，其中?表示任意值，即这些多出的元素
//       不需要初始化
void DynamicArray_resize(DynamicArray* this, size_t new_size)
{
    if(this)
    {
        if(!(this->size)||(new_size>(this->capacity))||(new_size<((this->capacity)>>2)))
        {
            for(; (new_size>(this->capacity)); (this->capacity)<<=1);
            for(; (new_size<((this->capacity)>>2))&&((this->capacity)>dft_cap); (this->capacity)>>=1);
            Elem *Data=NULL;
            if(new_size)
            {
                Data=malloc((this->capacity)*sizeof(Elem));
                for(Elem *p=Data,*q=(this->data); (p-Data<new_size)&&(q-(this->data)<(this->size)); ++p,++q)
                    *p=*q;
            }
            free(this->data),this->data=Data;
        }
        this->size=new_size;
    }
}

// 删除数组。不要忘记释放原有数组的空间，否则会造成内存泄漏。
void DynamicArray_delete(DynamicArray* this)
{
    if(this)
        this->capacity=0,this->size=0,free(this->data),this->data=NULL;
}
