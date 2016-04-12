#pragma once

char * left(char *dst,char *src, int n);
void wcharTochar(const wchar_t *wchar, char *chr, int length);
void UTF_8ToUnicode(WCHAR* pOut,char *pText);
void UnicodeToUTF_8(char* pOut,WCHAR* pText);
void MySplit(char *src, const char *separator, char **dest, int *num);
int MyRand(int max);