const std = @import("std");

pub fn build(b: *std.Build) void {
    const mode = b.standardReleaseOptions();

    const exe = b.addExecutable("libui_example", "src/main.c");
    exe.setTarget(b.standardTargetOptions(.{}));
    exe.setBuildMode(mode);

    // Include the libui header files from /include if needed
    exe.addIncludeDir("include");

    // Add the libui library from /lib if it's not installed system-wide
    //libAdd

    exe.install();
}
