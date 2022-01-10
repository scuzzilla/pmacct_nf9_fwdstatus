### Summary

The current implementation of PMACCT is encoding the "IPFIX forwardingStatus" field into decimal format.
It's the job of an external entity to map it into the human-readable format like described by [RFC-7270 Section 4.12](https://www.rfc-editor.org/rfc/rfc7270.html#section-4.12). 
At the moment the "IPFIX forwardingStatus" is handled by defining an ah-hoc [custom-defined primitive](https://github.com/pmacct/pmacct/blob/master/examples/primitives.lst.example).

The main goals of the new implementation are:
1. Embedding the mapping action within PMACCT (decimal-to-humanReadable).
2. Hanndling the "IPFIX forwardingStatus" field like a standard primitive (avoid custom-defined primitive).

The "IPFIX forwardingStatus" field can be, for example, serialized to KAFKA (via the kafka-plugin) using either JSON or AVRO.
The new implementation is taking care of pairing the decimal format with the associated human-readable string before serializing.
A configuration flag is required ot enable the new implementation:
```TEXT
nf9_fwdstatus_encode_as_string: true
```

### Main 'Mapping' Steps:

- PMACCT is returning the decimal representation of the "IPFIX forwardingStatus" field
- An intermediate step is translating from the decimal to the related human-readable string
- Finally, the string is ready to be serialized (for example to kafka, JSON or AVRO supported)  
```C
  /* RFC-7270: forwardingStatus with a compliant reason code */
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
    "FORWARDED Unknown",
    "FORWARDED Fragmented",
    "FORWARDED Not Fragmented",
    "DROPPED Unknown",
    "DROPPED ACL deny",
    "DROPPED ACL drop",
    "DROPPED Unroutable",
    "DROPPED Adjacency",
    "DROPPED Fragmentation and DF set",
    "DROPPED Bad header checksum",
    "DROPPED Bad total Length",
    "DROPPED Bad header length",
    "DROPPED bad TTL",
    "DROPPED Policer",
    "DROPPED WRED",
    "DROPPED RPF",
    "DROPPED For us",
    "DROPPED Bad output interface",
    "DROPPED Hardware",
    "CONSUMED Unknown",
    "CONSUMED Punt Adjacency",
    "CONSUMED Incomplete Adjacency",
    "CONSUMED For us",
  };

```

### JSON output
- Current
```JSON
{                                                                                                                                                              
  "forwarding_status": "decimal_value_string",                                                                                                                                               
  "other1": "other1",
  "other2": "other2",
  "other3": "other3"
} 
```

- Future
```JSON
{                                                                                                                                                              
  "forwarding_status": "human_readable_string",                                                                                                                                              
  "other1": "other1",
  "other2": "other2",
  "other3": "other3"
} 
```

### AVRO schema
- Current
```JSON
/* the decimal is converted to string directly and then serialized*/
{                                                                                                                                                                                                    
  "type": "record",

  "name": "acct_data",                                                                                                             
  "fields": [                                                                                         
    {                                                                                                                                                        
      "name": "forwarding_status",                                                              
      "type": {                                                                                                                                                                         
        "type": "string"                                                                                                            
      }                                                                                                                           
    }
  ]
}
```

- Future
```JSON
/* the decimal is first mapped to the human-readable format and then serialized*/
{                                                                                                                                                                                                    
  "type": "record",

  "name": "acct_data",                                                                                                             
  "fields": [                                                                                         
    {                                                                                                                                                        
      "name": "forwarding_status",                                                              
      "type": {                                                                                                                                                                         
        "type": "string"                                                                                                            
      }                                                                                                                           
    }
  ]
}
```