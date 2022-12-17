
#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include <string.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 20


int space_count = 0;
int single_line_comment_count = 0;
int multi_line_comment_count = 0;
int insideStringState = 0;
int flag = 0;


int single_line_comment(char c){
    if( c == '/' && single_line_comment_count == 0 ){
        single_line_comment_count = 1;
        return 0;
    }else if( single_line_comment_count == 1 && c == '/' ){
        single_line_comment_count = 2;
        return 0;
    }else if( single_line_comment_count == 1 ){
        single_line_comment_count = 0;
        return 0;
    }else if( single_line_comment_count == 2 && c == '\n' ){
        single_line_comment_count = 3;
        return 0;
    }else if( single_line_comment_count == 2 ){
        single_line_comment_count = 2;
        return 0;
    }
    else if( single_line_comment_count == 3 ){
        single_line_comment_count = 0;
        return 1;
    }else{
        return 1;
    }
}


int multi_line_comment(char c){
    if( c == '/' && multi_line_comment_count == 0 ){
        multi_line_comment_count = 1;
        return 0;
    }else if( multi_line_comment_count == 1 && c == '*' ){
        multi_line_comment_count = 2;
        return 0;
    }else if( multi_line_comment_count == 1 && c == '/' ){
        multi_line_comment_count = 1;
        return 0;
    }else if( multi_line_comment_count == 1 ){
        multi_line_comment_count = 0;
        return 0;
    }else if( multi_line_comment_count == 2 && c == '*' ){
        multi_line_comment_count = 3;
        return 0;
    }else if( multi_line_comment_count == 2 && c == '/' ){
        multi_line_comment_count = 2;
        return 0;
    }else if( multi_line_comment_count == 2 ){
        multi_line_comment_count = 2;
        return 0;
    }else if( multi_line_comment_count == 3 && c == '/' ){
        multi_line_comment_count = 4;
        return 0;
    }else if( multi_line_comment_count == 3 && c == '*' ){
        multi_line_comment_count = 3;
        return 0;
    }else if( multi_line_comment_count == 3 ){
        multi_line_comment_count = 2;
        return 0;
    }else if( multi_line_comment_count == 4 ){
        multi_line_comment_count = 0;
        return 1;
    }else{
        return 1;
    }
}

int isInsideString(char c){
    if( (c == '"') && insideStringState == 0 ){
        insideStringState = 1;
        return 1;
    }else if( insideStringState == 1 && (c == '"') ){
        insideStringState = 2;
        return 1;
    }else if( insideStringState == 1 ){
        insideStringState = 1;
        return 1;
    }else if( insideStringState == 2 ){
        insideStringState = 0;
        return 1;
    }else{
        return 0;
    }
}


int extra_space_remove(char c){
    if( isInsideString(c) )
        return 1;
    if( c == ' ' )
        space_count += 1;
    if( c == ' ' && space_count > 2 ){
        space_count = 0;
        return 0;
    }
    return 1;
}


int space_state = 0;
int space_remove(char c){
    if( isInsideString(c) )
        return 1;
    if( c == ' ' && space_state == 0 ){
        space_state = 1;
        return 1;
    }else if( c != ' ' && space_state == 0 ){
        space_state = 0;
        return 1;
    }else if( c == ' ' && space_state == 1 ){
        space_state = 0;
        return 0;
    }else{
        space_state = 0;
        return 1;
    }
}

int new_line_remove(char c){
    if( c == '\n' || c == '\t' ){
        return 0;
    }
    return 1;
}


char* assignment_1_output(char *data){
    char c;
    char s[10000] = "";
    for( int i = 0; i < strlen(data); i++){
        c = data[i];
        if( !single_line_comment(c) ){
            flag = 1;
        }

        if( !multi_line_comment(c) ){
            flag = 1;
        }

        if( !space_remove(c) )
            flag = 1;

        if( !new_line_remove(c) )
            flag = 1;

        if( flag != 1 )
            strncat(s, &c, 1);
        else
            flag = 0;
    }
    return strdup(s);
}


