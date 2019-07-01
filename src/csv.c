#include <stdlib.h>
#include <string.h>
#include "csv.h"

int count_fields(char *record)
{
    int i = 0, j = 0, k = 0, bl = strlen(record);

    while (i < bl) {
        while (record[i] != ',' && i < bl)
            if (record[i] != '\"')
                i++;
            else {
                i++;
                while (record[i] != '\"')
                i++;
            }
            i++;
            j++;
    }
    return(j);   
}

/* read nth field from csv record */
void read_field(char *field, char *record, int n)
{
   int i = 0, j = 0, k = 0, bl = strlen(record);

   while (i < bl) {
      while (i < bl && record[i] != ',' && record[i] != '\n') {
         if (record[i] != '\"')
            if (j + 1 == n && k < FLDLEN-1)
               field[k++] = record[i++];
            else
               i++;
         else {
            i++;  /* skip the escape quote */
            if ((j+1) == n && k < FLDLEN-1)
               field[k++] = record[i++];
            else
               i++;
            while (record[i] != '\"') {
               if ((j+1) == n && k < FLDLEN-1)
                  field[k++] = record[i++];
               else
                  i++;
            }
            i++;  /* skip the escape quote */
         }
      }
      if (j + 1 == n && k < FLDLEN) {
         field[k] = '\0'; /* cap the field */
         return;
      }
      i++;
      j++;
   }
}
