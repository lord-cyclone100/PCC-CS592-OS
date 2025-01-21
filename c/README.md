# OS-PCC-CS-592

## Lab Questions

#### Solve the classical producer consumer problem. Consider the buffer is bounded. Create at least 3 producers and 3 consumers.

```c
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCER_COUNT 3
#define CONSUMER_COUNT 3

sem_t mutex, full, empty;
int buffer[BUFFER_SIZE], in = 0, out = 0;

void* producer(){
	int item;
	while(1){
		item = rand()%10;
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in] = item;
		printf("Producer produced item %d at location %d\n",item,in);
		in = (in+1)%BUFFER_SIZE;
		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}
}
void* consumer(){
	int item;
	while(1){
		sem_wait(&full);
		sem_wait(&mutex);
		item = buffer[out];
		printf("Consumer consumed item %d at location %d\n",item,out);
		out = (out+1)%BUFFER_SIZE;
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1);
	}
}

int main(){

	pthread_t producers[PRODUCER_COUNT], consumers[CONSUMER_COUNT];
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,BUFFER_SIZE);

	for(int i=0;i<PRODUCER_COUNT;i++){
		pthread_create(&producers[i],NULL,producer,NULL);
	}

	for(int i=0;i<CONSUMER_COUNT;i++){
		pthread_create(&consumers[i],NULL,consumer,NULL);
	}

	for(int i=0;i<PRODUCER_COUNT;i++){
		pthread_join(producers[i],NULL);
	}

	for(int i=0;i<CONSUMER_COUNT;i++){
		pthread_join(consumers[i],NULL);
	}

	return 0;
}
```


#### Solve the classical reader writer problem. Create 5 readers and 2 writers then synchronize it.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READER_COUNT 5
#define WRITER_COUNT 2

sem_t mutex,wrt;
int readers_num=0,write_data=0;

void* reader(){
    while(1){
        sem_wait(&mutex);
        readers_num++;
        printf("Reader entered\n");
        if(readers_num == 1){
            sem_wait(&wrt);
        }
        sem_post(&mutex);
        printf("Reader is reading %d\n",readers_num);
        sleep(1);
        sem_wait(&mutex);
        readers_num--;
        printf("Reader left\n");
        if(readers_num == 0){
            sem_post(&wrt);
        }
        sem_post(&mutex);
        sleep(1);
    }
}

void* writer(){
    while(1){
        sem_wait(&wrt);
        write_data++;
        printf("Writer entered\n");
        printf("Writer writing %d\n",write_data);
        sem_post(&wrt);
        printf("Writer left\n");
        sleep(1);
    }
}

int main(){

    pthread_t reader_grp[READER_COUNT], writer_grp[WRITER_COUNT];

    sem_init(&wrt,0,1);
    sem_init(&mutex,0,1);

    for(int i=0;i<READER_COUNT;i++){
        pthread_create(&reader_grp[i],NULL,reader,NULL);
    }
    for(int i=0;i<WRITER_COUNT;i++){
        pthread_create(&writer_grp[i],NULL,writer,NULL);
    }
    for(int i=0;i<READER_COUNT;i++){
        pthread_join(reader_grp[i],NULL);
    }
    for(int i=0;i<WRITER_COUNT;i++){
        pthread_join(writer_grp[i],NULL);
    }
    return 0;
}
```


#### Write a C program where the parent process sends a number to child process using PIPE and child process computes whether that number is an odd or even number.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

    int buffer[2],num;
    pid_t pid;

    pipe(buffer);

    pid = fork();

    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }

    if(pid == 0){
        close(buffer[1]);
        read(buffer[0],&num,sizeof(int));
        if(num%2 == 0){
            printf("%d is even\n",num);
        }
        else{
            printf("%d is odd\n",num);
        }
        close(buffer[0]);
    }
    else{
        close(buffer[0]);
        printf("Enter a number:");
        scanf("%d",&num);
        write(buffer[1],&num,sizeof(int));
        close(buffer[1]);
        wait(NULL);
    }

    return 0;
}
```