//---------------------------------------- ASSIGNMENT 2 --------------------------------------------//

int is_keyword_int(char *C){
    int int_keyword_state = 0;
    int l = strlen(C);
    if( l != 3 )
        return 0;

    for(int i = 0; i < l; i++){
        char c = C[i];
        if( c == 'i' && int_keyword_state == 0 ){
            int_keyword_state = 1;
        }else if( c == 'n' && int_keyword_state == 1 ){
            int_keyword_state = 2;
        }else if( c == 't' && int_keyword_state == 2 ){
            int_keyword_state = 3;
        }else{
            int_keyword_state = 0;
        }
    }

    if( int_keyword_state == 3 ){
        return 1;
    }else{
        return 0;
    }
}

int is_keyword_float(char *C){
    int state = 0;
    int l = strlen(C);
    if( l != 5 )
        return 0;

    for(int i = 0; i < l; i++){
        char c = C[i];
        if( c == 'f' && state == 0 ){
            state = 1;
        }else if( c == 'l' && state == 1 ){
            state = 2;
        }else if( c == 'o' && state == 2 ){
            state = 3;
        }else if( c == 'a' && state == 3 ){
            state = 4;
        }else if( c == 't' && state == 4 ){
            state = 5;
        }else{
            state = 0;
        }
    }

    if( state == 5 ){
        return 1;
    }else{
        return 0;
    }
}

int is_if(char *C){
    int state = 0;
    int l = strlen(C);

    if( l != 2 )
        return 0;

    for(int i = 0; i < l; i++){
        char c = C[i];
        if( c == 'i' && state == 0 ){
            state = 1;
        }else if( c == 'f' && state == 1 ){
            state = 2;
        }else{
            state = 0;
            return 0;
        }
    }

    if( state == 2 ){
        return 1;
    }else{
        return 0;
    }
}

int is_else(char *C){
    int state = 0;
    int l = strlen(C);

    if( l != 4 )
        return 0;

    for(int i = 0; i < l; i++){
        char c = C[i];
        if( c == 'e' && state == 0 ){
            state = 1;
        }else if( c == 'l' && state == 1 ){
            state = 2;
        }else if( c == 's' && state == 2 ){
            state = 3;
        }else if( c == 'e' && state == 3 ){
            state = 4;
        }else{
            state = 0;
            return 0;
        }
    }

    if( state == 4 ){
        return 1;
    }else{
        return 0;
    }
}


int is_keyword_char(char *C){

    int state = 0;
    int l = strlen(C);
    if( l != 4 )
        return 0;

    for(int i = 0; i < l; i++){
        char c = C[i];
        if( c == 'c' && state == 0 ){
            state = 1;
        }else if( c == 'h' && state == 1 ){
            state = 2;
        }else if( c == 'a' && state == 2 ){
            state = 3;
        }else if( c == 'r' && state == 3 ){
            state = 4;
        }
        else{
            state = 0;
        }
    }

    if( state == 4 ){
        return 1;
    }else{
        return 0;
    }
}


int is_keyword(char *C){
    if( is_keyword_int(C) || is_keyword_char(C) || is_keyword_float(C) ){
        return 1;
    }else{
        return 0;
    }
}

int is_keyword_all(char *C){
    int size = 10;
    char kw[size][50] = {
        {'i','n','t','\0'},{'c','h','a','r','\0'},{'f','l','o','a','t','\0'},{'d','o','u','b','l','e','\0'},
        {'i','f','\0'},{'e','l','s','e','\0'},{'b','r','e','a','k','\0'},{'c','o','n','t','i','n','u','e','\0'},{'v','o','i','d','\0'},
        {'r','e','t','u','r','n','\0'}
    };

    for( int i = 0; i < size; i++ ){
        int j = 0;
        int state = 0;
        while( kw[i][j] != '\0' ){
            char c = C[j];
            if( c == kw[i][j] && state == j ){
                state++;
            }else{
                state = 0;
                break;
            }
            j++;
        }
        if( state == j && state != 0 )
            return 1;
    }
    return 0;
}

