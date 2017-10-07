#include <stdio.h>    
#include <stdlib.h>
#include <unistd.h>

int condizione;

typedef int * semaphore;
semaphore sem1, sem2, sem3, sem4, sem5;

semaphore make_sem () {
  int *sem;

  sem = calloc (2,sizeof(int));
  pipe (sem);
  return sem;
}

void WAIT (semaphore s) {
  int junk;

  if (read(s[0], &junk, 1) <=0) {
    fprintf(stderr, "ERROR : wait\n");
    exit(1);
  }
}

void SIGNAL (semaphore s) {
  if (write(s[1], "x", 1) <=0) {
    fprintf(stderr, "ERROR : signal\n");
    exit(1);
  }
}

void p1() {
  while (1) {
    WAIT (sem1);
    printf ("1\n");  
    sleep (1);  
    SIGNAL (sem2);
    SIGNAL (sem3); 
    if (condizione) 
      SIGNAL (sem4);
  }

}

void p2() {
  while (1) {
    WAIT (sem2);
    printf("2\n");   
    sleep (2);
    SIGNAL (sem5);   
  }
}

void p3() {
  while (1) {
    WAIT (sem3); 
    printf ("3\n");   
    sleep (3); 
    SIGNAL (sem5);  
  }
}

void p4() {
  while (1) {
    if (condizione) { 
      WAIT (sem4);  
      printf ("4\n");
      sleep (4);
      SIGNAL (sem5);
    }
    sleep (1);
  }
}

void p5() {
  while (1) {
    WAIT (sem5);
    WAIT (sem5);
    if (condizione) {
      WAIT (sem5);
    }
    printf("5\n");
    sleep (5); 
    SIGNAL (sem1);
  }  
}

int main (int argc, char *argv[]) { 
  int i;

  if (argc==2)
    condizione = 1;
  else
    condizione = 0;

  sem1=make_sem(); 
  sem2=make_sem(); 
  sem3=make_sem(); 
  sem4=make_sem(); 
  sem5=make_sem(); 
 
  SIGNAL (sem1);
  for(i=0;i<5;i++) {
    if (!fork()) {
      switch(i) { 
        case 0: p1(); break;
        case 1: p2(); break;
        case 2: p3(); break;
        case 3: p4(); break;
        case 4: p5(); break;
      }
    }
  }

  return (0);
}

