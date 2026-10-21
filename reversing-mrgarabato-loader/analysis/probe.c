// probe.c - inspecciona lo que Wine expone, para saber que dispara el check anti-VM
#include <windows.h>
#include <stdio.h>
#include <setupapi.h>
#include <winhttp.h>
#include <stdlib.h>

static void scan(const char *buf, unsigned len, const char *what) {
    // imprime cadenas imprimibles >=4 chars
    char out[512]; unsigned n = 0; int found = 0;
    for (unsigned i = 0; i < len && n < sizeof(out) - 1; i++) {
        unsigned char c = (unsigned char)buf[i];
        if (c >= 0x20 && c < 0x7f) {
            if (n == 0) { found = 1; out[n++] = '['; }
            out[n++] = c;
        } else {
            if (n > 1) { out[n++] = ']'; out[n++] = ' '; }
            n = 0;
        }
    }
    if (n > 1) { out[n++] = ']'; }
    out[n] = 0;
    if (found) printf("  %s: %s\n", what, out);
}

int main(void) {
    printf("=== PROBE DE ENTORNO (lo que ve el sample) ===\n");

    // 1) SMBIOS
    DWORD sz = GetSystemFirmwareTable('RSMB', 0, NULL, 0);
    printf("\n[1] GetSystemFirmwareTable('RSMB') size=%u\n", sz);
    if (sz) {
        char *b = malloc(sz);
        GetSystemFirmwareTable('RSMB', 0, b, sz);
        // recorrer estructuras SMBIOS y volcar sus strings
        unsigned char *p = (unsigned char *)b;
        while (p + 4 < b + sz) {
            unsigned type = p[0], len = p[1];
            if (len < 4) break;
            // los strings empiezan tras los datos formateados
            unsigned q = 2;
            while (q + 2 < len) {
                unsigned off = p[q] | (p[q+1] << 8);
                if (off == 0) break;
                q += 2;
            }
            unsigned hdr_end = (q + 1 < len) ? (q + 1) : len;
            unsigned strbase = 2 + hdr_end;
            char *s = (char *)(p + strbase);
            unsigned maxlen = len - strbase;
            printf("  SMBIOS type=%-3u len=%-3u strings: ", type, len);
            unsigned k = 0;
            while (k < maxlen && s[k]) {
                printf("'%s' ", s + k);
                k += strlen(s + k) + 1;
            }
            printf("\n");
            p += len;
        }
        free(b);
    }

    // 2) Claves de registro sospechosa
    printf("\n[2] Registros de deteccion de VM\n");
    const char *keys[] = {
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion",
        "SOFTWARE\\Wine", "SOFTWARE\\Classes\\Applications", NULL };
    for (int i = 0; keys[i]; i++) {
        HKEY k;
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keys[i], 0, KEY_READ, &k) != ERROR_SUCCESS) continue;
        printf("  HKLM\\%s:\n", keys[i]);
        char nm[256]; DWORD sz2 = sizeof(nm); DWORD ti;
        for (DWORD j = 0; RegEnumValueA(k, j, nm, &sz2, NULL, &ti, NULL, NULL) == ERROR_SUCCESS; j++) {
            char val[512]; DWORD sz3 = sizeof(val); DWORD ty;
            RegEnumValueA(k, j, nm, &sz2, NULL, &ty, (LPBYTE)val, &sz3);
            val[sz3 < sizeof(val) ? sz3 : sizeof(val)-1] = 0;
            printf("     %-34s = %s\n", nm, (ty == REG_SZ) ? val : "(binario/otro)");
            sz2 = sizeof(nm);
        }
        RegCloseKey(k);
    }

    // 3) Enumeracion de dispositivos (lo que hace 234 veces el sample)
    printf("\n[3] SetupDiGetDeviceRegistryProperty SPDRP_HARDWAREID (muestra)\n");
    HDEVINFO di; SP_DEVINFO_DATA dd; DWORD i = 0; int shown = 0;
    di = SetupDiGetClassDevsA(NULL, NULL, NULL, DIGCF_ALLCLASSES);
    if (di != INVALID_HANDLE_VALUE) {
        dd.cbSize = sizeof(dd);
        while (SetupDiEnumDeviceInfo(di, i++, &dd)) {
            DWORD req = 0;
            SetupDiGetDeviceRegistryPropertyA(di, &dd, SPDRP_HARDWAREID, NULL, NULL, 0, &req);
            if (req) {
                char *b = malloc(req);
                if (SetupDiGetDeviceRegistryPropertyA(di, &dd, SPDRP_HARDWAREID, NULL, (PBYTE)b, req, NULL)) {
                    if (shown < 12) { scan(b, req, "  HWID"); shown++; }
                }
                free(b);
            }
        }
        SetupDiDestroyDeviceInfoList(di);
    }
    printf("  (dispositivos enumerados: %u)\n", i);

    // 4) Otros vectores
    printf("\n[4] Otros vectores\n");
    printf("  IsDebuggerPresent        = %d\n", IsDebuggerPresent());
    SYSTEM_INFO si; GetSystemInfo(&si);
    printf("  dwNumberOfProcessors    = %u\n", si.dwNumberOfProcessors);
    printf("  lpMinimumApplicationAddress = %p\n", si.lpMinimumApplicationAddress);
    MEMORYSTATUSEX ms; ms.dwLength = sizeof(ms);
    GlobalMemoryStatusEx(&ms);
    printf("  RAM total               = %llu MB\n", ms.ullTotalPhys / (1024*1024));
    printf("  GetModuleHandleA(ntdll)  = %p\n", GetModuleHandleA("ntdll.dll"));
    char cn[256]; DWORD cns = sizeof(cn);
    if (GetComputerNameA(cn, &cns)) printf("  GetComputerNameA         = %s\n", cn);
    char us[256]; DWORD uss = sizeof(us);
    if (GetUserNameA(us, &uss)) printf("  GetUserNameA            = %s\n", us);
    return 0;
}