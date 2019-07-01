#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

int main(int argc, char *argv[])
{
   int i, fl, noflds;
   int *field_lengths;
   char **format;
   char record[RECLEN], field[FLDLEN];
   FILE *ifp, *ofp;
   
   if ( argc < 3 ) {
      fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
      return(EXIT_FAILURE);
   }

   if ( ( ifp = fopen(argv[1], "r") ) == NULL ) {  /* error trap */
      fprintf(stderr, "ERROR - opening input file %s failed.\n", argv[1]);
      return(EXIT_FAILURE);
   }
   
   fscanf(ifp, " %[^\n]", record);
   noflds = count_fields(record);
   
   field_lengths = (int *) malloc(noflds * sizeof(int));
   for (i = 0; i < noflds; i++) 
      field_lengths[i] = 0;
   
   rewind(ifp);
   fscanf(ifp, " %[^\n]", record);
   while ( !feof(ifp) ) {
      for (i = 0; i < noflds; ++i) {
         read_field(field, record, i+1);
         fl = strlen(field);
         if (fl > field_lengths[i])
            field_lengths[i] = fl;
      }
      fscanf(ifp, " %[^\n]", record);
   }

   /* construct field width format strings for flat output */
   format = (char **) malloc(noflds * sizeof(char *));
   for (i = 0; i < noflds; i++) {
      format[i] = (char *) malloc(6 * sizeof(char));
      sprintf(format[i], "%%-%ds", field_lengths[i]);
   }

   free(field_lengths);

   rewind(ifp);

   if ( ( ofp = fopen(argv[2], "w") ) == NULL ) {  /* error trap */
      fprintf(stderr, "ERROR - opening output file %s failed.\n", argv[2]);
      fclose(ifp);
      for (i = 0; i < noflds; ++i)
         free(format[i]);
      free(format);      
      return(EXIT_FAILURE);
   }

   fscanf(ifp, " %[^\n]", record);
   while ( !feof(ifp) ) {
      for (i = 0; i < noflds; ++i) {
         read_field(field, record, i+1);
         fprintf(ofp, format[i], field);
      }
      fputc('\n', ofp);
      fscanf(ifp, " %[^\n]", record);
   }

   fclose(ifp);
   fclose(ofp);

   for (i = 0; i < noflds; ++i)
      free(format[i]);
   free(format);

   return(EXIT_SUCCESS);
}
