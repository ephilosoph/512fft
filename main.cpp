/*****************************************************************************
 *
 *  Program: main.c
 * 
 *  Created: 10/31/2014
 *
 *  Author:  E. Philosoph
 * 
 *  Purpose: Extracts tests results from 512-FFT float to int conversion
 *
 *  Usage:   512-diff.exe
 * 
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // BYTE

#define  STRINGLEN            2048
#define  FILENAMELEN          256


void main(int argc, char* argv[])
{
   char  szInFile[FILENAMELEN], szOutFile[FILENAMELEN] ;
   char  *pInFile=szInFile, *pOutFile=szOutFile ;
   FILE  *pfr, *pfw ;
   char  szInput[STRINGLEN], szOutput[STRINGLEN] ;
   char  *extension[2] = { "._float", "" } ;

   strcpy( pOutFile, "results.csv" ) ;

   if ( (pfw = fopen ( pOutFile, "wb" )) == NULL )
   {
      printf ("Err: can't open output file: %s\r\n", pOutFile ) ;
      exit(0) ;
   }

   fprintf( pfw, ",Float Algorithm,,Integer Algorithm\r\n" ) ;
   fprintf( pfw, "Test Number,Steps,Distance,Steps,Distance\r\n" ) ;

   for ( int j=0 ; j < 45 ; j++ )
   {
      for ( int k=0 ; k < 2 ; k++ )
      {
         sprintf( pInFile, "j:/mems/mems_sf%s/output/log_output/stepDetect%02d.log", extension[k], j+1 ) ;

         if ( (pfr = fopen ( pInFile, "rb" )) == NULL )
         {
            printf ("Err: can't open input file: %s\r\n", pInFile ) ;
            exit(0) ;
         }

         while ( fgets( szInput, sizeof(szInput), pfr ) )
         {
            char *p ;

            if ( !(p=strstr( szInput, "Steps= " )) )
               continue;

            int   steps ;
            float distance ;

            sscanf( p, "Steps= %d, distance: %f", &steps, &distance ) ;

            if ( !k )
               sprintf( szOutput, "%d,%d,%.02f", j+1, steps, distance ) ;
            else
               sprintf( szOutput, ",%d,%.02f\r\n", steps, distance ) ;

            fprintf( pfw, szOutput ) ;
         }
         fclose(pfr) ;
      }
   }
   fclose(pfw) ;
}
