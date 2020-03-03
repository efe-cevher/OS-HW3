
struct transaction{
	int day;
	int customer;
    char *items[128];
};

typedef struct transaction Transaction;