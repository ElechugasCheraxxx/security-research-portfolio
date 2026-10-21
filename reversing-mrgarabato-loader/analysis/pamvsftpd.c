/* pamvsftpd.c -- replica EXACTA de la secuencia PAM que ejecuta vsftpd
 * (sysdeputil.c: vsf_sysdep_check_auth, rama PAM).
 *
 * Uso: pamvsftpd <servicio> <usuario> <pass> [rhost]
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <security/pam_appl.h>

static const char *g_pass = NULL;

static int my_conv(int n, const struct pam_message **msg,
                   struct pam_response **resp, void *appdata)
{
    struct pam_response *r = calloc(n, sizeof(*r));
    int i;
    if (!r) return PAM_BUF_ERR;
    for (i = 0; i < n; i++) {
        switch (msg[i]->msg_style) {
        case PAM_PROMPT_ECHO_OFF:
        case PAM_PROMPT_ECHO_ON:
            r[i].resp = strdup(g_pass ? g_pass : "");
            break;
        case PAM_ERROR_MSG:
            fprintf(stderr, "  [PAM ERROR] %s\n", msg[i]->msg ? msg[i]->msg : "");
            r[i].resp = strdup("");
            break;
        case PAM_TEXT_INFO:
            fprintf(stderr, "  [PAM INFO ] %s\n", msg[i]->msg ? msg[i]->msg : "");
            r[i].resp = strdup("");
            break;
        default:
            r[i].resp = strdup("");
            break;
        }
    }
    *resp = r;
    return PAM_SUCCESS;
}

int main(int argc, char **argv)
{
    pam_handle_t *pam = NULL;
    struct pam_conv conv = { my_conv, NULL };
    const char *rhost = (argc > 4) ? argv[4] : "127.0.0.1";
    const void *item = NULL;
    int rc;

    if (argc < 4) { fprintf(stderr, "uso: %s <servicio> <usuario> <pass> [rhost]\n", argv[0]); return 2; }
    g_pass = argv[3];

    rc = pam_start(argv[1], argv[2], &conv, &pam);
    printf("  pam_start            -> %2d (%s)\n", rc, pam_strerror(pam, rc));
    if (rc != PAM_SUCCESS) return 1;

    rc = pam_set_item(pam, PAM_RHOST, rhost);
    printf("  pam_set_item(RHOST)  -> %2d (%s)\n", rc, pam_strerror(pam, rc));

    rc = pam_set_item(pam, PAM_TTY, "ftp");
    printf("  pam_set_item(TTY)    -> %2d (%s)\n", rc, pam_strerror(pam, rc));

    rc = pam_set_item(pam, PAM_RUSER, argv[2]);
    printf("  pam_set_item(RUSER)  -> %2d (%s)\n", rc, pam_strerror(pam, rc));

    rc = pam_authenticate(pam, 0);
    printf("  pam_authenticate     -> %2d (%s)   <<< si != 0, FALLO AQUI\n",
           rc, pam_strerror(pam, rc));

    rc = pam_get_item(pam, PAM_USER, &item);
    printf("  pam_get_item(USER)   -> %2d (%s)  [user PAM='%s']\n",
           rc, pam_strerror(pam, rc), item ? (char *)item : "(null)");

    rc = pam_acct_mgmt(pam, 0);
    printf("  pam_acct_mgmt        -> %2d (%s)\n", rc, pam_strerror(pam, rc));

    rc = pam_setcred(pam, PAM_ESTABLISH_CRED);
    printf("  pam_setcred(ESTAB)   -> %2d (%s)   <<< si != 0, FALLO AQUI\n",
           rc, pam_strerror(pam, rc));

    rc = pam_open_session(pam, 0);
    printf("  pam_open_session     -> %2d (%s)   <<< si != 0, FALLO AQUI\n",
           rc, pam_strerror(pam, rc));

    pam_close_session(pam, 0);
    pam_setcred(pam, PAM_DELETE_CRED);
    pam_end(pam, 0);
    return 0;
}
