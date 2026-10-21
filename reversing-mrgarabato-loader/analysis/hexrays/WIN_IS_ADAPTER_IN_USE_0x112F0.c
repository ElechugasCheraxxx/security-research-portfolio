char __fastcall sub_112F0(__int64 *a1)
{
  __int64 v1; // rdx
  unsigned __int64 v2; // rcx

  v1 = *a1;
  v2 = 0LL;
  while ( *(_QWORD *)&byte_5CFEC0[v2] != v1 || byte_5CFEC0[v2 + 264] != 1 )
  {
    v2 += 272LL;
    if ( v2 >= 0x11000 )
      return 0;
  }
  return 1;
}