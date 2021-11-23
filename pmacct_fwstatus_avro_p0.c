/*
 * first prototype - linked-list logic with libcdada (AVRO version)
 *
 * 1. Invoke generator with the types you want to support
 *    ~/Projects/libcdada/tools/cdada-gen list:nf9_fwstatus -o ~/Projects/pmacct_nf9_fwstatus/autogen_cdada_nf9_fwstatus.cc
 *
 * 2. Add header includes for types 'nf9_fwstatus' in the place holder
 *    vim ~/Projects/pmacct_nf9_fwstatus/autogen_cdada_nf9_fwstatus.cc
 *
 * 3. Add to your build system
 *    g++ -c ~/Projects/pmacct_nf9_fwstatus/autogen_cdada_nf9_fwstatus.cc
 *
 * 4. Link your application; make sure to link against -lcdada:
 *    cd ~/Projects/pmacct_nf9_fwstatus/
 *    gcc -Wall pmacct_nf9_fwstatus_avro_p0.c autogen_cdada_nf9_fwstatus.o -o bin/pmacct_nf9_fwstatus_avro_p0 -lcdada -lstdc++ -lavro
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <avro.h>
#include <cdada/list.h>
#include "cdada_types/nf9_fwstatus.h"

CDADA_LIST_CUSTOM_TYPE_DECL(nf9_fwstatus);


//
// --- AVRO global variables ---
//
//avro_schema_t sc_type_record, sc_type_array, sc_type_string;
//avro_value_t v_type_string, v_type_array, v_type_record;
//avro_value_iface_t *if_type_record, *if_type_array, *if_type_string;

//
// --- AVRO prototypes ---
//
//void compose_nf9_fwstatus_avro_schema(void);
//int compose_nf9_fwstatus_avro_data(cdada_list_t *, size_t);
//int print_nf9_fwstatus_avro_data(cdada_list_t *, size_t);
//void free_nf9_fwstatus_avro_data_memory(void);

/* Function prototypes */
size_t generate_rnd(void);
cdada_list_t *nf9_fwstatus_to_linked_list();


int
main(void)
{
  compose_nf9_fwstatus_avro_schema();

  //while(1)
  {
    /* rnd unsigned int (0 - 256) generation */
    //size_t rnd = generate_rnd();

    /* linked-list creation */
    cdada_list_t *ll = nf9_fwstatus_to_linked_list();
    int ll_size = cdada_list_size(ll);

    //compose_nf9_fwstatus_avro_data(ll, ll_size);
    //print_nf9_fwstatus_avro_data(ll, ll_size);
    //free_nf9_fwstatus_avro_data_memory();

    cdada_list_destroy(ll);

    //sleep(1);
  }

  return (0);
}


size_t
generate_rnd()
{
  size_t rnd;

  srand((size_t) time(0));
  rnd = rand() % 256;

  printf("\n%lu\n", rnd);

  return rnd;
}