#### Write a C program where parent process send a number to child process using PIPE and child process compute whether that number is a prime number or not.

```c
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int checkPrime(int num){
    if(num <= 1){
        return 0;
    }
    for(int i=num-1;i>1;i--){
        if(num%i == 0){
            return 0;
        }
        else{
            return 1;
        }
    }
}

int main(){

    int buffer[2], num;
    pid_t pid;

    pipe(buffer);
    pid = fork();

    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }

    if(pid == 0){
        close(buffer[1]);
        read(buffer[0],&num,sizeof(int));
        int isPrime = checkPrime(num);
        if(isPrime == 1){
            printf("%d is prime",num);
        }
        else{
            printf("%d is not prime",num);
        }
        close(buffer[0]);
    }

    else{
        close(buffer[0]);
        printf("Enter a number:");
        scanf("%d",&num);
        write(buffer[1],&num,sizeof(int));
        close(buffer[1]);
        wait(NULL);
    }

    return 0;
}
```


#### Write a C program where parent process send a number to child process using PIPE and child process compute whether that number is Armstrong number or not.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

void checkArmstrong(int num, int count){
    int sum = 0,rem,num2 = num;
    while(num > 0){
        rem = num%10;
        sum += (int)pow(rem,count);
        num = num/10;
    }
    if(sum == num2){
        printf("%d is an Armstrong number",num2);
    }
    else{
        printf("%d is an not an Armstrong number",num2);
    }
}

int countDigits(int num){
    int count = 0;
    while(num > 0){
        count++;
        num = num/10;
    }
    return count;
}

int main(){

    int buffer[2],num;
    pid_t pid;

    pipe(buffer);
    pid = fork();

    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }

    if(pid == 0){
        close(buffer[1]);
        read(buffer[0],&num,sizeof(int));
        int c = countDigits(num);
        checkArmstrong(num,c);
        close(buffer[0]);
    }

    else{
        close(buffer[0]);
        printf("Enter a number:");
        scanf("%d",&num);
        write(buffer[1],&num,sizeof(int));
        close(buffer[1]);
        wait(NULL);
    }

    return 0;
}
```


#### Write a C program to create a child process. Parent process send a string to child process using PIPE then child process will calculate how many, alphabet, numeric and special characters (#, &) are there?

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(){

    pid_t pid;
    int buffer[2];
    char str[100];
    pipe(buffer);
    pid = fork();
    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }
    if(pid == 0){
        close(buffer[1]);
        int letterCount = 0,numCount = 0, spCharCount = 0;
        read(buffer[0],str,sizeof(str));
        for(int i=0;str[i] != '\0';i++){
            if((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z')){
                letterCount++;
            }
            else if (str[i]>='0' && str[i]<='9'){
                numCount++;
            }
            else{
                spCharCount++;
            }
        }
        printf("No of alphabets : %d\nNo of digits : %d\nNo of special characters : %d\n",letterCount,numCount,spCharCount);
        close(buffer[0]);
    }
    else{
        close(buffer[0]);
        printf("Enter a string:");
        scanf("%s",str);
        write(buffer[1],str,strlen(str)+1);
        close(buffer[1]);
        wait(NULL);
    }
    return 0;
}
```


#### Write a C program using fork() system call that generates the Fibonacci sequence in the parent process and prime checking in the child process.

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int fibo(int num){
    if(num == 0){
        return 0;
    }
    else if(num == 1){
        return 1;
    }
    else{
        return fibo(num-1)+fibo(num-2);
    }
}

int checkPrime(int num){
    if(num <= 1){
        return 0;
    }
    for(int i=num-1;i>1;i--){
        if(num%i == 0){
            return 0;
        }
        else{
            return 1;
        }
    }
}

