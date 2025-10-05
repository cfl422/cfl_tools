#include "head.h"
ll DLLIMPORT rd() {
	char c;
	ll ret = 0, flag = 1;
	c = getchar();

	while ((c < '0' || c > '9') && c != '-') c = getchar();

	if (c == '-') flag = -1, c = getchar();

	while (c >= '0' && c <= '9') ret = ret * 10 + (c - '0'), c = getchar();

	return ret * flag;
}

char DLLIMPORT getc() {
	char c = getchar();

	while (c < 'A' || c > 'Z') c = getchar();

	return c;
}
