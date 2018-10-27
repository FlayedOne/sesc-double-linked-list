#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LLIST struct LinkedList *
#define CELL struct cell *
#define ENTRY list->entry

struct cell {
	struct cell *previous, *following;
	int value;
};

struct LinkedList {
	CELL entry;
	size_t length;
};


int push_front(LLIST list, int val);
int pop_front(LLIST list);
int push_back(LLIST list, int val);
int pop_back(LLIST list);
int peek_front(const LLIST list);
int peek_back(const LLIST list);
void clear(LLIST list);
void dump(LLIST list, FILE *out);
void dump_reserved(LLIST list, FILE *out);

LLIST Constructor();
void Destructor(LLIST list);

int main() {
	LLIST list = Constructor();
	for (char str[32]; scanf("%s", str) != EOF; ) {
		if (!strcmp("push-front", str)) {
			int val;
			scanf("%d", &val);
			printf("%d\n", push_front(list, val) );
		} 
		else if (!strcmp("pop-front", str)) {
			if (list->length != 0) printf("%d\n", pop_front(list));
			else printf("empty\n");
		}
		else if (!strcmp("push-back", str)) {
			int val;
			scanf("%d", &val);
			printf("%d\n", push_back(list, val) );
		}
		else if (!strcmp("pop-back", str)) {
			if (list->length != 0) printf("%d\n", pop_back(list));
			else printf("empty\n");
		}
		else if (!strcmp("peek-front", str)) {
			if (list->length != 0) printf("%d\n", peek_front(list));
			else printf("empty\n");
		}
		else if (!strcmp("peek-back", str)) {
			if (list->length != 0) printf("%d\n", peek_back(list));
			else printf("empty\n");
		}
		else if (!strcmp("size", str)) {
			printf("%u\n", list->length);
		}
		else if (!strcmp("clear", str)) {
			clear(list);
			printf("empty\n");
		}
		else if (!strcmp("dump", str)) {
			dump(list, stdout);
		}
		else if (!strcmp("dump-reversed", str)) {
			dump_reserved(list, stdout);
		}
		else {
			printf("ERROR: UNKNOWN OPERATION %s\n", str);
		}
	}
	Destructor(list);
	return 0;
}


int push_front(LLIST list, int val) {
	CELL _cell = (CELL) malloc(sizeof(struct cell));
	_cell->value = val;
	_cell->following = ENTRY->following;
	_cell->previous = ENTRY;
	ENTRY->following->previous = _cell;
	ENTRY->following = _cell;
	list->length++;
	return val;
}


int pop_front(LLIST list) {
	CELL _cell = ENTRY->following;
	int val = _cell->value;
	ENTRY->following = _cell->following;
	_cell->following->previous = ENTRY;
	free(_cell);
	list->length--;
	return val;
}


int push_back(LLIST list, int val) {
	CELL _cell = (CELL)malloc(sizeof(struct cell));
	_cell->value = val;
	_cell->following = ENTRY;
	_cell->previous = ENTRY->previous;
	ENTRY->previous->following = _cell;
	ENTRY->previous = _cell;
	list->length++;
	return val;
}

int pop_back(LLIST list) {
	CELL _cell = ENTRY->previous;
	int val = _cell->value;
	ENTRY->previous = _cell->previous;
	_cell->previous->following = ENTRY;
	free(_cell);
	list->length--;
	return val;
}

int peek_front(const LLIST list) {
	return ENTRY->following->value;
}

int peek_back(const LLIST list) {
	return ENTRY->previous->value;
}


LLIST Constructor() {
	LLIST list = (LLIST)malloc(sizeof(struct LinkedList));
	ENTRY = (CELL) malloc(sizeof(struct cell));
	ENTRY->following = ENTRY;
	ENTRY->previous = ENTRY;
	list->length = 0;
	return list;
}

void Destructor(LLIST list) {
	clear(list);
	free(ENTRY);
	free(list);
}

void clear(LLIST list) {
	CELL i = ENTRY->following;
	CELL i_following = i->following;
	while(i != ENTRY ) {
		free(i);
		i = i_following;
		i_following = i->following;
	}
	ENTRY->following = ENTRY;
	ENTRY->previous = ENTRY;
	list->length = 0;
}

void dump(LLIST list, FILE * out) {
	if (list->length != 0) {
		for (CELL i = ENTRY->following; i != ENTRY; i = i->following)
			fprintf(out, "%d ", i->value);
		fprintf(out,"\n");
	}
	else fprintf(out,"empty\n");
}

void dump_reserved(LLIST list, FILE * out) {
	if (list->length != 0) {
		for (CELL i = ENTRY->previous; i != ENTRY; i = i->previous)
			fprintf(out, "%d ", i->value);
		fprintf(out, "\n");
	}
	else fprintf(out, "empty\n");
}
