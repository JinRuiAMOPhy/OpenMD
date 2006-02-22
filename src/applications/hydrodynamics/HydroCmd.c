/*
  File autogenerated by gengetopt version 2.11
  generated with the following command:
  /home/maul/gezelter/tim/program/gengetopt-2.11/src/gengetopt -F HydroCmd 

  The developers of gengetopt consider the fixed text that goes in all
  gengetopt output files to be in the public domain:
  we make no copyright claims on it.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "getopt.h"

#include "HydroCmd.h"

void
cmdline_parser_print_version (void)
{
  printf ("%s %s\n", CMDLINE_PARSER_PACKAGE, CMDLINE_PARSER_VERSION);
}

void
cmdline_parser_print_help (void)
{
  cmdline_parser_print_version ();
  printf("\n"
  "Usage: %s [OPTIONS]...\n", CMDLINE_PARSER_PACKAGE);
  printf("\n");
  printf("  -h, --help              Print help and exit\n");
  printf("  -V, --version           Print version and exit\n");
  printf("  -i, --input=filename    input dump file\n");
  printf("  -o, --output=STRING     output file prefix  (default=`hydro')\n");
  printf("      --viscosity=DOUBLE  viscosity of solvent\n");
  printf("      --sigma=DOUBLE      diameter of beads(use with rough shell model)\n");
  printf("      --model=STRING      hydrodynamics model (support RoughShell and \n                            BeadModel)\n");
}


static char *gengetopt_strdup (const char *s);

/* gengetopt_strdup() */
/* strdup.c replacement of strdup, which is not standard */
char *
gengetopt_strdup (const char *s)
{
  char *result = (char*)malloc(strlen(s) + 1);
  if (result == (char*)0)
    return (char*)0;
  strcpy(result, s);
  return result;
}

int
cmdline_parser (int argc, char * const *argv, struct gengetopt_args_info *args_info)
{
  int c;	/* Character of the parsed option.  */
  int missing_required_options = 0;

  args_info->help_given = 0 ;
  args_info->version_given = 0 ;
  args_info->input_given = 0 ;
  args_info->output_given = 0 ;
  args_info->viscosity_given = 0 ;
  args_info->sigma_given = 0 ;
  args_info->model_given = 0 ;
#define clear_args() { \
  args_info->input_arg = NULL; \
  args_info->output_arg = gengetopt_strdup("hydro") ;\
  args_info->model_arg = NULL; \
}

  clear_args();

  optarg = 0;
  optind = 1;
  opterr = 1;
  optopt = '?';

  while (1)
    {
      int option_index = 0;
      char *stop_char;

      static struct option long_options[] = {
        { "help",	0, NULL, 'h' },
        { "version",	0, NULL, 'V' },
        { "input",	1, NULL, 'i' },
        { "output",	1, NULL, 'o' },
        { "viscosity",	1, NULL, 0 },
        { "sigma",	1, NULL, 0 },
        { "model",	1, NULL, 0 },
        { NULL,	0, NULL, 0 }
      };

      stop_char = 0;
      c = getopt_long (argc, argv, "hVi:o:", long_options, &option_index);

      if (c == -1) break;	/* Exit from `while (1)' loop.  */

      switch (c)
        {
        case 'h':	/* Print help and exit.  */
          clear_args ();
          cmdline_parser_print_help ();
          exit (EXIT_SUCCESS);

        case 'V':	/* Print version and exit.  */
          clear_args ();
          cmdline_parser_print_version ();
          exit (EXIT_SUCCESS);

        case 'i':	/* input dump file.  */
          if (args_info->input_given)
            {
              fprintf (stderr, "%s: `--input' (`-i') option given more than once\n", CMDLINE_PARSER_PACKAGE);
              clear_args ();
              exit (EXIT_FAILURE);
            }
          args_info->input_given = 1;
          args_info->input_arg = gengetopt_strdup (optarg);
          break;

        case 'o':	/* output file prefix.  */
          if (args_info->output_given)
            {
              fprintf (stderr, "%s: `--output' (`-o') option given more than once\n", CMDLINE_PARSER_PACKAGE);
              clear_args ();
              exit (EXIT_FAILURE);
            }
          args_info->output_given = 1;
          if (args_info->output_arg)
            free (args_info->output_arg); /* free default string */
          args_info->output_arg = gengetopt_strdup (optarg);
          break;


        case 0:	/* Long option with no short option */
          /* viscosity of solvent.  */
          if (strcmp (long_options[option_index].name, "viscosity") == 0)
          {
            if (args_info->viscosity_given)
              {
                fprintf (stderr, "%s: `--viscosity' option given more than once\n", CMDLINE_PARSER_PACKAGE);
                clear_args ();
                exit (EXIT_FAILURE);
              }
            args_info->viscosity_given = 1;
            args_info->viscosity_arg = strtod (optarg, NULL);
            break;
          }
          
          /* diameter of beads(use with rough shell model).  */
          else if (strcmp (long_options[option_index].name, "sigma") == 0)
          {
            if (args_info->sigma_given)
              {
                fprintf (stderr, "%s: `--sigma' option given more than once\n", CMDLINE_PARSER_PACKAGE);
                clear_args ();
                exit (EXIT_FAILURE);
              }
            args_info->sigma_given = 1;
            args_info->sigma_arg = strtod (optarg, NULL);
            break;
          }
          
          /* hydrodynamics model (support RoughShell and BeadModel).  */
          else if (strcmp (long_options[option_index].name, "model") == 0)
          {
            if (args_info->model_given)
              {
                fprintf (stderr, "%s: `--model' option given more than once\n", CMDLINE_PARSER_PACKAGE);
                clear_args ();
                exit (EXIT_FAILURE);
              }
            args_info->model_given = 1;
            args_info->model_arg = gengetopt_strdup (optarg);
            break;
          }
          

        case '?':	/* Invalid option.  */
          /* `getopt_long' already printed an error message.  */
          exit (EXIT_FAILURE);

        default:	/* bug: option not considered.  */
          fprintf (stderr, "%s: option unknown: %c\n", CMDLINE_PARSER_PACKAGE, c);
          abort ();
        } /* switch */
    } /* while */


  if (! args_info->input_given)
    {
      fprintf (stderr, "%s: '--input' ('-i') option required\n", CMDLINE_PARSER_PACKAGE);
      missing_required_options = 1;
    }
  if (! args_info->viscosity_given)
    {
      fprintf (stderr, "%s: '--viscosity' option required\n", CMDLINE_PARSER_PACKAGE);
      missing_required_options = 1;
    }
  if (! args_info->model_given)
    {
      fprintf (stderr, "%s: '--model' option required\n", CMDLINE_PARSER_PACKAGE);
      missing_required_options = 1;
    }
  if ( missing_required_options )
    exit (EXIT_FAILURE);

  return 0;
}
