#include <stdio.h>   /* gets */
#include <stdlib.h>  /* atoi, malloc */
#include <string.h>  /* strcpy */
#include <zlib.h>  
#include "uthash.h"
#include "utlist.h"
#include "utstring.h"
#include "utarray.h"
#include "kseq.h"
#include "common.h"


int
strsplit_size (const char *str, const char *delimiter) {
  /* First count parts number*/
  char *pch;
  int i = 1;
  char *tmp = strdup(str);
  pch = strtok(tmp, delimiter);
  while (pch) {
    pch = strtok(NULL, delimiter);
    if (NULL == pch) break;
	i++;
  }
  free(tmp);
  free(pch);
  return i;
}

int
strsplit (const char *str, char *parts[], const char *delimiter) {	
  char *pch;
  int i = 0;
  char *tmp = strdup(str);
  pch = strtok(tmp, delimiter);

  parts[i++] = strdup(pch);

  while (pch) {
    pch = strtok(NULL, delimiter);
    if (NULL == pch) break;
    parts[i++] = strdup(pch);
  }

  free(tmp);
  free(pch);
  return 0;
}

void 
kmer_uthash_destroy(struct kmer_uthash **table) {
	/*free the kmer_hash table*/
  struct kmer_uthash *cur, *tmp;
  HASH_ITER(hh, *table, cur, tmp) {
      HASH_DEL(*table, cur);  /* delete it (users advances to next) */
      free(cur);            /* free it */
    }
}

char* 
concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    strcpy(result, s1);
	strcat(result, s2);
	return result;
}

char* 
strToUpper(char* s){
	int i, n;
	n=strlen(s);
	char* r;
	r = (char*)malloc(n * sizeof(char));
	for(i=0; i < n; i++){
		r[i] = toupper(s[i]);
	}
	r[n] = '\0';
	return r;
}

int 
write_kmer_htable(struct kmer_uthash **htable, char *fname){
	/* write htable to disk*/
	FILE *ofp = fopen(fname, "w");
	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n", fname);
	  exit(1);
	}
	struct kmer_uthash *s, *tmp;
	HASH_ITER(hh, *htable, s, tmp) {
		/* print the head */
		fprintf(ofp, ">%s\t%d\n", s->kmer, s->count);		
		for(int i=0; i < s->count; i++){
			if(i==0){
				fprintf(ofp, "%s", s->pos[i]);																
			}else{
				fprintf(ofp, "|%s", s->pos[i]);
			}
		}
		fprintf(ofp, "\n");
	}
	fclose(ofp);
	return 0;
}

void 
fasta_uthash_destroy(struct fasta_uthash **table) {
	/*free the kmer_hash table*/
  struct fasta_uthash *cur, *tmp;
  HASH_ITER(hh, *table, cur, tmp) {
      HASH_DEL(*table, cur);  /* delete it (users advances to next) */
      free(cur);            /* free it */
    }
}
