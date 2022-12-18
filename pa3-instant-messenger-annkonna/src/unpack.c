#include <stdlib.h>
#include <string.h>

#include "serialize.h"

int get_packet_type(void *packed){
    int type = *(int *)packed;
    switch(type){
    case REFRESH: return REFRESH;
    case STATUS: return STATUS;
    case MESSAGE: return MESSAGE;
    case LABELED: return LABELED;
    case STATISTICS: return STATISTICS;
    default: return -1;
    }
    return -1;
}

int unpack_labeled_type(char *unpacked, void *packed){
    packed = packed + sizeof(int);
    strcpy(unpacked, packed);
    unpacked = unpacked + strlen(packed);
    packed = packed + NAME_SIZE;
    int m_length = *(size_t *)packed;
    packed = packed + 3*sizeof(size_t);
    strcpy(unpacked, ": @");
    unpacked = unpacked + 3;
    strcpy(unpacked, packed + m_length);
    unpacked = unpacked + strlen(packed+m_length);
    *unpacked = ' ';
    unpacked = unpacked + 1;
    strncpy(unpacked, packed, m_length);
    *(unpacked + m_length) = '\0';
    return LABELED;
}

/* Unpack the given message into the buffer unpacked.  You can assume
 * that packed points to a message buffer large enough to hold the
 * message described therein, but you cannot assume that the message is
 * otherwise valid.  You can assume that unpacked points to a character
 * buffer large enough to store the unpacked message, if it is a valid
 * message.
 *
 * Returns the message type that was unpacked, or -1 if it is invalid.
 */

int unpack(char *unpacked, void *packed) {
    int type = get_packet_type(packed);
    if(type != STATUS && type != MESSAGE && type != LABELED){
       return -1;
    }
    if(type == LABELED){
        return unpack_labeled_type(unpacked, packed);
    }
    int count = 0;
    packed = packed + sizeof(int);
    size_t len = strlen(packed);
    for(int i = 0; i < len; i++){
        *(char *)unpacked = *(char *)packed;
        packed = packed + 1;
        unpacked = unpacked + 1;
        count = count + 1;
    }
    if(type == MESSAGE){
        strcpy(unpacked, ": ");
        unpacked = unpacked + 2;
    } else {
        strcpy(unpacked, " ");
        unpacked = unpacked + 1;
    }
    for(int j = 0; j < NAME_SIZE - count; j++){
        packed = packed + 1;
    }
    packed = packed + 2*sizeof(size_t);
    len = strlen(packed);
    for(int k = 0; k < len; k++){
        *(char *)unpacked = *(char *)packed;
        packed = packed + 1;
        unpacked = unpacked + 1;
    }
    *(char *)unpacked = '\0';
//    strcpy(unpacked, "annkonn: Hello Appa");
    return MESSAGE;
}

/* Unpack the given packed message into the given statistics structure.
 * You can assume that packed points to a message buffer large enough to
 * hold the statistics message, but you cannot assume that it is
 * otherwise valid.  You can assume that statistics points to a
 * statistics structure.
 *
 * Returns the message type that was unpacked, or -1 if it is invalid.
 */
int unpack_statistics(struct statistics *statistics, void *packed) {
    packed = packed + sizeof(int);
    strncpy(statistics->sender, packed, NAME_SIZE);
    statistics->sender[NAME_SIZE] = '\0';
    packed = packed + NAME_SIZE * sizeof(char);
    strncpy(statistics->most_active, packed, NAME_SIZE);
    statistics->most_active[NAME_SIZE] = '\0';
    packed = packed + NAME_SIZE * sizeof(char);
    statistics->most_active_count = *(int *)packed;
    packed = packed + sizeof(int);
    statistics->invalid_count = *(long *)packed;
    packed = packed + sizeof(long);
    statistics->refresh_count = *(long *)packed;
    packed = packed + sizeof(long);
    statistics->messages_count = *(int *)packed;
    return STATISTICS;
}