int is_keyword_all_except_conditional(char *C){
    int size = 8;
    char kw[size][50] = {
        {'i','n','t','\0'},{'c','h','a','r','\0'},{'f','l','o','a','t','\0'},{'d','o','u','b','l','e','\0'},
        {'b','r','e','a','k','\0'},{'c','o','n','t','i','n','u','e','\0'},{'v','o','i','d','\0'},
        {'r','e','t','u','r','n','\0'}
    };

    for( int i = 0; i < size; i++ ){
        int j = 0;
        int state = 0;
        while( kw[i][j] != '\0' ){
            char c = C[j];
            if( c == kw[i][j] && state == j ){
                state++;
            }else{
                state = 0;
                break;
            }
            j++;
        }
        if( state == j && state != 0 )
            return 1;
    }
    return 0;
}

int is_keyword_all_data_type(char *C){
    int size = 5;
    char kw[size][50] = {
        {'i','n','t','\0'},{'c','h','a','r','\0'},{'f','l','o','a','t','\0'},{'d','o','u','b','l','e'},{'l','o','n','g'}
    };

    for( int i = 0; i < size; i++ ){
        int j = 0;
        int state = 0;
        while( kw[i][j] != '\0' ){
            char c = C[j];
            if( c == kw[i][j] && state == j ){
                state++;
            }else{
                state = 0;
                break;
            }
            j++;
        }
        if( state == j && state != 0 )
            return 1;
    }
    return 0;
}


int is_sep(char *C){
    int sep_state = 0;
    int l = strlen(C);
    if( l != 1 )
        return 0;
    char c = C[0];
    if( c == ';' || c == ',' || c == '\'' || c == '"' ){
        sep_state = 1;
    }else{
        sep_state = 0;
    }

    if( sep_state == 1 ){
        sep_state = 0;
        return 1;
    }else{
        sep_state = 0;
        return 0;
    }
}

int is_op(char *C){
    int op_state = 0;
    int l = strlen(C);
    if( !(l >= 1 && l <= 2) )
        return 0;

    for( int i = 0; i < l; i++ ){
        char c = C[i];
        if( c == '<' || c == '>' || c == '=' || c == '!'  ){
            op_state = 1;
        }else if( c == '+' || c == '-' || c == '/' || c == '*' || c == '%'  ){
            op_state = 1;
        }else{
            op_state = 0;
        }
        if( l == 2 ){
            if( op_state == 1 && c == '=' ){
                op_state = 2;
            }else{
                op_state = 0;
            }
        }
    }

    if( l == 1 && op_state == 1 )
        return 1;
    else if( l == 2 && op_state == 2 )
        return 1;
    else
        return 0;
}

int is_par(char *C){
    int state = 0;
    int l = strlen(C);
    if( l != 1 )
        return 0;
    char c = C[0];
    if( c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' ){
        state = 1;
    }else{
        state = 0;
    }

    if( state == 1 ){
        state = 0;
        return 1;
    }else{
        state = 0;
        return 0;
    }
}


int is_par_custom(char *C, char type){
    int state = 0;
    int l = strlen(C);
    if( l != 1 )
        return 0;
    char c = C[0];
    if( c == type ){
        state = 1;
    }else{
        state = 0;
    }

    if( state == 1 ){
        state = 0;
        return 1;
    }else{
        state = 0;
        return 0;
    }
}


