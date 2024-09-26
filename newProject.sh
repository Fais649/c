#!/usr/bin/env bash
read -rp "Enter Project Name: " name
i=0
while [ $i -lt 2 ]; do

	if echo "$name" | grep -qE '(\s|\.)'; then
		echo No, idiot... NO SPACES AND NO DOTS!
		read -rp "Enter Project Name: " name
		i=$((i + 1))
	else
		echo Great Choice!
		break
	fi

done

if [ $i -gt 2 ]; then
	echo Fuck off, dumbass...
	exit 0
fi

compiler=$(echo zig | fzf --height=10 --header "Choose Compiler" --layout=reverse)

if [[ -z $compiler ]]; then
	exit 0
fi

libraries=$(echo libui | fzf --height=10 --header "Choose Libraries" --layout=reverse)

mkdir "$name"
cp build_template.zig "$name"/build.zig
cd "$name" || exit

if [ "$compiler" = "zig" ]; then
	mkdir src lib include zig-out
	touch src/main.c README.md
	echo "$name" created! have fun!!
fi

if [ "$libraries" = "libui" ]; then
	git clone https://github.com/libui-ng/libui-ng.git lib/libui

	insertion='    exe.addLibPath("lib/libui");
    exe.linkLibC();
    exe.linkSystemLibrary("ui");'

	sed -i "/\/\/libAdd/ {
        r /dev/stdin
        d
    }" build.zig <<<"$insertion"
fi
