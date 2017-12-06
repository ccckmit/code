#include <stdio.h>
#include <string.h>
#include <iconv.h>
#include <wctype.h>

int main(int argc, char **argv)
{
  FILE *fin, *fout;
  char *encFrom, *encTo;
  char bufin[1024], bufout[1024], *sin, *sout;
  int mode, lenin, lenout, ret, nline;
  iconv_t c_pt;

  if (argc != 5) {
    printf("Usage: a.out <encFrom> <encTo> <fin> <fout>\n");
    return 0;
  }
  encFrom = argv[1];
  encTo   = argv[2];
  if ((fin = fopen(argv[3], "rt")) == NULL) {
    printf("Cannot open file: %s\n", argv[3]);
    return -1;
  }
  if ((fout = fopen(argv[4], "wt")) == NULL) {
    printf("Cannot open file: %s\n", argv[4]);
    return -1;
  }

  if ((c_pt = iconv_open(encTo, encFrom)) == (iconv_t)-1) {
    printf("iconv_open false: %s ==> %s\n", encFrom, encTo);
    return -1;
  }
  iconv(c_pt, NULL, NULL, NULL, NULL);

  nline = 0;
  while (fgets(bufin, 1024, fin) != NULL) {
    nline ++;
    lenin  = strlen(bufin) + 1;
    lenout = 1024;
    sin    = bufin;
    sout   = bufout;
    ret = iconv(c_pt, &sin, &lenin, &sout, &lenout);
    printf("%s -> %s: %d: ret=%d, len_in=%d, len_out=%d\n", 
           encFrom, encTo, nline, ret, lenin, lenout);
    if (ret == -1) {
      printf("stop at: %s\n", sin);
      break;
    }
    fprintf(fout, "%s", bufout);
  }
  iconv_close(c_pt);
  fclose(fin);
  fclose(fout);
  return 0;
}
