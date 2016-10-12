#! /bin/sh

./bootstrap || exit 1
./configure --enable-maintainer-mode "$@"
