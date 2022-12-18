#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "serialize.h"

#define UBITNAME "jv"

// return Message Type, if input is valid, else -1.
int get_type(char *input) {
    if (*input == '/' && !strncmp(input+1, "me",2) && isspace(*(input+3))) {
        input = input+3;
        while (*input) {
            if ( !isspace(*input) ) return STATUS;
            input++;
        }
    } else if ( *input == '@' && !isspace(*(input+1))) {
        int iCount = 0;
        input = input + 1;
        while (*input && iCount < NAME_SIZE) {
            if (isspace(*input)) {
                while (*input) {
                    if (!isspace(*input)) return LABELED;
                    input++;
                }
                break;
            }
            input++;
            iCount++;
        }
    } else if ( *input == '/' && !strncmp(input+1, "stats", 5) &&
                (isspace(*(input+6)) || *(input+6) == '\0')) {
        return STATISTICS;
    } else if ( *input == '/' || *input == '@' ) {
        return -1;
    } else {
        while (*input) {
            if (!isspace(*input)) return MESSAGE;
            input++;
        }
    }

    return -1;

}

// packs the fixed portion. Returns the address of packed after the fixed portion.
void *pack_fixed_part(void *packed, int type) {
    *(int *)packed = type;
    packed += sizeof(int);

    size_t nLength = strlen(UBITNAME);
    strcpy(packed, UBITNAME);
    packed += nLength;

    memset(packed, '\0', NAME_SIZE - strlen(UBITNAME));
    packed += NAME_SIZE - nLength;

    return packed;
}

// packs the data lengths portion into packed.
// packed should point to the position after the fixed part.
// input should point to the start position of the data.
// Returns the address of packed after the data lengths.
void *pack_data_lengths(void *packed, char *input, int type) {
    if (type == LABELED) {
        // get target and message lengths
        size_t tLength=0;
        while (!isspace(*input)) {
            input++;
            tLength++;
        }
        while (isspace(*input)) {
            input++;
        }
        size_t mLength=strlen(input);        

        // pack the message and target lengths
        *(size_t *)packed = mLength;
        packed += sizeof(size_t);        
        *(size_t *)packed = tLength;
        packed += sizeof(size_t);                
    } else { // MESSAGE or STATUS
        size_t iLength = strlen(input);
        *(size_t *)packed = iLength;
        packed += sizeof(size_t);        
    }

    // LABELED, MESSAGE or STATUS
    // pack the last data length - the one with 0 value.
    *(size_t *)packed = 0;
    packed += sizeof(size_t);

    return packed;
}

// packs the data into packed.
// packed should point to the position after the data_lengths part.
// input should point to the start position of the data.
void pack_data(void *packed, char *input, int type) {
    if (type == LABELED) {
        // get target length and message offset
        void *pStart = input;
        size_t tLength=0;
        size_t mOffset = 0;
        while (!isspace(*input)) {
            input++;
            tLength++;
            mOffset++;
        }
        while (isspace(*input)) {
            input++;
            mOffset++;            
        }

        // pack the data - messsage followed with target
        strcpy(packed, pStart+mOffset);
        packed += strlen(pStart+mOffset);
        strncpy(packed, pStart, tLength);
        packed += tLength;

        int rSize = PACKET_SIZE -sizeof(int) - NAME_SIZE - 3 * sizeof(size_t) - strlen(pStart);
        memset(packed, '\0', rSize);
    } else { // MESSAGE or STATUS
        strcpy(packed, input);
        packed += strlen(input);
        int rSize = PACKET_SIZE - sizeof(int) - NAME_SIZE - 2 * sizeof(size_t) - strlen(input);
        memset(packed, '\0', rSize);
    }
}

int pack_message(void *packed, char *input) {

    packed = pack_fixed_part(packed, MESSAGE);
    packed = pack_data_lengths(packed, input, MESSAGE);
    pack_data(packed, input, MESSAGE);
    
    return MESSAGE;    
}

int pack_status(void *packed, char *input) {

    packed = pack_fixed_part(packed, STATUS);
    
    input = input+3;
    while (*input) {
        if ( isspace(*input) ) input++;
        break;
    }

    packed = pack_data_lengths(packed, input, STATUS);
    pack_data(packed, input, STATUS);
    

    return STATUS;
}

int pack_labeled(void *packed, char *input) {

    packed = pack_fixed_part(packed, LABELED);
    input++;
    packed = pack_data_lengths(packed, input, LABELED);
    pack_data(packed, input, LABELED);
    
    return LABELED;    
}

/* Pack the user input provided in input into the appropriate message
 * type in the space provided by packed.  You can assume that input is a
 * NUL-terminated string, and that packed is a buffer of size
 * PACKET_SIZE.
 *
 * Returns the message type for valid input, or -1 for invalid input.
 */
int pack(void *packed, char *input) {
    switch (get_type(input)) {
    case MESSAGE: return pack_message(packed, input);
    case STATUS: return pack_status(packed, input);
    case LABELED: return pack_labeled(packed, input);
    case STATISTICS:
        pack_fixed_part(packed, STATISTICS);
        return STATISTICS;
    default: break;
    }
    return -1;
}

/* Create a refresh packet for the given message ID.  You can assume
 * that packed is a buffer of size PACKET_SIZE.
 *
 * You should start by implementing this method!
 *
 * Returns the message type.
 */
int pack_refresh(void *packed, int message_id) {

    packed = pack_fixed_part(packed, REFRESH);
    
    *(int *)packed = message_id;
    packed += sizeof(int);

    int rSize = PACKET_SIZE - NAME_SIZE - 2 * sizeof(int);
    memset(packed, '\0', rSize);    
    
    return REFRESH;
}
