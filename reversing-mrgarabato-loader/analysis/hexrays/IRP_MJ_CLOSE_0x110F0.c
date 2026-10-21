__int64 __fastcall sub_110F0(__int64 a1, __int64 a2)
{
  sub_11F30("Nal Windows DriverClose: Starting\n");
  *(_QWORD *)(a2 + 56) = 0LL;
  *(_DWORD *)(a2 + 48) = 0;
  IofCompleteRequest(a2, 0LL);
  sub_11EF0(&dword_17120);
  sub_11F30("Nal Windows DriverClose: Leaving\n");
  return 0LL;
}