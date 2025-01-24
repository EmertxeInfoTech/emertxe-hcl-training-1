#include <stdlib.h>
#include <stdio.h>

struct numbers
{
  int n;
  int *nums;
};

int n;
struct numbers *number;

void create_numbers (struct numbers **nrs, int *n)
{
  *n = 2;
  *nrs = malloc ((sizeof (struct numbers) * 3));
  struct numbers *nm = *nrs;
  for (int i = 0; i < *n; i++)
    {
      nm->n = i + 1;
      nm->nums = malloc (sizeof (int) * (i + 1));
      for (int j = 0; j < i + 1; j++)
        nm->nums[j] = i + j;
      nm++;
    }
}

void output_report ()
{ 
  puts ("numbers"); 
  for (int i = 0; i < number->n; i++)
    printf ("Number: %d\n", number->nums[i]);
  printf ("\n");
}

int main ()
{ 
  create_numbers (&number, &n);
  struct numbers *temp = number;

  for (int i = 0; i < n; i++)
    {
      output_report ();
      number++;
    }
    free(temp);
    return 0;
}