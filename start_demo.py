#!/usr/bin/env python3

import subprocess

cmds = [
    "echo Hello from tab 1; exec bash",
    "echo Hello from tab 2; exec bash",
    "echo Hello from tab 3; exec bash"
]

terminal_cmd = ["gnome-terminal"]
for i, cmd in enumerate(cmds):
    terminal_cmd.extend([
        "--tab",
        "--title=Tab{}".format(i + 1),
        "--", "bash", "-c", cmd
    ])

subprocess.run(terminal_cmd)
