/* 
 * Skeleton code for prodcons problem
 * (C) Mohammad H. Mofrad, 2016
 *   
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <linux/prodcons.h>

void *BASE_PTR;
void main(int argc, char *argv[]) {
     if (argc < 4) {
          printf("Not enough arguments");
          exit(1);
     }
     const int ncons = atoi(argv[1]);
     const int nprod = atoi(argv[2]);
     const int n = atoi(argv[3]);
     BASE_PTR = (void *) mmap(NULL, MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
     if(BASE_PTR == (void *) -1) 
     {
          fprintf(stderr, "Error mapping memory\n");
          exit(1);
     }
     
     int *base_ptr = BASE_PTR;
     int *new_ptr;
     int *curr_ptr = BASE_PTR;
     int semsize = sizeof(struct cs1550_sem);
     // Empty semaphore
     curr_ptr = curr_ptr + semsize;
     if(curr_ptr > base_ptr + MAP_SIZE) 
     {
          fprintf(stderr, "Address out of range\n");
          exit(1);
     }
     else
     {
          new_ptr = curr_ptr - semsize;
     }
     struct cs1550_sem *empty = (struct cs1550_sem *) new_ptr;
     empty->value = n;
     // Full semaphore
     curr_ptr = curr_ptr + semsize;
     if(curr_ptr > base_ptr + MAP_SIZE) 
     {
          fprintf(stderr, "Address out of range\n");
          exit(1);
     }
     else
     {
          new_ptr = curr_ptr - semsize;
     }
     struct cs1550_sem *full = (struct cs1550_sem *) new_ptr;
     full->value = 0;
     // Mutex semaphore
     curr_ptr = curr_ptr + semsize;
     if(curr_ptr > base_ptr + MAP_SIZE) 
     {
          fprintf(stderr, "Address out of range\n");
          exit(1);
     }
     else
     {
          new_ptr = curr_ptr - semsize;
     }
     struct cs1550_sem *mutex = (struct cs1550_sem *) new_ptr;
     mutex->value = 1;

     // Pancakes
     curr_ptr = curr_ptr + n * sizeof(int);
     if(curr_ptr > base_ptr + MAP_SIZE) 
     {
          fprintf(stderr, "Address out of range\n");
          exit(1);
     }
     else
     {
          new_ptr = curr_ptr - n * sizeof(int);
     }
     int *buffer = (int *) new_ptr;

     // in position
     curr_ptr = curr_ptr + sizeof(int);
     if(curr_ptr > base_ptr + MAP_SIZE) 
     {
          fprintf(stderr, "Address out of range\n");
          exit(1);
     }
     else
     {
          new_ptr = curr_ptr - sizeof(int);
     }
     int *in = (int *) new_ptr;
     *in = 0;
     // out position
     curr_ptr = curr_ptr + sizeof(int);
     if(curr_ptr > base_ptr + MAP_SIZE) 
     {
          fprintf(stderr, "Address out of range\n");
          exit(1);
     }
     else
     {
          new_ptr = curr_ptr - sizeof(int);
     }
     int *out = (int *) new_ptr;
     *out = 0;

     int i, pid;
     for (i = 0; i < nprod; i++) {
          pid = fork();
          if (pid < 0) {
               printf("Producer forking error");
               exit(1);
          } else if (pid == 0) {
               for(;;) {
                    printf("Chef %c\n", i + 'A'); 
                    sleep(5);
               }
          }
     }

     for (i = 0; i < ncons; i++) {
          pid = fork();
          if (pid < 0) {
               printf("Consumer forking error");
               exit(1);
          } else if (pid == 0) {
               for(;;) {
                    printf("Consumer %c\n", i + 'A');
                    sleep(5);
               }
          }
     }
     
	

/*
     printf("Base pointer (0x%08x), Current pointer (0x%08x), New pointer (0x%08x)\n", base_ptr, curr_ptr, new_ptr);
     printf("Base pointer (%d), Current pointer (%d), New pointer (%d)\n", *base_ptr, *curr_ptr, *new_ptr);
     cs1550_down(sem);
     sleep(5);
     printf("Semaphore value (%d)\n", sem->value);
     printf("Base pointer (%d), Current pointer (%d), New pointer (%d)\n", *base_ptr, *curr_ptr, *new_ptr);
     cs1550_up(sem);
     printf("Semaphore value (%d)\n", sem->value);
     printf("Base pointer (%d), Current pointer (%d), New pointer (%d)\n", *base_ptr, *curr_ptr, *new_ptr);
*/

}

void cs1550_down(struct cs1550_sem *sem) 
{
     syscall(__NR_sys_cs1550_down, sem);
}

void cs1550_up(struct cs1550_sem *sem) 
{
     syscall(__NR_sys_cs1550_up, sem);
}
