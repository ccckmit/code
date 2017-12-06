#include <stdarg.h>
#include <stddef.h>

char *concat(const char *str, ...)
{
  va_list ap;
  size_t allocated = 100;
  char *result = (char *) malloc (allocated);
   
  if (result != NULL)
  {
    char *newp, *wp;
	const char *s;
   
    va_start (ap, str);
    wp = result;
    for (s = str; s != NULL; s = va_arg (ap, const char *))
    {
      size_t len = strlen (s);
   
      /* Resize the allocated memory if necessary.  */
      if (wp + len + 1 > result + allocated)
      {
        allocated = (allocated + len) * 2;
        newp = (char *) realloc (result, allocated);
        if (newp == NULL)
        {
          free (result);
          return NULL;
        }
        wp = newp + (wp - result);
        result = newp;
      }
      wp = mempcpy (wp, s, len);
    }
    /* Terminate the result string.  */
    *wp++ = '\0';   
    /* Resize memory to the optimal size.  */
    newp = (char*) realloc (result, wp - result);
    if (newp != NULL)
    result = newp;   
    va_end (ap);
  }
  return result;
}

int main() {
  char str[] = "abc";
  char *s = str;
  char *newstr = concat(s, "def", "ghi", "jkl", NULL);
  printf("newstr=%s\n", newstr);
}

