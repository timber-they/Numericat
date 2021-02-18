#!/bin/sh

Backend/Program.x $1 $2
cd Frontend/src
java de.numericat.Main "../../output"