int is_id(char *C){

    int state = 0;
    int l = strlen(C);

    if( is_keyword_all(C) )
        return 0;

    for( int i = 0; i < l; i++ ){
        char c = C[i];
        if( isalpha(c) && state == 0 ){
            state = 1;
        }else if( (isalpha(c) || isdigit(c) || c == '_') && state == 1 ){
            state = 1;
        }else{
            state = 0;
            return 0;
        }
    }
    if( state == 1  )
        return 1;
    else
        return 0;
}


int is_num_rec(char *lex)
{
    int i, l, s;
    i=0;
    if(isdigit(lex[i])) {
        s=1; i++;
    }
    else
    if(lex[i]=='.') {
        s=2; i++;
    }
    else s=0;

    l=strlen(lex);
    if(s==1)
        for(;i<l;i++){
            if(isdigit(lex[i]))
                s=1;
            else
                if(lex[i]=='.') {
                    s=2; i++; break;
                }
                else {
                    s=0; break;
                }
        }

    if(s==2)
        if(isdigit(lex[i])) {
            s=3; i++;
        }
        else
            s=0;
        if(s==3)
            for(;i<l;i++) {
                if(isdigit(lex[i]))
                    s=3;
                else {
                    s=0; break;
                }
            }
        if(s==3) s=1;
            return s;
}



char* assignment_2_output(char *data){

    char arr[20];
    int arr_index = 0;

    char c;
    int sepFlag = 0;

    char final_data[10000];
    int fd = 0;

    int k = 0;
    while( data[k] != '\0' ){

        c = data[k];
        char arr2[3];
        arr2[0] = c;
        arr2[1] = '\0';

        if( is_sep(arr2) || is_par(arr2) || is_op(arr2) ){
            if( is_op(arr2) && data[k+1] == '=' ){
                final_data[fd] = ' ';
                fd++;
                final_data[fd] = c;
                fd++;
                final_data[fd] = data[k+1];
                fd++;
                if( data[k+2] != ' ' ){
                    final_data[fd] = ' ';
                    fd++;
                }

                k++;
            }else{
                final_data[fd] = ' ';
                fd++;
                final_data[fd] = c;
                fd++;
                if( data[k+1] != ' ' ){
                    final_data[fd] = ' ';
                    fd++;
                }
            }
        }else{
            final_data[fd] = c;
            fd++;
        }
        k++;
    }
    final_data[fd] = '\0';
    //printf("%s\n", final_data);


    char cln_data[10000];
    int cln = 0;

    int index = 0;
    int space = 0;
    while( final_data[index] != '\0' ){
        if( final_data[index] != ' ' )
            space = 0;
        else if( final_data[index] == ' ' )
            space++;
        if( space > 1 ){
            index++;
            continue;
        }
        cln_data[cln] = final_data[index];
        cln++;
        index++;
    }
    cln_data[cln] = '\0';
    //printf("%s\n", cln_data);


    char the_final_output[10000] = "";
    for( int i = 0; i < strlen(cln_data); i++ ){
        c = cln_data[i];
        if( isspace(c) ){
            arr[arr_index] = '\0';
            is_keyword_char(arr);

            char s1[50];
            char s2[50];

            strcpy(s2,  arr);
            strcat(s2, "]");

            if( is_keyword_all(arr) ){
                strcpy(s1,  "[kw ");
                strcat(s1, s2);
                strcat( the_final_output, s1 );
            }else if( is_sep(arr) ){
                strcpy(s1,  "[sep ");
                strcat(s1, s2);
                strcat( the_final_output, s1 );
            }else if( is_op(arr) ){
                strcpy(s1,  "[op ");
                strcat(s1, s2);
                strcat( the_final_output, s1 );
            }else if( is_par(arr) ){
                strcpy(s1,  "[par ");
                strcat(s1, s2);
                strcat( the_final_output, s1 );
            }else if( is_id(arr) ){
                strcpy(s1,  "[id ");
                strcat(s1, s2);
                strcat( the_final_output, s1 );
            }else if( is_num_rec(arr) ){
                strcpy(s1,  "[num ");
                strcat(s1, s2);
                strcat( the_final_output, s1 );
            }else{
                strcpy(s1,  "[unkn ");
                strcat(s1, s2);
                strcat( the_final_output, s1 );
            }
            arr_index = 0;
            arr[0] = '\0';
            continue;
        }
        arr[arr_index] = c;
        arr_index += 1;
    }
    //printf("%s\n", the_final_output);
    return strdup(the_final_output);
}


