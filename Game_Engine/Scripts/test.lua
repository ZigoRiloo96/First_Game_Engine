f1() -- some function!
f2() -- some other function!

-- need class instance if you don't bind it with the function
print(m1(sc)) -- 24.5
-- does not need class instance: was bound to lua with one
print(m2()) -- 24.5

-- need class instance if you
-- don't bind it with the function
print(v1(sc)) -- 30
-- does not need class instance:
-- it was bound with one
print(v2()) -- 30

-- can set, still
-- requires instance
v1(sc, 212)
-- can set, does not need
-- class instance: was bound with one
v2(254)

print(v1(sc)) -- 212
print(v2()) -- 254