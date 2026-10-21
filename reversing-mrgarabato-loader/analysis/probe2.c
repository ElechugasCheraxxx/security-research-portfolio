// probe2.c - SMBIOS crudo + subclaves de HKLM\SOFTWARE\Wine + donde lee Wine el hardware
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

static void dump_reg(HKEY root, const char *path, int depth) {
    HKEY k;
    if (RegOpenKeyExA(root, path, 0, KEY_READ, &k) != ERROR_SUCCESS) return;
    printf("%*s[%s]\n", depth * 2, "", path);
    char nm[256], val[1024];
    for (DWORD i = 0;; i++) {
        DWORD ns = sizeof(nm), vs = sizeof(val), ty = 0;
        if (RegEnumValueA(k, i, nm, &ns, NULL, &ty, (LPBYTE)val, &vs) != ERROR_SUCCESS) break;
        val[sizeof(val) - 1] = 0;
        printf("%*s  %-38s = %s\n", depth * 2, "", nm,
               (ty == REG_SZ || ty == REG_EXPAND_SZ) ? val : "(bin)");
        ns = sizeof(nm);
    }
    char sub[256]; DWORD ss = sizeof(sub);
    for (DWORD i = 0;; i++) {
        ss = sizeof(sub);
        if (RegEnumKeyExA(k, i, sub, &ss, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) break;
        char full[512]; snprintf(full, sizeof(full), "%s\\%s", path, sub);
        dump_reg(root, full, depth + 1);
    }
    RegCloseKey(k);
}

int main(void) {
    printf("=== SMBIOS CRUDO (lo que ve el sample) ===\n");
    DWORD sz = GetSystemFirmwareTable('RSMB', 0, NULL, 0);
    printf("size=%u\n", sz);
    unsigned char *b = malloc(sz ? sz : 1);
    GetSystemFirmwareTable('RSMB', 0, b, sz);
    // volcar todas las cadenas imprimibles
    char line[512]; unsigned n = 0;
    printf("cadenas:\n  ");
    for (unsigned i = 0; i < sz; i++) {
        if (b[i] >= 0x20 && b[i] < 0x7f) {
            if (n < sizeof(line) - 1) line[n++] = b[i];
        } else {
            if (n >= 3) { line[n] = 0; printf("'%s' ", line); }
            n = 0;
        }
    }
    printf("\n\nhex primeros 256B:\n");
    for (unsigned i = 0; i < 256 && i < sz; i += 16) {
        printf("  %04x: ", i);
        for (int j = 0; j < 16 && i + j < sz; j++) printf("%02x ", b[i + j]);
        printf(" ");
        for (int j = 0; j < 16 && i + j < sz; j++) {
            unsigned char c = b[i + j];
            putchar(c >= 0x20 && c < 0x7f ? c : '.');
        }
        printf("\n");
    }

    printf("\n=== HKLM\\SOFTWARE\\Wine ===\n");
    dump_reg(HKEY_LOCAL_MACHINE, "SOFTWARE\\Wine", 0);

    printf("\n=== HKLM\\Hardware\\Description\\System (config hardware de Wine) ===\n");
    dump_reg(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System", 0);
    dump_reg(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", 0);

    printf("\n=== HKLM\\HARDWARE\\ACPI / enumeracion ===\n");
    dump_reg(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\CentralProcessor", 0);

    printf("\n=== Other ===\n");
    HKEY k; DWORD ty, vs;
    char v[256];
    const char *keys[] = { "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                           "SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName",
                           "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", NULL };
    for (int i = 0; keys[i]; i++)
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keys[i], 0, KEY_READ, &k) == ERROR_SUCCESS) {
            printf("  [%s]\n", keys[i]);
            for (DWORD j = 0; ; j++) {
                char nm[256]; DWORD ns = sizeof(nm);
                if (RegEnumValueA(k, j, nm, &ns, NULL, &ty, (LPBYTE)v, &vs) != ERROR_SUCCESS) break;
                v[sizeof(v)-1] = 0;
                printf("     %-32s = %s\n", nm, ty == REG_SZ ? v : "(bin)");
            }
            RegCloseKey(k);
        }
    return 0;
}