int main(){

    int num1,num2;
    pid_t pid;
    
    pid = fork();
    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }
    if(pid == 0){
        printf("\nEnter a number:");
        scanf("%d",&num1);
        int isPrime = checkPrime(num1);
        if(isPrime == 1){
            printf("%d is prime",num1);
        }
        else{
            printf("%d is not prime",num1);
        }
    }
    else{
        wait(NULL);
        printf("\nEnter a number:");
        scanf("%d",&num2);
        for(int i=0;i<num2;i++){
            printf("%d ",fibo(i));
        }
    }
    return 0;
}
```


#### Solve the classical dining philosophers(5 philosophers) problem.

```c
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define PHILOSOPHER_COUNT 5
#define CHOPSTICK_COUNT 5

sem_t chopsticks[CHOPSTICK_COUNT];

void* diningPhilosopher(void* args){
    int id = *(int*)args;
    while(1){
        
        sem_wait(&chopsticks[id]);
        sem_wait(&chopsticks[(id+1)%CHOPSTICK_COUNT]);
        printf("Philosopher %d is now eating\n",id);
        sleep(1);
        sem_post(&chopsticks[id]);
        sem_post(&chopsticks[(id+1)%CHOPSTICK_COUNT]);
        printf("Philosopher %d is now thinking\n",id);
        sleep(1);
    }
}

int main(){
    pthread_t philosophers[PHILOSOPHER_COUNT];
    for(int i=0;i<CHOPSTICK_COUNT;i++){
        sem_init(&chopsticks[i],0,1);
    }
    for(int i=0;i<PHILOSOPHER_COUNT;i++){
        philosophers[i]=i;
        pthread_create(&philosophers[i],NULL,&diningPhilosopher,(int*)&i);
    }
    for(int i=0;i<PHILOSOPHER_COUNT;i++){
        pthread_join(philosophers[i],NULL);
    }

    return 0;
}
```


#### Consider 3 threads running simultaneously. First thread1 read a number a. After that thread2 reads a number b then thread3 will do addition of a and b. Synchronize it using semaphore.

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int a,b,c;
sem_t mutex;

void* receiveFirstNum(){
    printf("Enter the value of a : ");
    scanf("%d",&a);
    sem_post(&mutex);
}

void* receiveSecondNum(){
    sem_wait(&mutex);
    printf("Enter the value of b : ");
    scanf("%d",&b);
    sem_post(&mutex);
}

void* calcResult(){
    sem_wait(&mutex);
    printf("Sum : %d",a+b);
    sem_post(&mutex);
}

int main(){
    sem_init(&mutex,0,0);
    pthread_t thread1,thread2,thread3;

    pthread_create(&thread1,NULL,&receiveFirstNum,NULL);
    pthread_create(&thread2,NULL,&receiveSecondNum,NULL);
    pthread_create(&thread3,NULL,&calcResult,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);

    return 0;
}
```


#### Write a C program to create a child process. Parent process send a string to child process using PIPE then child process will check the string is palindrome or not.

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int checkPalindrome(char str[]){
    for(int i=0;i<strlen(str);i++){
        if(str[i] != str[strlen(str)-1-i]){
            return 0;
        }
    }
    return 1;
}

int main(){

    pid_t pid;
    int buffer[2];
    char str[30];
    pipe(buffer);
    pid = fork();
    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }

    if(pid == 0){
        close(buffer[1]);
        read(buffer[0],str,sizeof(str));
        int pl = checkPalindrome(str);
        if(pl == 0){
            printf("%s is not a palindrome",str);
        }
        else{
            printf("%s is a palindrome",str);
        }
    }

    else{
        close(buffer[0]);
        printf("Enter a string : ");
        scanf("%s",str);
        write(buffer[1],&str,strlen(str)+1);
        close(buffer[1]);
        wait(NULL);
    }

    return 0;
}
```


#### Write a C program that will create a child process by using the fork() system call , the parent process will print the PID of itself, as well as the PID of the child. The child process will also print the PID of its parent as well as the PID of itself.

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

    pid_t pid;
    pid = fork();
    
    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }

    if(pid == 0){
        printf("Child process\nCurrent process : %d\tParent process : %d\n",getpid(),getppid());
    }
    else{
        printf("Parent process\nCurrent process : %d\tChild process : %d\n",getpid(),pid);
    }

    return 0;
}
```


