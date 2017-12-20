/*
 *  StQ 01.10.2012
 *
 *  DEMO Program for the Debugging Tool GDB
 *
 *  Run as: <pgrm>
 *  - It reads file fileNameR containig integers
 *  - It writes it 4 times on file fileNameW.v1, ...v2, ...v3, ...v4
 *
 *  Version v1: getc/putc buggy
 *  Version v2: fgets/fputs buggy
 *  Version v3: fscanf/fprintf buggy
 *  Version v4: fscanf/fprintf correct
 *
 */

#include <stdio.h>
#include <string.h>

#define fileNameR "pgrmIn.txt"
#define fileNameW "pgrmOut.txt"

#define L 1024

void f1 (char *, char *);
void f2 (char *, char *);
void f3 (char *, char *);
void f4 (char *, char *);

int main (int argc,  char *argv[]){
  char name[L];

  sprintf (name, "%s.v1", fileNameW);
  fprintf (stdout,
    "Reading %s. Writing %s. Wrong Reading Approach with fgetc/fputc.\n",
    fileNameR, name);
  f1 (fileNameR, name);

  sprintf (name, "%s.v2", fileNameW);
  fprintf (stdout,
    "Reading %s. Writing %s. Wrong Reading Approach with fgets/fputs.\n",
    fileNameR, name);
  f2 (fileNameR, name);

  sprintf (name, "%s.v3", fileNameW);
  fprintf (stdout,
    "Reading %s. Writing %s. Wrong Reading Approach with fscan/fprintf.\n",
    fileNameR, name);
  f3 (fileNameR, name);

  sprintf (name, "%s.v4", fileNameW);
  fprintf (stdout,
    "Reading %s. Writing %s. Correct Reading Approach with fscanf/fgets.\n",
    fileNameR, name);
  f4 (fileNameR, name);

  return 1;
}

void f1 (char *nameR, char *nameW){
  FILE *fpR, *fpW;
  char c;

  fpR = fopen (nameR, "r");
  fpW = fopen (nameW, "w");
  if (fpR==NULL || fpW==NULL) {
    fprintf (stderr, "Error opening file.\n");
    return;
  }
  while (!feof(fpR)) {
    c = fgetc (fpR);
    fputc (c, fpW);
  }
  fclose(fpR);
  fclose(fpW);

  return;
}
  
void f2 (char *nameR, char *nameW){
  FILE *fpR, *fpW;
  char buffer[L+1];

  fpR = fopen (nameR, "r");
  fpW = fopen (nameW, "w");
  if (fpR==NULL || fpW==NULL) {
    fprintf (stderr, "Error opening file.\n");
    return;
  }
  while (!feof(fpR)) {
    fgets (buffer, L, fpR);
    fputs (buffer, fpW);
  }
  fclose(fpR);
  fclose(fpW);

  return;
}

void f3 (char *nameR, char *nameW){
  FILE *fpR, *fpW;
  char c;

  fpR = fopen (nameR, "r");
  fpW = fopen (nameW, "w");
  if (fpR==NULL || fpW==NULL) {
    fprintf (stderr, "Error opening file.\n");
    return;
  }
  while (!feof(fpR)) {
    fscanf (fpR, "%c", &c);
    fprintf (fpW, "%c", c);
  }
  fclose(fpR);
  fclose(fpW);

  return;
}

void f4 (char *nameR, char *nameW){
  FILE *fpR, *fpW;
  char c;

  fpR = fopen (nameR, "r");
  fpW = fopen (nameW, "w");
  if (fpR==NULL || fpW==NULL) {
    fprintf (stderr, "Error opening file.\n");
    return;
  }
  while (fscanf (fpR, "%c", &c) != EOF) {
    fprintf (fpW, "%c", c);
  }
  fclose(fpR);
  fclose(fpW);

  return;
} 

