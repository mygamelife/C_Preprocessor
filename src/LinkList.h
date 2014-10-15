#ifndef LinkList_H
#define LinkList_H

typedef struct LinkList LinkList;

struct LinkList {
	char *name;
	char *value;
  LinkList *next;
};

LinkList *linkListNew(char *macroName, char *macroValue);
#endif // LinkList_H