#### Write a C program that will create a child process. The parent process will announce that it is the parent process and taking a input from user it will send it to the child process. The child will announce that it is the child process and will display the Fibonacci series of the number (Up to the range).

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include <sys/wait.h>

int printFibo(int n){
    if(n == 0){
        return 0;
    }
    else if(n == 1){
        return 1;
    }
    else{
        return printFibo(n-1) + printFibo(n-2);
    }
}

int main(){

    pid_t pid;
    int num, buffer[2];

    pipe(buffer);
    pid = fork();

    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }

    if(pid == 0){
        
        close(buffer[1]);
        printf("I am child process.\n");
        read(buffer[0],&num,sizeof(int));
        for(int i=0;i<num;i++){
            printf("%d ",printFibo(i));
        }
        close(buffer[0]);
    }

    else{
        close(buffer[0]);
        printf("I am parent process.\n");
        printf("Enter the number of terms : ");
        scanf("%d",&num);
        write(buffer[1],&num,sizeof(int));
        close(buffer[1]);
        wait(NULL);
    }

    return 0;
}
```


#### Write a C program to create a child process. Parent process send a string to child process using PIPE then child process will calculate how many vowel and consonant are there?

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){

    int buffer[2];
    char str[50];
    pid_t pid;
    pipe(buffer);
    pid = fork();

    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }
    if(pid == 0){
        close(buffer[1]);
        read(buffer[0],&str,sizeof(str));
        int v_count = 0,c_count = 0;
        for(int i=0;str[i] != '\0';i++){
            if(str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U' || str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u'){
                v_count++;
            }
            else{
                c_count++;
            }
        }
        printf("Number of vowels : %d\n",v_count);
        printf("Number of consonants : %d\n",c_count);
        close(buffer[0]);
    }
    else{
        close(buffer[0]);
        printf("Enter a string : ");
        scanf("%s",str);
        write(buffer[1],&str,strlen(str)+1);
        close(buffer[1]);
        wait(NULL);
    }

    return 0;
}
```


#### Create two threads one thread will take the input of a matrix and 2nd thread will check the matrix is symmetric or not.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int r,c,a[15][15],isSymmetric=1;

void* matrixInitialize(){
    pthread_mutex_lock(&mutex);
    printf("Enter the no of rows and columns : ");
    scanf("%d %d",&r,&c);
    printf("Enter the elements : ");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%d",&a[i][j]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void* checkSymmetric(){
    pthread_mutex_lock(&mutex);
    if(r != c){
        printf("The entered matrix is not a square matrix");
        exit(1);
    }
    printf("Entered matrix : \n");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(a[i][j] != a[j][i]){
                isSymmetric = 0;
                break;
            }
        }
        if(isSymmetric == 0){
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_t thread1, thread2;
    pthread_create(&thread1,NULL,matrixInitialize,NULL);
    pthread_create(&thread2,NULL,checkSymmetric,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    if(isSymmetric){
        printf("The entered matrix is symmetric");
    }
    else{
        printf("The entered matrix is not symmetric");
    }
    return 0;
}
```


#### A variable count is shared by 3 threads. Each thread will increment the variable. Write a C program to synchronize the threads.

```c
#include <stdio.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment_count(){
    for (int i = 0; i < 1000; i++){
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }   
}

int main() {
    pthread_t threads[3];
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, increment_count, NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Final count: %d\n", count);
    return 0;
}
```


#### Write a C program to create two threads 1st thread will take input of an array and 2nd thread will perform sorting i.e after 1st threads 2nd threads start execution.

```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int n, arr[100];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* arrayInput(){
    pthread_mutex_lock(&mutex);
    printf("Enter the length of the array : ");
    scanf("%d",&n);
    printf("Enter array elements:");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("Original array : ");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    pthread_mutex_unlock(&mutex);
}

