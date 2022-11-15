
#define DEL_STR "DEL_STR_1"
#define KEY_SIZE 4
#define VALUE_SIZE 10
#define CMD_LEN 10000

typedef struct {
	char key [KEY_SIZE];
	char value [VALUE_SIZE];
} kv_tuple;

int put_kv (const char * key, const char * value);
int get_kv (const char * key, char * value);
void get_all ();
