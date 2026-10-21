__int64 __fastcall DriverEntry(__int64 a1, __int64 a2, __int64 a3)
{
  unsigned __int64 v3; // rax

  v3 = qword_17108;
  if ( !qword_17108 || qword_17108 == 0x2B992DDFA232LL )
  {
    v3 = ((unsigned __int64)&qword_17108 ^ MEMORY[0xFFFFF78000000320]) & 0xFFFFFFFFFFFFLL;
    if ( !v3 )
      v3 = 0x2B992DDFA232LL;
    qword_17108 = v3;
  }
  qword_17100 = ~v3;
  return sub_5E2010((_QWORD *)a1);
}