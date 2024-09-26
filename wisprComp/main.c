// main.c
#include <stdlib.h>
#include <unistd.h>
#include <wayland-server-core.h>
#include <wlr/backend.h>
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_xdg_shell.h>
#include <wlr/util/log.h>
#include <xkbcommon/xkbcommon.h>
#include "xdg-shell-protocol.h"

struct compositor_state {
    struct wl_display *display;
    struct wlr_backend *backend;
    struct wlr_xdg_shell *xdg_shell;
    // ... other members ...
};

int main(int argc, char **argv) {
    wlr_log_init(WLR_DEBUG, NULL);

    struct compositor_state state = {0};

    state.display = wl_display_create();
    state.backend = wlr_backend_autocreate(state.display, NULL);

    if (!state.backend) {
        wlr_log(WLR_ERROR, "Failed to create backend");
        wl_display_destroy(state.display);
        return EXIT_FAILURE;
    }

    state.xdg_shell = wlr_xdg_shell_create(state.display);
    if (!state.xdg_shell) {
        wlr_log(WLR_ERROR, "Failed to create xdg_shell");
        wlr_backend_destroy(state.backend);
        wl_display_destroy(state.display);
        return EXIT_FAILURE;
    }

    // ... initialize outputs, inputs, listeners ...

    if (!wlr_backend_start(state.backend)) {
        wlr_log(WLR_ERROR, "Failed to start backend");
        wlr_xdg_shell_destroy(state.xdg_shell);
        wlr_backend_destroy(state.backend);
        wl_display_destroy(state.display);
        return EXIT_FAILURE;
    }

    // Launch the terminal emulator
    if (fork() == 0) {
        execlp("foot", "foot", NULL);  // Replace "foot" with your terminal emulator
    }

    wl_display_run(state.display);

    // Clean up
    wl_display_destroy_clients(state.display);
    wl_display_destroy(state.display);
    wlr_xdg_shell_destroy(state.xdg_shell);
    wlr_backend_destroy(state.backend);

    return EXIT_SUCCESS;
}
