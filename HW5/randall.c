/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

//#include <cpuid.h>
#include <errno.h>
#include <immintrin.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "./options.h"
#include "./output.h"
#include "./rand64-hw.h"
#include "./rand64-sw.h"

char* rsrc;
/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  /* Check arguments.  */
  	//long long nbytes;
  	struct opts opts;
  	optionProcess(argc, argv, &opts);
	if (opts.valid == false)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  	long long nbytes = opts.nbytes;
  /* If there's no work to do, don't worry about which library to use.  */
  	if (nbytes == 0)
    	return 0;

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
	void (*initialize) (void);
	unsigned long long (*rand64) (void);
	void (*finalize) (void);
  
    if (opts.input == MRAND48_R) 
	{
		initialize = mrand48_rng_init;
		rand64 = mrand48_rng;
		finalize = mrand48_rng_fini;
	}
	else if (opts.input == SLASH_F)  
	{
		rsrc = opts.r_src;
		initialize = software_file_init; 
		rand64 = software_file;
		finalize = software_file_fini;
	}
	else
	{
		if (rdrand_supported ())
	  	{
			initialize = hardware_rand64_init;
			rand64 = hardware_rand64;
			finalize = hardware_rand64_fini;
	  	}
		else
	  	{
			initialize = software_rand64_init;
			rand64 = software_rand64;
			finalize = software_rand64_fini;
	  	}
	}

	initialize ();
	long long outbytes;
	int size = sizeof rand64 ();
	int output_errno = 0;


	if (opts.block == -1) 
	{ 
		do
		{
			unsigned long long x = rand64 ();
			outbytes = nbytes < size ? nbytes : size;
			if (!writebytes (x, outbytes))
			{
				output_errno = errno;
				break;
			}
			nbytes -= outbytes;
		  }
		while (0 < nbytes);
	  }
	  else 
	  { 
		char *buffer;
		outbytes = opts.block*1024.0;
		int numloops = (int)(nbytes / outbytes);
		int num = numloops;

		while(num > 0) 
		{
			buffer = (char*) malloc(outbytes);

			if (opts.input == MRAND48_R) 
			{
			  for (int i = 0; i < (outbytes/4); i++) 
			  {
				unsigned long long x = rand64 ();
				memcpy(buffer + 4*i, &x, 4);  
			  }
			}
			else 
			{
			  for (int i = 0; i < (outbytes/8); i++) 
			  {
				unsigned long long x = rand64 ();
				memcpy(buffer + 8*i, &x, 8);  
			  }
			}
			if (!write(1, buffer, outbytes))
			{
			  output_errno = errno;
			  break;
			}
			free(buffer);
			num--;
		} 
 

		int remainder = nbytes - (outbytes*numloops);
		buffer = (char*) malloc(remainder);
		if (opts.input == MRAND48_R) 
		{
		  if (remainder < 4 && remainder > 0) 
		  {
			 unsigned long long x = rand64 ();
			 memcpy(buffer, &x, remainder);
		  }

		  for (int i = 0; i < (remainder/4); i++) 
		  {
			unsigned long long x = rand64 ();
			memcpy(buffer + 4*i, &x, 4);  
		  }
		}
		else 
		{
		  if (remainder < 8 && remainder > 0) 
		  {
			 unsigned long long x = rand64 ();
			 memcpy(buffer, &x, remainder);
		  }
		  for (int i = 0; i < (remainder/8); i++) 
		  {
			 unsigned long long x = rand64 ();
			 memcpy(buffer + 8*i, &x, 8); 
		  }
		}
		if (remainder > 0) 
		{
		  if (!write(1, buffer, remainder)) 
		  {
			output_errno = errno;
		  } 
		}
		free(buffer);
	  }


  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
    }

  finalize ();
  return !!output_errno;
}
