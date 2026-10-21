__int64 __fastcall sub_1400011F0(HANDLE hProcess, char *a2)
{
  bool v4; // zf
  __int64 result; // rax
  __int64 Buffer[7]; // [rsp+30h] [rbp-D0h] BYREF
  __int64 v7; // [rsp+68h] [rbp-98h]
  int v8; // [rsp+70h] [rbp-90h] BYREF
  __int64 v9; // [rsp+74h] [rbp-8Ch]
  __int64 v10; // [rsp+7Ch] [rbp-84h]
  __int64 v11; // [rsp+84h] [rbp-7Ch]
  __int64 v12; // [rsp+8Ch] [rbp-74h]
  __int64 v13; // [rsp+94h] [rbp-6Ch]
  int v14; // [rsp+9Ch] [rbp-64h]
  __int64 v15; // [rsp+A0h] [rbp-60h]
  __int64 v16; // [rsp+A8h] [rbp-58h]
  __int64 v17; // [rsp+B0h] [rbp-50h]
  __int64 v18; // [rsp+B8h] [rbp-48h]
  __int64 v19; // [rsp+C0h] [rbp-40h]
  __int64 v20; // [rsp+C8h] [rbp-38h]
  __int64 v21; // [rsp+D0h] [rbp-30h]
  __int64 v22; // [rsp+D8h] [rbp-28h]
  __int64 v23; // [rsp+E0h] [rbp-20h]
  __int64 v24; // [rsp+E8h] [rbp-18h]
  __int64 v25; // [rsp+F0h] [rbp-10h]
  __int64 v26; // [rsp+F8h] [rbp-8h]
  __int64 v27; // [rsp+100h] [rbp+0h]
  __int64 v28; // [rsp+108h] [rbp+8h]
  __int64 v29; // [rsp+110h] [rbp+10h]
  __int64 v30; // [rsp+118h] [rbp+18h]
  __int64 v31; // [rsp+120h] [rbp+20h]
  __int64 v32; // [rsp+128h] [rbp+28h]
  __int64 v33; // [rsp+130h] [rbp+30h]
  __int64 v34; // [rsp+138h] [rbp+38h]
  __int64 v35; // [rsp+140h] [rbp+40h]
  __int64 v36; // [rsp+148h] [rbp+48h]
  __int64 v37; // [rsp+150h] [rbp+50h]
  __int64 v38; // [rsp+158h] [rbp+58h]
  __int64 v39; // [rsp+160h] [rbp+60h]
  __int64 v40; // [rsp+168h] [rbp+68h]
  __int64 v41; // [rsp+170h] [rbp+70h]

  memset(Buffer, 0, sizeof(Buffer));
  v7 = 0LL;
  if ( !ReadProcessMemory(hProcess, a2, Buffer, 0x40uLL, 0LL) )
    return 0xFFFFFFFFLL;
  v8 = 0;
  v9 = 0LL;
  v10 = 0LL;
  v11 = 0LL;
  v12 = 0LL;
  v13 = 0LL;
  v14 = 0;
  v15 = 0LL;
  v16 = 0LL;
  v17 = 0LL;
  v18 = 0LL;
  v19 = 0LL;
  v20 = 0LL;
  v21 = 0LL;
  v22 = 0LL;
  v23 = 0LL;
  v24 = 0LL;
  v25 = 0LL;
  v26 = 0LL;
  v27 = 0LL;
  v28 = 0LL;
  v29 = 0LL;
  v30 = 0LL;
  v31 = 0LL;
  v32 = 0LL;
  v33 = 0LL;
  v34 = 0LL;
  v35 = 0LL;
  v36 = 0LL;
  v37 = 0LL;
  v38 = 0LL;
  v39 = 0LL;
  v40 = 0LL;
  v41 = 0LL;
  v4 = !ReadProcessMemory(hProcess, &a2[SHIDWORD(v7)], &v8, 0x108uLL, 0LL);
  result = WORD2(v20);
  if ( v4 )
    return 0xFFFFFFFFLL;
  return result;
}