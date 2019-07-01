#ifndef CSV_H
#define CSV_H

#define RECLEN 512
#define FLDLEN 80

int count_fields(char *);
void read_field(char *, char *, int);

#endif
