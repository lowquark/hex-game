#!/usr/bin/lua

local fun = { }

fun.objs = { }
fun.tiles = { }


local game = { }

function game.draw_events(cbs)
  cbs.move(0x222, 4, 5);
  cbs.move(0x223, 5, 5);
  cbs.explode(0x224, 2);
end

function game.draw_state(cbs)
  cbs.obj(0x222, 5, 5, 'GIG')
  cbs.obj(0x223, 6, 5, 'BIB')
  cbs.obj(0x224, 7, 8, 'smol')
end

