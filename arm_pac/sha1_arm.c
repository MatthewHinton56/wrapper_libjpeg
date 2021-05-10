#include "sha1_arm.h"

void sha1_process_arm(uint32_t state[5], const uint8_t data[], uint32_t length)
{
       uint32x4_t ABCD, ABCD_SAVED;
       uint32x4_t TMP0, TMP1;
       uint32x4_t MSG0, MSG1, MSG2, MSG3;
       uint32_t   E0, E0_SAVED, E1;

       /* Load state */
       ABCD = vld1q_u32(&state[0]);
       E0 = state[4];
       while (length > 0){
           /* Save state */
           ABCD_SAVED = ABCD;
           E0_SAVED = E0;
           /* Load message */
           if(length<64){
               uint8_t message[64];
               memset(message, 0x00, sizeof(message));
               for(int index = 0; index<length; index++){
                   message[index] = /*(uint8_t)*/data[index];            
               }
	       length = 64;
               MSG0 = vld1q_u32((const uint32_t*)(message));
               MSG1 = vld1q_u32((const uint32_t*)(message + 16));
               MSG2 = vld1q_u32((const uint32_t*)(message + 32));
               MSG3 = vld1q_u32((const uint32_t*)(message + 48));
           }else{
               MSG0 = vld1q_u32((const uint32_t*)(data));
               MSG1 = vld1q_u32((const uint32_t*)(data + 16));
               MSG2 = vld1q_u32((const uint32_t*)(data + 32));
               MSG3 = vld1q_u32((const uint32_t*)(data + 48));
           }
           /* Reverse for little endian */
           MSG0 = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(MSG0)));
           MSG1 = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(MSG1)));
           MSG2 = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(MSG2)));
           MSG3 = vreinterpretq_u32_u8(vrev32q_u8(vreinterpretq_u8_u32(MSG3)));

																	 
       TMP0 = vaddq_u32(MSG0, vdupq_n_u32(0x5A827999));
																	 
       TMP1 = vaddq_u32(MSG1, vdupq_n_u32(0x5A827999));

																	 
       /* Rounds 0-3 */
																	 
       E1 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1cq_u32(ABCD, E0, TMP0);
																	 
       TMP0 = vaddq_u32(MSG2, vdupq_n_u32(0x5A827999));
																	 
       MSG0 = vsha1su0q_u32(MSG0, MSG1, MSG2);

																	 
       /* Rounds 4-7 */
																	 
       E0 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1cq_u32(ABCD, E1, TMP1);
																	 
       TMP1 = vaddq_u32(MSG3, vdupq_n_u32(0x5A827999));
																	 
       MSG0 = vsha1su1q_u32(MSG0, MSG3);
																	 
       MSG1 = vsha1su0q_u32(MSG1, MSG2, MSG3);

																	 
       /* Rounds 8-11 */
																	 
       E1 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1cq_u32(ABCD, E0, TMP0);
																	 
       TMP0 = vaddq_u32(MSG0, vdupq_n_u32(0x5A827999));
																	 
       MSG1 = vsha1su1q_u32(MSG1, MSG0);
																	 
       MSG2 = vsha1su0q_u32(MSG2, MSG3, MSG0);

																	 
       /* Rounds 12-15 */
																	 
       E0 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1cq_u32(ABCD, E1, TMP1);
																	 
       TMP1 = vaddq_u32(MSG1, vdupq_n_u32(0x6ED9EBA1));
																	 
       MSG2 = vsha1su1q_u32(MSG2, MSG1);
																	 
       MSG3 = vsha1su0q_u32(MSG3, MSG0, MSG1);

																	 
       /* Rounds 16-19 */
																	 
       E1 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1cq_u32(ABCD, E0, TMP0);
																	 
       TMP0 = vaddq_u32(MSG2, vdupq_n_u32(0x6ED9EBA1));
																	 
       MSG3 = vsha1su1q_u32(MSG3, MSG2);
																	 
       MSG0 = vsha1su0q_u32(MSG0, MSG1, MSG2);

																	 
       /* Rounds 20-23 */
																	 
       E0 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1pq_u32(ABCD, E1, TMP1);
																	 
       TMP1 = vaddq_u32(MSG3, vdupq_n_u32(0x6ED9EBA1));
																	 
       MSG0 = vsha1su1q_u32(MSG0, MSG3);
																	 
       MSG1 = vsha1su0q_u32(MSG1, MSG2, MSG3);

																	 
       /* Rounds 24-27 */
																	 
       E1 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1pq_u32(ABCD, E0, TMP0);
																	 
       TMP0 = vaddq_u32(MSG0, vdupq_n_u32(0x6ED9EBA1));
																	 
       MSG1 = vsha1su1q_u32(MSG1, MSG0);
																	 
       MSG2 = vsha1su0q_u32(MSG2, MSG3, MSG0);

																	 
       /* Rounds 28-31 */
																	 
       E0 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1pq_u32(ABCD, E1, TMP1);
																	 
       TMP1 = vaddq_u32(MSG1, vdupq_n_u32(0x6ED9EBA1));
																	 
       MSG2 = vsha1su1q_u32(MSG2, MSG1);
																	 
       MSG3 = vsha1su0q_u32(MSG3, MSG0, MSG1);

																	 
       /* Rounds 32-35 */
																	 
       E1 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1pq_u32(ABCD, E0, TMP0);
																	 
       TMP0 = vaddq_u32(MSG2, vdupq_n_u32(0x8F1BBCDC));
																	 
       MSG3 = vsha1su1q_u32(MSG3, MSG2);
																	 
       MSG0 = vsha1su0q_u32(MSG0, MSG1, MSG2);

																	 
       /* Rounds 36-39 */
																	 
       E0 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1pq_u32(ABCD, E1, TMP1);
																	 
       TMP1 = vaddq_u32(MSG3, vdupq_n_u32(0x8F1BBCDC));
																	 
       MSG0 = vsha1su1q_u32(MSG0, MSG3);
																	 
       MSG1 = vsha1su0q_u32(MSG1, MSG2, MSG3);

																	 
       /* Rounds 40-43 */
																	 
       E1 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1mq_u32(ABCD, E0, TMP0);
																	 
       TMP0 = vaddq_u32(MSG0, vdupq_n_u32(0x8F1BBCDC));
																	 
       MSG1 = vsha1su1q_u32(MSG1, MSG0);
																	 
       MSG2 = vsha1su0q_u32(MSG2, MSG3, MSG0);

																	 
       /* Rounds 44-47 */
																	 
       E0 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1mq_u32(ABCD, E1, TMP1);
																	 
       TMP1 = vaddq_u32(MSG1, vdupq_n_u32(0x8F1BBCDC));
																	 
       MSG2 = vsha1su1q_u32(MSG2, MSG1);
																	 
       MSG3 = vsha1su0q_u32(MSG3, MSG0, MSG1);

																	 
       /* Rounds 48-51 */
																	 
       E1 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1mq_u32(ABCD, E0, TMP0);
																	 
       TMP0 = vaddq_u32(MSG2, vdupq_n_u32(0x8F1BBCDC));
																	 
       MSG3 = vsha1su1q_u32(MSG3, MSG2);
																	 
       MSG0 = vsha1su0q_u32(MSG0, MSG1, MSG2);

																	 
       /* Rounds 52-55 */
																	 
       E0 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1mq_u32(ABCD, E1, TMP1);
																	 
       TMP1 = vaddq_u32(MSG3, vdupq_n_u32(0xCA62C1D6));
																	 
       MSG0 = vsha1su1q_u32(MSG0, MSG3);
																	 
       MSG1 = vsha1su0q_u32(MSG1, MSG2, MSG3);

																	 
       /* Rounds 56-59 */
																	 
       E1 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1mq_u32(ABCD, E0, TMP0);
																	 
       TMP0 = vaddq_u32(MSG0, vdupq_n_u32(0xCA62C1D6));
																	 
       MSG1 = vsha1su1q_u32(MSG1, MSG0);
																	 
       MSG2 = vsha1su0q_u32(MSG2, MSG3, MSG0);

																	 
       /* Rounds 60-63 */
																	 
       E0 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1pq_u32(ABCD, E1, TMP1);
																	 
       TMP1 = vaddq_u32(MSG1, vdupq_n_u32(0xCA62C1D6));
																	 
       MSG2 = vsha1su1q_u32(MSG2, MSG1);
																	 
       MSG3 = vsha1su0q_u32(MSG3, MSG0, MSG1);

																	 
       /* Rounds 64-67 */
																	 
       E1 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1pq_u32(ABCD, E0, TMP0);
																	 
       TMP0 = vaddq_u32(MSG2, vdupq_n_u32(0xCA62C1D6));
																	 
       MSG3 = vsha1su1q_u32(MSG3, MSG2);
																	 
       MSG0 = vsha1su0q_u32(MSG0, MSG1, MSG2);

																	 
       /* Rounds 68-71 */
																	 
       E0 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1pq_u32(ABCD, E1, TMP1);
																	 
       TMP1 = vaddq_u32(MSG3, vdupq_n_u32(0xCA62C1D6));
																	 
       MSG0 = vsha1su1q_u32(MSG0, MSG3);

																	 
       /* Rounds 72-75 */
																	 
       E1 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1pq_u32(ABCD, E0, TMP0);

																	 
       /* Rounds 76-79 */
																	 
       E0 = vsha1h_u32(vgetq_lane_u32(ABCD, 0));
																	 
       ABCD = vsha1pq_u32(ABCD, E1, TMP1);

																	 
       /* Combine state */
																	 
       E0 += E0_SAVED;
																	 
       ABCD = vaddq_u32(ABCD_SAVED, ABCD);

																	 
       data += 64;
																	 
       length -= 64;
																	 
   }/* Save state */
   vst1q_u32(&state[0], ABCD);
   state[4] = E0;
}
