#!/usr/bin/env sh

echo "Installing all dependencies...";

if [[ -d ./ressources/lib/glad ]]; then
	echo "glad is already installed";
else
	echo "installing glad...";
	if ! python3 -m glad --version &>/dev/null; then
		python3 -m pip install --quiet --user glad
	fi
	python3 -m glad --generator=c \
					--spec=gl \
					--profile=core \
					--api="gl=3.3" \
					--out-path="ressources/lib/glad"
	echo "glad is installed!"
fi

echo "All dependencies are installed"
