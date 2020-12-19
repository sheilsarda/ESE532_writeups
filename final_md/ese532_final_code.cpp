#define NFRAMES 256
#define MAX_RESULTS 8*NFRAMES
#define frame_type ap_int<240>
#define lookup_result_type ap_int<128>
#define STATELEN 12
#define KEYLEN (STATELEN+8)
#define KEY_MASK 0x0FFFFF
#define VAL_MASK 0x0FFF
#define NUM_SLOTS 16384
#define BUCKET_MASK 0x0FFFFFFFF
#define slot_type uint32_t
#define BUCKET_CAPACITY 4
#include<stdint.h>
extern lookup_result_type lookup[NUM_SLOTS];
extern uint16_t init_lookup[256];

/**
 * Memories bitpos, lookup, init_lookup, and results are arrays defined in the code above.  
 * 
 * Registers val64, b, state, and result_count are variables defined in the code above.
 */

void extract_compress(frame_type frames[NFRAMES],
                                      uint8_t bitlocs[64],
                                      uint16_t bitpos[KEYLEN],
                                      uint16_t results[MAX_RESULTS],
                                      int *num_results)
{
  uint64_t tmp[NFRAMES];
  
  for (int i=0;i<NFRAMES;i++) { // Loop A
    uint64_t result=0;
    int finalpos=1;
    frame_type val=frames[i];
    for (int j=0;j<64;j++) { // Loop B
       uint8_t bitloc=bitlocs[j];
       for (int k=128;k>0;k=k/2) { // Loop C
            if ((bitloc&0x01)==1)
                val=val/k;
            bitloc=bitloc/2;
         }
       if ((val&0x01)==1)
            result|=finalpos;
       finalpos=finalpos*2;
     }
    tmp[i]=result;
  }
  int result_count=0;
  int state=0;
  for (int i=0;i<NFRAMES;i++) { // Loop D
    uint64_t val64=tmp[i]; // val64 is input to pipeline pix
    for (int b=0;b<8;b++)  // Loop E (also shown in pipeline pix)
      {
        // <see pipeline in next box; complete code for question 4>

        // assign ID_enable register
        int Id_enable = (b == 7);

        /** 
         * Select the correct val8 based on b reg val
         * 
         * Using a switch-case statement here would be 
         * most similar to the mux select operation 
         * described in the diagram.
         */
        uint8_t val8 = val64 >> 8*b && 0xFF;

        uint32_t key = (val8 << STATELEN) | state;
        uint16_t init_lookup_result = init_lookup[val8];

        // Bitwise-XOR operation
        // Loop F
        
        // stores temp result of bitwise-xor operations
        uint8_t temp1[20]; 
        uint8_t temp2[20]; 
        uint8_t temp3[20];

        for (int j = 0; j < 20; ++j)
          temp1[j] = key[j] ? bitpos[j] : 0;
        
        int d = 20;
        while(d > 1){
          for(int k = 0; k < d-1; k+=2)
            temp2[k] = temp1[k] ^ temp1[k + 1];
            temp3 = temp1;
            temp1 = temp2;
            temp2 = temp3;
            d /= 2;
        }
        
        // Loop G - unrolled for ease of writing
        
        // last output of the bitwise-xor gets sent to lookup
        lookup_result_type result = lookup[temp1[0]];
        lookup_result_type temp4[4];
        // inputs to muxes
        temp4[3] = (key[3] == result[127:108]) ? val8[3] : 0;
        temp4[2] = (key[2] == result[95:76]) ? val8[2] : 0;
        temp4[1] = (key[1] == result[63:44]) ? val8[1] : 0;
        temp4[0] = (key[0] == result[31:12]) ? val8[0] : 0;

        // use each of these compare equals outputs to select either slot_val or 0

        // then perform 2 levels of bitwise ors

        // compare equals step to select between bitwise or or init_lookup output

        // Write compare equals output to results memory

        // increment Id_enable
      }
  }
  *num_results=result_count;
  return;
}
