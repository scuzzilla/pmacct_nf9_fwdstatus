#ifndef NF9_FWDSTATUS
#define NF9_FWDSTATUS

/* Data structures */
typedef struct {
  unsigned int decimal;
  char description[50];
} __attribute__((packed)) nf9_fwdstatus;

#endif
