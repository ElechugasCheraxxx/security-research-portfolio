__int64 sub_11F30(char *Format, ...)
{
  CHAR Formata[512]; // [rsp+20h] [rbp-418h] BYREF
  char Dest[512]; // [rsp+220h] [rbp-218h] BYREF
  __int64 v4; // [rsp+420h] [rbp-18h]
  va_list Args; // [rsp+448h] [rbp+10h] BYREF

  va_start(Args, Format);
  v4 = qword_17108;
  if ( byte_17128 != 1 || !Format )
    return 3362422795LL;
  vsprintf(Dest, Format, Args);
  strcpy(Formata, "Kernel: ");
  strncpy(&Formata[8], Dest, 0x1F3uLL);
  DbgPrint(Formata);
  return 0LL;
}