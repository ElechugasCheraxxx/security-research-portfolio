void __fastcall _security_check_cookie(__int64 a1)
{
  __int64 v1; // rcx

  if ( a1 != qword_17108 )
ReportFailure:
    sub_14270(a1);
  v1 = __ROL8__(a1, 16);
  if ( (_WORD)v1 )
  {
    a1 = __ROR8__(v1, 16);
    goto ReportFailure;
  }
}