/* nf9_fwstatus to linked-list */
cdada_list_t *nf9_fwstatus_to_linked_list()
{
  const size_t nf9_fwstatus_decimal[23] = {
    64, 65, 66,
    128, 129, 130,
    131, 132, 133,
    134, 135, 136,
    137, 138, 139,
    140, 141, 142,
    143, 192, 193,
    194, 195
  };

  const char nf9_fwstatus_description[23][50] = {
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

  cdada_list_t *nf9_fwstatus_linked_list = cdada_list_create_custom(tcpflag);
  nf9_fwstatus fwstate;

  size_t idx_0;
  for (idx_0 = 0; idx_0 < 23; idx_0++)
  {
    memset(&fwstate, 0, sizeof(fwstate));
    strcpy(fwstate.decimal, nf9_fwstatus_decimal[idx_0]);
    strcpy(tcpstate.description, nf9_fwstatus_description[idx_0]);

    cdada_list_push_back(nf9_fwstatus_linked_list, &fwstate);
  }

  return nf9_fwstatus_linked_list;
}


/*
//
// --- AVRO functions ---
//
void
compose_tcpflags_avro_schema(void)
{
  sc_type_string = avro_schema_string();
  sc_type_array = avro_schema_array(sc_type_string);
  sc_type_record = avro_schema_record("acct_data", NULL);
  avro_schema_record_field_append(sc_type_record, "tcp_flags", sc_type_array);

  FILE *avro_schema_fp = NULL;
  avro_writer_t avro_schema_writer = NULL;
  avro_schema_fp = fopen("avro_schema.dump", "w");
  avro_schema_writer = avro_writer_file(avro_schema_fp);
  avro_schema_to_json(sc_type_record, avro_schema_writer);
  fclose(avro_schema_fp);
}


int
compose_tcpflags_avro_data(cdada_list_t *ll, size_t ll_size)
{
  tcpflag tcpstate;

  printf("\nstart -> linked-list:\n");
  size_t idx_0;
  for (idx_0 = 0; idx_0 < ll_size; idx_0++)
  {
    cdada_list_get(ll, idx_0, &tcpstate);
    printf("tcpflag: %s\n", tcpstate.flag);
  }

  if_type_record = avro_generic_class_from_schema(sc_type_record);
  if_type_array = avro_generic_class_from_schema(sc_type_array);
  if_type_string = avro_generic_class_from_schema(sc_type_string);

  avro_generic_value_new(if_type_record, &v_type_record);
  avro_generic_value_new(if_type_array, &v_type_array);
  avro_generic_value_new(if_type_string, &v_type_string);

  avro_file_writer_t db_w;
  const char *dbname = "avro_record.db";

  remove(dbname);
  int rval_w = avro_file_writer_create(dbname, sc_type_record, &db_w);
  if (rval_w)
  {
    fprintf(stderr, "Error: %s\n", avro_strerror());
    return -1;
  }

  size_t array_size;
  avro_value_get_size(&v_type_array, &array_size);
  printf("before: %lu\n", array_size);

  size_t idx_1;
  for (idx_1 = 0; idx_1 < ll_size; idx_1++)
  {
    cdada_list_get(ll, idx_1, &tcpstate);
    if (avro_value_get_by_name(&v_type_record, "tcp_flags", &v_type_array, NULL) == 0)
    {
      if (avro_value_append(&v_type_array, &v_type_string, NULL) == 0)
      {
        if (strcmp(tcpstate.flag, "NULL") != 0)
        {
          avro_value_set_string(&v_type_string, tcpstate.flag);
        }
      }
    }
  }
  avro_file_writer_append_value(db_w, &v_type_record);

  avro_file_writer_flush(db_w);
  avro_file_writer_close(db_w);

  avro_value_get_size(&v_type_array, &array_size);
  printf("after: %lu\n", array_size);

  return 0;
}


int
print_tcpflags_avro_data(cdada_list_t *ll, size_t ll_size)
{
  const char *dbname = "avro_record.db";
  avro_file_reader_t db_r;
  int rval_r = avro_file_reader(dbname, &db_r);
  if (rval_r)
  {
    fprintf(stderr, "Error: %s\n", avro_strerror());
    return -1;
  }

  avro_file_reader_read_value(db_r, &v_type_record);
  size_t value_size;
  const char *p = NULL;

  size_t array_size;
  avro_value_get_size(&v_type_array, &array_size);
  printf("\nprint_array_size: %lu\n", array_size);

  size_t idx_0;
  for (idx_0 = 0; idx_0 < ll_size; idx_0++)
  {
    if (avro_value_get_by_name(&v_type_record, "tcp_flags", &v_type_array, NULL) == 0)
    {
      if (avro_value_get_by_index(&v_type_array, idx_0, &v_type_string, NULL) == 0)
      {
        avro_value_get_string(&v_type_string, &p, &value_size);
      }
    }
    //fprintf(stdout, "%lu\n", value_size);
    fprintf(stdout, "%s ", p);
  }
  printf("\n");

  avro_file_reader_close(db_r);

  return 0;
}


void
free_tcpflags_avro_data_memory(void)
{
  avro_value_iface_decref(if_type_record); //no need to decref the associated value
  avro_value_iface_decref(if_type_array); //no need to decref the associated value
  avro_value_iface_decref(if_type_string); //no need to decref the associated value
  avro_schema_decref(sc_type_record);
  avro_schema_decref(sc_type_array);
  avro_schema_decref(sc_type_string);
  //avro_value_decref(&v_type_record);
  //avro_value_decref(&v_type_array);
  //avro_value_decref(&v_type_string);
}
*/
