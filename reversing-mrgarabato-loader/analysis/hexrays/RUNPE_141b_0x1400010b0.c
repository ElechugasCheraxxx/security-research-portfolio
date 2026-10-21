__int64 __fastcall sub_1400010B0(HANDLE hProcess, char *a2)
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
  __int64 v14; // [rsp+9Ch] [rbp-64h]
  __int64 v15; // [rsp+A4h] [rbp-5Ch]
  __int64 v16; // [rsp+ACh] [rbp-54h]
  int v17; // [rsp+B4h] [rbp-4Ch]
  __int64 v18; // [rsp+B8h] [rbp-48h]
  __int64 v19; // [rsp+C0h] [rbp-40h]
  int v20; // [rsp+C8h] [rbp-38h]
  __int64 v21; // [rsp+CCh] [rbp-34h]
  __int64 v22; // [rsp+D4h] [rbp-2Ch]
  __int64 v23; // [rsp+DCh] [rbp-24h]
  __int64 v24; // [rsp+E4h] [rbp-1Ch]
  __int64 v25; // [rsp+ECh] [rbp-14h]
  __int64 v26; // [rsp+F4h] [rbp-Ch]
  __int64 v27; // [rsp+FCh] [rbp-4h]
  __int64 v28; // [rsp+104h] [rbp+4h]
  __int64 v29; // [rsp+10Ch] [rbp+Ch]
  __int64 v30; // [rsp+114h] [rbp+14h]
  __int64 v31; // [rsp+11Ch] [rbp+1Ch]
  __int64 v32; // [rsp+124h] [rbp+24h]
  __int64 v33; // [rsp+12Ch] [rbp+2Ch]
  __int64 v34; // [rsp+134h] [rbp+34h]
  __int64 v35; // [rsp+13Ch] [rbp+3Ch]
  __int64 v36; // [rsp+144h] [rbp+44h]
  __int64 v37; // [rsp+14Ch] [rbp+4Ch]
  __int64 v38; // [rsp+154h] [rbp+54h]
  __int64 v39; // [rsp+15Ch] [rbp+5Ch]
  int v40; // [rsp+164h] [rbp+64h]

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
  v14 = 0LL;
  v15 = 0LL;
  v16 = 0LL;
  v17 = 0;
  v18 = 0LL;
  v19 = 0LL;
  v20 = 0;
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
  v40 = 0;
  v4 = !ReadProcessMemory(hProcess, &a2[SHIDWORD(v7)], &v8, 0xF8uLL, 0LL);
  result = (unsigned __int16)v21;
  if ( v4 )
    return 0xFFFFFFFFLL;
  return result;
}