//--------------------------------------------------- ASSIGNMENT 3 ----------------------------------- //


struct DataItem {
   char *name;
   char *id_type;
   char *data_type;
   char *scope;
   char *value;
   int key;
};

struct DataItem* hashArray[SIZE];
struct DataItem* item;

int tableSize = 1;

int hashCode(int key) {
   return key % SIZE;
}

struct DataItem *search(int key) {
   int hashIndex = hashCode(key);
   while(hashArray[hashIndex] != NULL) {
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex];
      ++hashIndex;
      hashIndex %= SIZE;
   }
   return NULL;
}

void update(int key,char *name, char *id_type, char *data_type, char *scope, char *value){
    struct DataItem *item = search(key);
    item->name = name;
    item->id_type = id_type;
    //item->data_type = data_type;
    item->scope = scope;
    item->value = value;
}

int searchName(char *name, char *id_type, char *data_type, char *scope, char *value){
    for(int i = 1; i < tableSize; i++){
        struct DataItem* s_item = search(i);
        if( strcmp(name, s_item->name) == 0 && strcmp(id_type, s_item->id_type) == 0 && strcmp(scope, s_item->scope) == 0 && value != NULL ){
            update(i, name, id_type, data_type, scope, value);
            return 2;
        }
        else if( strcmp(name, s_item->name) == 0 && strcmp(id_type, s_item->id_type) == 0 && strcmp(data_type, s_item->data_type) == 0
           && strcmp(scope, s_item->scope) == 0 && value == NULL){
            return 1;
        }
    }
    return 0;
}

void insert(int key,char *name, char *id_type, char *data_type, char *scope, char *value) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->name = strdup(name);
   item->id_type = strdup(id_type);
   item->data_type = strdup(data_type);
   item->scope = strdup(scope);
   item->value = strdup(value);
   item->key = key;
   int hashIndex = hashCode(key);
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      ++hashIndex;
      hashIndex %= SIZE;
   }
   hashArray[hashIndex] = item;
}

void display() {
   printf("\n");
   int i = 0;
   printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", "key", "name", "id_type", "data_type", "scope", "value");
   for(i = 0; i<SIZE; i++) {
      if(hashArray[i] != NULL)
         printf("%d\t\t%s\t\t%s\t\t%s\t\t\t%s\t\t%s\n",hashArray[i]->key, hashArray[i]->name, hashArray[i]->id_type, hashArray[i]->data_type, hashArray[i]->scope, hashArray[i]->value);
   }
   printf("\n");
}


char* clearString( char *str ){
    for( int i = 0; i < 100; i++){
        str[i] = 0;
    }
    return str;
}


int check_if_id(char *C){
    int state = 0;
    char c;
    for(int i = 0; i < strlen(C); i++){
        c = C[i];
        if( c == 'i' && state == 0 ){
            state = 1;
        }else if( c == 'd' && state == 1 ){
            state = 2;
            return 1;
        }else{
            state = 0;
            return 0;
        }
    }
}

int is_num(char *lex)
{
    int i, l, s;
    i=0;
    if(isdigit(lex[i])) {
        s=1; i++;
    }
    else
    if(lex[i]=='.') {
        s=2; i++;
    }
    else s=0;

    l=strlen(lex);
    if(s==1)
        for(;i<l;i++){
            if(isdigit(lex[i]))
                s=1;
            else
                if(lex[i]=='.') {
                    s=2; i++; break;
                }
                else {
                    s=0; break;
                }
        }

    if(s==2)
        if(isdigit(lex[i])) {
            s=3; i++;
        }
        else
            s=0;
        if(s==3)
            for(;i<l;i++) {
                if(isdigit(lex[i]))
                    s=3;
                else {
                    s=0; break;
                }
            }
        if(s==3) s=1;
            return s;
}

