#include <stdlib.h>
#include <string.h>

#include "serialize.h"

int unpack_data(char *unpacked, void *packed, int type) {
    packed = packed + sizeof(int);
    strcpy(unpacked, packed);
    size_t nLen = strlen(packed);
    if ( nLen == 0 || nLen > NAME_SIZE ) return -1;
    unpacked += nLen;
    packed += NAME_SIZE;
    switch (type) {
    case STATUS:
        strcpy(unpacked, " ");
        unpacked += 1;
        break;
    case MESSAGE:
    case LABELED:
        strcpy(unpacked, ": ");
        unpacked += 2;
    default: return -1;
    }

    if (type == LABELED) {
        // get length of message
        size_t mLength = *(size_t *)packed;
        packed += sizeof(size_t)*3;
        // unpack the target
        strcpy(unpacked, "@");
        unpacked++;
        size_t tLength = strlen(packed+mLength);
        if (mLength == 0 || tLength == 0 || (mLength+tLength) > MAX_MESSAGE_SIZE)
            return -1;
        strcpy(unpacked, packed+mLength);
        unpacked+=tLength;
        strcpy(unpacked, " ");
        unpacked++;
        // unpack the message
        strncpy(unpacked, packed, mLength);
        *(unpacked+mLength) = '\0';
    } else { // MESSAGE or STATUS
        packed += sizeof(size_t)*2;
        size_t mLength = strlen(packed);
        if (mLength == 0 || mLength > MAX_MESSAGE_SIZE) return -1;
        strcpy(unpacked, packed);
    }
    
    return type;
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
    int type = *(int *)packed;
    switch ( type ) {
    case MESSAGE: return unpack_data(unpacked, packed, MESSAGE);
    case STATUS: return unpack_data(unpacked, packed, STATUS);
    case LABELED: return unpack_data(unpacked, packed, LABELED);
    default: return -1;
    }
    
    return -1;
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
    char *sender = (char *)(packed + sizeof(int));
    packed += NAME_SIZE;
    char *most_active = (char *)packed;
    packed += NAME_SIZE;
    int most_active_count = *(int *)packed;
    packed += sizeof(int);
    long invalid_count = *(long *)packed;
    packed += sizeof(long);
    long refresh_count = *(long *)packed;
    packed += sizeof(long);
    int messages_count = *(int *)packed;    
    
    void *temp = (void *)statistics;
    strcpy((char *)temp, (char *)sender); // sender
    temp += NAME_SIZE+1;
    int tSize = NAME_SIZE+1;
    size_t padding = -tSize % sizeof(int); // lookup modulo of negative number
    temp += padding;
    tSize += padding;
    *(int *)temp = messages_count; // messages_count
    temp += sizeof(int);
    tSize += sizeof(int);
    strcpy((char *)temp, (char *)most_active); // most_active
    temp += NAME_SIZE+1;
    tSize += NAME_SIZE+1;
    padding = -tSize % sizeof(int);
    temp += padding;
    tSize += padding;
    *(int *)temp = most_active_count; // most_active_count
    temp += sizeof(int);
    tSize += sizeof(int);
    padding = -tSize % sizeof(long);
    temp += padding;
    tSize += padding;
    *(long *)temp = invalid_count; // invalid_count
    temp += sizeof(long);
    *(long *)temp = refresh_count; // refresh_count
    
    return STATISTICS;
}
