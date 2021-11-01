#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

/** Redirect stdout and stderr. Returns 0 upon success. **/
static int redirect_std_out_err(const char *log_name) {
  int failure = 1;

  /* Open log FILE stream. */
  FILE *const fp = fopen(log_name, "wb");
  if (fp != NULL) {

    /* Extract log FILE fd, and standard stdout/stderr ones. */
    const int log_fd = fileno(fp);
    const int stdout_fd = fileno(stdout);
    const int stderr_fd = fileno(stderr);
    if (log_fd != -1 && stdout_fd != -1 && stderr_fd != -1) {

      /* Clone log fd to standard stdout/stderr ones. */
      if (dup2(log_fd, stdout_fd) != -1 && dup2(log_fd, stderr_fd) != -1) {
        failure = 0;
      }
    }

    /* Close initial file. We do not need it, as we cloned it. */
    fclose(fp);
  }
  return failure;
}

int main(int argc, char **argv) {
  /* Redirect stdout and stderr to a single log file */
  if (argc != 2 || redirect_std_out_err(argv[1])) {
    return EXIT_FAILURE;
  }

  /* Print output to both streams */
  printf("Hey, stdout is redirected!\n");
  fprintf(stderr, "Hey, stderr is also redirected!\n");

  return EXIT_SUCCESS;
}