/*
 * fourth prototype - linked-list logic with libcdada (JSON version)
 *
 * 1. Invoke generator with the types you want to support
 *    ~/Projects/libcdada/tools/cdada-gen list:nf9_fwdstatus -o ~/Projects/pmacct_nf9_fwdstatus/autogen_cdada_nf9_fwdstatus.cc
 *
 * 2. Add header includes for types 'nf9_fwdstatus' in the place holder
 *    vim ~/Projects/pmacct_nf9_fwdstatus/autogen_cdada_nf9_fwdstatus.cc
 *
 * 3. Add to your build system
 *    g++ -c ~/Projects/pmacct_nf9_fwdstatus/autogen_cdada_nf9_fwdstatus.cc
 *
 * 4. Link your application; make sure to link against -lcdada:
 *    cd ~/Projects/pmacct_nf9_fwdstatus/
 *    gcc -Wall pmacct_nf9_fwdstatus_json_p4.c autogen_cdada_nf9_fwdstatus.o -o bin/pmacct_nf9_fwdstatus_json_p4 -lcdada -lstdc++ -ljansson
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <jansson.h>
#include <cdada/list.h>
#include "cdada_types/nf9_fwdstatus.h"

CDADA_LIST_CUSTOM_TYPE_DECL(nf9_fwdstatus);


/* Function prototypes */
size_t generate_rnd(void);
cdada_list_t *nf9_fwdstatus_to_linked_list();
//
// --- JSON prototypes ---
//
json_t *compose_nf9_fwdstatus_json_data(size_t, cdada_list_t *, size_t);


int main(void)
{
  while(1)
  {
    /* rnd unsigned int (0 - 256) generation */
    size_t rnd = generate_rnd();

    /* linked-list creation */
    cdada_list_t *nf9_fwdstatus_ll = nf9_fwdstatus_to_linked_list();
    int ll_size = cdada_list_size(nf9_fwdstatus_ll);

    json_t *root_l0 = json_object();
    json_t *root_l1 = compose_nf9_fwdstatus_json_data(rnd, nf9_fwdstatus_ll, ll_size);

    json_object_set_new(root_l0, "forwarding_status", root_l1);

    char *j_dump_final  = json_dumps(root_l0, JSON_INDENT(2));
    printf("%s\n", j_dump_final);
    free(j_dump_final);

    json_decref(root_l0);
    cdada_list_destroy(nf9_fwdstatus_ll);

    sleep(1);
  }

  return (0);
}


size_t generate_rnd()
{
  size_t rnd;

  srand((size_t) time(0));
  rnd = rand() % 256;

  printf("\n%lu\n", rnd);

  return rnd;
}


/* nf9_fwdstatus to linked-list */
cdada_list_t *nf9_fwdstatus_to_linked_list()
{
  const unsigned int nf9_fwdstatus_decimal[23] = {
    64, 65, 66,
    128, 129, 130,
    131, 132, 133,
    134, 135, 136,
    137, 138, 139,
    140, 141, 142,
    143, 192, 193,
    194, 195
  };

  const char nf9_fwdstatus_description[23][50] = {
    "FWD Unknown",
    "FWD Fragmented",
    "FWD Not Fragmented",
    "DROP Unknown",
    "DROP ACL deny",
    "DROP ACL drop",
    "DROP Unroutable",
    "DROP Adjacency",
    "DROP Fragmentation and DF set",
    "DROP Bad header checksum",
    "DROP Bad total Length",
    "DROP Bad header length",
    "DROP bad TTL",
    "DROP Policer",
    "DROP WRED",
    "DROP RPF",
    "DROP For us",
    "DROP Bad output interface",
    "DROP Hardware",
    "CONSUMED Unknown",
    "CONSUMED Punt Adjacency",
    "CONSUMED Incomplete Adjacency",
    "CONSUMED For us",
  };

  cdada_list_t *nf9_fwdstatus_linked_list = cdada_list_create_custom(nf9_fwdstatus);
  nf9_fwdstatus fwdstate;

  size_t idx_0;
  for (idx_0 = 0; idx_0 < 23; idx_0++) {
    memset(&fwdstate, 0, sizeof(fwdstate));
    fwdstate.decimal = nf9_fwdstatus_decimal[idx_0];
    strcpy(fwdstate.description, nf9_fwdstatus_description[idx_0]);

    cdada_list_push_back(nf9_fwdstatus_linked_list, &fwdstate);
  }

  return nf9_fwdstatus_linked_list;
}


//
// --- JSON functions ---
//
json_t *compose_nf9_fwdstatus_json_data(size_t fwdstatus_rnd, cdada_list_t *ll, size_t ll_size)
{
  nf9_fwdstatus fwdstate;

  printf("\nstart -> linked-list:\n");
  size_t idx_0;
  for (idx_0 = 0; idx_0 < ll_size; idx_0++) {
    cdada_list_get(ll, idx_0, &fwdstate);
    printf("nf9_fwdstatus: %s\n", fwdstate.description);
  }
  printf("\n\n---\n");

  json_t *root = json_string();

  int idx_1;
  for (idx_1 = 0; idx_1 < ll_size; idx_1++) {
    cdada_list_get(ll, idx_1, &fwdstate);
    if (fwdstate.decimal == fwdstatus_rnd) {
      json_string_set(root, fwdstate.description);
    }
  }

  return root;
}
