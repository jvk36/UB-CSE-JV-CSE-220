#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define UBIT_NAME "annkonna"

#include "serialize.h"

// Return type if the input is valid else return -1
int get_input_type(char *input){
    if (strncmp(input,"/me", 3) == 0){
        if(!isspace(*(input+3))){
            return -1;
        }
        for(int i = 4; *(input + i) != '\0'; i++){
            if(!isspace(*(input + i))){
                return STATUS;
            }
        }
        return -1;
    } else if(strncmp(input, "/stats", 6) == 0){
        if (strlen(input) > 6 && !isspace(*(input +6))){
            return -1;
        }
        return STATISTICS;
    } else if(strncmp(input, "@", 1) == 0){
        if(isspace(*(input+1))){
            return -1;
        }
        while(*input != '\0'){
            if(isspace(*(input))){
                while(*input != '\0'){
                    if(!isspace(*(input))){
                        return LABELED;
                    }
                    input = input + 1;
                }
                return -1;
            }
            input = input + 1;
        }
        return -1;
    } else{
        for(int i = 0; *(input + i) != '\0'; i++){
            if(!isspace(*(input + i))){
                return MESSAGE;
            }
        }
        return -1;
    }
    
    return -1;
}

/* Set the fixed part of the packet and returns the address
 * right after the fixed part.
 */

void *set_fixed_part(void *packed, int type){
    *(int *)packed = type;
    packed = packed + sizeof(int);
    char *ubitName = UBIT_NAME;
    for (int i = 0; i < strlen(UBIT_NAME); i++){
        *(char *)packed = *(ubitName + i);
        packed = packed + 1;
    }
    for (int j = 0; j < NAME_SIZE - strlen(UBIT_NAME); j++){
        *(char *)packed = '\0';
        packed = packed + 1;
    }
    return packed;
}

/* Set the variable part of packet when the type is LABELED
 * It takes the address of the packet right after the UBIT_NAME
 * Returns LABELED if packed else -1.
 */

int pack_labeled_type(void *packed, char *input){
    int t_length = 0;
    char *pos = input+1;
    int count = sizeof(int) + NAME_SIZE*sizeof(char);
    for(int i = 1; !isspace(*pos); i++){
        t_length = t_length + 1;
        pos = pos + 1;
    }
    for(int j = 0; isspace(*pos); j++){
        pos = pos + 1;
    }
    int m_length = strlen(pos);
    
    *(size_t *)packed = m_length;
    packed = packed + sizeof(size_t);
    count = count + sizeof(size_t);
    *(size_t *)packed = t_length;
    packed = packed + sizeof(size_t);
    count = count + sizeof(size_t);
    *(size_t *)packed = 0;
    packed = packed + sizeof(size_t);
    count = count + sizeof(size_t);
    strcpy(packed, pos);
    packed = packed + m_length;
    count = count + m_length;
    strncpy(packed, input + 1, t_length);
    packed = packed + t_length;
    count = count + t_length;
    for(int k = 0; k < PACKET_SIZE - count; k++){
        *(char *)packed = '\0';
        packed = packed + 1;
    }
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
    int type = get_input_type(input);
    if (type != MESSAGE && type != STATUS && type != LABELED && type != STATISTICS){
        return -1;
    }
    
    packed = set_fixed_part(packed, type);
    
    if(type == STATISTICS){
        return type;
    }
    
    int count = sizeof(int)+NAME_SIZE * sizeof(char);

    if(type == LABELED){
        return pack_labeled_type(packed, input);
    }
    
    if(type == STATUS){
        input = input + 3;
        while(isspace(*input)){
            input = input + 1;
        }
    }

    *(size_t *)packed = strlen(input);
    packed = packed + sizeof(size_t);
    count = count + sizeof(size_t);    
    *(size_t *)packed = 0;
    packed = packed + sizeof(size_t);
    count = count + sizeof(size_t);
    for (int k = 0; k < strlen(input); k++){
        *(char *)packed = *(input + k);
        packed = packed + 1;
        count = count + 1;
    }
    for (int m = 0; m < PACKET_SIZE - count; m++){
        *(char *)packed = '\0';
        packed = packed + 1;
    }
    return type;
}

/* Create a refresh packet for the given message ID.  You can assume
 * that packed is a buffer of size PACKET_SIZE.
 *
 * You should start by implementing this method!
 *
 * Returns the message type.
 */
int pack_refresh(void *packed, int message_id) {
    *(int *)packed = REFRESH;
    int count = 0;
    packed = packed + sizeof(int);
    count = count + sizeof(int);
    for(int i = 0; i < strlen(UBIT_NAME); i++){
        *(char *)packed = *(UBIT_NAME + i);
        packed = packed + 1;
        count = count + 1;
    }
    for(int j = 0; j < NAME_SIZE - strlen(UBIT_NAME); j++){
        *(char *)packed = '\0';
        packed = packed + 1;
        count = count + 1;
    }
    *(int *)packed = message_id;
    packed = packed + sizeof(int);
    count = count + sizeof(int);
    for(int k = 0; k < PACKET_SIZE - count; k++){
        *(char *)packed = '\0';
        packed = packed + 1;
    }
    return REFRESH;
}