char* assignment_3_output_1(char *data){

    char part1[100] = "";
    char part2[100] = "";
    char cleaned[10000] = "";
    int st = 0;

    char c;
    for( int i = 0; i < strlen(data); i++ ){
        c = data[i];
        if( c == '[' && st == 0 ){
            st = 1;
            continue;
        }else if( c == ' ' && st == 1 ){
            st = 2;
            continue;
        }else if( c == ']' && st == 2 ){
            st = 0;
            char x = '[';
            char y = ']';
            char z = ' ';
            if( strcmp(part1, "id") == 0 ){
                strncat(cleaned, &x, 1);
                strcat(cleaned, part1);
                strncat(cleaned, &z, 1);
                strcat(cleaned, part2);
                strncat(cleaned, &y, 1);
                strncat(cleaned, &z, 1);
            }else{
                strncat(cleaned, &x, 1);
                strcat(cleaned, part2);
                strncat(cleaned, &y, 1);
                strncat(cleaned, &z, 1);
            }
            clearString(part1);
            clearString(part2);
            continue;
        }

        if( st == 1 ){
            strncat(part1, &c, 1);
        }else if( st == 2 ){
            strncat(part2, &c, 1);
        }
    }
    return strdup(cleaned);
}


void assignment_3_output_2(char *data[50], int col){

    char *error = "";

    int state = 0;
    int token_state = 0;

    char token[100];
    int index_token = 0;
    int id_state = 0;

    int kw_found = 0;
    int kw_type = 0;

    char token_value[100];
    int tvi = 0;

    int data_type_found = 0;
    int id_found = 0;
    int operator_found = 0;
    int seperator_found = 0;
    int bracket_found = 0;
    int value_found = 0;
    int is_inside_scope = 0;

    char *NAME;
    char *DATA_TYPE;
    char *ID_TYPE;
    char *SCOPE;
    char *VALUE;

    SCOPE = strdup("global");
    char c;
    for( int j = 0; j < col; j++ ){
        for( int i = 0; i < strlen(data[j]); i++ ){
            c = data[j][i];
            if( c == '[' && state == 0 ){
                state = 1;
            }else if( c == ']' ){
                token_value[tvi] = '\0';
                tvi = 0;
                if ( is_keyword_all_data_type(token_value) ){
                    data_type_found = 1;
                    DATA_TYPE = strdup(token_value);
                }else if ( check_if_id(token_value) ){
                    id_found = 1;
                    char temp[100];
                    for( int j = 0; j < 100-3; j++ ){
                        temp[j] = token_value[j+3];
                    }
                    NAME = strdup(temp);
                }else if ( is_op(token_value) ){
                    operator_found = 1;
                }else if ( is_num(token_value) ){
                    if( (data_type_found || id_found) && operator_found ){
                        VALUE = strdup(token_value);
                        value_found = 1;
                    }
                }else if ( is_sep(token_value) ){
                    seperator_found = 1;
                    if( data_type_found && id_found && operator_found && value_found && seperator_found ){
                        ID_TYPE = strdup("var");

                        if ( !searchName(NAME, ID_TYPE, DATA_TYPE, SCOPE, VALUE) ){
                            insert(tableSize, NAME, ID_TYPE, DATA_TYPE, SCOPE, VALUE);

                            char charValue[10];
                            itoa(tableSize, charValue, 10);
                            tableSize++;
                        }else{
                            printf("Error at line %d, Duplicate declaration of variable found!\n", j+1);
                        }

                        data_type_found = 0;
                        id_found = 0;
                        operator_found = 0;
                        seperator_found = 0;
                        value_found = 0;
                    }else if( id_found && operator_found && value_found && seperator_found ){
                        ID_TYPE = strdup("var");

                        if ( !searchName(NAME, ID_TYPE, DATA_TYPE, SCOPE, VALUE) ){
                            insert(tableSize, NAME, ID_TYPE, DATA_TYPE, SCOPE, VALUE);

                            char charValue[10];
                            itoa(tableSize, charValue, 10);
                            tableSize++;
                        }
                        id_found = 0;
                        operator_found = 0;
                        seperator_found = 0;
                        value_found = 0;
                    }else if( data_type_found && id_found && seperator_found ){
                        ID_TYPE = strdup("var");
                        if ( !searchName(NAME, ID_TYPE, DATA_TYPE, SCOPE, NULL) ){
                            insert(tableSize, NAME, ID_TYPE, DATA_TYPE, SCOPE, NULL);

                            char charValue[10];
                            itoa(tableSize, charValue, 10);
                            tableSize++;
                        }else{
                            //char charValue[10];
                            //itoa(j, charValue, 10);
                            //strcat(error, "")
                            printf("Error at line %d, Duplicate declaration of variable found!\n", j+1);
                        }
                        data_type_found = 0;
                        id_found = 0;
                        seperator_found = 0;
                    }
                }else if ( is_par(token_value) ){
                    bracket_found = 1;
                    if( data_type_found && id_found && bracket_found && strcmp(token_value, "(") == 0 ){
                        ID_TYPE = strdup("func");
                        SCOPE = strdup(NAME);
                        insert(tableSize, NAME, ID_TYPE, DATA_TYPE, "global", NULL);

                        char charValue[10];
                        itoa(tableSize, charValue, 10);
                        tableSize++;

                        data_type_found = 0;
                        id_found = 0;
                        bracket_found = 0;
                    }else if( data_type_found && id_found && bracket_found && strcmp(token_value, ")") == 0 ){
                        ID_TYPE = strdup("var");
                        insert(tableSize, NAME, ID_TYPE, DATA_TYPE, SCOPE, NULL);

                        char charValue[10];
                        itoa(tableSize, charValue, 10);
                        tableSize++;

                        data_type_found = 0;
                        id_found = 0;
                        bracket_found = 0;
                    }
                }else{
                    clearString(token_value);
                    tvi = 0;
                }
                state = 0;
                clearString(token_value);
                tvi = 0;
            }else if( state == 1 ){
                token_value[tvi] = c;
                tvi++;
            }
        }

    }

    //display();
    //printf("\n");
}










