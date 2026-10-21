/* pamtest.c -- comprueba si PAM autentica a un usuario con un servicio dado.
 * Uso: pamtest <servicio> <usuario> <password>
 * Implementa una funcion de conversacion que entrega la password.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <security/pam_appl.h>

static const char *g_pass = NULL;

static int my_conv(int num_msg, const struct pam_message **msg,
                   struct pam_response **resp, void *appdata)
{
    struct pam_response *r = NULL;
    int i;

    if (num_msg <= 0) return PAM_CONV_ERR;
    r = calloc(num_msg, sizeof(*r));
    if (!r) return PAM_BUF_ERR;

    for (i = 0; i < num_msg; i++) {
        switch (msg[i]->msg_style) {
        case PAM_PROMPT_ECHO_OFF:
        case PAM_PROMPT_ECHO_ON:
            r[i].resp = strdup(g_pass ? g_pass : "");
            break;
        case PAM_ERROR_MSG:
        case PAM_TEXT_INFO:
            fprintf(stderr, "  [PAM %s] %s\n",
                    msg[i]->msg_style == PAM_ERROR_MSG ? "ERROR" : "INFO",
                    msg[i]->msg ? msg[i]->msg : "");
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
    if (argc < 4) { fprintf(stderr, "uso: %s <servicio> <usuario> <pass>\n", argv[0]); return 2; }
    pam_handle_t *pam = NULL;
    struct pam_conv conv = { my_conv, NULL };
    int rc;

    g_pass = argv[3];

    rc = pam_start(argv[1], argv[2], &conv, &pam);
    printf("  pam_start      -> %2d (%s)\n", rc, pam_strerror(pam, rc));

    rc = pam_authenticate(pam, 0);
    printf("  pam_authenticate -> %2d (%s)\n", rc, pam_strerror(pam, rc));

    rc = pam_acct_mgmt(pam, 0);
    printf("  pam_acct_mgmt  -> %2d (%s)\n", rc, pam_strerror(pam, rc));

    pam_end(pam, 0);
    return 0;
}
