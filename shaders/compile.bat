@echo off

call glslangValidator -V -o basic.frag.spv basic.frag.glsl
call glslangValidator -V -o basic.vert.spv basic.vert.glsl

pause