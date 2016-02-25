<?php
/**
 * Configure for Udoo software
 * Nate Bosscher
 * 2016-Feb-25
 */

include "functions.php";
define("BASE_DIR", __dir__ . "/../");

$list = scanDirRecursive(BASE_DIR);

$headers = array_filter($list, function($v){
	return preg_match("/\.h$/", $v);
});
array_walk($headers, function(&$v){
	$v = realpath($v);
});

$cc = array_filter($list, function($v){
	return preg_match("/\.cpp$/", $v);
});
array_walk($cc, function(&$v){
	$v = str_replace(".cc", ".o", realpath($v));
});

$headerFiles = implode(" ", $headers);
$ccFiles = implode(" ", $cc);

if(file_exists(BASE_DIR . "/makefile"))
	unlink(BASE_DIR . "/makefile");

$f = fopen(BASE_DIR . "/makefile", "w");
fseek($f, 0);

fwrite($f, '#
# Autogenerated Makefile
# Created by scripts/configure.php
# Nate Bosscher
#

IDIR=/usr/xenomai/include

CC=gcc
CFLAGS=-I$(IDIR)

aDEPS='.$headerFiles.'
OBJ='.$ccFiles.'

ODIR=./bin
LDIBS=-std
INCDIR=./

DEPS=$(patsubst %,$(IDIR)/%,$(aDEPS))

%.o: %.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)

make: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
');

fclose($f); 