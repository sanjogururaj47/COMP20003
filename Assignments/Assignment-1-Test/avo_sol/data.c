#include "data.h"
#include <ctype.h>
// demonstration: using getdelim to read .csv
// note that it is simpler just to getline and parse string char by char


//------ HEADER STUFFS: reading column names of csv file  -----------------
// global variables & const for use in this module only
#define NUM_FIELDS 11  // number of fields, assigned for simplicity
static char *dname[NUM_FIELDS];   // the header
void data_get_header(FILE *f) {
	int i;
	for (i=0; i<NUM_FIELDS-1; i++) {
		dname[i]= getfield(f,C);
	}
	dname[i]= getfield(f,NL);
}

void data_free_header() {
	int i;
	for (i=0; i<NUM_FIELDS; i++) {
		free(dname[i]);
	}
}
//--------------------- END OF HEADER STUFFS -----------------


// chop the last char of s if it is delim	
void chop(char *s, char delim) {
	int l= strlen(s)- 1;
	// first: shop \n or \r (Windows problem!) 
	for (; l>=0 && isspace(s[l]) ; l--) s[l]= '\0';
	if (s[l]==delim) s[l]= '\0';
}

// copying s top t, reducing "" to "
//     return 0 if s contains final "
//            1 otherwise (ie. s not yet finished)
int scopy(char *t, char *s, char deli) {
	char *p= t, *q= s;
	char prev=' ';
	while (*q) {
		if (*q==Q && prev!=Q && (*(q+1)!=Q) ) {
			*p= '\0'; 
			return 0;
		}
		if (*q==Q && prev==Q) {
			prev= ' ';
			q++;
			continue;
		}
		prev= *q;
		*p++= *q++;
	}
	*p= '\0';
    return 1;
}

// get & return next csv field, which might or might not start with "
//    the field deds withj "deli", which can be  a comma or a newline
char *getfield(FILE *f, char deli) {
	char *s=NULL;
	size_t l= 0;

	// get first component
    if (getdelim(&s, &l, deli, f) <=0 ) {
		if (s) free(s);
		return NULL;
	}  
	if (*s != Q) {  // simple return for field not starting with "
		chop(s, deli);
		return s;
	}

	char line[FIELD_LEN+3]; // buffer, +3 for possible \r \n \0
	int cont= scopy(line, s+1, deli);  // add first component to buffer

	while (cont) {
		char *p= line+strlen(line);
		getdelim(&s, &l, deli, f);
		cont= scopy(p, s, deli);
	}
    free(s);
	return my_strdup(line);
}	


data_t *get_next_data(FILE *f) {
	char *s= getfield(f,C);
	if (!s) return NULL;

	data_t *d= my_malloc(sizeof(*d));
    d->year= s;
	d->bid= getfield(f,C);
	d->pid= getfield(f,C); 
	d->bpid= getfield(f,C);
	d->clue= getfield(f,C);
	d->name= getfield(f,C);
	d->code= getfield(f,C);
	d->desc= getfield(f,C);
	d->x= getfield(f,C);
	d->y= getfield(f,C);
	// To localize reading errors, read until \n here
	d->loc= getfield(f,NL);
	return d;
}



void free_data(data_t *d) {
	free(d->year); free(d->bid); free(d->pid); free(d->bpid);
    free(d->clue);
	free(d->name);
	free(d->code); 
	free(d->desc);
	free(d->x); free(d->y);
 	free(d->loc);
	free(d);
}	

void print_data(data_t *d, FILE *f) {
	int i;
	for (i=0; i<NUM_FIELDS; i++) {
		if (i!=5) fprintf(f, "%s: ", dname[i]);
		switch (i) {
			case 0:
				fprintf(f,"%s", d->year);
				break;
			case 1:
				fprintf(f,"%s", d->bid);
				break;
			case 2:
				fprintf(f,"%s", d->pid);
				break;
			case 3:
				fprintf(f,"%s", d->bpid);
				break;
			case 4:
				fprintf(f,"%s", d->clue);
				break;
			case 5:
				//fprintf(f,"%s", d->name);
				break;
			case 6:
				fprintf(f,"%s", d->code);
				break;
			case 7:
				fprintf(f,"%s", d->desc);
				break;
			case 8:
				fprintf(f,"%s", d->x);
				break;
			case 9:
				fprintf(f,"%s", d->y);
				break;
			case 10:
				fprintf(f,"%s", d->loc);
				break;
		}
		if (i!=5) fprintf(f, " || ");
	}
	fprintf(f,"\n");
}	