void* arraySort(){
    pthread_mutex_lock(&mutex);
    for(int i=0;i<n-1;i++){
        int swapped = 0;
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = 1;
            }
        }
        if(swapped == 0){
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main(){

    pthread_t thread1, thread2;

    pthread_create(&thread1,NULL,arrayInput,NULL);
    pthread_create(&thread2,NULL,arraySort,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    printf("\nSorted array : ");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }

    return 0;
}
```


#### Write a C program to create two threads. 1st thread will take input of a matrix and 2nd thread will perform Transpose of the matrix i.e after 1st thread, 2nd thread will start execution.

```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int a[15][15],b[15][15],r,c;

void* inputMatrix(){
    pthread_mutex_lock(&mutex);
    printf("Enter the number of rows and columns : ");
    scanf("%d %d",&r,&c);
    printf("Enter the matrix elements : ");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%d",&a[i][j]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void* calcTranspose(){
    pthread_mutex_lock(&mutex);
    
    if(r != c){
        printf("The matrix is not a square matrix\n");
        exit(1);
    }

    printf("Original matrix : \n");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            b[i][j] = a[j][i];
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_t thread1, thread2;

    pthread_create(&thread1,NULL,inputMatrix,NULL);
    pthread_create(&thread2,NULL,calcTranspose,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    printf("Transpose\n");

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
}
```


#### Write a C program to create two threads. 1st thread will take input of two matrixes and 2nd thread will perform subtraction i.e after 1st thread, 2nd thread will start execution.

```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int a[15][15],b[15][15],c[15][15],r1,c1,r2,c2;

void* inputMatrix(){
    pthread_mutex_lock(&mutex);
    printf("Enter the number of rows and columns of 1st matrix: ");
    scanf("%d %d",&r1,&c1);
    printf("Enter the 1st matrix elements : ");
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            scanf("%d",&a[i][j]);
        }
    }
    printf("Enter the number of rows and columns of 2nd matrix: ");
    scanf("%d %d",&r2,&c2);
    printf("Enter the 2nd matrix elements : ");
    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            scanf("%d",&b[i][j]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void* calcDifference(){
    pthread_mutex_lock(&mutex);
    
    if(r1 != r2 || c1 != c2){
        printf("The matrices is not of same order\n");
        exit(1);
    }

    printf("1st matrix : \n");
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("2nd matrix : \n");
    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_t thread1, thread2;

    pthread_create(&thread1,NULL,inputMatrix,NULL);
    pthread_create(&thread2,NULL,calcDifference,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    printf("Difference\n");

    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
}
```

#### a count variable is shared among two threads, each thread will increment the count. show the output if the threads are not synchronized.

```c
#include <stdio.h>
#include <pthread.h>

int count = 0;

void* increment_count(void* arg){
    for (int i = 0; i < 100000; i++) {
        count++;
    }
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment_count, NULL);
    pthread_create(&thread2, NULL, increment_count, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final count: %d\n", count);
    return 0;
}
```


#### A book is shared among 5 friends.each friend will read the book but at a time the book can not be read by any two persons. Show how the book is read by the friends.

```c
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

#define NO_OF_FRIENDS 5
sem_t mutex;

void* readBook(void* args){
    int id = *(int*)args;
    while(1){
        sem_wait(&mutex);
        printf("Friend %d is reading the book\n",id);
        sleep(1);
        printf("Friend %d has finished reading the book\n",id);
        sem_post(&mutex);
        sleep(1);
    }
}

int main(){
    sem_init(&mutex,0,1);
    pthread_t friends[NO_OF_FRIENDS];
    for(int i=0;i<NO_OF_FRIENDS;i++){
        pthread_create(&friends[i],NULL,readBook,(int*)&i);
    }

    for(int i=0;i<NO_OF_FRIENDS;i++){
        pthread_join(friends[i],NULL);
    }
    return 0;
}
```