//---------------------------------------- ASSIGNMENT 4 -------------------------------//



int main(){

    FILE *p1;
    p1 = fopen("assignment4.txt","r");
    char data[50][1000];

    char c;
    int col = 0;
    while( (c = fgetc(p1)) != EOF ){
        strncat(data[col], &c, 1);
        if( c == '\n' )
            col++;
    }
    col++;

    for( int i = 0; i < col; i++ ){
        printf("%d %s", i+1, data[i]);
    }
    printf("\n\n");


    printf("----------------------------- Assignment 1 -----------------------------------\n");
    char *data1[50];
    for( int i = 0; i < col; i++ ){
        data1[i] = assignment_1_output(data[i]);
        printf("%s", data1[i]);
    }
    printf("\n");
    printf("------------------------------------------------------------------------------\n");

    printf("----------------------------- Assignment 2 -----------------------------------\n");
    char *data2[50];
    for( int i = 0; i < col; i++ ){
        data2[i] = assignment_2_output(data1[i]);
        printf("%s\n", data2[i]);
    }
    printf("\n");
    printf("------------------------------------------------------------------------------\n");

    printf("----------------------------- Assignment 3 -----------------------------------\n");
    char *data3_1[50];
    for( int i = 0; i < col; i++ ){
        data3_1[i] = assignment_3_output_1(data2[i]);
        printf("%s\n", data3_1[i]);
    }
    printf("\n");

    char *data3_2[50];
    assignment_3_output_2( data3_1, col);
    display();
    printf("------------------------------------------------------------------------------\n");


    printf("----------------------------- Assignment 4 -----------------------------------\n");
    char *data4_1[50];
    for( int i = 0; i < col; i++ ){
        printf("%d ", i+1);
        for ( int j = 0; j < strlen(data3_1[i]); j++ ){
            c = data3_1[i][j];
            if( c != '[' && c != ']' ){
                printf("%c", c);
            }
        }
        printf("\n");
    }
    printf("\n");



    int state = 0;
    char token_value[100];
    int tvi = 0;

    int kw_found_count = 0;
    int sep_found_count = 0;
    int par_found_count = 0;

    int last_known_start_par_found = -1;
    int last_known_end_par_found = -1;

    int if_found_count = 0;
    int else_found_count = 0;

    for( int j = 0; j < col; j++ ){

        for( int i = 0; i < strlen(data3_1[j]); i++ ){
            c = data3_1[j][i];
            if( c == '[' && state == 0 ){
                state = 1;
            }else if( c == ']' ){
                token_value[tvi] = '\0';
                tvi = 0;

                //printf("%d, token:%s, par_count: %d\n", j+1, token_value, par_found_count);

                if( is_keyword_all_except_conditional(token_value) ){
                    //printf("kw: %s\n", token_value);
                    kw_found_count++;
                    if( kw_found_count > 1 ){
                        printf("Error at line %d, duplicate keywords found!\n", j+1);
                    }
                    sep_found_count = 0;
                }else if( is_sep(token_value) ){
                    //printf("kw: %s\n", token_value);
                    sep_found_count++;
                    if( sep_found_count > 1 ){
                        printf("Error at line %d, duplicate seperators found!\n", j+1);
                    }
                    kw_found_count = 0;
                }else if( is_par_custom(token_value, '{') ){
                    //printf("kw: %s\n", token_value);
                    par_found_count++;
                    last_known_start_par_found = j;
                    //printf("par_count:%d, \n", par_found_count, j+1);

                    kw_found_count = 0;
                    sep_found_count = 0;
                }else if( is_par_custom(token_value, '}') ){
                    //printf("kw: %s\n", token_value);
                    par_found_count--;
                    last_known_end_par_found = j;
                    if( par_found_count < 0 ){
                        printf("Error at line %d, unbalanced brackets found!\n", j+1);
                        par_found_count = 0;
                    }

                    kw_found_count = 0;
                    sep_found_count = 0;
                }else if( is_if(token_value) ){
                    //printf("kw: %s\n", token_value);
                    if_found_count++;
                    //printf("par_count:%d, \n", par_found_count, j+1);
                    kw_found_count = 0;
                    sep_found_count = 0;
                }else if( is_else(token_value) ){
                    //printf("kw: %s\n", token_value);
                    if_found_count--;
                    if( if_found_count < 0 ){
                        printf("Error at line %d, unbalanced else found!\n", j+1);
                        if_found_count = 0;
                    }
                    kw_found_count = 0;
                    sep_found_count = 0;
                }else{
                    kw_found_count = 0;
                    sep_found_count = 0;
                }

                state = 0;
                clearString(token_value);
                tvi = 0;
            }else if( state == 1 ){
                token_value[tvi] = c;
                tvi++;
            }
        }
    }

    if( last_known_end_par_found >= last_known_start_par_found && par_found_count > 0 ){
        printf("Error at line %d, unbalanced brackets found!\n", last_known_end_par_found+1);
    }

    printf("------------------------------------------------------------------------------\n");
    //printf("%s\n", assignment_1_output(data));
    //printf("%s\n", lineNubmer(data));

    return 0;
}














