#include <stdio.h> 
#include "cJSON.c"
#include "cJSON.h" 
  
int main() { 
    // open the file 
    FILE *fp = fopen("test.json", "r"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    } 
  
    // read the file contents into a string 
    char buffer[8192]; 
    fread(buffer, 1, sizeof(buffer), fp); 
    fclose(fp); 
  
    // parse the JSON data 
    cJSON *json = cJSON_Parse(buffer); 
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr(); 
        if (error_ptr != NULL) { 
            printf("Error: %s\n", error_ptr); 
        } 
        cJSON_Delete(json); 
        return 1; 
    } 
    cJSON *n = cJSON_DetachItemFromObject(json, "EVCar");
    //printf("%p", (void *) name);
    // access the JSON data 
    // stops working when [] are added
    
    cJSON *realName = cJSON_GetArrayItem(n, 10);
    cJSON *name = cJSON_GetObjectItemCaseSensitive(realName, "Type");
    //printf("%p", (void *) realName);
    //printf("%s", realName->valuestring);
    
    if (cJSON_IsString(name) && (name->valuestring != NULL)) { 
        printf("Name: %s\n", name->valuestring); 
    }
  
    // delete the JSON object 
    cJSON_Delete(json); 
    return 0; 
}